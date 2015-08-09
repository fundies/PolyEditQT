#ifndef ANIMATIONTOOLBAR_H
#define ANIMATIONTOOLBAR_H

#include <QToolBar>
#include <QSpinBox>
#include <QDoubleSpinBox>

class AnimationFrame;

/**
 * @brief The AnimationToolBar class
 */
class AnimationToolBar : public QToolBar
{
public:

    /**
     * @brief AnimationToolBar
     * @param parent parent window
     */
    AnimationToolBar(AnimationFrame *parent);

    QSpinBox *frame;
    QDoubleSpinBox *speed;
};

#endif // ANIMATIONTOOLBAR_H
