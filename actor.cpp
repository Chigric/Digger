#include "actor.h"

Actor::Actor(int pos_x, int pos_y, QString imageName, BigTheater* Bt) : QObject(),  GraphicPixmapObject(pos_x, pos_y, imageName)
{
    BT = Bt;
    Block_X = pos_x;
    Block_Y = pos_y;
    f_CX = OwnX;
    f_CY = OwnY;
    move_D = false;
    move_U = false;
    move_L = false;
    move_R = false;
    msec = 50;
    sprite->setMask(sprite->createHeuristicMask());
}

void Actor::move(qreal dx_, qreal dy_, Course c)
{
    course = c;
    dx = dx_;
    dy = dy_;
    int X = int(OwnX) % sizeOfBlockX;
    int Y = int(OwnY) % sizeOfBlockY;
    int cen_X = sizeOfBlockX/2;
    int cen_Y = sizeOfBlockY/2;

//    if (X - cen_X < dx) dx = X - cen_X;
//    if (X - cen_Y < dy) dy = Y - cen_Y;

    if (X == cen_X && Y == cen_Y){
        OwnX += dx_;
        OwnY += dy_;
    }
    if(dy_){
        if (X == cen_X && Y != cen_Y)
            OwnY += dy_;
        else if(X < cen_X)
            OwnX += speedX;
        else if(X > cen_X)
            OwnX -= speedX;
    }
    if (dx_){
        if (Y == cen_Y && X != cen_X)
            OwnX += dx_;
        else if(Y < cen_Y)
            OwnY += speedY;
        else if(Y > cen_Y)
            OwnY -= speedY;
    }
    whereIAm();

//    QList<QGraphicsItem*> cItems = collidingItems();
//    qDebug() << cItems.size();
}

void Actor::whereIAm()
{
    switch (course) {
    case Right:
        f_CX = OwnX+sizeOfItemX/2;
        Block_X = f_CX / sizeOfBlockX;
        f_CY = OwnY;
        Block_Y = f_CY / sizeOfBlockY;
        break;
    case Left:
        f_CX = OwnX-sizeOfItemX/2;
        Block_X = f_CX / sizeOfBlockX;
        f_CY = OwnY;
        Block_Y = f_CY / sizeOfBlockY;
        break;
    case Up:
        f_CX = OwnX;
        Block_X = f_CX / sizeOfBlockX;
        f_CY = OwnY-sizeOfItemX/2;
        Block_Y = f_CY / sizeOfBlockY;
        break;
    case Down:
        f_CX = OwnX;
        Block_X = f_CX / sizeOfBlockX;
        f_CY = OwnY+sizeOfItemX/2;
        Block_Y = f_CY / sizeOfBlockY;
    default:
        break;
    }
}

void Actor::stopHere()
{
    qDebug() << "stopHere()";
    move_U = false;
    move_D = false;
    move_L = false;
    move_R = false;
}

void Actor::moveOnBlock(const Course c_)
{
    switch (c_) {
    case Up:
        move_U = true;
        break;
    case Down:
        move_D = true;
        break;
    case Left:
        move_L = true;
        break;
    case Right:
        move_R = true;
        break;
    }
    connect(timer, SIGNAL(timeout()), this, SLOT(frame()));
}

void Actor::frame()
{
    if (move_U && (OwnY != (sizeOfBlockY/2) + sizeOfBlockY) ) {
        move(0, -speedY, Up);
    }
    if (move_D && (OwnY != (sizeOfBlockY*(blockOnMapY-2) - sizeOfBlockY/2) + sizeOfBlockY)){
        qDebug() << move_D;
        move(0, speedY, Down);
    }
    if (move_L && (OwnX != (sizeOfBlockX/2) + sizeOfBlockX)){
        move(-speedX, 0, Left);
    }
    if (move_R && (OwnX != (sizeOfBlockX*(blockOnMapX-2) - sizeOfBlockX/2) + sizeOfBlockX)){
        move(speedX, 0, Right);
    }
}

Actor::~Actor()
{
    qDebug() << "delete Actor";
}

void Actor::stopTimer()
{
    timer->stop();
}

void Actor::beginTimer()
{
    timer->start(msec);
}
