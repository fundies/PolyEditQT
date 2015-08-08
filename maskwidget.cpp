#include "maskwidget.h"
#include "maskcombobox.h"

#include <QLayout>
#include <QFileDialog>

MaskWidget::MaskWidget(QWidget *parent, Canvas* canvas) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout;
    setLayout(layout);

    // this->table->mask needs access to canvas?
    mTable = new Table(this, canvas);

    MaskComboBox* combo = new MaskComboBox(mTable);
    QPushButton *mExport = new QPushButton("Export SVG", this);

    layout->addWidget(combo);
    layout->addWidget(mTable);
    layout->addWidget(mExport);

    connect(mExport, &QPushButton::pressed, this, &MaskWidget::exportSVG);
}

MaskWidget::MaskWidget(QWidget *parent, Canvas* canvas, Table* table) : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout;
    setLayout(layout);

    // this->table->mask needs access to canvas?
    mTable = table;

    MaskComboBox* combo = new MaskComboBox(mTable);
    combo->setType(table->getType());

    QPushButton *mExport = new QPushButton("Export SVG", this);

    layout->addWidget(combo);
    layout->addWidget(mTable);
    layout->addWidget(mExport);

    connect(mExport, &QPushButton::pressed, this, &MaskWidget::exportSVG);
}

Table *MaskWidget::table() const
{
    return mTable;
}
void MaskWidget::setTable(Table *table)
{
    mTable = table;
}
QString MaskWidget::name() const
{
    return mName;
}

void MaskWidget::setName(const QString &name)
{
    mName = name;
}

void MaskWidget::exportSVG()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    "untitled.svg",
                               tr("SVG (*.svg)"),  0, QFileDialog::DontUseNativeDialog);
    mTable->exportSVG(fileName);
}
