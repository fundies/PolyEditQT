#ifndef TABLE_H
#define TABLE_H

#include <QTableWidget>
#include <QHeaderView>
#include "cell.h"
#include "mask.h"

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
    Table(QWidget *parent, QGLWidget *glParent);
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

    // Todo : replace with overload
    const Coordinate getc(int i) const;

    /*const Coordinate& operator[](int i) const
    {
        return mMask->getc(i);
    }*/

private slots:

    /**
     * @brief itemChanged cell selection changed
     * @param item new cell
     */
    void itemChanged(QTableWidgetItem * item);

private:

    /**
     * @brief getItem get a specific cell
     * @param row row
     * @param column column
     * @return cell*
     */
    Cell* getItem(int row, int column) const;

    /**
     * @brief insertRow override for insertRow()
     * @param row row
     */
    void insertRow(int row);

    /**
     * @brief keyPressEvent override for keypress
     * @param event event
     */
    void keyPressEvent(QKeyEvent * event);

    bool isReady;
    Mask* mMask;
    PolyEdit::Shape mType;
};

#endif // TABLE_H
