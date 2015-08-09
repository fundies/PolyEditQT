#include <QPushButton>
#include <QTabBar>

#include "masktab.h"
#include "maskwidget.h"
#include "mainwindow.h"

MaskTab::MaskTab(MainWindow *parent, Canvas *canvas) : QTabWidget(parent)
{
    numMask = 0;
    deleting = false;

    mTable = new QList<Table *>();

    mParent = parent;
    mCanvas = canvas;

    setTabsClosable(true);

    MaskWidget *widget = new MaskWidget(this, mCanvas);
    widget->setName("Mask 0");
    QTabWidget::insertTab(0, widget, "Mask 0");
    mTable->append(widget->table());
    mParent->setMask(widget->table());

    // Tab to add tabs
    QTabWidget::addTab(new QWidget(this), "");
    tabBar()->setTabIcon(1, QIcon(":/img/add.png"));

    connect(this, &QTabWidget::tabCloseRequested, this, &MaskTab::closeTab);
    connect(this, &QTabWidget::currentChanged, this, &MaskTab::currentChanged);

    // Disable closing it
    tabBar()->tabButton(1, QTabBar::RightSide)->resize(0, 0);
}

MaskTab::~MaskTab()
{
    //delete mTable;
}

void MaskTab::addTab(Table *table)
{
    numMask++;
    QString name = "Mask " + QString::number(numMask);

    MaskWidget *widget = new MaskWidget(this, mCanvas, table);
    widget->setName(name);
    QTabWidget::insertTab(count()-1, widget, name);
    mTable->append(widget->table());

    setCurrentIndex(count()-2);
}

void MaskTab::addTab()
{
    numMask++;
    QString name = "Mask " + QString::number(numMask);

    MaskWidget *widget = new MaskWidget(this, mCanvas);
    QTabWidget::insertTab(count()-1, widget, name);
    widget->setName(name);
    mTable->append(widget->table());
}

void MaskTab::closeTab(int index)
{
    deleting = true;
    mTable->removeAll(static_cast<MaskWidget *>(widget(index))->table());
    removeTab(index);

    if(count() <= 1)
    {
        addTab();
        setCurrentIndex(0);
        mParent->setMask(static_cast<MaskWidget *>(currentWidget())->table());
    }
}


void MaskTab::currentChanged(int index)
{
    if (index == count()-1 && count() > 1 && !deleting)
    {
        addTab();
        setCurrentIndex(count()-2);
        mParent->setMask(static_cast<MaskWidget *>(currentWidget())->table());
    }
    else if (deleting)
    {
        setCurrentIndex(0);
        deleting = false;
        mParent->setMask(static_cast<MaskWidget *>(currentWidget())->table());
    }
}


QList<Table *> *MaskTab::table() const
{
    return mTable;
}

QTabBar *MaskTab::tabBar()
{
    return QTabWidget::tabBar();
}

Table *MaskTab::currentTable()
{
    return static_cast<MaskWidget *>(currentWidget())->table();
}

void MaskTab::replaceCurrentTable(Table *t)
{
    int current = currentIndex();
    QString name = static_cast<MaskWidget *>(currentWidget())->name();

    MaskWidget *widget = new MaskWidget(this, mCanvas, t);
    widget->setName(name);
    deleting = true;
    QTabWidget::removeTab(current);
    QTabWidget::insertTab(current, widget, name);
    mTable->replace(current, widget->table());
    setCurrentIndex(current);
}

void MaskTab::clear()
{
    deleting = true;

    QTabWidget::clear();

    MaskWidget *widget = new MaskWidget(this, mCanvas);
    widget->setName("Mask 0");
    QTabWidget::insertTab(0, widget, "Mask 0");
    mTable->append(widget->table());
    mParent->setMask(widget->table());

    // Tab to add tabs
    QTabWidget::addTab(new QWidget(this), "");
    tabBar()->setTabIcon(1, QIcon(":/img/add.png"));
    tabBar()->tabButton(1, QTabBar::RightSide)->resize(0, 0);
}
