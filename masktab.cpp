#include "masktab.h"

#include <QPushButton>
#include <iostream>

MaskTab::MaskTab(MainWindow *parent, Canvas* canvas) : QTabWidget(parent)
{
    mTable = new QMap<int, Table*>;

    mParent = parent;
    mCanvas = canvas;

    setTabsClosable(true);
    //setMovable(true);

    addTab();

    // Default to mask 0
    mParent->setMask(mTable->value(0));

    connect(this, &QTabWidget::tabCloseRequested, this, &MaskTab::closeTab);
    connect(this, &QTabWidget::currentChanged, this, &MaskTab::currentChanged);

    // Tab to add tabs
    QTabWidget::addTab(new QWidget(this), "+");

    // Disable closing it
    tabBar()->tabButton(1, QTabBar::RightSide)->resize(0, 0);
}

MaskTab::~MaskTab()
{
    delete mTable;
}

void MaskTab::addTab()
{
    QString name = "Mask " + QString::number(count());

    MaskWidget* widget = new MaskWidget(this, mCanvas);
    QTabWidget::insertTab(count()-1, widget, name);
    mTable->insert(count()-1, widget->table());
}

void MaskTab::closeTab(int index)
{
    /// Todo: fix this
   removeTab(index);
}


void MaskTab::currentChanged(int index)
{
    /// Todo: fix this
    if (index == count()-1 && count() > 1)
    {
        addTab();
        setCurrentIndex(count()-2);
    }

    mParent->setMask(mTable->value(currentIndex()));
}


QMap<int, Table *> *MaskTab::table() const
{
    return mTable;
}

QTabBar* MaskTab::tabBar()
{
  return QTabWidget::tabBar();
}
