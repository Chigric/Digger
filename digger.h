#ifndef DIGGER_H
#define DIGGER_H

#include "actor.h"


class Digger : public Actor
{
public:
    Digger(int pos_x, int pos_y);
    ~Digger();
    void keyPressEvent(QKeyEvent* k);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // DIGGER_H
