#include "glwindow.h"
#include "checkers.h"
#include "canvas.h"
#include "utility.h"
#include <QDebug>

#include <functional>
#include <iostream>

#include "mainwindow.h"

#include <QOpenGLContext>

GLWindow::GLWindow(MainWindow *parent) : QMainWindow(parent)
{
    zoom = 1;
    zoomLast = 1;

    mTimer = new QTimer(this);
    subImg = 0;

    mActions = QSharedPointer<QActions>(new QActions(this));

    connect(mActions->aZoomIn, &QAction::triggered, this, &GLWindow::zoomIn);
    connect(mActions->aZoomOut, &QAction::triggered, this, &GLWindow::zoomOut);
    connect(mActions->aZoom100, &QAction::triggered, this, &GLWindow::zoom100);

    connect(mActions->aPlay, &QAction::triggered,  this, &GLWindow::play);
    connect(mTimer, &QTimer::timeout, this, &GLWindow::incrementSubimg);
    connect(mActions->aPause, &QAction::triggered,  this, &GLWindow::pause);
    connect(mActions->aStop, &QAction::triggered,  this, &GLWindow::stop);
}

GLWindow::~GLWindow()
{
    mCheckers.clear();
}

void GLWindow::render()
{
    std::function<void()> c;
    c = [this] { mCheckers->render(); };
    mCanvas->draw(c, mCanvas->width()/2, mCanvas->height()/2);
}

void GLWindow::open()
{
}

void GLWindow::canvasResized(int w, int h)
{
    mCheckers->setSize(w,h);
}

void GLWindow::play()
{
    mTimer->start(1000/60);
}

void GLWindow::pause()
{
    mTimer->stop();
    //mToolBar->frame->setValue(subImg);
}

void GLWindow::stop()
{
    mTimer->stop();
    subImg = 0;
    //mToolBar->frame->setValue(0);
}

void GLWindow::incrementSubimg()
{
    if (subImg < mSpr->count()-1)
        subImg++;
    else
        subImg = 0;
}

void GLWindow::zoomIn()
{
   setZoom(2);
}

void GLWindow::zoomOut()
{
   setZoom(0.5);
}

void GLWindow::zoom100()
{
    setZoom(1);
}

void GLWindow::setZoom(double factor)
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

    if (mSpr != Q_NULLPTR)
        mSpr->scale(zoom);
}

QSharedPointer<QActions> GLWindow::actions() const
{
    return mActions;
}

bool GLWindow::spriteExists() const
{
   return (mSpr != Q_NULLPTR);
}
