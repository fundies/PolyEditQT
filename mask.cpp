#include "mask.h"
#include "utility.h"
#include <QDebug>
#include <QFile>
#include <QXmlStreamWriter>

namespace PolyEdit
{
    Shape hashit (QString const &inString)
    {
        if (inString == "polyline") return Polygon;
        if (inString == "circle") return Circle;
        if (inString == "rect") return Box;
        return Invalid;
    }
}

Mask::Mask(QOpenGLWidget *parent)
{
    mParent = parent;
    mRadius = 0;
    mType = PolyEdit::Polygon;
    xscale = 1;
    yscale = 1;
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

void Mask::scale(float scale)
{
    xscale=scale;
    yscale=scale;
}

void Mask::scale(float x, float y)
{
    xscale=x;
    yscale=y;
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
            glVertex2f(i.rx() * xscale, -i.ry() * yscale); // reverse y axis
        }

        glEnd();

        /// Todo: update steps based on radius
        int steps = 30;

        for (auto i : mcs)
            drawCircle(Coordinate(i.rx() * xscale, -i.ry() * yscale), 5, steps, false);
    }

    // Reset to white
    glColor4f(1,1,1,1);
}


void Mask::render(Coordinate mousePos)
{
    // Draw everything expect polygon's here
    if (mType == PolyEdit::Circle && !mcs.empty())
    {
        Coordinate c = Coordinate(mcs[0].rx() * xscale, -mcs[0].ry() * yscale); //reverse y axis
        drawCircle(c, 5, 30, false); // Origin

        if (mRadius == 0)
            drawCircle(c, distance(Coordinate(c.rx(), -c.ry()), mousePos * xscale), 30, true);
        else
            drawCircle(c, mRadius * xscale, 30, true);
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
            Coordinate origin = Coordinate(x * xscale, y * yscale);
            drawCircle(origin, 5, 30, false);
        }

        glBegin(GL_LINE_STRIP);

        for (auto i : *temp)
        {
            glVertex2f(i.rx() * xscale, -i.ry() * yscale); // reverse y axis
        }

        glEnd();
    }

    // Reset to white
    glColor4f(1,1,1,1);
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

const Coordinate &Mask::getc(int index) const
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

void Mask::exportSVG(QString fpath)
{
    if (mType == PolyEdit::Circle)
    {
        if (mcs.size() < 1 || mRadius <= 0)
            return;
    }
    else if (mcs.size() < 2)
        return;

    QList<Coordinate>::iterator result;

    result = std::min_element(mcs.begin(), mcs.end(), [](Coordinate &a, Coordinate &b)
    {
        return a.rx() < b.rx();
    });
    int minX = result->rx();

    result = std::max_element(mcs.begin(), mcs.end(), [](Coordinate &a, Coordinate &b)
    {
        return a.rx() < b.rx();
    });
    int maxX = result->rx();

    result = std::min_element(mcs.begin(), mcs.end(), [](Coordinate &a, Coordinate &b)
    {
        return -a.ry() < -b.ry();
    });
    int minY = -result->ry();

    result = std::max_element(mcs.begin(), mcs.end(), [](Coordinate &a, Coordinate &b)
    {
        return -a.ry() < -b.ry();
    });
    int maxY = -result->ry();

    unsigned int width; //= std::abs(maxX - minX);
    unsigned int height;// = std::abs(maxY - minY);

    if(mType == PolyEdit::Circle)
    {
        width = mRadius*2;
        height = mRadius*2;
    }
    else
    {
        width = std::abs(maxX - minX);
        height = std::abs(maxY - minY);
    }


    QFile data(fpath);
    if (data.open(QFile::WriteOnly | QFile::Truncate))
    {

        QString style = "fill:none;stroke:black;stroke-width:1";
        //style="fill:none;stroke:black;stroke-width:1"

        QXmlStreamWriter stream(&data);
        stream.setAutoFormatting(true);
        stream.writeStartDocument();

        stream.writeStartElement("svg");
        stream.writeAttribute("width", QString::number(width));
        stream.writeAttribute("height", QString::number(height));
        stream.writeAttribute("x", QString::number(minX));
        stream.writeAttribute("y", QString::number(minY));

        switch(mType)
        {
            case PolyEdit::Polygon:
            {
                QString points;
                for (auto i : mcs)
                    points += QString::number(i.rx() - minX) + ","  + QString::number(-i.ry() - minY) + " ";

                points = points.trimmed();

                stream.writeStartElement("polyline");
                stream.writeAttribute("points", points);
                stream.writeAttribute("style", style);
                stream.writeEndElement(); // polyline
                break;
            }
            case PolyEdit::Box:
            {
                stream.writeStartElement("rect");
                stream.writeAttribute("width", QString::number(width));
                stream.writeAttribute("height", QString::number(height));
                stream.writeAttribute("style", style);
                stream.writeEndElement(); // rect
                break;
            }
            case PolyEdit::Circle:
            {
                stream.writeStartElement("circle");
                stream.writeAttribute("cx", QString::number(mRadius));
                stream.writeAttribute("cy", QString::number(mRadius));
                stream.writeAttribute("r", QString::number(mRadius));
                stream.writeAttribute("style", style);
                stream.writeEndElement(); // circle
                break;
            }
            case PolyEdit::Invalid:
            {
                break;
            }
        }

        stream.writeEndElement(); // svg
        stream.writeEndDocument();
    }
}
