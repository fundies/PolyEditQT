#-------------------------------------------------
#
# Project created by QtCreator 2015-06-01T13:39:58
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PolyEditQT
TEMPLATE = app


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
    imageloader.cpp \
    imagebounds.cpp \
    glwindow.cpp \
    maincanvas.cpp \
    sprite.cpp \
    checkers.cpp

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
    imageloader.h \
    imagebounds.h \
    glwindow.h \
    maincanvas.h \
    sprite.h \
    checkers.h

CONFIG += c++11

QMAKE_LFLAGS += -lGLU

DISTFILES +=
