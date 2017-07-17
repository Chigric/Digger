#include "money.h"
#include "bigtheater.h"

Money::Money(int pos_x, int pos_y, BigTheater* Bt) :
    Actor(pos_x, pos_y, "Money.png", Bt)
{
    OwnY = pos_y*sizeOfBlockY + sizeOfBlockY/2;
    //5 pressure for move on 1 block
    speedX = ((double)sizeOfBlockX/4);
    speedY = ((double)sizeOfBlockY/3);

    flyingBlocks = 0;

    currentAct = 0;
    currentFrame = 0;
    wiggle = 0;
    wiggle_F = 3;
    compression = 8;

    sizeOfPictureX = 13;
    sizeOfPictureY = 10;

    sizeOfItemX = 36;//52;
    sizeOfItemY = 30;//45;

    setZValue(1.0);

    course = Right;
    status = Passive;
    connect(timer, SIGNAL(timeout()),
            this, SLOT(checkingLowerBlock()));
}

void Money::checkingLowerBlock()
{
//    stopHere(Down);
    if (flyingBlocks == 1) {
        sizeOfItemX += compression;
        flyingBlocks = 0;
        status = Passive;
    }
    else if (flyingBlocks > 1)
    {
        sizeOfItemX += compression; currentAct = 20;
        status = Cash;
        disconnect(timer, SIGNAL(timeout()),
                   this, SLOT(checkingLowerBlock()));
        timer -> singleShot(12000,// 12 second
                            this, SLOT(deleteLater()));
    }
    if ( !BT->scenery[Block_Y+1][Block_X].isBoxFull() ){
        moveOnBlock(Down);
    }
}

void Money::moveOnBlock(const Course c_)
//preparation
{
    if (c_ == Down) {
        connect(timer, SIGNAL(timeout()),
                this, SLOT(nextFrame()));
        if (status == Passive){
            stopHere(Down);
            currentAct = 10;
            timer -> setInterval(250);
        }
    } else if (c_ == Right || c_ == Left) {
        status = MovOnHor;
    }
    if (c_ != None)
        disconnect(timer, SIGNAL(timeout()),
                   this, SLOT(checkingLowerBlock()));
    Actor::moveOnBlock(c_);
}

void Money::frame()
{
    if (flyingBlocks)
        BT->scenery[Block_Y][Block_X].
                eatingBlock(getF_C(), pos(),course);
    Actor::frame();
}

void Money::checkAfterMove()
{
    if ( BT->scenery[Block_Y+1][Block_X].isBoxFull() )
    {
        connect(timer, SIGNAL(timeout()),
                this, SLOT(checkingLowerBlock()));
        moveOnBlock(None);
        status = Passive;
    }
    else {
        if (course == Down) {
            ++flyingBlocks;
            if (status == Neutral)
                status = Falling;
        } else {
            moveOnBlock(Down);
        }
    }
}

void Money::nextFrame()
{
    if (currentAct == 0){
        disconnect(timer, SIGNAL(timeout()),
                   this, SLOT(nextFrame()));
        wiggle = 0;
        sizeOfItemX -= compression;
        timer -> setInterval(msec);
        flyingBlocks = 1;
        BT->scenery[Block_Y][Block_X].setBox(false);
        stopHere(None);
        if (status == MovOnHor)
            status = Neutral;
        else
            status = Falling;
    } else if (currentAct == 10){
        if (wiggle < wiggle_F){
            currentFrame += sizeOfPictureX;
            if (currentFrame >= sizeOfPictureX*wiggle_F)
                currentFrame = 0;
            ++wiggle;
        } else
            currentAct = 0;
    }
}

inline void Money::setStatus(const Status s_)
{status = s_;}

Money::~Money()
{
    qDebug() << "Delete MMMMMoney!!!!!!!!!!!!!!!!";
}
