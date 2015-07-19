#ifndef IMAGEBOUNDS_H
#define IMAGEBOUNDS_H

#include <QWidget>
#include <QSpinBox>

class ImageBounds : public QWidget
{
    Q_OBJECT
public:
    explicit ImageBounds(QWidget *parent = 0);

    QSpinBox *spnColumns;
    QSpinBox *spnRows;

    QSpinBox *spnXsep;
    QSpinBox *spnYsep;
};

#endif // IMAGEBOUNDS_H