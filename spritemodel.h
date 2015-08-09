#ifndef SPRITEMODEL_H
#define SPRITEMODEL_H

#include <QAbstractListModel>

#include "sprite.h"

/**
 * @brief The SpriteModel class
 */
class SpriteModel : public QAbstractListModel
{
    Q_OBJECT

public:

    /**
     * @brief SpriteModel constructor
     * @param parent parent widget
     */
    SpriteModel(QWidget *parent = 0);

    /**
     * @brief rowCount get row count
     * @param parent parent
     * @return rows
     */
    int rowCount(const QModelIndex &parent) const;

    /**
     * @brief data get data
     * @param index index
     * @param role role
     * @return data
     */
    QVariant data(const QModelIndex &index, int role) const;

    /**
     * @brief setData st the data
     * @param index index
     * @param value new data
     * @param role role
     * @return success
     */
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    /**
     * @brief supportedDropActions supported actions
     * @return supported actions
     */
    Qt::DropActions supportedDropActions() const;

    /**
     * @brief insertRows insert rows
     * @param row row
     * @param count count
     * @param parent parent
     * @return  success
     */
    bool insertRows(int row, int count, const QModelIndex &parent);

    /**
     * @brief removeRows remove rows
     * @param row row
     * @param count count
     * @param parent parent
     * @return success
     */
    bool removeRows(int row, int count, const QModelIndex &parent);

    /**
     * @brief flags
     * @param index index
     * @return  flags
     */
    Qt::ItemFlags flags(const QModelIndex &index) const;

    /**
     * @brief mimeData mime data
     * @param indexes selected data
     * @return data
     */
    QMimeData *mimeData(const QModelIndexList &indexes) const;

    /**
     * @brief dropMimeData drop mime data
     * @param data data
     * @param action action
     * @param row row
     * @param column column
     * @param parent parent
     * @return success
     */
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent);

    /**
     * @brief mimeTypes accepted mime types
     * @return mimetypes
     */
    QStringList mimeTypes() const;

    /**
     * @brief setSprite set the sprite
     * @param spr new sprite
     */
    void setSprite(const SpritePtr &spr);

    /**
     * @brief getSprite gets the sprite
     * @return  sprite
     */
    SpritePtr getSprite() const;

    /**
     * @brief getCurrentSize get the current subimage's size
     * @return size
     */
    QSize getCurrentSize() const;

private:

    SpritePtr mSpr;
    SubImage mDefault;
    QWidget *mParent;
};

#endif // SPRITEMODEL_H
