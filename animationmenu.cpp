#include "animationmenu.h"
#include "animationframe.h"
#include "qactions.h"

AnimationMenu::AnimationMenu(AnimationFrame *parent) : QMenuBar(parent)
{
    fileMenu = new QMenu("File");
    fileMenu->addAction(parent->actions()->aOpen);
    fileMenu->addSeparator();
    fileMenu->addAction(parent->actions()->aSave);
    //fileMenu->addAction(parent->actions()->saveAs);
    addMenu(fileMenu);

    editMenu = new QMenu("Edit");
    editMenu->addAction(parent->actions()->aCut);
    editMenu->addAction(parent->actions()->aCopy);
    editMenu->addAction(parent->actions()->aPaste);
    addMenu(editMenu);

    viewMenu = new QMenu("View");
    viewMenu->addAction(parent->actions()->aZoomIn);
    viewMenu->addAction(parent->actions()->aZoomOut);
    viewMenu->addAction(parent->actions()->aZoom100);
    addMenu(viewMenu);
}

