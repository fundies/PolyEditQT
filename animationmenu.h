#ifndef ANIMATIONMENU_H
#define ANIMATIONMENU_H

#include <QMenuBar>

class AnimationFrame;

/**
 * @brief The AnimationMenu class
 */
class AnimationMenu : public QMenuBar
{
public:

    /**
     * @brief AnimationMenu constructor
     * @param parent parent window
     */
    AnimationMenu(AnimationFrame *parent);

private:

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
};

#endif // ANIMATIONMENU_H
