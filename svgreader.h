#ifndef SVGREADER_H
#define SVGREADER_H

#include <QtXml>
#include <QDebug>
#include "coordinate.h"
#include "mask.h"

class SVG
{
public:
    SVG();

    QList<Coordinate> getCoords() const;
    void setCoords(const QList<Coordinate> &value);

    PolyEdit::Shape getType() const;
    void setType(const PolyEdit::Shape &type);

    int getWidth() const;
    void setWidth(int value);

    int getHeight() const;
    void setHeight(int value);

    int getRadius() const;
    void setRadius(int value);

private:
    QList<Coordinate> coords;
    PolyEdit::Shape mType;
    int width;
    int height;
    int radius;
};

class SVGReader
{
public:
    SVGReader(const QString filename);
    const SVG read();

private:
    bool processSVG();
    bool proccessPolygon(QXmlStreamAttributes attributes);
    bool processCircle(QXmlStreamAttributes attributes);
    bool processBox(QXmlStreamAttributes attributes);

    QString _filename;
    QXmlStreamReader xml;

    QList<Coordinate> coords;
    SVG mSVG;

    int xoffset;
    int yoffset;
};


#endif // SVGREADER_H
