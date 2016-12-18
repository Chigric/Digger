#include "graphicpixmapobject.h"
#include <QDebug>

GraphicPixmapObject::GraphicPixmapObject(int pos_x, int pos_y, QString spriteName) : QGraphicsPixmapItem()
{
    OwnX = pos_x*sizeOfBlockX + sizeOfBlockX/2;
    OwnY = pos_y*sizeOfBlockY + sizeOfBlockY/2;

    QString str = ":";
    sprite = new QPixmap(str += spriteName, "png", Qt::PreferDither);

    setZValue(0.0);
}

void GraphicPixmapObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(OwnX-sizeOfItemX/2, OwnY-sizeOfItemY/2, sizeOfItemX, sizeOfItemY, *sprite, 0, 0, sizeOfPictureX, sizeOfPictureY);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

bool GraphicPixmapObject::itIsCollision(const QPoint& other, bool onBorders)
{
    double y_ = OwnY - other.y();
    double x_ = OwnX - other.x();
    qreal dis = sqrt(x_*x_ + y_*y_);
    if (onBorders){
        if (dis < sizeOfItemX/2 || dis < sizeOfItemY/2)
            return true;
        else
            return false;
    }
    else{
        if (dis < sizeOfItemX || dis < sizeOfItemY)
            return true;
        else
            return false;
    }

}
