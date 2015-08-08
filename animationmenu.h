#ifndef ANIMATIONMENU_H
#define ANIMATIONMENU_H

class AnimationFrame;
#include <QMenuBar>

class AnimationMenu : public QMenuBar
{
public:
    AnimationMenu(AnimationFrame *parent);

private:
    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* viewMenu;
};

#endif // ANIMATIONMENU_H
