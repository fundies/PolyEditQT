#include "imageloader.h"

#include <QHBoxLayout>
#include "imagebounds.h"
#include <iostream>

ImageLoader::ImageLoader(QWidget *parent) : GLWindow(parent)
{
    mCentralWidget = new QWidget(this);
    this->setCentralWidget(mCentralWidget);
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mCentralWidget->setLayout(mainLayout);

    ImageBounds* bounds = new ImageBounds(this);
    mainLayout->addWidget(bounds);

    mCanvas = new Canvas(this);
    mainLayout->addWidget(mCanvas);

    mGrid = new Grid(width(), height(), 1, 1, 0, 0);

    mSpnRows = 1;
    mSpnColumns = 1;
    mSpnX = 0;
    mSpnY = 0;

    connect(bounds->spnRows, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ImageLoader::setSpnRows);
    connect(bounds->spnColumns, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ImageLoader::setSpnColumns);
    connect(bounds->spnX, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ImageLoader::setSpnX);
    connect(bounds->spnY, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ImageLoader::setSpnY);

    QImage img = QImage("/home/greg/mario.png");
    spr = new Sprite(img);
}

void ImageLoader::render()
{
    std::function<void(void)> g = std::bind(&Grid::render, mGrid);
    mCanvas->draw(g, 0,0);

    std::function<void(void)> s = std::bind(&Sprite::render, spr);
    mCanvas->draw(s, 0,0);
}

void ImageLoader::canvasResized(int w, int h)
{
    mGrid->setSize(w, h, mSpnRows, mSpnColumns, mSpnX, mSpnY);
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
   mGrid->setSize(mCanvas->width(), mCanvas->height(), mSpnRows, mSpnColumns, mSpnX, mSpnY);
}
