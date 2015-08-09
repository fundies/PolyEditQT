#include <QGLWidget>

#include "grid.h"

Grid::Grid(int xSep, int ySep, int canvasW, int canvasH)
{
    alwaysVisible = false;
    setSize(0, 0, xSep, ySep, canvasW, canvasH, 1);
}

Grid::Grid(unsigned int width, unsigned int height, unsigned int rows, unsigned int columns, unsigned int xSep, unsigned int ySep)
{
    alwaysVisible = false;
    setSize(width, height, rows, columns, xSep, ySep);
}

void Grid::setSize(int xoff, int yoff, int xSep, int ySep, int canvasW, int canvasH, double zoom)
{
    mXsep = xSep;
    mYSep = ySep;

    // Factor the zoom into the seperations
    float realXsep = xSep*zoom;
    float realYsep = ySep*zoom;

    setXoffset(xoff);
    setYoffset(yoff);

    // Delete the last grid
    mcs.clear();

    // Gray
    QColor defaultColor = QColor(255, 255, 255, 40);

    // Repeat the grid when larger than the window
    /// TODO:  vertical repeat
    if (xoff == 0)
        mXrepeat = 0;
    else
        mXrepeat = (xoff / (canvasW/2))*zoom;

    float relXoff = (xoff - ((canvasW/2) * mXrepeat))*zoom;

    mcs.push_back(Coordinate(0,(canvasH / 2) + yoff, (mYRepeat == 0) ? Qt::red : defaultColor));
    mcs.push_back(Coordinate(canvasW,(canvasH / 2) + yoff, (mYRepeat == 0) ? Qt::red : defaultColor));

    mcs.push_back(Coordinate((canvasW / 2) + relXoff, 0, (mXrepeat == 0) ? Qt::blue : defaultColor));
    mcs.push_back(Coordinate((canvasW / 2) + relXoff,canvasH, (mXrepeat == 0) ? Qt::blue : defaultColor));

    for (int i=((canvasW/2)-realXsep + relXoff); i > 0; i-=realXsep)
    {
        mcs.push_back(Coordinate(i,0, defaultColor));
        mcs.push_back(Coordinate(i,canvasH, defaultColor));
    }

    for (int i=((canvasW/2)+realXsep + relXoff); i < canvasW; i+=realXsep)
    {
        mcs.push_back(Coordinate(i,0, defaultColor));
        mcs.push_back(Coordinate(i,canvasH, defaultColor));
    }

    for (int i=((canvasH/2)-realYsep + yoff); i > 0; i-=realYsep)
    {
        mcs.push_back(Coordinate(0,i, defaultColor));
        mcs.push_back(Coordinate(canvasW,i, defaultColor));
    }

    for (int i=((canvasH/2)+realYsep + yoff); i < canvasH; i+=realYsep)
    {
        mcs.push_back(Coordinate(0,i, defaultColor));
        mcs.push_back(Coordinate(canvasW,i, defaultColor));
    }
}

void Grid::setSize(unsigned int width, unsigned int height, unsigned int rows, unsigned int columns, unsigned int xSep, unsigned int ySep)
{

    // Delete previous grid
    mcs.clear();

    // Int/Int always returns int
    int w = (int)width / columns;
    int h = (int)height / rows;

    for(size_t i = 0; i < rows; i++)
    {
        for(size_t j = 0; j < columns; j++)
        {
            // Added counter clockwise
            Coordinate w2(w * j + xSep, h * i + ySep);
            Coordinate x(w * j + xSep, h * (i + 1) - ySep);
            Coordinate y(w * (j + 1) - xSep, h * (i + 1) - ySep);
            Coordinate z(w * (j + 1) - xSep, h * i + ySep);

            mcs.push_back(w2);
            mcs.push_back(x);

            mcs.push_back(x);
            mcs.push_back(y);

            if (xSep > 0)
            {
                mcs.push_back(y);
                mcs.push_back(z);
            }

            if (ySep > 0)
            {
                mcs.push_back(z);
                mcs.push_back(w2);
            }
        }
    }

    if (xSep == 0)
    {
        mcs.push_back(Coordinate(0,0));
        mcs.push_back(Coordinate(width,0));
    }

    if (ySep == 0)
    {
        mcs.push_back(Coordinate(width,0));
        mcs.push_back(Coordinate(width,height));
    }
}

void Grid::render()
{
    // Alpha
    glEnable (GL_BLEND);

    if (alwaysVisible)
        glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO);
    else
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDisable(GL_TEXTURE_2D);
    glBegin(GL_LINES);

    for (auto i : mcs)
    {
        QColor c = i.color();
        glColor4f(c.red()/255.f, c.green()/255.f, c.blue()/255.f, c.alpha()/255.f);
        glVertex2f(i.rx(), i.ry());
    }

    glEnd();

    // Reset color to white
    glColor4f(1,1,1,1);

    glDisable(GL_BLEND);
}
void Grid::setAlwaysVisible(bool value)
{
    alwaysVisible = value;
}


