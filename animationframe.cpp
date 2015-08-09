#include <QVBoxLayout>
#include <QSplitter>
#include <QFileDialog>
#include <QStatusBar>
#include <QMessageBox>

#include "spritemodel.h"
#include "animationframe.h"
#include "animationtoolbar.h"
#include "checkers.h"
#include "canvas.h"
#include "animationmenu.h"
#include "animationview.h"
#include "yesnowidget.h"
#include "mainwindow.h"
#include "qactions.h"

AnimationFrame::AnimationFrame(MainWindow *parent) : GLWindow(parent)
{
    mParent = parent;

    mCanvas = new Canvas(this);

    setWindowTitle("Animation Editor");

    mCentralWidget = new QWidget(this);
    setCentralWidget(mCentralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mCentralWidget->setLayout(mainLayout);

    QSplitter *splitter = new QSplitter(Qt::Vertical, this);

    mModel = new SpriteModel(this);

    splitter->addWidget(mCanvas);

    animator = new AnimationView(this);
    animator->setModel(mModel);
    splitter->addWidget(animator);

    mainLayout->addWidget(splitter);

    mSubmit = new YesNoWidget(this);
    mainLayout->addWidget(mSubmit);

    mToolBar = new AnimationToolBar(this);
    mMenuBar = new AnimationMenu(this);

    setMenuBar(mMenuBar);
    addToolBar(mToolBar);

    resize(800,600);

    QImage checkers = createCheckers();
    mCheckers = SpritePtr(new Sprite(checkers, width(), height()));


    statusBar()->setStyleSheet("QStatusBar::item { border: 0px solid black }; ");
    statusBar()->addPermanentWidget(new QLabel("Animator", this, 0), 1);
    mWidth = new QLabel("Width: 0px", this, 0);
    mHeight = new QLabel("Height: 0px", this, 0);
    mFrames = new QLabel("Frames: 0", this, 0);
    statusBar()->addPermanentWidget(mWidth, 0);
    statusBar()->addPermanentWidget(mHeight, 0);
    statusBar()->addPermanentWidget(mFrames, 0);

    mActions->aOpen->setText("Import");
    mActions->aSave->setText("Export");

    connect(mActions->aAddBlank, &QAction::triggered,  this, &AnimationFrame::insertImage);
    connect(mActions->aDeleteImg, &QAction::triggered,  this, &AnimationFrame::deleteImage);
    connect(mActions->aCut, &QAction::triggered,  this, &AnimationFrame::cut);
    connect(mActions->aCopy, &QAction::triggered,  this, &AnimationFrame::copy);
    connect(mActions->aPaste, &QAction::triggered,  this, &AnimationFrame::paste);
    connect(mActions->aOpen, &QAction::triggered,  this, &AnimationFrame::import);

    connect(mActions->aSave, &QAction::triggered,  this, &AnimationFrame::exportStrip);
    connect(mSubmit, &YesNoWidget::yes,  this, &AnimationFrame::submit);
    connect(mSubmit, &YesNoWidget::no,  this, &AnimationFrame::close);

    connect(mToolBar->speed, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged), this, &GLWindow::setSpeed);
    connect(mToolBar->frame, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &AnimationFrame::setFrame);

    mSpr = Q_NULLPTR;
}

void AnimationFrame::setSprite(const SpritePtr &spr)
{
    int width = (spr->isNull())? 0 : spr->mSubimg.first().img.width();
    int height = (spr->isNull())? 0 : spr->mSubimg.first().img.height();

    mWidth->setText("Width: " + QString::number(width) + "px");
    mHeight->setText("Height: " + QString::number(height) + "px");
    mFrames->setText("Frames: " + QString::number(spr->count()));
    mModel->setSprite(new Sprite(*spr));
    mToolBar->frame->setMaximum(std::max(0, static_cast<int>(mModel->getSprite()->count())));
}

void AnimationFrame::incrementSubimg()
{
    if (subImg < mModel->getSprite()->count()-1)
        subImg++;
    else
        subImg = 0;
}

void AnimationFrame::render()
{
    GLWindow::render();

    if (mModel->getSprite() != Q_NULLPTR && !mModel->getSprite()->isNull())
    {
        std::function<void()> s;
        s = [this] { mModel->getSprite()->render(subImg); };
        mCanvas->draw(s, mCanvas->width()/2, mCanvas->height()/2);
    }
}

void AnimationFrame::insertImage()
{
    int pos = animator->getCursor();

    if (pos == -1 && mModel->getSprite() != Q_NULLPTR)
        pos = mModel->getSprite()->count();

    mModel->insertRows(pos, 1, QModelIndex());

    mFrames->setText("Frames: " + QString::number(mModel->getSprite()->count()));
    mToolBar->frame->setMaximum(std::max(0, static_cast<int>(mModel->getSprite()->count())));
}

void AnimationFrame::deleteImage()
{
    QModelIndexList list = animator->getSelection();

    while(!list.isEmpty())
    {
        int row = list.first().row();
        mModel->removeRows(row, 1, QModelIndex());
        list = animator->getSelection();
    }

    mFrames->setText("Frames: " + QString::number(mModel->getSprite()->count()));
    mToolBar->frame->setMaximum(std::max(0, static_cast<int>(mModel->getSprite()->count())));
}

void AnimationFrame::cut()
{
    mClipboard->setMimeData(mModel->mimeData(animator->getSelection()));
    deleteImage();
}

void AnimationFrame::copy()
{
    mClipboard->setMimeData(mModel->mimeData(animator->getSelection()));
}

void AnimationFrame::paste()
{
    mModel->dropMimeData(mClipboard->mimeData(), Qt::CopyAction, animator->getCursor(), 0,  QModelIndex());
    mFrames->setText("Frames: " + QString::number(mModel->getSprite()->count()));
}

void AnimationFrame::setZoom(double factor)
{
    GLWindow::setZoom(factor);

    if (mModel->getSprite() != Q_NULLPTR)
        mModel->getSprite()->scale(zoom);
}

void AnimationFrame::exportStrip()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                       "untitled.png",
                       tr("Images (*.png *.bmp *.jpg)"),  0, QFileDialog::DontUseNativeDialog);

    if (!fileName.isEmpty())
        mModel->getSprite()->exportStrip(fileName);
}

void AnimationFrame::submit()
{
    mParent->setSprite(mModel->getSprite());
    close();
}

void AnimationFrame::cancel()
{
    delete mSpr;
    close();
}

void AnimationFrame::import()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                       tr("Open Image"), QString(), tr("Image Files (*.png *.jpg *.bmp"), 0, QFileDialog::DontUseNativeDialog);
    QImage img = QImage(fileName);

    if (!img.isNull())
    {
        if(mModel->getCurrentSize() != img.size() && !mModel->getSprite()->isNull())
        {
            QString error = QString("Image dimensions must match\n") + "Source: " + QString::number(img.size().rwidth()) + "x" + QString::number(img.size().rheight()) +"\n" + "Target: " + QString::number(mModel->getCurrentSize().rwidth()) + "x" + QString::number(mModel->getCurrentSize().rheight());

            QMessageBox::critical(this, tr("Error"),
                                  error,
                                  QMessageBox::Ok);
            return;
        }

        int pos = animator->getCursor();

        if (pos == -1)
            pos = mModel->getSprite()->count();

        insertImage();
        QModelIndex idx = mModel->index(pos, 0, QModelIndex());
        mModel->setData(idx, img,  Qt::DecorationRole);
    }
}

void AnimationFrame::pause()
{
    GLWindow::pause();
    mToolBar->frame->setValue(subImg);
}

void AnimationFrame::stop()
{
    GLWindow::stop();
    mToolBar->frame->setValue(0);
}

void AnimationFrame::setFrame(int frame)
{
    subImg = frame;
}
