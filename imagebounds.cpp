#include "imagebounds.h"

#include <QLabel>
#include <QGridLayout>

ImageBounds::ImageBounds(QWidget *parent) : QWidget(parent)
{
    QGridLayout *layout = new QGridLayout();
    layout->setSizeConstraint(QLayout::SetFixedSize);

    ///Todo: make this align top
    layout->setAlignment(Qt::AlignTop);
    setLayout(layout);

    btnAlpha = new QPushButton("Alpha", this);
    layout->addWidget(btnAlpha, 0,1);
    layout->addWidget(new QLabel("Rows: ", this, 0),1,0);
    layout->addWidget(new QLabel("Columns: ", this, 0),2,0);
    layout->addWidget(new QLabel("X Seperation: ", this, 0),3,0);
    layout->addWidget(new QLabel("Y Seperation: ", this, 0),4,0);

    spnRows = new QSpinBox(this);
    spnRows->setValue(1);
    spnColumns = new QSpinBox(this);
    spnColumns->setValue(1);
    spnXsep = new QSpinBox(this);
    spnYsep = new QSpinBox(this);

    layout->addWidget(spnRows,1,1);
    layout->addWidget(spnColumns,2,1);
    layout->addWidget(spnXsep,3,1);
    layout->addWidget(spnYsep,4,1);

    btnImport = new QPushButton("Import", this);
    layout->addWidget(btnImport, 5,0);
    layout->addWidget(new QPushButton("Cancel", this), 5,1);
}

