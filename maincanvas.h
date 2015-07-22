#ifndef MAINCANVAS_H
#define MAINCANVAS_H

#include <QMouseEvent>

#include "canvas.h"
#include "mainwindow.h"

class MainCanvas : public Canvas
{
public:
    MainCanvas(MainWindow *parent);

    /**
     * @brief mousePos the mouse position relative to the canvas
     */
    Coordinate mousePos;

    QSize sizeHint() const;

private:

    /**
     * @brief mouseMoveEvent Mouse moved event
     * @param event event
     */
    void mouseMoveEvent(QMouseEvent * event);

    /**
     * @brief mousePressEvent Mouse Pressed event
     * @param event event
     */
    void mousePressEvent(QMouseEvent * event);

    MainWindow* mParent;
};

#endif // MAINCANVAS_H
