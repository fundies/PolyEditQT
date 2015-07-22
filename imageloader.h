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
#include "mainwindow.h"

class ImageLoader : public GLWindow
{
    Q_OBJECT
public:
    ImageLoader(MainWindow *parent, QImage &image);
    void canvasResized(int w, int h);


private:
    void import();
    void render();
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
    Canvas* mCanvas;
    Grid* mGrid;

    int mSpnRows;
    int mSpnColumns;
    int mSpnX;
    int mSpnY;

    QSharedPointer<Sprite> mSpr;
    Sprite *mCheckers;

    MainWindow *mParent;

};

#endif // IMAGELOADER_H
