#ifndef MONEY_H
#define MONEY_H

#include "actor.h"

class Money : public Actor
{
    Q_OBJECT
    enum Status{Passive = 0, MovOnHor = 1,
                Neutral = 2,//Don't touch me
                Falling = 3, Cash = 4};
    Status status;
    //Falling Bag
    int flyingBlocks;
    //Animation
    int wiggle;
    int wiggle_F;
    int compression;
    //Timer For Delete Money
    int remaining;
    QTimer *timerForDelete;
    //Func
    void checkAfterMove();
    inline void setStatus(const Status s_)
    {status = s_;}
public:
    Money(int pos_x, int pos_y, BigTheater* Bt);
    ~Money();
    virtual void moveOnBlock(const Course c_);
    virtual void stopTimer();
    virtual void beginTimer();

    inline Status getStat() const {return status;}
public slots:
    void die();
private slots:
    void nextFrame();
    void checkingLowerBlock();
    void frame();
};

#endif // MONEY_H
