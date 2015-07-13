#include "mainwindow.h"
#include <QApplication>
#include <QColorDialog>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //QColorDialog* c = new QColorDialog();
    //p->setOptions(QColorDialog::DontUseNativeDialog);
    //p->show();
    w.show();

    return a.exec();
}
