#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class MainWindow;

#include <QMainWindow>
#include <QLabel>
#include <functional>
#include <QList>
#include <QSharedPointer>
#include <QTimer>
#include <QOpenGLContext>

#include "sprite.h"
#include "glwindow.h"
#include "grid.h"
#include "table.h"
//#include "imageloader.h"
#include "animationframe.h"
#include "svgreader.h"

class MaskTab;
class MenuBar;
class ToolBar;
class MainCanvas;
class ImageFrame;

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
    void setMask(Table* mask);

    void setSpr(const SpritePtr &spr);

private slots:

    void reset();
    void open();
    void save();
    void saveAs();
    void about();
    //void play();
    void pause();
    void stop();
    //void incrementSubimg();
    void editSprite();
    void editAnimation();
    void viewGrid(bool value);
    void viewSprite(bool value);
    //void zoomIn();
    //void zoomOut();
    //void zoom100();
    void updateGrid();
    void setXsep(int value);
    void setYsep(int value);
    void setFrame(int frame);

private:

    void openImage(QString fpath);
    void openImage(QString fpath, int rows, int columns);
    void openSVG(QString fpath);
    void openSpr(QString fpath);
    void addMask(SVG &svg);

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

    //void setZoom(double factor);

    //Canvas* mCanvas;
    //Sprite *mCheckers;

    bool mViewGrid;
    bool mViewSprite;
    int mXsep;
    int mYsep;

    ImageFrame* imgLoader;
    AnimationFrame* animationEdit;

    //double zoom;
    //double zoomLast;

    Coordinate mCoord;

    QLabel* xCoord;
    QLabel* yCoord;

    QSharedPointer<Grid> mGrid;

    ToolBar* mToolBar;
    MenuBar* mMenuBar;

    Table* currentMask;

    MaskTab* mTabs;
    QList<Table*> *table;

    QString saveFile;

};

#endif // MAINWINDOW_H
