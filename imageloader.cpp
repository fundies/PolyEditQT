#include <QHBoxLayout>
#include <iostream>

#include "imageloader.h"
#include "imagebounds.h"
#include "checkers.h"

ImageLoader::ImageLoader(QWidget *parent) : GLWindow(parent)
{
    mCentralWidget = new QWidget(this);
    this->setCentralWidget(mCentralWidget);
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setMargin(0);
    mCentralWidget->setLayout(mainLayout);

    ImageBounds* bounds = new ImageBounds(this);
    mainLayout->addWidget(bounds);

    mCanvas = new Canvas(this);
    mainLayout->addWidget(mCanvas);

    mSpnRows = 1;
    mSpnColumns = 1;
    mSpnX = 0;
    mSpnY = 0;

    connect(bounds->spnRows, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ImageLoader::setSpnRows);
    connect(bounds->spnColumns, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ImageLoader::setSpnColumns);
    connect(bounds->spnXsep, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ImageLoader::setSpnX);
    connect(bounds->spnYsep, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ImageLoader::setSpnY);

    QImage checkers = createCheckers();
    mCheckers = new Sprite(checkers, width(), height());

    QImage img = QImage("/home/greg/mario.png");
    mSpr = new Sprite(img);

    mGrid = new Grid(mSpr->width(), mSpr->height(), 1, 1, 0, 0);
}

void ImageLoader::render()
{
    std::function<void(void)> c = std::bind(&Sprite::render, mCheckers);
    mCanvas->draw(c, mCanvas->width()/2, mCanvas->height()/2);

    std::function<void(void)> s = std::bind(&Sprite::render, mSpr);
    mCanvas->draw(s, mCanvas->width()/2, mCanvas->height()/2);

    std::function<void(void)> g = std::bind(&Grid::render, mGrid);
    mCanvas->draw(g, mCanvas->width()/2 - mSpr->hotspot().rx(), mCanvas->height()/2 - mSpr->hotspot().ry());
}

void ImageLoader::canvasResized(int w, int h)
{
    mCheckers->setSize(w,h);
    //mGrid->setSize(w, h, mSpnRows, mSpnColumns, mSpnX, mSpnY);
}

void ImageLoader::setSpnRows(int i)
{
    mSpnRows = i;
    updateGrid();
}

void ImageLoader::setSpnColumns(int i)
{
    mSpnColumns = i;
    updateGrid();
}

void ImageLoader::setSpnX(int i)
{
    mSpnX = i;
    updateGrid();
}

void ImageLoader::setSpnY(int i)
{
    mSpnY = i;
    updateGrid();
}

void ImageLoader::updateGrid()
{
   mGrid->setSize(mSpr->width(), mSpr->height(), mSpnRows, mSpnColumns, mSpnX, mSpnY);
}
