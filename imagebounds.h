#ifndef IMAGEBOUNDS_H
#define IMAGEBOUNDS_H

#include <QWidget>
#include <QSpinBox>
#include <QPushButton>

/**
 * @brief The ImageBounds class
 */
class ImageBounds : public QWidget
{
    Q_OBJECT
public:

    /**
     * @brief ImageBounds constructor
     * @param parent parent widget
     */
    explicit ImageBounds(QWidget *parent = 0);

    QPushButton *btnAlpha;
    QPushButton *btnImport;
    QSpinBox *spnColumns;
    QSpinBox *spnRows;
    QSpinBox *spnXsep;
    QSpinBox *spnYsep;
};

#endif // IMAGEBOUNDS_H
