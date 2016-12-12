#ifndef MONEY_H
#define MONEY_H

#include "actor.h"

class Money : public Actor
{
    Q_OBJECT

    bool firstBlock;

    int moving;
    int currentFrame;
    int currentAct;
    int wiggle;
public:
    Money(int pos_x, int pos_y, BigTheater* Bt);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private slots:
    void nextFrame();
    void checkingLowerBlock();
};

#endif // MONEY_H
