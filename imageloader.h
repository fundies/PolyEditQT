#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QMainWindow>
#include <QScrollArea>
#include <QColorDialog>
#include <QSharedPointer>

#include "canvas.h"
#include "grid.h"
#include "sprite.h"
#include "imagebounds.h"
//#include "mainwindow.h"

class MainWindow;

class ImageFrame : public GLWindow
{
    Q_OBJECT
public:
    ImageFrame(MainWindow *parent, QImage &image);
    void canvasResized(int w, int h);
    void render();

private:

    void import();
    void setColor();
    void setAlpha(const QColor & color);
    void setSpnRows(int i);
    void setSpnColumns(int i);
    void setSpnX(int i);
    void setSpnY(int i);
    void updateGrid();

    QColorDialog *colorDialog;
    ImageBounds* bounds;
    QScrollArea* scrollArea;
    QWidget* mCentralWidget;
    QSharedPointer<Grid> mGrid;

    int mSpnRows;
    int mSpnColumns;
    int mSpnX;
    int mSpnY;


    MainWindow *mParent;

};

#endif // IMAGELOADER_H
