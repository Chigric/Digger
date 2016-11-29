#include "actor.h"

class BigTheater;
Actor::Actor(int pos_x, int pos_y, QString imageName) : QObject(),  GraphicPixmapObject(pos_x, pos_y, imageName)
{
    Block_X = pos_x;
    Block_Y = pos_y;
}

void Actor::nextFrame()
{
//    std::cout << "nextFrame " << currentFrame << std::endl;
    currentFrame += 17;
    if (currentFrame >= 102 ) currentFrame = 0;
}

void Actor::move(qreal dx_, qreal dy_, int c)
{
    course = c;
    dx = dx_;
    dy = dy_;
    int X = int(OwnX) % sizeOfBlockX;
    int Y = int(OwnY) % sizeOfBlockY;
    int cen_X = 25;
    int cen_Y = 22;

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
    std::cout << Block_X <<"\t"<< Block_Y << std::endl;

//    QList<QGraphicsItem*> cItems = collidingItems();
//    qDebug() << cItems.size();
}

void Actor::whereIAm()
{
    switch (course) {
    case Right:
        Block_X = (OwnX+sizeOfItemX/2) / sizeOfBlockX;
        Block_Y = OwnY / sizeOfBlockY;
        break;
    case Left:
        Block_X = (OwnX-sizeOfItemX/2) / sizeOfBlockX;
        Block_Y = OwnY / sizeOfBlockY;
        break;
    case Up:
        Block_X = OwnX / sizeOfBlockX;
        Block_Y = (OwnY-sizeOfItemX/2) / sizeOfBlockY;
        break;
    case Down:
        Block_X = OwnX / sizeOfBlockX;
        Block_Y = (OwnY+sizeOfItemX/2) / sizeOfBlockY;
    default:
        break;
    }
}

Actor::~Actor()
{
    qDebug() << "delete Actor";
}
