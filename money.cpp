#include "money.h"
#include "bigtheater.h"

Money::Money(int pos_x, int pos_y, BigTheater* Bt) : Actor(pos_x, pos_y, "Money.png", Bt)
{
    OwnY = pos_y*sizeOfBlockY + sizeOfBlockY/2 + 4;

    speedX = ((double)sizeOfBlockX/10);//10 pressure for move on 1 block
    speedY = ((double)sizeOfBlockY/5);//10 pressure for move on 1 block

    firstBlock = false;

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
    connect(timer, SIGNAL(timeout()), this, SLOT(/*nextFrame()*/checkingLowerBlock()));
    timer -> start(50);
}
//////////
void Money::checkingLowerBlock()
{
    if (firstBlock ) { sizeOfItemX += 8; firstBlock = false; }

    if ( !BT->scenery[Block_Y+1][Block_X].isFull() ){
        disconnect(timer, SIGNAL(timeout()), this, SLOT(checkingLowerBlock()));
        connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
        currentAct = 10;
        timer -> setInterval(250);
    }
}

void Money::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(OwnX-sizeOfItemX/2, OwnY-sizeOfItemY/2, sizeOfItemX, sizeOfItemY, *sprite, currentFrame, currentAct, sizeOfPictureX, sizeOfPictureY);

    qDebug() << speedY;
    if (moving){
        if (/*OwnY == (Block_Y+1)*sizeOfBlockY + sizeOfBlockY/2 + 4*/moving <= 5){
            move(0, speedY, Down);
            BT->scenery[Block_Y][Block_X].eatingBlock(getF_C(), course);
            ++moving;
        } else {
            moving = 0;
            if ( BT->scenery[Block_Y+1][Block_X].isFull() )
                connect(timer, SIGNAL(timeout()), this, SLOT(checkingLowerBlock()));
            else moving = 1;
            if (firstBlock){}
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
            firstBlock = true;
            BT->scenery[Block_Y][Block_X].setBox(false);
        }
    }
}

