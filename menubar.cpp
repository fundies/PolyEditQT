#include "menubar.h"

MenuBar::MenuBar(MainWindow *parent) : QMenuBar(parent)
{
    fileMenu = new QMenu("File");
    fileMenu->addAction(parent->actions()->open);
    fileMenu->addSeparator();
    fileMenu->addAction(parent->actions()->save);
    //fileMenu->addAction(parent->actions()->saveAs);
    fileMenu->addSeparator();
    fileMenu->addAction(parent->actions()->quit);
    addMenu(fileMenu);

    editMenu = new QMenu("Edit");
    editMenu->addAction(parent->actions()->cut);
    editMenu->addAction(parent->actions()->copy);
    editMenu->addAction(parent->actions()->paste);
    editMenu->addSeparator();
    //editMenu->addAction(parent->actions()->"Sprite");
    //editMenu->addAction(parent->actions()->"Animation");
    addMenu(editMenu);

    viewMenu = new QMenu("View");
    viewMenu->addAction(parent->actions()->viewGrid);
    viewMenu->addAction(parent->actions()->viewSprite);
    viewMenu->addAction(parent->actions()->viewSymmetry);
    viewMenu->addSeparator();
    viewMenu->addAction(parent->actions()->zoomIn);
    viewMenu->addAction(parent->actions()->zoomOut);
    viewMenu->addAction(parent->actions()->zoom100);
    addMenu(viewMenu);

    helpMenu = new QMenu("Help");
    helpMenu->addAction(parent->actions()->about);
    addMenu(helpMenu);
}

MenuBar::~MenuBar()
{
    delete fileMenu;
    delete editMenu;
    delete viewMenu;
    delete helpMenu;
}
