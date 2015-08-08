#include "aboutframe.h"

#include <QHBoxLayout>
#include <QPlainTextEdit>
#include <QTextStream>
#include <QLabel>

AboutFrame::AboutFrame(QWidget *parent) : QMainWindow(parent)
{
    QWidget *mCentralWidget = new QWidget(this);
    setCentralWidget(mCentralWidget);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mCentralWidget->setLayout(mainLayout);


    QImage icon(":/img/icon.png");
    QLabel *myLabel = new QLabel();
    myLabel->setPixmap(QPixmap::fromImage(icon));
    mainLayout->addWidget(myLabel);

    QFile file(":/Lisence");
    file.open(QFile::ReadOnly | QFile::Text);

    QTextStream ReadFile(&file);

    QPlainTextEdit *mText = new QPlainTextEdit(this);
    mText->setPlainText(ReadFile.readAll());
    mText->setReadOnly(true);

    mainLayout->addWidget(mText);

    setMinimumSize(860,375);
    setWindowTitle("About PolyEdit");

    show();
}

