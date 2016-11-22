#include "money.h"

Money::Money(qreal pos_x, qreal pos_y) : Actor(pos_x, pos_y, "Money.png")
{
    sizeOfPictureX = 13;
    sizeOfPictureY = 10;

    sizeOfItemX = 52;
    sizeOfItemY = 45;
}

void Money::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    GraphicPixmapObject::paint(painter, option, widget);
}
