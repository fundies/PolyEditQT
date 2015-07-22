#ifndef IMAGEBOUNDS_H
#define IMAGEBOUNDS_H

#include <QWidget>
#include <QSpinBox>
#include <QPushButton>

class ImageBounds : public QWidget
{
    Q_OBJECT
public:
    explicit ImageBounds(QWidget *parent = 0);

    QPushButton *btnAlpha;
    QPushButton *btnImport;

    QSpinBox *spnColumns;
    QSpinBox *spnRows;

    QSpinBox *spnXsep;
    QSpinBox *spnYsep;
};

#endif // IMAGEBOUNDS_H
