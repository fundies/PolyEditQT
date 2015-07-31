#include "mainwindow.h"
#include "checkers.h"

#include <QApplication>
#include <QOpenGLContext>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QApplication a(argc, argv);

    Q_INIT_RESOURCE(images);
    MainWindow w;
    w.show();

    return a.exec();
}
