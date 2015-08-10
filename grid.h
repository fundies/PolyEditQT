#ifndef GRID_H
#define GRID_H

#include <QOpenGLFunctions>

#include "coordinate.h"

/**
 * @brief The Grid class
 */
class Grid : protected QOpenGLFunctions
{
public:

    /**
     * @brief Grid constructor for grids used on MainWindow
     * @param xSep horizontal seperation
     * @param ySep vertical seperation
     * @param canvasW canvas width
     * @param canvasH canvas height
     */
    Grid(int xSep, int ySep, int canvasW, int canvasH);

    /**
     * @brief Grid constructor used for grids used in ImageLoader
     * @param width width
     * @param height height
     * @param rows rows
     * @param columns columns
     * @param xsep horizontal seperation
     * @param ysep vertical seperation
     */
    Grid(unsigned int width, unsigned int height, unsigned int rows, unsigned int columns, unsigned int xSep, unsigned int ySep);

    /**
     * @brief ~Grid Destructor
     */
    virtual ~Grid() {}

    /**
     * @brief getXsep returns horizontal seperation
     * @return horizontal seperation
     */
    int getXsep()
    {
        return mXsep;
    }

    /**
     * @brief getYsep returns vertical seperation
     * @return vertical seperation
     */
    int getYsep()
    {
        return mYSep;
    }

    /**
     * @brief getXoffset returns x offset
     * @return x offset
     */
    int getXoffset()
    {
        return mXoffset;
    }

    /**
     * @brief getYoffset returns y offset
     * @return y offset
     */
    int getYoffset()
    {
        return mYoffset;
    }

    /**
     * @brief setXoffset set the x offset
     * @param x new x offset
     */
    void setXoffset(int x)
    {
        mXoffset = x;
    }

    /**
     * @brief setYoffset set the y offset
     * @param y new y offset
     */
    void setYoffset(int y)
    {
        mYoffset = y;
    }

    /**
     * @brief setSize resize method for Canvas' grid
     * @param xoff x offset
     * @param yoff y offset
     * @param xSep horizontal seperation
     * @param ySep vertical seperation
     * @param canvasW canvas width
     * @param canvasH canvas height
     * @param zoom canvas zoom factor
     */
    void setSize(int xoff, int yoff, int xSep, int ySep, int canvasW, int canvasH, double zoom);


    /**
     * @brief setSize resize method for ImageLoader's grid
     * @param width width
     * @param height height
     * @param rows rows
     * @param columns columns
     * @param xSep horizontal seperation
     * @param ySep vertical seperation
     */
    void setSize(unsigned int width, unsigned int height, unsigned int rows, unsigned int columns, unsigned int xSep, unsigned int ySep);

    /**
     * @brief render draw the grid
     */
    void render();

    /**
     * @brief setAlwaysVisible makes the grid's lines invert background color
     * @param value true/false
     */
    void setAlwaysVisible(bool value);

private:

    QList<Coordinate> mcs;
    bool alwaysVisible;
    int mXsep = 0;
    int mYSep = 0;
    int mXoffset = 0;
    int mYoffset = 0;
    int mXrepeat = 0;
    int mYRepeat = 0;
};

#endif // GRID_H
