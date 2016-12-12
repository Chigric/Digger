#include "money.h"
#include "bigtheater.h"

Money::Money(int pos_x, int pos_y, BigTheater* Bt) : Actor(pos_x, pos_y, "Money.png", Bt)
{
    currentAct = 0;
    currentFrame = 0;
    wiggle = 0;

    sizeOfPictureX = 13;
    sizeOfPictureY = 10;

    sizeOfItemX = 36;//52;
    sizeOfItemY = 30;//45;

    course = Right;
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(checkingLowerBlock()));
    timer -> start(50);
}

void Money::checkingLowerBlock()
{
    if ( !BT->scenery[Block_Y+1][Block_X].isFull() ){
        connect(timer, SIGNAL(timeout()), this, SLOT(fall()));
        move(0, speedY, Down);
    }
    qDebug() << !BT->scenery[Block_Y+1][Block_X].isFull() << Block_Y+1 << Block_X;
    qDebug() << OwnY+sizeOfItemX/2;
}
void Money::fall()
{
    disconnect(timer, SIGNAL(timeout()), this, SLOT(checkingLowerBlock()));
    currentAct = 1;
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer -> setInterval(500);

    if (wiggle == 4)
        if (!BT->scenery[Block_Y][Block_X].isFull())
            move(0, speedY, Down);
}

void Money::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(OwnX-sizeOfItemX/2, OwnY-sizeOfItemY/2, sizeOfItemX, sizeOfItemY, *sprite, currentFrame, currentAct*sizeOfPictureY, sizeOfPictureX, sizeOfPictureY);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Money::nextFrame()
{
    if (wiggle < 4){
        if (currentAct == 1){
            currentFrame += sizeOfPictureX;
            if (currentFrame >= 36) currentFrame = 0;
        }
        ++wiggle;
    } else {
        disconnect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
        timer -> setInterval(50);
    }
}

