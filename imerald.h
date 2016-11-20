#ifndef IMERALD_H
#define IMERALD_H

#include <QPainter>
#include <QBitmap>
#include <QGraphicsPixmapItem>
#include "define.h"

class Imerald : public QGraphicsPixmapItem
{
    QPixmap *sprite;

    int X;
    int Y;
    int sizeOfItemX;
    int sizeOfItemY;
    int sizeOfPictureX;
    int sizeOfPictureY;
public:
    QPoint getCentre() const;
    Imerald(int pos_x, int pos_y);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // IMERALD_H
