#ifndef SPRITEMODEL_H
#define SPRITEMODEL_H

#include <QAbstractListModel>
#include <QImage>
#include <QOpenGLTexture>

#include "sprite.h"

const auto mimeType = QStringLiteral("application/x-qabstractitemmodeldatalist");

class SpriteModel : public QAbstractListModel
{
    Q_OBJECT
public:

    SpriteModel(QObject * parent = 0);
    void setContents(QList<QPair<QImage, QOpenGLTexture *> > &newList);
    int rowCount(const QModelIndex & parent) const;
    QVariant data(const QModelIndex & index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::DropActions supportedDropActions() const;
    bool insertRows(int row, int count, const QModelIndex &parent);
    bool removeRows(int row, int count, const QModelIndex &parent);
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QMimeData *mimeData(const QModelIndexList &indexes) const;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);
    QStringList mimeTypes() const;

    void setSpr(const SpritePtr &spr);
    SpritePtr getSpr() const;

private:

    SpritePtr mSpr;
    SubImagePtr mDefault;
};

#endif // SPRITEMODEL_H
