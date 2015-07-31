#ifndef ANIMATIONVIEW_H
#define ANIMATIONVIEW_H

#include <QWidget>
#include <QListView>

class AnimationView : public QListView
{
public:
    AnimationView(QWidget *parent);
    //void paintEvent(QPaintEvent * event);
    QSize sizeHint() const;
};

#endif // ANIMATIONVIEW_H
