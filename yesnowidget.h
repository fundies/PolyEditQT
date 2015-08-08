#ifndef YESNOWIDGET_H
#define YESNOWIDGET_H

#include <QWidget>
#include <QPushButton>

class YesNoWidget : public QWidget
{
    Q_OBJECT
public:
    YesNoWidget(QWidget *parent = 0);

signals:
    void yes();
    void no();

private slots:
    void yesPressed();
    void noPressed();

private:
    QPushButton *mYes;
    QPushButton *mNo;
};

#endif // YESNOWIDGET_H
