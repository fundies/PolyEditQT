#ifndef TABLE_H
#define TABLE_H

#include <QTableWidget>
#include <QOpenGLWidget>

#include "coordinate.h"
#include "shapes.h"

class Cell;
class Mask;

/**
 * @brief The Table class is the main modifier widget for masks
 */
class Table : public QTableWidget
{
    Q_OBJECT

public:

    /**
     * @brief Table constructor
     * @param parent parent
     * @param glParent widget we draw to
     */
    Table(QWidget *parent, QOpenGLWidget *glParent);
    ~Table();

    /**
     * @brief render draw
     */
    void render();

    /**
     * @brief render draw
     * @param mousePos mouse position
     */
    void render(Coordinate mousePos);

    /**
     * @brief removeRow override for removeRow()
     * @param row row
     */
    void removeRow(int row);

    /**
     * @brief addCoord add coordinate
     * @param p new coordinate
     */
    void addCoord(Coordinate c);

    /**
     * @brief setMaskType set the mask type
     * @param type Polygon, Circle, Box
     */
    void setMaskType(PolyEdit::Shape type);

    /**
     * @brief clearContents override for clearContents()
     */
    void clearContents();

    /**
     * @brief getType returns shape type
     * @return Polygon, Circle, Box
     */
    PolyEdit::Shape getType() const;

    /**
     * @brief size returns number of vertecies
     * @return number of vertecies
     */
    std::size_t size() const;

    /**
     * @brief getRadius returns radius for circle shapes
     * @return  radius
     */
    int getRadius() const;

    /**
     * @brief setRadius set the radius
     * @param radius radius
     */
    void setRadius(int radius);

    /**
     * @brief setBoxSize set the box size
     * @param width width
     * @param height height
     */
    void setBoxSize(int width, int height);

    /**
     * @brief getcoordinate get coordinate
     * @param i index
     * @return coordinate
     */
    const Coordinate getcoordinate(int i) const;

    /**
     * @brief scale set the scale
     * @param factor factor
     */
    void scale(double factor);

    /**
     * @brief exportSVG export SVG
     * @param fpath file path
     */
    void exportSVG(QString fpath);

    /**
     * @brief setRender enable drawing
     * @param state true/false
     */
    void setRender(bool state);

private slots:

    /**
     * @brief itemChanged cell selection changed
     * @param item new cell
     */
    void itemChanged(QTableWidgetItem *item);

private:

    /**
     * @brief getItem get a specific cell
     * @param row row
     * @param column column
     * @return cell*
     */
    Cell *getItem(int row, int column) const;

    /**
     * @brief insertRow override for insertRow()
     * @param row row
     */
    void insertRow(int row);

    /**
     * @brief keyPressEvent override for keypress
     * @param event event
     */
    void keyPressEvent(QKeyEvent *event);

    Mask *mMask;
    PolyEdit::Shape mType;
    bool isReady;
    bool mRender;
};

#endif // TABLE_H
