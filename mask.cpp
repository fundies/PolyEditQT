#include "mask.h"
#include "utility.h"
#include <iostream>

Mask::Mask(QGLWidget* parent)
{
    mParent = parent;
    mRadius = 0;
    mType = PolyEdit::Polygon;
}

void Mask::addc(Coordinate c)
{
    mcs.append(c);
}

void Mask::replace(int index, Coordinate c)
{
    mcs.replace(index, c);
}

void Mask::deletec(int index)
{
    mcs.removeAt(index);
}

int Mask::size()
{
    return mcs.size();
}

void Mask::render()
{
    // Disable textures in the pipeline
    glDisable(GL_TEXTURE_2D);

    // We only draw polygons here
    if (mType == PolyEdit::Polygon)
    {
        glBegin(GL_LINE_STRIP);

        for (auto i : mcs)
        {
            //mParent->qglColor(i.getColor());
            glVertex2f(i.rx(), -i.ry()); // reverse y axis
        }

        glEnd();

        /// Todo: update steps based on radius
        int steps = 30;

        for (auto i : mcs)
        {
            drawCircle(Coordinate(i.rx(), -i.ry()), 5, steps, false);
        }
    }

    // Reset to white
    glColor4f(1,1,1,1);
}


void Mask::render(Coordinate mousePos)
{
    // Draw everything expect polygon's here
    if (mType == PolyEdit::Circle && !mcs.empty())
    {
        Coordinate c = Coordinate(mcs[0].rx(), -mcs[0].ry()); //reverse y axis
        drawCircle(c, 5, 30, false); // Origin

        if (mRadius == 0)
            drawCircle(c, distance(mcs[0], mousePos), 30, true);
        else
            drawCircle(c, mRadius, 30, true);
    }

    if (mType == PolyEdit::Box && !mcs.empty())
    {
        /* We bind this to rectangle coords if
         * there is more than one coordinate
         * otherwise we generate a temporary mask
         * using the mouse as the second Coordinate
         */
        QList<Coordinate> *temp;
        if (mcs.size() == 1)
        {
            temp = new QList<Coordinate>();

            int width = mousePos.rx() - mcs[0].rx();
            int height = mcs[0].ry() - mousePos.ry();

            int x = (sign(width) == -1) ? mousePos.rx() : mcs[0].rx();
            int y = (sign(height) == -1) ? mousePos.ry() : mcs[0].ry();

            std::cout << y << std::endl;

            width = abs(width);
            height = abs(height);

            temp->append(Coordinate(x,y));
            temp->append(Coordinate(x+width, y));
            temp->append(Coordinate(x+width, y-height));
            temp->append(Coordinate(x, y-height));
            temp->append(Coordinate(x,y));
        }
        else
        {
            temp = &mcs;
            int x = (mcs[2].rx() + mcs[0].rx())/2;
            int y = -(mcs[2].ry() + mcs[0].ry())/2;

            // Draw the orgin too
            Coordinate origin = Coordinate(x,y);
            drawCircle(origin, 5, 30, false);
        }

        glBegin(GL_LINE_STRIP);

        for (auto i : *temp)
        {
            //mParent->qglColor(i.getColor());
            glVertex2f(i.rx(), -i.ry()); // reverse y axis
        }

        glEnd();
    }
}

void Mask::clear()
{
    mcs.clear();
}

void Mask::setCircle(Coordinate origin, int radius)
{
    mcs.clear();
    mcs.append(origin);
    mRadius = radius;
    mType = PolyEdit::Circle;
}

void Mask::setBox(int left, int top, int width, int height)
{
    mRadius = 0;
    mcs.clear();

    // Added clockwise
    mcs.append(Coordinate(left,top));
    mcs.append(Coordinate(left+width, top));
    mcs.append(Coordinate(left+width, top-height));
    mcs.append(Coordinate(left, top-height));
    mcs.append(Coordinate(left,top));

    mType = PolyEdit::Box;
}

const Coordinate& Mask::getc(int index) const
{
    return mcs[index];
}
int Mask::getRadius() const
{
    return mRadius;
}
void Mask::setRadius(int radius)
{
    mRadius = radius;
}
void Mask::setType(const PolyEdit::Shape &type)
{
    mType = type;
}