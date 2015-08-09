#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "sprite.h"

class MainWindow;
class Canvas;
class QActions;

/**
 * @brief The GLWindow class
 */
class GLWindow : public QMainWindow
{
    Q_OBJECT
public:

    /**
     * @brief GLWindow constructor
     * @param parent pointer to main window
     */
    explicit GLWindow(MainWindow *parent = 0);

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

    /**
     * @brief actions pointer to all the actions
     * @return actions
     */
    QSharedPointer<QActions> actions() const;

    /**
     * @brief setSpeed sets the animation speed
     * @param value new speed
     */
    void setSpeed(double value);

protected slots:

    /**
     * @brief open open a file
     */
    virtual void open();

    /**
     * @brief play begin animation
     */
    virtual void play();

    /**
     * @brief pause pause animation
     */
    virtual void pause();

    /**
     * @brief stop stop animation
     */
    virtual void stop();

    /**
     * @brief incrementSubimg increase the subimage
     */
    virtual void incrementSubimg();

    /**
     * @brief zoomIn increases the zoom factor
     */
    virtual void zoomIn();

    /**
     * @brief zoomOut decreases the zoom factor
     */
    virtual void zoomOut();

    /**
     * @brief zoom100 resests the zoom factor
     */
    virtual void zoom100();

protected:

    /**
     * @brief setZoom sets the zoom
     * @param factor new zoom factor
     */
    virtual void setZoom(double factor);

    double zoom;
    double zoomLast;
    double speed;
    double subImg;
    QTimer *mTimer;
    QWidget *mCentralWidget;
    QSharedPointer<QActions> mActions;
    Canvas *mCanvas;
    SpritePtr mCheckers;
    SpritePtr mSpr;
};

#endif // GLWINDOW_H
