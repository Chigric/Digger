#include "digger.h"
#include "bigtheater.h"
#include <QDebug>

class BigTheater;
Digger::Digger(int pos_x, int pos_y, BigTheater* Bt) : Actor(pos_x, pos_y, "Digger.png")
{
    this->BT = Bt;
    //paramof_block*#block + center_of_block

    sizeOfPictureX =  17;
    sizeOfPictureY  = 12;
    sizeOfItemX  = sizeOfPictureX * 2;
    sizeOfItemY = sizeOfPictureY * 2;


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
    qDebug() << OwnX << OwnY << sizeOfBlockY/2 << sizeOfBlockY*10 - sizeOfBlockY/2 << sizeOfBlockX/2 << sizeOfBlockX*15 - sizeOfBlockX/2;
    switch (k -> key()){
    case Qt::Key_Up:
        if (OwnY != (sizeOfBlockY/2) + sizeOfBlockY){
            move(0, -speedY, Up);
            collidesInBlock();
        }
        break;
    case Qt::Key_Down:
        if (OwnY != (sizeOfBlockY*10 - sizeOfBlockY/2) + sizeOfBlockY){
            move(0, speedY, Down);
            collidesInBlock();
        }
        break;
    case Qt::Key_Left:
        if (OwnX != (sizeOfBlockX/2) + sizeOfBlockX){
            move(-speedX, 0, Left);
            collidesInBlock();

        }
        break;
    case Qt::Key_Right:
        if (OwnX != (sizeOfBlockX*15 - sizeOfBlockX/2) + sizeOfBlockX){
            move(speedX, 0, Right);
            collidesInBlock();
        }
        break;
    default:
        break;
    }
}

void Digger::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    std::cout << "paint" << std::endl;
    painter -> save();
    painter -> translate(OwnX, OwnY);
    painter -> rotate( atan2(dx, dy) *180/M_PI - 90 );

    switch (course) {
    case Right:
//        painter -> scale(1,1);
        break;
    case Up:
        painter -> scale(-1,1);
        break;
    case Left:
        painter -> scale(1,-1);
        break;
    case Down:
        painter -> scale(-1,1);
        break;
    default:
        break;
    }
    painter -> drawPixmap(-sizeOfItemX/2, -sizeOfItemY/2, sizeOfItemX, sizeOfItemY, *sprite, currentFrame, 0, sizeOfPictureX, sizeOfPictureY);
    painter -> restore();
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Digger::collidesInBlock()
{
    switch(course){
    //if I'am fast moving, it have dropped, but
    //if I'am slow moving, it haven't dropped. //it was stating, after evolution **scenery into ***scenery //such as
    case Up:
        if (Block_Y != 10/*9*/){
            if (( (OwnY+sizeOfItemX/2) >= BT->scenery[Block_Y+1][Block_X].getPos().y() )
                    &&!( (OwnY-sizeOfItemX/2) >= BT->scenery[Block_Y+1][Block_X].getPos().y())  )
                BT->scenery[Block_Y+1][Block_X].setHLine(false);//hLine
            if (( (OwnY-sizeOfItemX/2) <= BT->scenery[Block_Y][Block_X].getPos().y() + sizeOfBlockY/*/2*/) )
                BT->scenery[Block_Y][Block_X].setBox(false);//box
            qDebug() << Block_Y << Block_Y+1 << BT->scenery[Block_Y+1][Block_X].getPos().y();
        }
        break;
    case Down:
        if (( (OwnY+sizeOfItemX/2) >= BT->scenery[Block_Y][Block_X].getPos().y() )
                &&!( (OwnY-sizeOfItemX/2) >= BT->scenery[Block_Y][Block_X].getPos().y())  )
            BT->scenery[Block_Y][Block_X].setHLine(false);//hLine
        if (( (OwnY+sizeOfItemX/2) >= BT->scenery[Block_Y][Block_X].getPos().y() /*+ sizeOfBlockY/2*/) )
            BT->scenery[Block_Y][Block_X].setBox(false);//box
        break;
    case Left:
        if (Block_X != 15/*14*/){
            if (( (OwnX+sizeOfItemX/2) >= BT->scenery[Block_Y][Block_X+1].getPos().x() )
                    &&!( (OwnX-sizeOfItemX/2) >= BT->scenery[Block_Y][Block_X+1].getPos().x())  )
                BT->scenery[Block_Y][Block_X+1].setVLine(false);//vLine
            if (( (OwnX-sizeOfItemX/2) <= BT->scenery[Block_Y][Block_X].getPos().x() + sizeOfBlockX/*/2*/) )
                BT->scenery[Block_Y][Block_X].setBox(false);//box
            qDebug() << Block_X + 1 << BT->scenery[Block_Y][Block_X+1].getPos().x();
        }
        break;
    case Right:
        if (( (OwnX+sizeOfItemX/2) >= BT->scenery[Block_Y][Block_X].getPos().x() )
                &&!( (OwnX-sizeOfItemX/2) >= BT->scenery[Block_Y][Block_X].getPos().x())  )
            BT->scenery[Block_Y][Block_X].setVLine(false);//vLine
        if (( (OwnX+sizeOfItemX/2) >= BT->scenery[Block_Y][Block_X].getPos().x() /*+ sizeOfBlockX/2*/) )
            BT->scenery[Block_Y][Block_X].setBox(false);//box
        break;
    default:
        break;
    }
}
