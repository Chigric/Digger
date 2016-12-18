#include "money.h"
#include "bigtheater.h"

Money::Money(int pos_x, int pos_y, BigTheater* Bt) : Actor(pos_x, pos_y, "Money.png", Bt)
{
    OwnY = pos_y*sizeOfBlockY + sizeOfBlockY/2;

    speedX = ((double)sizeOfBlockX/5);//10 pressure for move on 1 block
    speedY = ((double)sizeOfBlockY/5);//10 pressure for move on 1 block

    flyingBlocks = 0;

    currentAct = 0;
    currentFrame = 0;
    wiggle = 0;
    wiggle_F = 3;
    compression = 8;
    moving = 0;

    sizeOfPictureX = 13;
    sizeOfPictureY = 10;

    sizeOfItemX = 36;//52;
    sizeOfItemY = 30;//45;

    setZValue(1.0);

    course = Right;
    status = Passive;
    connect(timer, SIGNAL(timeout()), this, SLOT(checkingLowerBlock()));
}
//////////
void Money::checkingLowerBlock()
{
//    stopHere(Down);

    if (flyingBlocks == 1) { sizeOfItemX += compression; flyingBlocks = 0; status = Passive;}
    else if (flyingBlocks > 1)
    {
        sizeOfItemX += compression; currentAct = 20;
//        BT->addToCash(this);
        status = Cash;
        disconnect(timer, SIGNAL(timeout()), this, SLOT(checkingLowerBlock()));
        timer -> singleShot(12000, this, SLOT(deleteLater()));
    }

    if ( !BT->scenery[Block_Y+1][Block_X].isBoxFull() ){
//        disconnect(timer, SIGNAL(timeout()), this, SLOT(checkingLowerBlock()));
//        connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
        moveOnBlock(Down);
//        currentAct = 10;
//        timer -> setInterval(250);
    }
}

void Money::moveOnBlock(const Course c_)
{
    if (c_ != None) disconnect(timer, SIGNAL(timeout()), this, SLOT(checkingLowerBlock()));

    if (c_ == Down)
    {
        stopHere(Down);
        connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
        currentAct = 10;
        timer -> setInterval(250);
    }

    Actor::moveOnBlock(c_);
}

void Money::frame()
{
    if (flyingBlocks) BT->scenery[Block_Y][Block_X].eatingBlock(getF_C(), pos(),course);
    Actor::frame();
}

void Money::checkAfterMove()
{
//    switch (startMove) {
//    case Left:
//        stopHere(Left);
//        break;
//    case Right:
//        stopHere(Right);
//        break;
//    default:
//        break;
//    }

    if ( BT->scenery[Block_Y+1][Block_X].isBoxFull() )
    {
        connect(timer, SIGNAL(timeout()), this, SLOT(checkingLowerBlock()));
        moveOnBlock(None);
    }
    else
    {
        if (course == Down) ++flyingBlocks;
        else moveOnBlock(Down);
    }
}

void Money::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(OwnX-sizeOfItemX/2, OwnY-sizeOfItemY/2, sizeOfItemX, sizeOfItemY, *sprite, currentFrame, currentAct, sizeOfPictureX, sizeOfPictureY);

//    if (moving){
//        if (/*OwnY == (Block_Y+1)*sizeOfBlockY + sizeOfBlockY/2 + 4*/moving <= 5){
//            move(0, speedY, Down);
//            BT->scenery[Block_Y][Block_X].eatingBlock(getF_C(), pos(),course);
//            ++moving;
//        } else {
//            moving = 0;
//            if ( BT->scenery[Block_Y+1][Block_X].isBoxFull() ) {
//                connect(timer, SIGNAL(timeout()), this, SLOT(checkingLowerBlock()));
//                BT->deleteFromLethalSubjects(this);
//            }
//            else {
//                moving = 1;
//                ++flyingBlocks;
//            }
//        }
//    }

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Money::nextFrame()
{
    if (currentAct == 10){
        if (wiggle < wiggle_F){
            currentFrame += sizeOfPictureX;
            if (currentFrame >= sizeOfPictureX*wiggle_F) currentFrame = 0;
            ++wiggle;
        } else {
            disconnect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
            wiggle = 0;
            currentAct = 0;
            sizeOfItemX -= compression;
            timer -> setInterval(msec);
//            ++moving;
            flyingBlocks = 1;
            BT->scenery[Block_Y][Block_X].setBox(false);
//            BT->addToLethalSubjects(this);
            stopHere(None);
            status = Moving;
        }
    }
}
