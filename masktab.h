#ifndef MASKTAB_H
#define MASKTAB_H

#include <QTabWidget>
#include <QList>

class MainWindow;
class Canvas;
class Table;

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
    QTabBar *tabBar();

    /**
     * @brief table return's a cer to map of tables[]
     * @return tables[]
     */
    QList<Table *> *table() const;

    /**
     * @brief currentTable returns the current table
     * @return pointer to table
     */
    Table *currentTable();

    /**
     * @brief addTab adds a new tab/mask
     * @param table table to use
     */
    void addTab(Table *table);

    /**
     * @brief replaceCurrentTable replaces a table
     * @param t table
     */
    void replaceCurrentTable(Table *t);

    /**
     * @brief clear remove all tabs
     */
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

    QList<Table *> *mTable;
    Canvas *mCanvas;
    MainWindow *mParent;
    bool deleting;
    int numMask;
};

#endif // MASKTAB_H
