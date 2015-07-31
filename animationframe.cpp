#include <QListView>
#include <QVBoxLayout>
#include <QSplitter>

#include "spritemodel.h"
#include "animationframe.h"
#include "animationview.h"
#include "animationtoolbar.h"
#include "checkers.h"
#include "canvas.h"

#include <iostream>

AnimationFrame::AnimationFrame(MainWindow *parent) : GLWindow(parent)
{
    mCanvas = new Canvas(this);

    setWindowTitle("Animation Editor");

    /// Todo: move this
    mCentralWidget = new QWidget(this);
    setCentralWidget(mCentralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mCentralWidget->setLayout(mainLayout);

    QSplitter *splitter = new QSplitter(Qt::Vertical, this);

    mModel = new SpriteModel();

    splitter->addWidget(mCanvas);

    AnimationView *animator = new AnimationView(this);
    animator->setModel(mModel);
    splitter->addWidget(animator);

    mainLayout->addWidget(splitter);

    mToolBar = new AnimationToolBar(this);

    //setMenuBar(mMenuBar);
    addToolBar(mToolBar);

    //mCheckers = new Sprite(checkers, 10, 10);
    resize(800,600);

    QImage checkers = createCheckers();
    mCheckers = SpritePtr(new Sprite(checkers, width(), height()));
}

void AnimationFrame::setContents(const QSharedPointer<Sprite> &spr)
{
    mSpr = spr;
    mModel->setSpr(spr);
    mCanvas->resize(0,0);
}

void AnimationFrame::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);

    mModel->submit();
    //mSpr = mModel->getSpr();
    close();
}

void AnimationFrame::incrementSubimg()
{
    if (subImg < mModel->getSpr()->count()-1)
        subImg++;
    else
        subImg = 0;
}

void AnimationFrame::render()
{
    GLWindow::render();

    if (mSpr != Q_NULLPTR)
    {
        std::function<void()> s;
        s = [this] { mModel->getSpr()->render(this->subImg); };
        mCanvas->draw(s, mCanvas->width()/2, mCanvas->height()/2);
    }
}
