#ifndef ANIMATIONTOOLBAR_H
#define ANIMATIONTOOLBAR_H

#include <QToolBar>
#include <QSpinBox>
#include <QDoubleSpinBox>

class AnimationFrame;

class AnimationToolBar : public QToolBar
{
public:
    AnimationToolBar(AnimationFrame *parent);
    QSpinBox* frame;
    QDoubleSpinBox* speed;
};

#endif // ANIMATIONTOOLBAR_H
