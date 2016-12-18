#include "actor.h"

Actor::Actor(int pos_x, int pos_y, QString imageName, BigTheater* Bt) : QObject(),  GraphicPixmapObject(pos_x, pos_y, imageName)
{
    BT = Bt;
    Block_X = pos_x;
    Block_Y = pos_y;
    f_CX = OwnX;
    f_CY = OwnY;
    startMove = None;
    stopMove = None;
    msec = 50;
    sprite->setMask(sprite->createHeuristicMask());
    timer = new QTimer();
    timer -> start(msec);
    connect(timer, SIGNAL(timeout()), this, SLOT(frame()));
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

void Actor::stopHere(Course c_)
{
    qDebug() << "stopHere()" << c_;
    stopMove = c_;
}

void Actor::moveOnBlock(const Course c_)
{
    startMove = c_;
}

void Actor::frame()
{
    if (startMove != None){
        switch (startMove) {
        case Up:
            if ( (OwnY != (sizeOfBlockY/2) + sizeOfBlockY) && stopMove != Up) {
                qDebug() << "move_U";
                move(0, -speedY, Up);
            }
            break;
        case Down:
            if ( (OwnY != (sizeOfBlockY*(blockOnMapY-1) - sizeOfBlockY/2)) && stopMove != Down){
                qDebug() << "move_D";
                move(0, speedY, Down);
            }
            break;
        case Left:
            if ( (OwnX != (sizeOfBlockX/2) + sizeOfBlockX) && stopMove != Left){
                qDebug() << "move_L";
                move(-speedX, 0, Left);
            }
            break;
        case Right:
            if ( (OwnX != (sizeOfBlockX*(blockOnMapX-1) - sizeOfBlockX/2)) && stopMove != Right){
                qDebug() << "move_R";
                move(speedX, 0, Right);
            }
            break;
        default:
            break;
        }
        int X = int(OwnX) % sizeOfBlockX;
        int Y = int(OwnY) % sizeOfBlockY;
        int cen_X = sizeOfBlockX/2;
        int cen_Y = sizeOfBlockY/2;

        if (X == cen_X && Y == cen_Y){
            checkAfterMove();
        }
    }
}

void Actor::checkAfterMove()
{
    qDebug() << "check";
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
