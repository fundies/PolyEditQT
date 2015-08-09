#include <QSpinBox>

#include "mainwindow.h"
#include "toolbar.h"
#include "qactions.h"

ToolBar::ToolBar(MainWindow *parent) : QToolBar(parent)
{
    addAction(parent->actions()->aOpen);

    addSeparator();

    addAction(parent->actions()->aSave);
    addAction(parent->actions()->aSaveAs);

    addSeparator();

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

