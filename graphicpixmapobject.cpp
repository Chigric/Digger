#include "graphicpixmapobject.h"
#include <QDebug>

GraphicPixmapObject::GraphicPixmapObject(qreal pos_x, qreal pos_y, QString spriteName) : QGraphicsPixmapItem()
{
    OwnX = pos_x + sizeOfPixelX/2;
    OwnY = pos_y + sizeOfPixelY/2;

    QString str = ":";
    if (spriteName == "Digger.png"){
        qDebug() << "aaaaaaaaaaaa";
//        str = ":";
    }
    sprite = new QPixmap(str += spriteName, "png", Qt::PreferDither);
    sprite->setMask(sprite->createHeuristicMask());
}

void GraphicPixmapObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(OwnX-sizeOfItemX/2, OwnY-sizeOfItemY/2, sizeOfItemX, sizeOfItemY, *sprite, 0, 0, sizeOfPictureX, sizeOfPictureY);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

qreal GraphicPixmapObject::x() const {return OwnX;}
qreal GraphicPixmapObject::y() const {return OwnY;}
QPoint GraphicPixmapObject::pos() const
{
    return QPoint(OwnX, OwnY);
}
