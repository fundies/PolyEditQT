#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QOpenGLContext>

#include <QtGui/QWindow>
#include <QtGui/QOpenGLFunctions>

#include "qactions.h"
#include "sprite.h"
//#include "mainwindow.h"

class MainWindow;
class Canvas;

class GLWindow : public QMainWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit GLWindow(MainWindow *parent = 0);
    virtual ~GLWindow();

    /**
     * @brief render draw everything here
     */
    virtual void render();

    /**
     * @brief canvasResized
     * @param w width
     * @param h height
     */
    virtual void canvasResized(int w, int h);


    QSharedPointer<QActions> actions() const;

    bool spriteExists() const;

protected slots:

    virtual void open();
    virtual void play();
    virtual void pause();
    virtual void stop();
    virtual void incrementSubimg();
    virtual void zoomIn();
    virtual void zoomOut();
    virtual void zoom100();

protected:

    virtual void setZoom(double factor);
    double zoom;
    double zoomLast;


    QTimer *mTimer;
    unsigned int subImg;

    QWidget* mCentralWidget;
    QSharedPointer<QActions> mActions;
    Canvas* mCanvas;

    SpritePtr mCheckers;
    SpritePtr mSpr;
};

#endif // GLWINDOW_H
