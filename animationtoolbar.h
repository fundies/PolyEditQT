#ifndef ANIMATIONTOOLBAR_H
#define ANIMATIONTOOLBAR_H

#include <QToolBar>

//#include "animationframe.h"

class AnimationFrame;

class AnimationToolBar : public QToolBar
{
public:
    AnimationToolBar(AnimationFrame *parent);
};

#endif // ANIMATIONTOOLBAR_H
