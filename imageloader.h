#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QMainWindow>
#include "canvas.h"
#include "grid.h"
#include "sprite.h"

class ImageLoader : public GLWindow
{
    Q_OBJECT
public:
    explicit ImageLoader(QWidget *parent = 0);
    void canvasResized(int w, int h);

private:
    void render();
    void setSpnRows(int i);
    void setSpnColumns(int i);
    void setSpnX(int i);
    void setSpnY(int i);
    void updateGrid();

    QWidget* mCentralWidget;
    Canvas* mCanvas;
    Grid* mGrid;

    int mSpnRows;
    int mSpnColumns;
    int mSpnX;
    int mSpnY;

    Sprite *spr;

};

#endif // IMAGELOADER_H
