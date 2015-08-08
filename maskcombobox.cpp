#include "maskcombobox.h"
#include <iostream>
#include <QCheckBox>
#include <QHBoxLayout>

MaskComboBox::MaskComboBox(Table *parent) : QWidget(parent)//QComboBox(parent)
{
    //mVisible = true;
    QHBoxLayout *mainLayout = new QHBoxLayout;
    setLayout(mainLayout);

    mainLayout->setMargin(0);

    mCombo = new QComboBox(this);
    QCheckBox *mVisible = new QCheckBox("Visible", this);
    mVisible->setChecked(true);
    mainLayout->addWidget(mCombo);
    mainLayout->addWidget(mVisible);

    mCombo->addItem("Polygon");
    mCombo->addItem("Circle");
    mCombo->addItem("Box");

    connect(mCombo, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &MaskComboBox::currentIndexChanged);
    connect(mVisible, &QCheckBox::stateChanged, this, &MaskComboBox::setRender);

    mParent = parent;
}

void MaskComboBox::currentIndexChanged(int index)
{
    // Todo: are you sure?

    // Cast from int to PolyEdit::Shape typedef for readability
    mParent->setMaskType(static_cast<PolyEdit::Shape>(index));
}

void MaskComboBox::setType(PolyEdit::Shape type)
{
    mCombo->setCurrentIndex(type);
}

void MaskComboBox::setRender(bool state)
{
    mParent->setRender(state);
}
