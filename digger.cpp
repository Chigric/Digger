#include "digger.h"
#include "bigtheater.h"
#include <QDebug>

class BigTheater;
Digger::Digger(BigTheater* Bt) : Actor()
{
    this->BT = Bt;
    //paramof_block*#block + center_of_block
    OwnX = 75*0 + 37;
    OwnY = 66*0 + 33;
    Block_X = 0;
    Block_Y = 0;

    sizeOfItemX  = 51;
    sizeOfItemY = 36;
    sizeOfPictureX =  17;
    sizeOfPictureY  = 12;

    dx = 10;
    dy = 0;

    course = Right;
    currentFrame = 0;
    sprite = new QPixmap(":Digger.png", "png", Qt::PreferDither);
    sprite->setMask(sprite->createHeuristicMask());
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer -> start(50);
    qDebug() << "I'am Digger";
}

Digger::~Digger()
{
    qDebug() << "delete Digger";
}

void Digger::keyPressEvent(QKeyEvent *k)
{
    switch (k -> key()){
    case Qt::Key_Up:
        if (OwnY != 33){
            move(0, -speedY, Up);
            collidesInBlock();
        }
        break;
    case Qt::Key_Down:
        if (OwnY != 627){
            move(0, speedY, Down);
            collidesInBlock();
        }
        break;
    case Qt::Key_Left:
        if (OwnX != 37){
            move(-speedX, 0, Left);
            collidesInBlock();

        }
        break;
    case Qt::Key_Right:
        if (OwnX != 1087){
            move(speedX, 0, Right);
            collidesInBlock();
        }
        break;
    default:
        break;
    }
}

void Digger::collidesInBlock()
{
    switch(course){
    case Up:
        if (( (OwnY+sizeOfItemX/2) >= BT->scenery[Block_Y+1][Block_X].getPos().y() )
                &&!( (OwnY-sizeOfItemX/2) >= BT->scenery[Block_Y+1][Block_X].getPos().y())  )
            BT->scenery[Block_Y+1][Block_X].setHLine(false);
        if (( (OwnY-sizeOfItemX/2) <= BT->scenery[Block_Y][Block_X].getPos().y() + sizeOfPixelY/2) )
            BT->scenery[Block_Y][Block_X].setBox(false);
        break;
    case Down:
        if (( (OwnY+sizeOfItemX/2) >= BT->scenery[Block_Y][Block_X].getPos().y() )
                &&!( (OwnY-sizeOfItemX/2) >= BT->scenery[Block_Y][Block_X].getPos().y())  )
            BT->scenery[Block_Y][Block_X].setHLine(false);
        if (( (OwnY+sizeOfItemX/2) >= BT->scenery[Block_Y][Block_X].getPos().y() + sizeOfPixelY/2) )
            BT->scenery[Block_Y][Block_X].setBox(false);
        break;
    case Left:
        if (( (OwnX+sizeOfItemX/2) >= BT->scenery[Block_Y][Block_X+1].getPos().x() )
                &&!( (OwnX-sizeOfItemX/2) >= BT->scenery[Block_Y][Block_X+1].getPos().x())  )
            BT->scenery[Block_Y][Block_X+1].setVLine(false);
        if (( (OwnX-sizeOfItemX/2) <= BT->scenery[Block_Y][Block_X].getPos().x() + sizeOfPixelX/2) )
            BT->scenery[Block_Y][Block_X].setBox(false);
        break;
    case Right:
        if (( (OwnX+sizeOfItemX/2) >= BT->scenery[Block_Y][Block_X].getPos().x() )
                &&!( (OwnX-sizeOfItemX/2) >= BT->scenery[Block_Y][Block_X].getPos().x())  )
            BT->scenery[Block_Y][Block_X].setVLine(false);
        if (( (OwnX+sizeOfItemX/2) >= BT->scenery[Block_Y][Block_X].getPos().x() + sizeOfPixelX/2) )
            BT->scenery[Block_Y][Block_X].setBox(false);
        break;
    default:
        break;
    }
}
