#ifndef QACTIONS_H
#define QACTIONS_H

#include <QAction>

/**
 * @brief The QActions class gets all the action
 */
class QActions
{
public:
    QActions(QWidget *parent);
    QAction* open;
    QAction* save;
    QAction* saveAs;
    QAction* quit;
    QAction* cut;
    QAction* copy;
    QAction* paste;
    QAction* viewGrid;
    QAction* viewSprite;
    QAction* viewSymmetry;
    QAction* zoomIn;
    QAction* zoomOut;
    QAction* zoom100;
    QAction* play;
    QAction* pause;
    QAction* stop;
    QAction* about;
};

#endif // QACTIONS_H
