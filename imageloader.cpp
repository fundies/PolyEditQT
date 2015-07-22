#include <QHBoxLayout>
#include <QScrollArea>
#include <iostream>

#include "imageloader.h"
#include "imagebounds.h"
#include "checkers.h"

ImageLoader::ImageLoader(MainWindow *parent, QImage &image) : GLWindow(parent)
{

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


    mCanvas = new Canvas(this);
    mCanvas->setMinimumSize(image.width(), image.height());

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

    connect(bounds->spnRows, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ImageLoader::setSpnRows);
    connect(bounds->spnColumns, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ImageLoader::setSpnColumns);
    connect(bounds->spnXsep, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ImageLoader::setSpnX);
    connect(bounds->spnYsep, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &ImageLoader::setSpnY);

    connect(bounds->btnAlpha, &QPushButton::pressed, this, &ImageLoader::setColor);
    connect(colorDialog, &QColorDialog::colorSelected, this, &ImageLoader::setAlpha);

    connect(bounds->btnImport, &QPushButton::pressed, this, &ImageLoader::import);

    QImage checkers = createCheckers();
    mCheckers = new Sprite(checkers, width(), height());

    mSpr = QSharedPointer<Sprite>(new Sprite(image));
    mGrid = new Grid(mSpr->width(), mSpr->height(), 1, 1, 0, 0);
    mGrid->setAlwaysVisible(true);
}

void ImageLoader::import()
{
    mSpr->genSubimg(mSpnRows, mSpnColumns, mSpnX, mSpnY);
    mParent->setSpr(mSpr);
    hide();
}

void ImageLoader::render()
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

void ImageLoader::canvasResized(int w, int h)
{
    mCheckers->setSize(w,h);
    //mGrid->setSize(w, h, mSpnRows, mSpnColumns, mSpnX, mSpnY);
}

void ImageLoader::setColor()
{
    mSpr->setOrigTexture(true);
    colorDialog->open();
}

void ImageLoader::setAlpha(const QColor &color)
{
mSpr->setAlpha(color);
    //std::cout << color.name().toStdString() << std::endl;
    //bounds->btnAlpha->setStyleSheet("QPushButton {background-color: " + color.name() + ";}");
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
