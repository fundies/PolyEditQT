#include "mainwindow.h"
#include "menubar.h"
#include "toolbar.h"

#include <QMenuBar>
#include <QToolBar>
#include <QLayout>
#include <QSplitter>
#include <QStatusBar>
#include <QToolButton>
#include <QErrorMessage>
#include <QFileDialog>

#include "masktab.h"
#include "utility.h"
#include "maincanvas.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : GLWindow(parent)
{
    mTimer = new QTimer(this);
    subImg = 0;

    mViewGrid = true;
    mViewSprite = true;
    mXsep = 16;
    mYsep = 16;

    mCoord = Coordinate(0,0);
    mActions = new QActions(this);
    mGrid = new Grid(16, 16, width(), height());
    mCanvas = new MainCanvas(this);

    mCentralWidget = new QWidget(this);

    this->setCentralWidget(mCentralWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout;

    QSplitter *splitter = new QSplitter(this);

    MaskTab* tabs = new MaskTab(this, mCanvas);
    table = tabs->table();

    splitter->addWidget(tabs);
    splitter->addWidget(mCanvas);

    mMenuBar = new MenuBar(this);
    mToolBar = new ToolBar(this);

    setMenuBar(mMenuBar);
    addToolBar(mToolBar);

    mainLayout->addWidget(splitter);

    mainLayout->setMargin(0);
    mCentralWidget->setLayout(mainLayout);

    statusBar()->setStyleSheet("QStatusBar::item { border: 0px solid black }; ");

    statusBar()->addPermanentWidget(new QLabel("PolyEditQT 1.0", this, 0), 1);
    xCoord = new QLabel("X: ", this, 0);
    yCoord = new QLabel("Y: ", this, 0);
    statusBar()->addPermanentWidget(xCoord, 0);
    statusBar()->addPermanentWidget(yCoord, 0);

    connect(mActions->aOpen, &QAction::triggered,  this, &MainWindow::open);
    connect(mActions->aSprite, &QAction::triggered,  this, &MainWindow::editSprite);

    connect(mActions->aViewGrid, &QAction::toggled,  this, &MainWindow::viewGrid);
    connect(mActions->aViewSprite, &QAction::toggled,  this, &MainWindow::viewSprite);
    connect(mActions->aZoomIn, &QAction::triggered, this, &MainWindow::zoomIn);
    connect(mActions->aZoomOut, &QAction::triggered, this, &MainWindow::zoomOut);
    connect(mActions->aZoom100, &QAction::triggered, this, &MainWindow::zoom100);

    connect(mActions->aPlay, &QAction::triggered,  this, &MainWindow::play);
    connect(mTimer, &QTimer::timeout, this, &MainWindow::incrementSubimg);
    connect(mActions->aPause, &QAction::triggered,  this, &MainWindow::pause);
    connect(mActions->aStop, &QAction::triggered,  this, &MainWindow::stop);

    connect(mToolBar->gridX, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MainWindow::setXsep);
    connect(mToolBar->gridY, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &MainWindow::setYsep);
}

MainWindow::~MainWindow()
{
    delete mActions;
    delete mGrid;
    delete mCanvas;
    delete mCentralWidget;
}

QActions* MainWindow::actions()
{
    return mActions;
}

void MainWindow::render()
{

    if (!mSpr.isNull() && mViewSprite)
    {
        std::function<void()> s;
        s = [this] { mSpr->render(subImg); };
        mCanvas->draw(s, mCanvas->width()/2, mCanvas->height()/2);
    }

    /// TODO: Move this
    int xOff = fmod(((zoom*mGrid->getXoffset()) + mCanvas->width()/2),(zoom*mGrid->getXsep()));
    int yOff = fmod(((zoom*mGrid->getYoffset()) + mCanvas->height()/2),(zoom*mGrid->getYsep()));

    int x = xOff + RoundNum((double)mCanvas->mousePos.x()-xOff, (zoom*mGrid->getXsep()));
    int y = yOff + RoundNum((double)mCanvas->mousePos.y()-yOff, (zoom*mGrid->getYsep()));

    Coordinate coord = mapToGrid(Coordinate(x,y));

    if (mViewGrid)
    {
        std::function<void(void)> g = std::bind(&Grid::render, mGrid);
        mCanvas->draw(g, 0,0);
    }

    for (auto i : *table)
    {
        std::function<void()> f;

        if (i->getType() == PolyEdit::Polygon)
            f = [i] { i->render(); };
        else
            f = [i, coord] { i->render(coord); };

        mCanvas->draw(f, mCanvas->width()/2, mCanvas->height()/2);

    }

    setStatusCoord(mapToGrid(Coordinate(x,y)));
    std::function<void(void)> c = std::bind(drawCircle, Coordinate(x,y), 5, 30, false);
    mCanvas->draw(c, 0, 0);
}

void MainWindow::canvasResized(int w, int h)
{
    mGrid->setSize(0, 0, mXsep, mYsep, w, h, zoom);
}

const Coordinate MainWindow::mapToGrid(Coordinate c)
{
    int x = (c.x() - mCanvas->width()/2 - mGrid->getXoffset())/zoom;
    int y = (mCanvas->height()/2 + mGrid->getYoffset() - c.y())/zoom;

    return Coordinate(x,y);
}

const Coordinate MainWindow::mapToReal(Coordinate c)
{
    int x = mCanvas->width()/2 + (c.x() + mGrid->getXoffset())*zoom;
    int y = mCanvas->height()/2 + (mGrid->getYoffset() - c.y())*zoom;

    return Coordinate(x,y);
}
void MainWindow::setSpr(const QSharedPointer<Sprite> &spr)
{
    mSpr = spr;
}


void MainWindow::setStatusCoord(Coordinate c)
{
    xCoord->setText("X: " + QString::number(c.rx()));
    yCoord->setText("Y: " + QString::number(c.ry()));

    mCoord = c;
}

const Coordinate MainWindow::getStatusCoord() const
{
    return mCoord;
}

void MainWindow::addCoord(Coordinate c)
{
    currentMask->addCoord(c);
}

void MainWindow::setMask(Table* mask)
{
    currentMask = mask;
}

void MainWindow::open()
{
    QFileDialog *file = new QFileDialog(this);
    file->setOption(QFileDialog::DontUseNativeDialog, true);

    QStringList mimeTypeFilters;
    mimeTypeFilters
            << "All images (*.jpg; *.png; *.gif)"
            << "image/bmp"
            << "image/jpeg"
            << "image/png"
            << "application/octet-stream"; // will show "All files (*)"

    file->setMimeTypeFilters(mimeTypeFilters);

    QStringList fileNames;
    if (file->exec())
        fileNames = file->selectedFiles();

    QImage img;
    if (!fileNames.isEmpty())
        img = QImage(fileNames[0]);

    if (!img.isNull())
    {
        imgLoader = new ImageLoader(this, img);
        imgLoader->show();
    }
}

void MainWindow::play()
{
    mTimer->start(1000/60);
}

void MainWindow::pause()
{
    mTimer->stop();
    mToolBar->frame->setValue(subImg);
}

void MainWindow::stop()
{
    mTimer->stop();
    subImg = 0;
    mToolBar->frame->setValue(0);
}

void MainWindow::incrementSubimg()
{
    if (subImg < mSpr->count())
        subImg++;
    else
        subImg = 0;
}

void MainWindow::editSprite()
{
    imgLoader->show();
}

void MainWindow::viewGrid(bool value)
{
    mViewGrid = value;
}

void MainWindow::viewSprite(bool value)
{
    mViewSprite = value;
}

void MainWindow::updateGrid()
{
    mGrid->setSize(0, 0, mXsep, mYsep, mCanvas->width(), mCanvas->height(), zoom);
}

void MainWindow::setXsep(int value)
{
    mXsep = value;
    updateGrid();
}

void MainWindow::setYsep(int value)
{
    mYsep = value;
    updateGrid();
}

void MainWindow::zoomIn()
{
    std::cout << "wat" << std::endl;
   setZoom(2);
}

void MainWindow::zoomOut()
{
   setZoom(0.5);
}

void MainWindow::zoom100()
{
    setZoom(1);
}

void MainWindow::setZoom(double factor)
{
    if (compareDouble(factor,1))
    {
        zoom = 1;
        return;
    }

    double zoomLast = zoom;

    zoom *= factor;
    zoom = std::min(std::max(0.125, zoom), static_cast<double>(32));

    if (compareDouble(zoomLast,zoom))
        return;

    updateGrid();
    //updateMouse();
}
