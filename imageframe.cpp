#include <QHBoxLayout>
#include <QScrollArea>

#include "imageframe.h"
#include "imagebounds.h"
#include "checkers.h"
#include "mainwindow.h"
#include "canvas.h"
#include "grid.h"

ImageFrame::ImageFrame(MainWindow *parent, QImage &image) : GLWindow(parent)
{
    mCanvas = new Canvas(this);
    mCanvas->setMinimumSize(image.width(), image.height());

    mParent = parent;

    mCentralWidget = new QWidget(this);
    setCentralWidget(mCentralWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mCentralWidget->setLayout(mainLayout);


    colorDialog = new QColorDialog(this);
    colorDialog->setOption(QColorDialog::DontUseNativeDialog, true);

    bounds = new ImageBounds(this);
    mainLayout->addWidget(bounds);
    bounds->btnAlpha->setFlat(true);

    scrollArea = new QScrollArea;
    scrollArea->setWidget(mCanvas);
    scrollArea->setWidgetResizable(true);
    mainLayout->addWidget(scrollArea);

    // Qt resizes widgets to fit window instead of fitting >:|
    resize(bounds->width() + image.width() + 200, image.height() + 200);

    mSpnRows = 1;
    mSpnColumns = 1;
    mSpnX = 0;
    mSpnY = 0;

    connect(bounds->spnRows, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ImageFrame::setSpnRows);
    connect(bounds->spnColumns, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ImageFrame::setSpnColumns);
    connect(bounds->spnXsep, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ImageFrame::setSpnX);
    connect(bounds->spnYsep, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ImageFrame::setSpnY);

    connect(bounds->btnAlpha, &QPushButton::pressed, this, &ImageFrame::setColor);
    connect(colorDialog, &QColorDialog::colorSelected, this, &ImageFrame::setAlpha);

    connect(bounds->btnImport, &QPushButton::pressed, this, &ImageFrame::import);

    QImage checkers = createCheckers();
    mCheckers = SpritePtr(new Sprite(checkers, width(), height()));

    mSpr = SpritePtr(new Sprite(image));
    mGrid = QSharedPointer<Grid>(new Grid(mSpr->width(), mSpr->height(), 1, 1, 0, 0));
    mGrid->setAlwaysVisible(true);
}

void ImageFrame::import()
{
    mSpr->genSubimg(mSpnRows, mSpnColumns, mSpnX, mSpnY);
    mParent->setSprite(mSpr);
    close();
}

void ImageFrame::render()
{
    std::function<void()> c;
    c = [this] { mCheckers->render(); };
    mCanvas->draw(c, mCanvas->width()/2, mCanvas->height()/2);

    std::function<void()> s;
    s = [this] { mSpr->render(); };
    mCanvas->draw(s, mCanvas->width()/2, mCanvas->height()/2);

    std::function<void(void)> g = std::bind(&Grid::render, mGrid);
    mCanvas->draw(g, mCanvas->width()/2 - mSpr->hotspot().rx(), mCanvas->height()/2 - mSpr->hotspot().ry());
}

void ImageFrame::canvasResized(int w, int h)
{
    mCheckers->setSize(w,h);
    //mGrid->setSize(w, h, mSpnRows, mSpnColumns, mSpnX, mSpnY);
}

void ImageFrame::setColor()
{
    mSpr->setOrigTexture(true);
    colorDialog->open();
}

void ImageFrame::setAlpha(const QColor &color)
{
    mSpr->setAlpha(color);
}

void ImageFrame::setSpnRows(int i)
{
    mSpnRows = i;
    updateGrid();
}

void ImageFrame::setSpnColumns(int i)
{
    mSpnColumns = i;
    updateGrid();
}

void ImageFrame::setSpnX(int i)
{
    mSpnX = i;
    updateGrid();
}

void ImageFrame::setSpnY(int i)
{
    mSpnY = i;
    updateGrid();
}

void ImageFrame::updateGrid()
{
    mGrid->setSize(mSpr->width(), mSpr->height(), mSpnRows, mSpnColumns, mSpnX, mSpnY);
}

void ImageFrame::setSprite(const SpritePtr &spr)
{
    mSpr = spr;
}
