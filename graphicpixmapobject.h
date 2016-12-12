#ifndef GRAPHICOBJECT_H
#define GRAPHICOBJECT_H

#include <QPainter>
#include <QBitmap>
#include <QGraphicsPixmapItem>
#include <QString>

#include "define.h"

class GraphicPixmapObject : public QGraphicsPixmapItem
{
protected:
    QPixmap *sprite;

    qreal OwnX, OwnY;
    int sizeOfItemX;
    int sizeOfItemY;
    int sizeOfPictureX;
    int sizeOfPictureY;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public:
    GraphicPixmapObject(int pos_x, int pos_y, QString spriteName);

    bool itIsCollision(const QPoint& other);

    inline qreal x() const {return OwnX;}
    inline qreal y() const {return OwnY;}
    inline QPoint pos() const
    {
        return QPoint(OwnX, OwnY);
    }


};

#endif // GRAPHICOBJECT_H
