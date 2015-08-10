#-------------------------------------------------
#
# Project created by QtCreator 2015-06-01T13:39:58
#
#-------------------------------------------------

QT  += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PolyEditQT
TEMPLATE = app

win32:INCLUDEPATH += $$_PRO_FILE_PWD_/libs/include

SOURCES += main.cpp\
        mainwindow.cpp \
    canvas.cpp \
    table.cpp \
    qactions.cpp \
    menubar.cpp \
    toolbar.cpp \
    grid.cpp \
    cell.cpp \
    mask.cpp \
    maskwidget.cpp \
    maskcombobox.cpp \
    coordinate.cpp \
    utility.cpp \
    masktab.cpp \
    imagebounds.cpp \
    glwindow.cpp \
    sprite.cpp \
    checkers.cpp \
    spritemodel.cpp \
    animationframe.cpp \
    animationview.cpp \
    animationtoolbar.cpp \
    imageframe.cpp \
    animationmenu.cpp \
    yesnowidget.cpp \
    svgreader.cpp \
    aboutframe.cpp \
    shapes.cpp

HEADERS  += mainwindow.h \
    canvas.h \
    table.h \
    qactions.h \
    menubar.h \
    toolbar.h \
    grid.h \
    cell.h \
    mask.h \
    maskwidget.h \
    maskcombobox.h \
    coordinate.h \
    utility.h \
    masktab.h \
    imagebounds.h \
    glwindow.h \
    sprite.h \
    checkers.h \
    spritemodel.h \
    animationframe.h \
    animationview.h \
    animationtoolbar.h \
    animationmenu.h \
    yesnowidget.h \
    svgreader.h \
    aboutframe.h \
    imageframe.h \
    shapes.h

CONFIG += c++11

RESOURCES += \
    images.qrc \
    lisence.qrc

win32:LIBS+=-L$$_PRO_FILE_PWD_/libs/lib -lOpengl32
LIBS +=  -lz -lquazip5
