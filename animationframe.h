#ifndef ANIMATIONEDIT_H
#define ANIMATIONEDIT_H

#include <QClipboard>
#include <QLabel>
#include "yesnowidget.h"

class SpriteModel;
class AnimationToolBar;
class AnimationMenu;

#include "glwindow.h"
#include "animationview.h"

class AnimationFrame : public GLWindow
{
    Q_OBJECT
public:
    AnimationFrame(MainWindow *parent);
    void setContents(const SpritePtr &spr);

private slots:
    void incrementSubimg();
    void insertImage();
    void deleteImage();
    void cut();
    void copy();
    void paste();
    void exportStrip();
    void submit();
    void cancel();
    void import();
    void pause();
    void stop();
    void setFrame(int frame);

private:

    void render();
    void setZoom(double factor);

    SpriteModel* mModel;
    AnimationToolBar* mToolBar;
    AnimationMenu* mMenuBar;
    AnimationView *animator;
    QClipboard *mClipboard;

    QLabel *mWidth;
    QLabel *mHeight;
    QLabel *mFrames;

    YesNoWidget *mSubmit;

    MainWindow* mParent;

};

#endif // ANIMATIONEDIT_H
