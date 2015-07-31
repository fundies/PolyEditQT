#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "mainwindow.h"
#include <QToolBar>
#include <QSpinBox>

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

    QSpinBox* gridX;
    QSpinBox* gridY;
    QSpinBox* frame;
    QDoubleSpinBox* speed;

};

#endif // TOOLBAR_H
