#ifndef ANIMATIONEDIT_H
#define ANIMATIONEDIT_H

#include <QClipboard>
#include <QLabel>

#include "glwindow.h"

class SpriteModel;
class AnimationToolBar;
class AnimationMenu;
class MainWindow;
class YesNoWidget;
class AnimationView;

/**
 * @brief The AnimationFrame class
 */
class AnimationFrame : public GLWindow
{
    Q_OBJECT
public:

    /**
     * @brief AnimationFrame constructor
     * @param parent pointer to main window
     */
    AnimationFrame(MainWindow *parent);

    /**
     * @brief setSprite sets the sprite
     * @param spr new Sprite
     */
    void setSprite(const SpritePtr &spr);

private slots:

    /**
     * @brief incrementSubimg increases the subimage based on speed and timer
     */
    void incrementSubimg();

    /**
     * @brief insertImage inserts a blank image into the model
     */
    void insertImage();

    /**
     * @brief deleteImage removes an image from the model
     */
    void deleteImage();

    /**
     * @brief cut removes and stores selects images
     */
    void cut();

    /**
     * @brief copy stores selected images in the clipboard
     */
    void copy();

    /**
     * @brief paste inserts the images stored on the clipboard
     */
    void paste();

    /**
     * @brief exportStrip exports all the images in the model as one strip
     */
    void exportStrip();

    /**
     * @brief submit export the changes to the model
     */
    void submit();

    /**
     * @brief cancel ignore any chanes to the model
     */
    void cancel();

    /**
     * @brief import imports an image from a file into the model
     */
    void import();

    /**
     * @brief pause override of GLWindow's pause method
     */
    void pause();

    /**
     * @brief stop override of GLWindow's stop method
     */
    void stop();

    /**
     * @brief setFrame sets the currently visible frame in the viewer
     * @param frame new frame
     */
    void setFrame(int frame);

private:

    /**
     * @brief render draws the sprite
     */
    void render();

    /**
     * @brief setZoom sets the zoom
     * @param factor zoom amount
     */
    void setZoom(double factor);

    SpriteModel *mModel;
    AnimationToolBar *mToolBar;
    AnimationMenu *mMenuBar;
    AnimationView *animator;
    QClipboard *mClipboard;
    QLabel *mWidth;
    QLabel *mHeight;
    QLabel *mFrames;
    YesNoWidget *mSubmit;
    MainWindow *mParent;

};

#endif // ANIMATIONEDIT_H
