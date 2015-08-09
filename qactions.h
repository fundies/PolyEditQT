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
    QAction *aNew;
    QAction *aOpen;
    QAction *aSave;
    QAction *aSaveAs;
    QAction *aQuit;
    QAction *aCut;
    QAction *aCopy;
    QAction *aPaste;
    QAction *aSprite;
    QAction *aAnimation;
    QAction *aViewGrid;
    QAction *aViewSprite;
    QAction *aViewSymmetry;
    QAction *aZoomIn;
    QAction *aZoomOut;
    QAction *aZoom100;
    QAction *aPlay;
    QAction *aPause;
    QAction *aStop;
    QAction *aAbout;
    QAction *aAddBlank;
    QAction *aDeleteImg;
};

#endif // QACTIONS_H
