#ifndef CANVAS_H
#define CANVAS_H

#include "mainwindow.h"
#include "coordinate.h"

#include <QGLWidget>
#include <functional>

/**
 * @brief The Canvas class
 */
class Canvas : public QGLWidget
{
public:

    /**
     * @brief Canvas Canvas used for drawing
     * @param parent parent
     */
    explicit Canvas(MainWindow *parent = 0);
    ~Canvas();

    /**
     * @brief draw passes opengl code to be executed
     * @param f draw function
     * @param x x offset
     * @param y y offset
     */
    void draw(const std::function<void(void)> &f, int x, int y);

    /**
     * @brief mousePos the mouse position relative to the canvas
     */
    Coordinate mousePos;

protected:

    /**
     * @brief initializeGL Intialize OpenGL
     */
    void initializeGL();

    /**
     * @brief paintGL Paint the canvas
     */
    void paintGL();

    /**
     * @brief resizeGL Canvas resized event
     * @param width new width
     * @param height new height
     */
    void resizeGL(int width, int height);

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

    /**
     * @brief minimumSizeHint Returns the minimum size allowed
     * @return minimum size
     */
    QSize minimumSizeHint() const;

    /**
     * @brief sizeHint Returns the suggested size
     * @return suggested size
     */
    QSize sizeHint() const;

private:

    MainWindow *mParent;
};

#endif // CANVAS_H
