#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class MainWindow;

#include <QMainWindow>
#include <QLabel>
#include <functional>
#include <QList>

#include "glwindow.h"
#include "qactions.h"
#include "grid.h"
#include "table.h"

class MenuBar;
class ToolBar;
class MainCanvas;

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

    ~MainWindow();

    /**
     * @brief actions stores actions used everywhere
     * @return cer to actions
     */
    QActions* actions();

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

private slots:

    void open();

private:

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


    MainCanvas* mCanvas;

    double zoom = 1;

    Coordinate mCoord;

    QLabel* xCoord;
    QLabel* yCoord;

    QActions* mActions;

    Grid* mGrid;

    ToolBar* mToolBar;
    MenuBar* mMenuBar;

    Table* currentMask;

    QMap<int, Table *> *table;
};

#endif // MAINWINDOW_H
