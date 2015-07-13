#include "maskwidget.h"
#include "maskcombobox.h"

#include <QLayout>

MaskWidget::MaskWidget(QWidget *parent, Canvas* canvas) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout;
    setLayout(layout);

    // this->table->mask needs access to canvas?
    mTable = new Table(this, canvas);

    MaskComboBox* combo = new MaskComboBox(mTable);

    layout->addWidget(combo);
    layout->addWidget(mTable);
}

Table *MaskWidget::table() const
{
    return mTable;
}


