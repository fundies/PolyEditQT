#ifndef MASKWIDGET_H
#define MASKWIDGET_H

#include <QWidget>

class Table;
class Canvas;

/**
 * @brief The MaskWidget class holds tools for editing masks
 */
class MaskWidget : public QWidget
{
    Q_OBJECT
public:

    /**
     * @brief MaskWidget constructor
     * @param parent parent
     * @param canvas canvas
     */
    MaskWidget(QWidget *parent, Canvas *canvas);

    /**
     * @brief MaskWidget constructor overload
     * @param parent parent
     * @param canvas canvas
     * @param table table
     */
    MaskWidget(QWidget *parent, Canvas *canvas, Table *table);

    /**
     * @brief table returns cer to table
     * @return table*
     */
    Table *table() const;

    /**
     * @brief setTable set the table
     * @param table table
     */
    void setTable(Table *table);

    /**
     * @brief name current tab's name
     * @return name
     */
    QString name() const;

    /**
     * @brief setName set the current tab's name
     * @param name name
     */
    void setName(const QString &name);

private slots:

    /**
     * @brief exportSVG export SVG
     */
    void exportSVG();

private:

    Table  *mTable;
    QString mName;
};

#endif // MASKWIDGET_H
