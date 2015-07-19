#include "imagebounds.h"

#include <QLabel>
#include <QGridLayout>

ImageBounds::ImageBounds(QWidget *parent) : QWidget(parent)
{
    QGridLayout* layout = new QGridLayout();
    setLayout(layout);

    layout->addWidget(new QLabel("Rows: ", this, 0),0,0);
    layout->addWidget(new QLabel("Columns: ", this, 0),1,0);
    layout->addWidget(new QLabel("X Seperation: ", this, 0),2,0);
    layout->addWidget(new QLabel("Y Seperation: ", this, 0),3,0);

    spnRows = new QSpinBox(this);
    spnRows->setMinimum(1);

    spnColumns = new QSpinBox(this);
    spnColumns->setMinimum(1);

    spnX = new QSpinBox(this);
    spnY = new QSpinBox(this);

    layout->addWidget(spnRows,0,1);
    layout->addWidget(spnColumns,1,1);
    layout->addWidget(spnX,2,1);
    layout->addWidget(spnY,3,1);
}

