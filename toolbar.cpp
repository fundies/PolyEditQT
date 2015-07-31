#include "toolbar.h"
#include <QSpinBox>

/// Todo: make this look nicer on small sizes?

ToolBar::ToolBar(MainWindow *parent) : QToolBar(parent)
{
    addAction(parent->actions()->aOpen);

    addSeparator();

    addAction(parent->actions()->aSave);
    addAction(parent->actions()->aSaveAs);

    addSeparator();

    //addAction(parent->actions()->aCut);
    //addAction(parent->actions()->aCopy);
    //addAction(parent->actions()->aPaste);

    //addSeparator();

    addAction(parent->actions()->aViewGrid);

    addSeparator();

    gridX = new QSpinBox(parent);
    gridX->setPrefix("X: ");
    gridX->setValue(16);
    addWidget(gridX);
    addSeparator();

    gridY = new QSpinBox(parent);
    gridY->setPrefix("Y: ");
    gridY->setValue(16);
    addWidget(gridY);

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
    speed->setPrefix("Speed: ");
    speed->setDecimals(3);
    speed->setSingleStep(0.001);
    speed->setAccelerated(true);
    addWidget(speed);

    addSeparator();

    frame = new QSpinBox(parent);
    frame->setPrefix("Frame: ");
    addWidget(frame);
}

