#include "animationview.h"
#include "checkers.h"

#include <QPainter>

AnimationView::AnimationView(QWidget* parent) : QListView(parent)
{
    setResizeMode(QListView::Adjust);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    setViewMode(QListView::IconMode);
    setMovement(QListView::Snap);
    setDragDropMode(QListView::InternalMove);
    setDefaultDropAction(Qt::MoveAction);
    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
    setDragDropOverwriteMode(false);
}

QSize AnimationView::sizeHint() const
{
    return QSize(600, 350);
}
