#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenuBar>
#include "mainwindow.h"

/**
 * @brief The MenuBar class
 */
class MenuBar: public QMenuBar
{
public:
    /**
     * @brief MenuBar constructor
     * @param parent parent
     */
    MenuBar(MainWindow* parent);

    ~MenuBar();

private:
    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* viewMenu;
    QMenu* helpMenu;
};

#endif // MENUBAR_H
