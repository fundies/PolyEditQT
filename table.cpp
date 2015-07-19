#include "table.h"
#include <iostream>
#include <QDebug>
#include <QKeyEvent>

#include "utility.h"

Table::Table(QWidget *parent, QOpenGLWidget *glParent) : QTableWidget(parent)
{
    mType = PolyEdit::Polygon;

    isReady = false;

    mMask = new Mask(glParent);

    setColumnCount(2);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    setHorizontalHeaderItem(0, new Cell("X"));
    setHorizontalHeaderItem(1, new Cell("Y"));
    setRowCount(1);

    connect(this, &QTableWidget::itemChanged, this, &Table::itemChanged);

    setItem(0,0, new Cell(""));
    setItem(0,1, new Cell(""));

    isReady = true;
}

Table::~Table()
{
    delete mMask;
    //QTableWidget::~QTableWidget;
}

Cell* Table::getItem(int row, int column) const
{
    // Cell holds custom methods / behaviors we need
    return static_cast<Cell*>(QTableWidget::item(row, column));
}

void Table::itemChanged(QTableWidgetItem *item)
{
    Cell* cell = static_cast<Cell*>(item);
    cell->setText(item->text());

    int c = cell->column();
    int r = cell->row();

    // Don't update shapes until new cells are valid
    if (isReady)
    {
        switch(mType)
        {
        case PolyEdit::Polygon:
        {

            QTableWidgetItem* neighbor = this->item(r,c + ((c > 0) ? -1 : 1));

            bool isEmpty = cell->text().isEmpty();
            bool isNeighborEmpty = neighbor->text().isEmpty();

            if (!isEmpty && !isNeighborEmpty)
            {
                int x = getItem(r, 0)->getInt();
                int y = getItem(r, 1)->getInt();

                if (r == rowCount()-1)
                {
                    insertRow(rowCount());
                    mMask->addc(Coordinate(x, y));
                }
                else
                    mMask->replace(r, Coordinate(x, y));
            }
            break;
        }
        case PolyEdit::Circle:
        {
            QString item[3];
            item[0] = getItem(0,0)->text();
            item[1] = getItem(1,0)->text();
            item[2] = getItem(2,0)->text();

            if (!item[0].isEmpty() && !item[1].isEmpty() && !item[2].isEmpty())
            {
                int x = getItem(0,0)->getInt();
                int y = getItem(1,0)->getInt();
                int radius = getItem(2,0)->getInt();
                mMask->setCircle(Coordinate(x, y), radius);
            }
            break;
        }
        case PolyEdit::Box:
        {
            QString item[4];
            item[0] = getItem(0,0)->text();
            item[1] = getItem(1,0)->text();
            item[2] = getItem(2,0)->text();
            item[3] = getItem(3,0)->text();

            if (!item[0].isEmpty() && !item[1].isEmpty() && !item[2].isEmpty() && !item[3].isEmpty())
            {
                int x = getItem(0,0)->getInt();
                int y = getItem(1,0)->getInt();

                int width = getItem(2,0)->getInt();
                int height = getItem(3,0)->getInt();

                mMask->setBox(x, y, width, height);
            }
            break;
        }
        }
    }
}
void Table::insertRow(int row)
{
    isReady = false;
    QTableWidget::insertRow(row);
    setItem(row,0, new Cell(""));
    setItem(row,1, new Cell(""));
    isReady = true;
}

void Table::addCoord(Coordinate c)
{
    switch(mType)
    {
    case PolyEdit::Polygon:
    {
        int row = rowCount()-1;
        setItem(row,0, new Cell(QString::number(c.rx())));
        setItem(row,1, new Cell(QString::number(c.ry())));
        break;
    }
    case PolyEdit::Circle:
    {
        Cell* item[3];
        item[0] = getItem(0,0);
        item[1] = getItem(1,0);
        item[2] = getItem(2,0);

        if (!item[2]->text().isEmpty() && mMask->size() == 1)
        {
            clearContents();
            mMask->clear();
            mMask->addc(c);
            mMask->setRadius(0);
            setItem(0,0, new Cell(QString::number(c.rx())));
            setItem(1,0, new Cell(QString::number(c.ry())));
        }
        else if (item[0]->text().isEmpty() || item[1]->text().isEmpty())
        {
            setItem(0,0, new Cell(QString::number(c.rx())));
            setItem(1,0, new Cell(QString::number(c.ry())));
            mMask->addc(c);
        }
        else
        {
            int x1 = item[0]->getInt();
            int y1 = item[1]->getInt();
            Coordinate c1(x1,y1);
            //int x2 = c.rx();
            //int y2 = c.ry();

            int radius = distance(c, c1);//sqrt(pow((x2-x1),2) + pow((y2-y1),2));

            setItem(2,0, new Cell(QString::number(radius)));
        }
        break;
    }
    case PolyEdit::Box:
    {
        bool item[4];
        item[0] = getItem(0,0)->text().isEmpty();
        item[1] = getItem(1,0)->text().isEmpty();
        item[2] = getItem(2,0)->text().isEmpty();
        item[3] = getItem(3,0)->text().isEmpty();

        if (!item[0] && !item[1] && !item[2] && !item[3])
        {
            clearContents();
            setItem(0,0, new Cell(QString::number(c.rx())));
            setItem(1,0, new Cell(QString::number(c.ry())));
            mMask->clear();
            mMask->addc(c);
        }
        if (item[0] || item[1])
        {
            setItem(0,0, new Cell(QString::number(c.rx())));
            setItem(1,0, new Cell(QString::number(c.ry())));
            mMask->addc(c);
        }
        else if (item[2] || item[3])
        {
            int width = c.rx() - getItem(0,0)->getInt();
            int height = getItem(1,0)->getInt() - c.ry();

            if (sign(width) == -1)
            {
                setItem(0,0, new Cell(QString::number(c.rx())));
                setItem(2,0, new Cell(QString::number(abs(width))));
            }
            else
            {
                setItem(2,0, new Cell(QString::number(width)));
            }

            if (sign(height) == -1)
            {
                setItem(1,0, new Cell(QString::number(c.ry())));
                setItem(3,0, new Cell(QString::number(abs(height))));
            }
            else
            {
                setItem(3,0, new Cell(QString::number(height)));
            }
        }

        break;
    }
    }
}

void Table::keyPressEvent(QKeyEvent * event)
{
    // Delete's all the selected rows for use with polygons only
    if (event->key() == Qt::Key_Delete && mType == PolyEdit::Polygon)
    {
        QList<QTableWidgetItem *> selected = selectedItems();

        int lastRow = -1;

        for(auto i : selected)
        {
            int r = i->row();

            if(lastRow == -1)
            {
                lastRow = r;
                removeRow(r);
            }
            else if(lastRow != r)
            {
                removeRow(r);
            }
        }

        // Ensure we have atleast one row
        if (rowCount() == 0)
            insertRow(rowCount());
    }
}

PolyEdit::Shape Table::getType() const
{
    return mType;
}


void Table::render()
{
    mMask->render();
}

void Table::render(Coordinate mousePos)
{
    mMask->render(mousePos);
}

void Table::removeRow(int row)
{
    QTableWidget::removeRow(row);
    mMask->deletec(row);
}

void Table::setMaskType(PolyEdit::Shape type)
{
    isReady = false;

    clear();
    mMask->clear();

    switch (type)
    {
    case PolyEdit::Polygon:
    {
        setColumnCount(2);
        setRowCount(1);
        setHorizontalHeaderItem(0, new Cell("X"));
        setHorizontalHeaderItem(1, new Cell("Y"));
        break;
    }
    case PolyEdit::Circle:
    {
        setColumnCount(1);
        setRowCount(3);
        setHorizontalHeaderItem(0, new Cell("Circle"));
        setVerticalHeaderItem(0,new Cell("X"));
        setVerticalHeaderItem(1,new Cell("Y"));
        setVerticalHeaderItem(2,new Cell("Radius"));
        break;
    }
    case PolyEdit::Box:
    {
        setColumnCount(1);
        setRowCount(4);
        setHorizontalHeaderItem(0, new Cell("Box"));
        setVerticalHeaderItem(0,new Cell("Left"));
        setVerticalHeaderItem(1,new Cell("Top"));
        setVerticalHeaderItem(2,new Cell("Width"));
        setVerticalHeaderItem(3,new Cell("Height"));
        break;
    }
    }

    clearContents();

    mType = type;
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    mMask->setType(type);

    isReady = true;
}

std::size_t Table::size() const
{
    return mMask->size();
}

const Coordinate Table::getc(int i) const
{
    return mMask->getc(i);
}

int Table::getRadius() const
{
    return mMask->getRadius();
}

void Table::clearContents()
{
    // We need to create new cells upon clearing
    for(int i=0; i < rowCount(); i++)
    {
        for(int j=0; j < columnCount(); j++)
            setItem(i, j, new Cell(""));
    }
}
