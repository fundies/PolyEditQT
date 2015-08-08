#ifndef MASKTAB_H
#define MASKTAB_H

#include <QTabWidget>
//#include <QTabBar>
#include <QList>

#include "mainwindow.h"
#include "maskwidget.h"

/**
 * @brief The MaskTab class
 */
class MaskTab : public QTabWidget
{
    Q_OBJECT
public:

    /**
     * @brief MaskTab constructor
     * @param parent parent
     * @param canvas canvas
     */
    MaskTab(MainWindow *parent, Canvas *canvas);
    ~MaskTab();

    /**
     * @brief tabBar override tabBar() to enable colored headers
     * @return QTabBar
     */
    QTabBar* tabBar();

    /**
     * @brief table return's a cer to map of tables[]
     * @return tables[]
     */
    QList<Table *> *table() const;

    Table* currentTable();

    void addTab(Table* table);
    void replaceCurrentTable(Table *t);
    void clear();

public slots:

    /**
     * @brief closeTab tab closed event
     * @param index index
     */
    void closeTab(int index);

    /**
     * @brief currentChanged tab changed event
     * @param index new tab
     */
    void currentChanged(int index);

private:

    /**
     * @brief addTab override for adding tabs
     */
    void addTab();

    //QMap<QString, Table *> *mTable;
    QList<Table*> *mTable;

    Canvas* mCanvas;
    MainWindow* mParent;

    bool deleting;
    int numMask;
};

#endif // MASKTAB_H
