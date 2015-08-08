#ifndef MASKWIDGET_H
#define MASKWIDGET_H

#include <QWidget>

#include "table.h"
#include "canvas.h"

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
    MaskWidget(QWidget *parent, Canvas* canvas, Table* table);

    /**
     * @brief table returns cer to table
     * @return table*
     */
    Table *table() const;
    void setTable(Table *table);

    QString name() const;
    void setName(const QString &name);

private:
    Table*  mTable;\
    QString mName;

private slots:
        void exportSVG();
};

#endif // MASKWIDGET_H
