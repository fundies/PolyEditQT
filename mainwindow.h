#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

#include "glwindow.h"

class MainWindow;
class ImageFrame;
class AnimationFrame;
class MaskTab;
class MenuBar;
class ToolBar;
class MainCanvas;
class Table;
class SVG;
class Grid;

/**
 * @brief The MainWindow class
 */
class MainWindow : public GLWindow
{
    Q_OBJECT

public:

    /**
     * @brief MainWindow
     * @param parent parent
     */
    MainWindow(QWidget *parent = 0);

    /**
     * @brief render draw everything here
     */
    void render();

    /**
     * @brief canvasResized
     * @param w width
     * @param h height
     */
    void canvasResized(int w, int h);

    /**
     * @brief setStatusCoord update the statusbar coordinate
     * @param p c
     */
    void setStatusCoord(Coordinate c);

    /**
     * @brief addCoord add coordinate
     * @param p coodrinate
     */
    void addCoord(Coordinate c);

    /**
     * @brief getStatusCoord get the mouse's position relative to grid
     * @return coordinate
     */
    const Coordinate getStatusCoord() const;

    /**
     * @brief setMask set the current mask we're editing
     * @param mask new mask
     */
    void setMask(Table *mask);

    /**
     * @brief setSprite sets the sprite
     * @param spr new sprite
     */
    void setSprite(const SpritePtr &spr);

private slots:

    /**
     * @brief reset removes any loaded files
     */
    void reset();

    /**
     * @brief open open a file
     */
    void open();

    /**
     * @brief save save the current file
     */
    void save();

    /**
     * @brief saveAs save the current file under a new name
     */
    void saveAs();

    /**
     * @brief about opens the about window
     */
    void about();

    /**
     * @brief pause ovveride of GLWindow's pause
     */
    void pause();

    /**
     * @brief stop ovveride of GLWindow's stop
     */
    void stop();

    /**
     * @brief editSprite reopens the image loader's frame
     */
    void editSprite();

    /**
     * @brief editAnimation reopens the animation frame
     */
    void editAnimation();

    /**
     * @brief viewGrid sets the visibility of the grid
     * @param value true/false
     */
    void viewGrid(bool value);

    /**
     * @brief viewSprite sets the visibility of the sprite
     * @param value true/false
     */
    void viewSprite(bool value);

    /**
     * @brief updateGrid updates the grid
     */
    void updateGrid();

    /**
     * @brief setXsep sets the horizontal seperation
     * @param value horizontal seperation
     */
    void setXsep(int value);

    /**
     * @brief setYsep sets the vertical seperation
     * @param value vertical seperation
     */
    void setYsep(int value);

    /**
     * @brief setFrame sets the current frame
     * @param frame current frame
     */
    void setFrame(int frame);

private:

    /**
     * @brief openImage opens a image file
     * @param fpath file path
     */
    void openImage(QString fpath);

    /**
     * @brief openImage opens an image based on infro from xml
     * @param fpath file path
     * @param rows rows
     * @param columns columns
     */
    void openImage(QString fpath, int rows, int columns);

    /**
     * @brief openSVG opens a mask
     * @param fpath file path
     */
    void openSVG(QString fpath);

    /**
     * @brief openSpr Opens a .spr file
     * @param fpath file path
     */
    void openSpr(QString fpath);

    /**
     * @brief addMask generates a mask based on an SVG
     * @param svg SVG
     */
    void addMask(SVG &svg);

    /**
     * @brief setZoom sets the zoom factor
     * @param factor factor
     */
    void setZoom(double factor);

    /**
     * @brief mapToGrid map a cordinate relative to the grid
     * @param p coordinate
     * @return new coordinate
     */
    const Coordinate mapToGrid(Coordinate c);

    /**
     * @brief mapToRealinverse of mapToGrid
     * @param p coordinate
     * @return new coordinate
     */
    const Coordinate mapToReal(Coordinate c);

    ImageFrame *imgLoader;
    AnimationFrame *animationEdit;
    Coordinate mCoord;
    QLabel *xCoord;
    QLabel *yCoord;
    QSharedPointer<Grid> mGrid;
    ToolBar *mToolBar;
    MenuBar *mMenuBar;
    Table *currentMask;
    MaskTab *mTabs;
    QList<Table *> *table;
    QString saveFile;
    bool mViewGrid;
    bool mViewSprite;
    int mXsep;
    int mYsep;

};

#endif // MAINWINDOW_H
