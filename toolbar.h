#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QToolBar>
#include <QSpinBox>

class MainWindow;

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

    QSpinBox *gridX;
    QSpinBox *gridY;
    QSpinBox *frame;
    QDoubleSpinBox *speed;

};

#endif // TOOLBAR_H
