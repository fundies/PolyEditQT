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

    addAction(parent->actions()->aCut);
    addAction(parent->actions()->aCopy);
    addAction(parent->actions()->aPaste);

    addSeparator();

    addAction(parent->actions()->aViewGrid);

    addSeparator();

    QSpinBox* gridX = new QSpinBox(parent);
    gridX->setPrefix("X: ");
    addWidget(gridX);
    addSeparator();

    QSpinBox* gridY = new QSpinBox(parent);
    gridY->setPrefix("Y: ");
    addWidget(gridY);

    addSeparator();

    addAction(parent->actions()->aZoomIn);
    addAction(parent->actions()->aZoomOut);
    addAction(parent->actions()->aZoom100);

    addSeparator();

    QDoubleSpinBox* speed = new QDoubleSpinBox(parent);
    speed->setPrefix("Speed: ");
    speed->setDecimals(3);
    speed->setSingleStep(0.001);
    speed->setAccelerated(true);
    addWidget(speed);

    addSeparator();

    addAction(parent->actions()->aPlay);
    addAction(parent->actions()->aPause);
    addAction(parent->actions()->aStop);
    addSeparator();

    QSpinBox* frame = new QSpinBox(parent);
    frame->setPrefix("Frame: ");
    addWidget(frame);
}

