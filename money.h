#ifndef MONEY_H
#define MONEY_H

#include "actor.h"

class Money : public Actor
{
    Q_OBJECT

    int flyingBlocks;

    int wiggle;
    int wiggle_F;
    int compression;

    enum Status{Passive = 0, Moving = 1, Cash = 2};
    Status status;

    void checkAfterMove();

public:
    Money(int pos_x, int pos_y, BigTheater* Bt);
    virtual void moveOnBlock(const Course c_);

    inline Status getStat() const {return status;}
private slots:
    void nextFrame();
    void checkingLowerBlock();
    void frame();
};

#endif // MONEY_H
