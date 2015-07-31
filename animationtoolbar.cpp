#include "animationtoolbar.h"
#include "animationframe.h"

AnimationToolBar::AnimationToolBar(AnimationFrame *parent)
{
    addAction(parent->actions()->aOpen);

    addSeparator();

    addAction(parent->actions()->aSave);
    addAction(parent->actions()->aSaveAs);

    addSeparator();

    addAction(parent->actions()->aCut);
    addAction(parent->actions()->aCopy);
    addAction(parent->actions()->aPaste);

    addSeparator();


    addAction(parent->actions()->aZoomIn);
    addAction(parent->actions()->aZoomOut);
    addAction(parent->actions()->aZoom100);

    addSeparator();

    /*speed = new QDoubleSpinBox(parent);
    speed->setPrefix("Speed: ");
    speed->setDecimals(3);
    speed->setSingleStep(0.001);
    speed->setAccelerated(true);
    addWidget(speed);*/

    addSeparator();

    addAction(parent->actions()->aPlay);
    addAction(parent->actions()->aPause);
    addAction(parent->actions()->aStop);
}

