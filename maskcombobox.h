#ifndef MASKCOMBOBOX_H
#define MASKCOMBOBOX_H

#include "table.h"
#include <QComboBox>

/**
 * @brief The MaskComboBox class
 */
class MaskComboBox : public QComboBox
{
    Q_OBJECT
public:
    /**
     * @brief MaskComboBox constructor
     * @param parent parent
     */
    MaskComboBox(Table *parent);

private slots:

    /**
     * @brief currentIndexChanged selection changed
     * @param index new index
     */
    void currentIndexChanged(int index);

private:
    Table* mParent;
};

#endif // MASKCOMBOBOX_H
