#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QMainWindow>

class Canvas;

class GLWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit GLWindow(QWidget *parent = 0);

    /**
     * @brief render draw everything here
     */
    virtual void render() {}

    /**
     * @brief canvasResized
     * @param w width
     * @param h height
     */
    virtual void canvasResized(int w, int h) {}

protected:
    QWidget* mCentralWidget;
};

#endif // GLWINDOW_H
