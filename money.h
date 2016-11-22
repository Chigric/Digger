#ifndef MONEY_H
#define MONEY_H

#include "actor.h"

class Money : public Actor
{

public:
    Money(qreal pos_x, qreal pos_y);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // MONEY_H
