#ifndef YESNOWIDGET_H
#define YESNOWIDGET_H

#include <QWidget>
#include <QPushButton>

/**
 * @brief The YesNoWidget class
 */
class YesNoWidget : public QWidget
{
    Q_OBJECT

public:

    /**
     * @brief YesNoWidget
     * @param parent parent
     */
    YesNoWidget(QWidget *parent = 0);

signals:

    /**
     * @brief yes
     */
    void yes();

    /**
     * @brief no
     */
    void no();

private slots:

    /**
     * @brief yesPressed
     */
    void yesPressed();

    /**
     * @brief noPressed
     */
    void noPressed();

private:
    QPushButton *mYes;
    QPushButton *mNo;
};

#endif // YESNOWIDGET_H
