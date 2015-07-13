#include "maskcombobox.h"
#include <iostream>

MaskComboBox::MaskComboBox(Table *parent) : QComboBox(parent)
{
    addItem("Polygon");
    addItem("Circle");
    addItem("Box");

    connect(this, static_cast<void (MaskComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &MaskComboBox::currentIndexChanged);

    mParent = parent;
}

void MaskComboBox::currentIndexChanged(int index)
{
    // Todo: are you sure?

    // Cast from int to PolyEdit::Shape typedef for readability
    mParent->setMaskType(static_cast<PolyEdit::Shape>(index));
}
