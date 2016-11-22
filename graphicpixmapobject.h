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
public:
    GraphicPixmapObject(qreal pos_x, qreal pos_y, QString spriteName);

    QPoint pos() const;
    qreal x() const;
    qreal y() const;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // GRAPHICOBJECT_H
