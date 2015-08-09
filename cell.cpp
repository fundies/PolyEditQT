#include "cell.h"

Cell::Cell() : QTableWidgetItem()
{
    // nothing to do here
}

Cell::Cell(const QString &text, int type) : QTableWidgetItem(text, type)
{
    last = text;
}

void Cell::setText(const QString &text)
{
    /* Update the cell's text only if it is an integer
     * revert to previous content otherwise
    */
    bool isInteger;
    text.toInt(&isInteger,10);

    if (!isInteger)
        QTableWidgetItem::setText(last);
    else
        last = text;
}

int Cell::getInt()
{
    bool isInteger;
    int x = text().toInt(&isInteger,10);

    return x;
}
