#ifndef CANVAS_H
#define CANVAS_H

#include "coordinate.h"

#include <QOpenGLWidget>
#include <functional>

#include "glwindow.h"

class GLWindow;

/**
 * @brief The Canvas class
 */
class Canvas : public QOpenGLWidget
{
public:

    /**
     * @brief Canvas Canvas used for drawing
     * @param parent parent
     */
    explicit Canvas(GLWindow *parent = 0);
    ~Canvas();

    /**
     * @brief draw passes opengl code to be executed
     * @param f draw function
     * @param x x offset
     * @param y y offset
     */
    virtual void draw(const std::function<void(void)> &f, int x, int y);

protected:

    /**
     * @brief initializeGL Intialize OpenGL
     */
    virtual void initializeGL();

    /**
     * @brief paintGL Paint the canvas
     */
    virtual void paintGL();

    /**
     * @brief resizeGL Canvas resized event
     * @param width new width
     * @param height new height
     */
    virtual void resizeGL(int width, int height);

    /**
     * @brief minimumSizeHint Returns the minimum size allowed
     * @return minimum size
     */
    virtual QSize minimumSizeHint() const;

    /**
     * @brief sizeHint Returns the suggested size
     * @return suggested size
     */
    virtual QSize sizeHint() const;

private:

    GLWindow *mParent;
};

#endif // CANVAS_H
