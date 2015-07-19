#include "menubar.h"

MenuBar::MenuBar(MainWindow *parent) : QMenuBar(parent)
{
    fileMenu = new QMenu("File");
    fileMenu->addAction(parent->actions()->aOpen);
    fileMenu->addSeparator();
    fileMenu->addAction(parent->actions()->aSave);
    //fileMenu->addAction(parent->actions()->saveAs);
    fileMenu->addSeparator();
    fileMenu->addAction(parent->actions()->aQuit);
    addMenu(fileMenu);

    editMenu = new QMenu("Edit");
    editMenu->addAction(parent->actions()->aCut);
    editMenu->addAction(parent->actions()->aCopy);
    editMenu->addAction(parent->actions()->aPaste);
    editMenu->addSeparator();
    //editMenu->addAction(parent->actions()->"Sprite");
    //editMenu->addAction(parent->actions()->"Animation");
    addMenu(editMenu);

    viewMenu = new QMenu("View");
    viewMenu->addAction(parent->actions()->aViewGrid);
    viewMenu->addAction(parent->actions()->aViewSprite);
    viewMenu->addAction(parent->actions()->aViewSymmetry);
    viewMenu->addSeparator();
    viewMenu->addAction(parent->actions()->aZoomIn);
    viewMenu->addAction(parent->actions()->aZoomOut);
    viewMenu->addAction(parent->actions()->aZoom100);
    addMenu(viewMenu);

    helpMenu = new QMenu("Help");
    helpMenu->addAction(parent->actions()->aAbout);
    addMenu(helpMenu);
}

MenuBar::~MenuBar()
{
    delete fileMenu;
    delete editMenu;
    delete viewMenu;
    delete helpMenu;
}
