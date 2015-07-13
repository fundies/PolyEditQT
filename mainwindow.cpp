#include "mainwindow.h"
#include "menubar.h"
#include "toolbar.h"

#include <QMenuBar>
#include <QToolBar>
#include <QLayout>
#include <QSplitter>
#include <QStatusBar>
#include <QToolButton>

#include "masktab.h"
#include "utility.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mCoord = Coordinate(0,0);
    mActions = new QActions(this);
    mGrid = new Grid(16, 16, width(), height());
    mCanvas = new Canvas(this);

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
    /// TODO: Move this
    int xOff = fmod(((zoom*mGrid->getXoffset()) + mCanvas->width()/2),(zoom*mGrid->getXsep()));
    int yOff = fmod(((zoom*mGrid->getYoffset()) + mCanvas->height()/2),(zoom*mGrid->getYsep()));

    int x = xOff + RoundNum((double)mCanvas->mousePos.x()-xOff, (zoom*mGrid->getXsep()));
    int y = yOff + RoundNum((double)mCanvas->mousePos.y()-yOff, (zoom*mGrid->getYsep()));

    Coordinate coord = mapToGrid(Coordinate(x,y));

    std::function<void(void)> g = std::bind(&Grid::render, mGrid);
    mCanvas->draw(g, 0,0);

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
    mGrid->setSize(0, 0, 16, 16, w, h, 1);
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
