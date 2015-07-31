#ifndef MASKTAB_H
#define MASKTAB_H

#include <QTabWidget>
#include <QTabBar>

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
    QMap<int, Table *> *table() const;

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

    QMap<int, Table *> *mTable;
    Canvas* mCanvas;
    MainWindow* mParent;
};

#endif // MASKTAB_H
