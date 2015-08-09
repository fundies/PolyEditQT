#ifndef CELL_H
#define CELL_H

#include <QTableWidgetItem>

/**
 * @brief The Cell class
 */
class Cell : public QTableWidgetItem
{

public:
    /**
     * @brief Cell Default Constructor
     */
    Cell();

    /**
     * @brief Cell
     * @param text text
     * @param type type
     */
    Cell(const QString &text, int type = Type);

    /**
     * @brief setText overide for QTableWidgetItem::setText
     * which ensures input is an integer
     * @param text input text
     */
    void setText(const QString &text);

    /**
     * @brief getInt returns Cell's content as an integer
     * @return cell's content
     */
    int getInt();

private:
    QString last;
};

#endif // CELL_H
