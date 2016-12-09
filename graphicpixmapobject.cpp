#include "graphicpixmapobject.h"
#include <QDebug>

GraphicPixmapObject::GraphicPixmapObject(int pos_x, int pos_y, QString spriteName) : QGraphicsPixmapItem()
{
    OwnX = pos_x*sizeOfBlockX + sizeOfBlockX/2;
    OwnY = pos_y*sizeOfBlockY + sizeOfBlockY/2;

    QString str = ":";
    sprite = new QPixmap(str += spriteName, "png", Qt::PreferDither);
}

void GraphicPixmapObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(OwnX-sizeOfItemX/2, OwnY-sizeOfItemY/2, sizeOfItemX, sizeOfItemY, *sprite, 0, 0, sizeOfPictureX, sizeOfPictureY);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
