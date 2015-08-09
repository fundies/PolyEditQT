#include "animationview.h"
#include "checkers.h"

#include <QPainter>

AnimationView::AnimationView(QWidget *parent) : QListView(parent)
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

int AnimationView::getCursor() const
{
    if (selectedIndexes().isEmpty())
        return -1;
    else
        return selectedIndexes()[0].row();
}

QModelIndexList AnimationView::getSelection()
{
    return selectedIndexes();
}

/*void AnimationView::setCursor(int index)
{
view.selectionModel().select(item.index(), QtGui.QItemSelectionModel.Rows|QtGui.QItemSelectionModel.Select)
    QItemSelection s;
    s.append(QItemSelectionRange().)
    this->selectionModel()->select();
}*/

QSize AnimationView::sizeHint() const
{
    return QSize(600, 350);
}
