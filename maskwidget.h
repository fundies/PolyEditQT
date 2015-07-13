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

    /**
     * @brief table returns cer to table
     * @return table*
     */
    Table *table() const;

private:
        Table*  mTable;
};

#endif // MASKWIDGET_H
