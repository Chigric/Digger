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
    int X = int(OwnX) % 75;
    int Y = int(OwnY) % 66;

    if (X == 37 && Y == 33){
        OwnX += dx_;
        OwnY += dy_;
    }
    if(dy_){
        if (X == 37 && Y != 33)
            OwnY += dy_;
        else if(X < 37)
            OwnX += speedX;
        else if(X > 37)
            OwnX -= speedX;
    }
    if (dx_){
        if (Y == 33 && X != 37)
            OwnX += dx_;
        else if(Y < 33)
            OwnY += speedY;
        else if(Y > 33)
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
        Block_X = (OwnX+sizeOfItemX/2) / 75;
        Block_Y = OwnY / 66;
        break;
    case Left:
        Block_X = (OwnX-sizeOfItemX/2) / 75;
        Block_Y = OwnY / 66;
        break;
    case Up:
        Block_X = OwnX / 75;
        Block_Y = (OwnY-sizeOfItemX/2) / 66;
        break;
    case Down:
        Block_X = OwnX / 75;
        Block_Y = (OwnY+sizeOfItemX/2) / 66;
    default:
        break;
    }
}

Actor::~Actor()
{
    qDebug() << "delete Actor";
}
