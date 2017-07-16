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
    enum Status{Passive = 0, MovOnHor = 1,
                Neutral = 2,//Don't touch me
                Falling = 3, Cash = 4};
    Status status;

    void checkAfterMove();
    inline void setStatus(const Status s_);
public:
    Money(int pos_x, int pos_y, BigTheater* Bt);
    ~Money();
    virtual void moveOnBlock(const Course c_);

    inline Status getStat() const {return status;}
private slots:
    void nextFrame();
    void checkingLowerBlock();
    void frame();
};

#endif // MONEY_H
