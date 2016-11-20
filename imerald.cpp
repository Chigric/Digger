#include "imerald.h"

Imerald::Imerald(int pos_x, int pos_y) : QGraphicsPixmapItem()
{
    X = pos_x + sizeOfPixelX/2;
    Y = pos_y + sizeOfPixelY/2;
    sizeOfPictureX = 8;
    sizeOfPictureY = 7;
    sprite = new QPixmap(":Imerald.png", "png", Qt::MonoOnly);
    sprite->setMask(sprite->createHeuristicMask());
    sizeOfItemX = 48;
    sizeOfItemY = 42;
}

void Imerald::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(X-sizeOfItemX/2, Y-sizeOfItemY/2, sizeOfItemX, sizeOfItemY, *sprite, 0, 0, sizeOfPictureX, sizeOfPictureY);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QPoint Imerald::getCentre() const {return QPoint(X, Y);}
