#include <QMouseEvent>

#include "glwindow.h"
#include "mainwindow.h"
#include "imageframe.h"
#include "animationframe.h"
#include "canvas.h"


Canvas::Canvas(AnimationFrame *parent)
    : QOpenGLWidget(parent)
{
    // we don't need the mainW here
    mMainW = Q_NULLPTR;
    mWin = parent;


    // Intialize mouse position
    mousePos = Coordinate(0,0);

    // we don't need mouse events here
    setMouseTracking(false);
}

Canvas::Canvas(ImageFrame *parent)
    : QOpenGLWidget(parent)
{
    // we don't need the mainW here
    mMainW = Q_NULLPTR;
    mWin = parent;


    // Intialize mouse position
    mousePos = Coordinate(0,0);

    // we don't need mouse events here
    setMouseTracking(false);
}

Canvas::Canvas(MainWindow *parent)
    : QOpenGLWidget(parent)
{
    // Store the MainWindow* for later use
    mMainW = parent;
    mWin = parent;

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

void Canvas::initializeGL()
{
    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

    glOrtho(0, width(), height(), 0, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // All drawing should be called from MainWindow->render()
    mWin->render();
}

void Canvas::resizeGL(int width, int height)
{
    /*
     * Inform the MainWindow* a resize has occured
     * so that the grid can be resized inorder
     * to compensate
    */
    mWin->canvasResized(width, height);

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

QSize Canvas::sizeHint() const
{
    if (mMainW != Q_NULLPTR)
        return QSize(800, 480);
    else
        return QSize(600, 250);

}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    if (mMainW != Q_NULLPTR)
        mousePos = event->pos();
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (mMainW != Q_NULLPTR)
    {
        if (event->button() == Qt::LeftButton)
            mMainW->addCoord(mMainW->getStatusCoord());
    }
}
