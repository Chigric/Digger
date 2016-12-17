#include "money.h"
#include "bigtheater.h"

Money::Money(int pos_x, int pos_y, BigTheater* Bt) : Actor(pos_x, pos_y, "Money.png", Bt)
{
    OwnY = pos_y*sizeOfBlockY + sizeOfBlockY/2;

    speedX = ((double)sizeOfBlockX/10);//10 pressure for move on 1 block
    speedY = ((double)sizeOfBlockY/5);//10 pressure for move on 1 block

    flyingBlocks = 0;

    currentAct = 0;
    currentFrame = 0;
    wiggle = 0;
    moving = 0;

    sizeOfPictureX = 13;
    sizeOfPictureY = 10;

    sizeOfItemX = 36;//52;
    sizeOfItemY = 30;//45;

    course = Right;
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(checkingLowerBlock()));
    timer -> start(50);
    enum status{cash};
}
//////////
void Money::checkingLowerBlock()
{
    if (flyingBlocks == 1) { sizeOfItemX += 8; flyingBlocks = 0; }
    else if (flyingBlocks > 0)
    {
        sizeOfItemX += 8; currentAct = 20;
        BT->addToCash(this);
        disconnect(timer, SIGNAL(timeout()), this, SLOT(checkingLowerBlock()));
        timer -> singleShot(12000, this, SLOT(deleteLater()));
    }

    if ( !BT->scenery[Block_Y+1][Block_X].isBoxFull() ){
        disconnect(timer, SIGNAL(timeout()), this, SLOT(checkingLowerBlock()));
        connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
        currentAct = 10;
        timer -> setInterval(250);
    }
}

void Money::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(OwnX-sizeOfItemX/2, OwnY-sizeOfItemY/2, sizeOfItemX, sizeOfItemY, *sprite, currentFrame, currentAct, sizeOfPictureX, sizeOfPictureY);

    if (moving){
        if (/*OwnY == (Block_Y+1)*sizeOfBlockY + sizeOfBlockY/2 + 4*/moving <= 5){
            move(0, speedY, Down);
            BT->scenery[Block_Y][Block_X].eatingBlock(getF_C(), pos(),course);
            ++moving;
        } else {
            moving = 0;
            if ( BT->scenery[Block_Y+1][Block_X].isBoxFull() ) {
                connect(timer, SIGNAL(timeout()), this, SLOT(checkingLowerBlock()));
                BT->deleteFromLethalSubjects(this);
            }
            else {
                moving = 1;
                ++flyingBlocks;
            }
        }
    }

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Money::nextFrame()
{
    if (currentAct == 10){
        if (wiggle < 3){
            currentFrame += sizeOfPictureX;
            if (currentFrame >= sizeOfPictureX*3) currentFrame = 0;
            ++wiggle;
        } else {
            disconnect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
            wiggle = 0;
            currentAct = 0;
            sizeOfItemX -= 8;
            timer -> setInterval(50);
            ++moving;
            flyingBlocks = 1;
            BT->scenery[Block_Y][Block_X].setBox(false);
            BT->addToLethalSubjects(this);
        }
    }
}
