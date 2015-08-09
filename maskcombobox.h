#ifndef MASKCOMBOBOX_H
#define MASKCOMBOBOX_H

#include <QComboBox>

#include "shapes.h"

class Table;

/**
 * @brief The MaskComboBox class
 */
class MaskComboBox : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief MaskComboBox constructor
     * @param parent parent
     */
    MaskComboBox(Table *parent);

    /**
     * @brief setType sets the mask type
     * @param type mask type
     */
    void setType(PolyEdit::Shape type);

private slots:

    /**
     * @brief currentIndexChanged selection changed
     * @param index new index
     */
    void currentIndexChanged(int index);

    /**
     * @brief setRender draw stuff?
     * @param state yes/no
     */
    void setRender(bool state);

private:

    Table *mParent;
    QComboBox *mCombo;
};

#endif // MASKCOMBOBOX_H
