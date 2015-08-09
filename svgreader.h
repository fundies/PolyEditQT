#ifndef SVGREADER_H
#define SVGREADER_H

#include <QtXml>

#include "coordinate.h"
#include "shapes.h"

/**
 * @brief The SVG class
 */
class SVG
{

public:

    /**
     * @brief SVG constructor
     */
    SVG();

    /**
     * @brief getCoords get the coordinates
     * @return coordinates
     */
    QList<Coordinate> getCoords() const;

    /**
     * @brief setCoords set the coordinates
     * @param value coordinates
     */
    void setCoords(const QList<Coordinate> &value);

    /**
     * @brief getType gets the mask type
     * @return shape type
     */
    PolyEdit::Shape getType() const;

    /**
     * @brief setType sets the mask type
     * @param type shape type
     */
    void setType(const PolyEdit::Shape &type);

    /**
     * @brief getWidth get the width
     * @return width
     */
    int getWidth() const;

    /**
     * @brief setWidth set the width
     * @param value width
     */
    void setWidth(int value);

    /**
     * @brief getHeight get the height
     * @return height
     */
    int getHeight() const;

    /**
     * @brief setHeight set the height
     * @param value height
     */
    void setHeight(int value);

    /**
     * @brief getRadius get the radius
     * @return radius
     */
    int getRadius() const;

    /**
     * @brief setRadius set the radius
     * @param value radius
     */
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

    /**
     * @brief SVGReader
     * @param filename file name
     */
    SVGReader(const QString filename);

    /**
     * @brief read read svg
     * @return SVG
     */
    const SVG read();

private:

    /**
     * @brief processSVG attempt to read svg
     * @return success
     */
    bool processSVG();

    /**
     * @brief proccessPolygon attempt to proccess a polygon
     * @param attributes info
     * @return success
     */
    bool proccessPolygon(QXmlStreamAttributes attributes);

    /**
     * @brief processCircle attempt to proccess a circle
     * @param attributes info
     * @return success
     */
    bool processCircle(QXmlStreamAttributes attributes);

    /**
     * @brief processBox attempt to proccess a box
     * @param attributes info
     * @return success
     */
    bool processBox(QXmlStreamAttributes attributes);

    QString _filename;
    QXmlStreamReader xml;
    QList<Coordinate> coords;
    SVG mSVG;
    int xoffset;
    int yoffset;
};


#endif // SVGREADER_H
