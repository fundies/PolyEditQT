#ifndef ANIMATIONVIEW_H
#define ANIMATIONVIEW_H

#include <QWidget>
#include <QListView>

/**
 * @brief The AnimationView class
 */
class AnimationView : public QListView
{
public:

    /**
     * @brief AnimationView constructor
     * @param parent parent widget
     */
    AnimationView(QWidget *parent);

    /**
     * @brief sizeHint suggested window size
     * @return suggested size
     */
    QSize sizeHint() const;

    /**
     * @brief getCursor gets the selected image's position in the model
     * @return image's position
     */
    int getCursor() const;

    /**
     * @brief getSelection gets a list of all selected images in the model
     * @return list of selected images
     */
    QModelIndexList getSelection();
};

#endif // ANIMATIONVIEW_H
