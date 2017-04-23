#include "nobbin.h"
#include "bigtheater.h"

Nobbin::Nobbin(int pos_x, int pos_y, BigTheater* Bt) :
    Actor(pos_x, pos_y, "Nobbin.png", Bt)
{
    OwnY = pos_y*sizeOfBlockY + sizeOfBlockY/2;
    //5 pressure for move on 1 block
    speedX = ((double)sizeOfBlockX/5);
    speedY = ((double)sizeOfBlockY/5);

    currentAct = 0;
    currentFrame = 0;

    sizeOfPictureX = 16;
    sizeOfPictureY = 16;

    sizeOfItemX = 32;
    sizeOfItemY = 32;

    course = Right;

    currentFrame = 0;
    currentAct = 0;

    msec = 70;
    connect(timer, SIGNAL(timeout()),
            this, SLOT(nextFrame()));
    timer -> setInterval(msec);
    qDebug() << "I'am Nobbin";
    checkAfterMove();
}

void Nobbin::nextFrame()
{
    currentFrame += 17;
    if (currentFrame >= 67) currentFrame = 0;
}

Nobbin::~Nobbin()
{
    qDebug() << "delete Nobbin";
}

void Nobbin::checkAfterMove()
{
    srand(time(NULL));
    Course variant[3];
    int n = 0;
    if (BT->scenery[Block_Y-1][Block_X].isBoxEmpty() &&
            !BT->scenery[Block_Y][Block_X].existHLine() &&
            course != Down){
        qDebug() << n;
        variant[n++] = Up;
    }
    qDebug() << BT->scenery[Block_Y][Block_X-1].isBoxEmpty()
            << !BT->scenery[Block_Y][Block_X].existVLine()
            << course;
    if (BT->scenery[Block_Y][Block_X-1].isBoxEmpty() &&
            !BT->scenery[Block_Y][Block_X].existVLine() &&
            course != Right){
        qDebug() << n;
        variant[n++] = Left;
    }
    if (BT->scenery[Block_Y+1][Block_X].isBoxEmpty() &&
            !BT->scenery[Block_Y+1][Block_X].existHLine() &&
            course != Up){
        qDebug() << n;
        variant[n++] = Down;
    }
    if (BT->scenery[Block_Y][Block_X+1].isBoxEmpty() &&
            !BT->scenery[Block_Y][Block_X+1].existVLine() &&
            course != Left){
        qDebug() << n;
        variant[n++] = Right;
    }
    if (n == 0) {
        moveOnBlock((Course)-course);
        qDebug() << n << startMove;
    } else {
        moveOnBlock(variant[rand()%n]);
        qDebug() << n << startMove;
    }
}

void Nobbin::die()
{
    BT->deleteFromCharacters(this);
}
