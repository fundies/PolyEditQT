#include "maincanvas.h"

MainCanvas::MainCanvas(MainWindow* parent) : Canvas(parent)
{
    // Store the MainWindow* for later use
    mParent = parent;

    // Intialize mouse position
    mousePos = Coordinate(0,0);

    // Enable mouse events
    setMouseTracking(true);
}

void MainCanvas::mouseMoveEvent(QMouseEvent * event)
{
    mousePos = event->pos();
}

void MainCanvas::mousePressEvent(QMouseEvent * event)
{
    if (event->button() == Qt::LeftButton)
        mParent->addCoord(mParent->getStatusCoord());
}

QSize MainCanvas::sizeHint() const
{
    return QSize(800, 480);
}
