#include "yesnowidget.h"

#include <QHBoxLayout>
#include <QDebug>

YesNoWidget::YesNoWidget(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* layout = new QHBoxLayout;
    setLayout(layout);

    mYes = new QPushButton("Subimt", this);
    mNo = new QPushButton("Cancel", this);

    layout->addWidget(mYes);
    layout->addWidget(mNo);

    connect(mYes, &QPushButton::pressed, this, &YesNoWidget::yesPressed);
    connect(mNo, &QPushButton::pressed, this, &YesNoWidget::noPressed);
}

void YesNoWidget::yesPressed()
{
    emit yes();
}

void YesNoWidget::noPressed()
{
    emit no();
}
