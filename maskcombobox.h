#ifndef MASKCOMBOBOX_H
#define MASKCOMBOBOX_H

#include "table.h"
#include <QComboBox>

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


    void setType(PolyEdit::Shape type);

private slots:

    /**
     * @brief currentIndexChanged selection changed
     * @param index new index
     */
    void currentIndexChanged(int index);
    void setRender(bool state);

private:
    Table* mParent;
    QComboBox *mCombo;
};

#endif // MASKCOMBOBOX_H
