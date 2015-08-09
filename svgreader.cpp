#include "svgreader.h"
#include "mask.h"

SVG::SVG()
{
    mType = PolyEdit::Invalid;
    width = 0;
    height = 0;
    radius = 0;
}

SVGReader::SVGReader(const QString filename)
{
    //mType = PolyEdit::Invalid;
    _filename = filename;
    xoffset = 0;
    yoffset = 0;

}

const SVG SVGReader::read()
{
    QFile xmlFile(_filename);
    xmlFile.open(QIODevice::ReadOnly);
    xml.setDevice(&xmlFile);

    if (xml.readNextStartElement() && xml.name() == "svg")
        processSVG();

    // readNextStartElement() leaves the stream in
    // an invalid state at the end. A single readNext()
    // will advance us to EndDocument.
    if (xml.tokenType() == QXmlStreamReader::Invalid)
        xml.readNext();

    if (xml.hasError())
        xml.raiseError();

    xmlFile.close();

    return mSVG;
}

bool SVGReader::processSVG()
{

    bool ok = true;


    if (!xml.isStartElement() || xml.name() != "svg")
        return false;

    QXmlStreamAttributes attr = xml.attributes();
    for (auto a : attr)
    {
        if (a.name() == "x")
            xoffset = a.value().toInt(&ok, 10);

        if (a.name() == "y")
            yoffset = a.value().toInt(&ok, 10);

        if(!ok)
            return false;
    }

    xml.readNextStartElement();

    switch(PolyEdit::hashit(xml.name().toString()))
    {
        case PolyEdit::Polygon:
        {
            return proccessPolygon(xml.attributes());
        }
        case PolyEdit::Box:
        {
            return processBox(xml.attributes());
        }
        case PolyEdit::Circle:
        {
            return processCircle(xml.attributes());
        }
        case PolyEdit::Invalid:
        {
            return false;
        }
    }
}

bool SVGReader::proccessPolygon(QXmlStreamAttributes attributes)
{
    //mType = PolyEdit::Polygon;

    bool ok = false;
    QString points;

    for (auto a : attributes)
    {
        if (a.name() == "points")
        {
            points = a.value().toString();
            break;
        }
    }

    if (points.isEmpty())
    {
        qDebug() << "invalid/missing coordinates";
        return false;
    }

    QStringList p;
    p = points.split(" ", QString::SkipEmptyParts);

    for (auto c : p)
    {
        QStringList coord = c.split(",");

        if (coord.size() != 2)
        {
            qDebug() << "invalid coordinate";
            break;
        }

        int x = coord[0].toInt(&ok, 10);
        if (!ok)
            return false;

        int y = coord[1].toInt(&ok, 10);
        if (!ok)
            return false;

        coords.append(Coordinate(x+xoffset,-y-yoffset));
    }

    mSVG.setType(PolyEdit::Polygon);
    mSVG.setCoords(coords);

    return true;
}

bool SVGReader::processCircle(QXmlStreamAttributes attributes)
{
    bool ok = false;
    QString r;

    for (auto a : attributes)
    {
        if (a.name() == "r")
            r = a.value().toString();

        if (!r.isEmpty())
            break;
    }

    int radius = r.toInt(&ok, 10);
    if(!ok)
        return false;

    coords.append(Coordinate(xoffset, -yoffset));

    mSVG.setType(PolyEdit::Circle);
    mSVG.setCoords(coords);
    mSVG.setRadius(radius);

    return true;
}

bool SVGReader::processBox(QXmlStreamAttributes attributes)
{
    bool ok = false;
    QString w;
    QString h;

    for (auto a : attributes)
    {
        if (a.name() == "width")
            w = a.value().toString();

        if (a.name() == "height")
            h = a.value().toString();

        if (!w.isEmpty() && !h.isEmpty())
            break;
    }

    int width = w.toInt(&ok, 10);
    if(!ok)
        return false;

    int height = h.toInt(&ok, 10);
    if(!ok)
        return false;

    coords.append(Coordinate(xoffset, -yoffset));

    mSVG.setType(PolyEdit::Box);
    mSVG.setCoords(coords);

    mSVG.setWidth(width);
    mSVG.setHeight(height);


    return true;
}


QList<Coordinate> SVG::getCoords() const
{
    return coords;
}

void SVG::setCoords(const QList<Coordinate> &value)
{
    coords = value;
}
PolyEdit::Shape SVG::getType() const
{
    return mType;
}

void SVG::setType(const PolyEdit::Shape &type)
{
    mType = type;
}
int SVG::getWidth() const
{
    return width;
}

void SVG::setWidth(int value)
{
    width = value;
}
int SVG::getHeight() const
{
    return height;
}

void SVG::setHeight(int value)
{
    height = value;
}
int SVG::getRadius() const
{
    return radius;
}

void SVG::setRadius(int value)
{
    radius = value;
}




