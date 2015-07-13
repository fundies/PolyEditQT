#include "canvas.h"
#include <GL/glu.h>

#include <QMouseEvent>

Canvas::Canvas(MainWindow *parent)
    : QGLWidget(QGLFormat(), parent)
{
    // Store the MainWindow* for later use
    mParent = parent;

    // Intialize mouse position
    mousePos = Coordinate(0,0);

    // Enable mouse events
    setMouseTracking(true);
}

Canvas::~Canvas()
{
    // nothing to do here
}

QSize Canvas::minimumSizeHint() const
{
    return QSize(50, 50);
}

QSize Canvas::sizeHint() const
{
    return QSize(800, 500);
}

void Canvas::initializeGL()
{
    // Clear the canvas
    qglClearColor(Qt::black);
}

void Canvas::paintGL()
{
    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_DEPTH_TEST);

    // Create a viewport because screw opengl's -1 to 1 system
    glViewport(0, 0, width(), height());
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D(0, width(), height(), 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // All drawing should be called from MainWindow->render()
    mParent->render();
}

void Canvas::resizeGL(int width, int height)
{
    /*
     * Inform the MainWindow* a resize has occured
     * so that the grid can be resized inorder
     * to compensate
    */
    mParent->canvasResized(width, height);

    // We need to repaint on resize
    paintGL();
}

void Canvas::draw(const std::function<void(void)> &f, int x, int y)
{
    // Draw f() at (x,y)
    glLoadIdentity();
    glTranslatef(x, y, 0);
    f();
    update();
}

void Canvas::mouseMoveEvent(QMouseEvent * event)
{
    mousePos = event->pos();
}

void Canvas::mousePressEvent(QMouseEvent * event)
{
    mParent->addCoord(mParent->getStatusCoord());
}
