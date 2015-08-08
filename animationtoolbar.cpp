#include "animationtoolbar.h"
#include "animationframe.h"

#include <QSpinBox>
#include <QDoubleSpinBox>

AnimationToolBar::AnimationToolBar(AnimationFrame *parent)
{
    addAction(parent->actions()->aOpen);

    addSeparator();

    addAction(parent->actions()->aAddBlank);
    addAction(parent->actions()->aDeleteImg);

    addSeparator();

    addAction(parent->actions()->aCut);
    addAction(parent->actions()->aCopy);
    addAction(parent->actions()->aPaste);

    addSeparator();


    addAction(parent->actions()->aZoomIn);
    addAction(parent->actions()->aZoomOut);
    addAction(parent->actions()->aZoom100);

    addSeparator();

    addAction(parent->actions()->aPlay);
    addAction(parent->actions()->aPause);
    addAction(parent->actions()->aStop);

    addSeparator();

    speed = new QDoubleSpinBox(parent);
    speed->setValue(0.03);
    speed->setPrefix("Speed: ");
    speed->setDecimals(4);
    speed->setSingleStep(0.0001);
    speed->setAccelerated(true);
    addWidget(speed);

    addSeparator();

    frame = new QSpinBox(parent);
    frame->setMaximum(0);
    frame->setPrefix("Frame: ");
    frame->setAccelerated(true);
    addWidget(frame);
}

