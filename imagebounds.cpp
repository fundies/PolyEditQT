#include "imagebounds.h"

#include <QLabel>
#include <QGridLayout>
#include <QPushButton>

ImageBounds::ImageBounds(QWidget *parent) : QWidget(parent)
{
    QGridLayout* layout = new QGridLayout();
    layout->setSizeConstraint(QLayout::SetFixedSize);

    ///Todo: make this align top
    layout->setAlignment(Qt::AlignTop);
    setLayout(layout);

    layout->addWidget(new QLabel("Rows: ", this, 0),0,0);
    layout->addWidget(new QLabel("Columns: ", this, 0),1,0);
    layout->addWidget(new QLabel("X Seperation: ", this, 0),2,0);
    layout->addWidget(new QLabel("Y Seperation: ", this, 0),3,0);

    spnRows = new QSpinBox(this);
    spnColumns = new QSpinBox(this);
    spnXsep = new QSpinBox(this);
    spnYsep = new QSpinBox(this);

    layout->addWidget(spnRows,0,1);
    layout->addWidget(spnColumns,1,1);
    layout->addWidget(spnXsep,2,1);
    layout->addWidget(spnYsep,3,1);

    layout->addWidget(new QPushButton("Import", this), 4,0);
    layout->addWidget(new QPushButton("Cancel", this), 4,1);
}

