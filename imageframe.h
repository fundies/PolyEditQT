#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QMainWindow>
#include <QScrollArea>
#include <QColorDialog>
#include <QSharedPointer>

#include "glwindow.h"

class MainWindow;
class ImageBounds;
class Grid;

/**
 * @brief The ImageFrame class
 */
class ImageFrame : public GLWindow
{
    Q_OBJECT

public:

    /**
     * @brief ImageFrame constructor
     * @param parent pointer to main mwindow
     * @param image image used for sprite
     */
    ImageFrame(MainWindow *parent, QImage &image);

    /**
     * @brief canvasResized Canvas resized event
     * @param w width
     * @param h height
     */
    void canvasResized(int w, int h);

    /**
     * @brief render draw stuff
     */
    void render();

    /**
     * @brief setSprite
     * @param spr new sprite
     */
    void setSprite(const SpritePtr &spr);

private slots:

    /**
     * @brief import import an image
     */
    void import();

    /**
     * @brief setColor revert alpha color
     */
    void setColor();

    /**
     * @brief setAlpha converts color to alpha
     * @param color colr to convert
     */
    void setAlpha(const QColor &color);

    /**
     * @brief setSpnRows sets number of rows
     * @param i rows
     */
    void setSpnRows(int i);

    /**
     * @brief setSpnColumns sets the number of columns
     * @param i columns
     */
    void setSpnColumns(int i);

    /**
     * @brief setSpnX sets the horizontal seperation
     * @param i horizontal seperation
     */
    void setSpnX(int i);

    /**
     * @brief setSpnY sets the vertical seperation
     * @param i vertical seperation
     */
    void setSpnY(int i);

private:

    /**
     * @brief updateGrid updates the grid
     */
    void updateGrid();

    MainWindow *mParent;
    QColorDialog *colorDialog;
    ImageBounds *bounds;
    QScrollArea *scrollArea;
    QWidget *mCentralWidget;
    QSharedPointer<Grid> mGrid;
    int mSpnRows;
    int mSpnColumns;
    int mSpnX;
    int mSpnY;
};

#endif // IMAGELOADER_H
