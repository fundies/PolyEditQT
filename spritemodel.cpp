#include "spritemodel.h"

#include <QDebug>
#include <QMimeData>

SpriteModel::SpriteModel(QObject * parent) : QAbstractListModel(parent)
{
}


bool SpriteModel::insertRows(int position, int rows, const QModelIndex &parent)
{
    Q_UNUSED(parent);

    beginInsertRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        mSpr->mSubimg.insert(position, mDefault);
    }

    endInsertRows();
    return true;
}

bool SpriteModel::removeRows(int position, int rows, const QModelIndex &parent)
{
    Q_UNUSED(parent);

    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row = 0; row < rows; ++row) {
        mSpr->mSubimg.removeAt(position);
    }

    endRemoveRows();
    return true;
}

bool SpriteModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Q_UNUSED(role);

    QImage img = value.value<QImage>();
    mSpr->mSubimg.replace(index.row(), SubImagePtr(new SubImage(img)));

    return true;
}

int SpriteModel::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    if (mSpr != nullptr)
        return mSpr->count();
    else
        return 0;
}

QVariant SpriteModel::data(const QModelIndex & index, int role) const
{
    if (role == Qt::DecorationRole)
        return mSpr->mSubimg[index.row()]->img;
    else if (role == Qt::DisplayRole)
        return "";
    else
        return QVariant();
}

bool SpriteModel::dropMimeData(const QMimeData *data,
    Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    qDebug() << "dropMimeData()";

    if (action == Qt::IgnoreAction)
        return true;

    if (!data->hasFormat("PolyEdit/DnD"))
        return false;

    if (column > 0)
        return false;

    int beginRow;

    if (row != -1)
        beginRow = row;

    else if (parent.isValid())
        beginRow = parent.row();
    else
        beginRow = rowCount(QModelIndex());

    QByteArray encodedData = data->data("PolyEdit/DnD");
    QDataStream stream(&encodedData, QIODevice::ReadOnly);
    QList<QVariant> newItems;
    int rows = 0;

    while (!stream.atEnd()) {
        QVariant img;
        stream >> img;
        newItems.append(img);
        ++rows;
    }

    insertRows(beginRow, rows, QModelIndex());

    for (auto i : newItems)
    {
        qDebug() << "newItems";
        QModelIndex idx = index(beginRow, 0, QModelIndex());
        setData(idx, i, 0);
        beginRow++;
    }

    return true;
}

Qt::ItemFlags SpriteModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractListModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
    else
        return Qt::ItemIsDropEnabled | defaultFlags;
}

QMimeData *SpriteModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData();
    QByteArray encodedData;

    QDataStream stream(&encodedData, QIODevice::WriteOnly);

    QVariant img;
    foreach (const QModelIndex &index, indexes) {
        if (index.isValid()) {
            img = data(index, Qt::DecorationRole);
            stream << img;
        }
    }

    mimeData->setData("PolyEdit/DnD", encodedData);
    mimeData->setImageData(img);
    return mimeData;
}

QStringList SpriteModel::mimeTypes() const
{
    return QStringList("PolyEdit/DnD");
}

SpritePtr SpriteModel::getSpr() const
{
    return mSpr;
}


void SpriteModel::setSpr(const SpritePtr &spr)
{
    beginResetModel();

    QImage img = spr->mSubimg[0]->img;
    img.fill(Qt::white);
    mDefault = SubImagePtr(new SubImage(img));
    mSpr = spr;

    endResetModel();
}


Qt::DropActions SpriteModel::supportedDropActions() const
{
    return Qt::MoveAction;
}
