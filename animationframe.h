#ifndef ANIMATIONEDIT_H
#define ANIMATIONEDIT_H

//#include <QMainWindow>
//#include <QAbstractItemModel>

//#include "canvas.h"
//#include "spritemodel.h"
//#include "sprite.h"

class SpriteModel;
class AnimationToolBar;

#include "glwindow.h"

class AnimationFrame : public GLWindow
{
    Q_OBJECT
public:
    AnimationFrame(MainWindow *parent);
    void setContents(const QSharedPointer<Sprite> &spr);
    void closeEvent(QCloseEvent *event);


private slots:
    void incrementSubimg();

private:

    void render();

    SpriteModel* mModel;
    AnimationToolBar* mToolBar;

};

#endif // ANIMATIONEDIT_H
