#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "mainwindow.h"
#include <QToolBar>

/**
 * @brief The ToolBar class
 */
class ToolBar : public QToolBar
{
public:
    /**
     * @brief ToolBar constructor
     * @param parent parent
     */
    ToolBar(MainWindow *parent);
};

#endif // TOOLBAR_H
