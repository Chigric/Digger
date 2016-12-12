#include "actor.h"

Actor::Actor(int pos_x, int pos_y, QString imageName, BigTheater* Bt) : QObject(),  GraphicPixmapObject(pos_x, pos_y, imageName)
{
    BT = Bt;
    Block_X = pos_x;
    Block_Y = pos_y;
    f_CX = OwnX;
    f_CY = OwnY;
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

Actor::~Actor()
{
    qDebug() << "delete Actor";
}
