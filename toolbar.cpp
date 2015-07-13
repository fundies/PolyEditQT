#include "toolbar.h"
#include <QSpinBox>

/// Todo: make this look nicer on small sizes?

ToolBar::ToolBar(MainWindow *parent) : QToolBar(parent)
{
    addAction(parent->actions()->open);

    addSeparator();

    addAction(parent->actions()->save);
    addAction(parent->actions()->saveAs);

    addSeparator();

    addAction(parent->actions()->cut);
    addAction(parent->actions()->copy);
    addAction(parent->actions()->paste);

    addSeparator();

    addAction(parent->actions()->viewGrid);

    addSeparator();

    QSpinBox* gridX = new QSpinBox(parent);
    gridX->setPrefix("X: ");
    addWidget(gridX);
    addSeparator();

    QSpinBox* gridY = new QSpinBox(parent);
    gridY->setPrefix("Y: ");
    addWidget(gridY);

    addSeparator();

    addAction(parent->actions()->zoomIn);
    addAction(parent->actions()->zoomOut);
    addAction(parent->actions()->zoom100);

    addSeparator();

    QDoubleSpinBox* speed = new QDoubleSpinBox(parent);
    speed->setPrefix("Speed: ");
    speed->setDecimals(3);
    speed->setSingleStep(0.001);
    speed->setAccelerated(true);
    addWidget(speed);

    addSeparator();

    addAction(parent->actions()->play);
    addAction(parent->actions()->pause);
    addAction(parent->actions()->stop);
    addSeparator();

    QSpinBox* frame = new QSpinBox(parent);
    frame->setPrefix("Frame: ");
    addWidget(frame);
}

