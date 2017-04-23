#include "actor.h"

Actor::Actor(int pos_x, int pos_y, QString imageName,
             BigTheater* Bt) :
    QObject(),
    GraphicPixmapObject(pos_x, pos_y, imageName)
{
    BT = Bt;//friend class?
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
    connect(timer, SIGNAL(timeout()),
            this, SLOT(frame()));
//    course;       ???
//    currentFrame; ???
//    currentAct;   ???
//    speedX;       ???
//    speedY;       ???
//    dx,dy;        ???
}

Actor::~Actor() {
    qDebug() << "delete Actor";
}

void Actor::move(qreal dx_, qreal dy_, Course c)
{
    course = c;
    dx = dx_;
    dy = dy_;
//    int X = int(OwnX) % sizeOfBlockX;
//    int Y = int(OwnY) % sizeOfBlockY;
    int cen_X = sizeOfBlockX/2;
    int cen_Y = sizeOfBlockY/2;
    int X = fmod(OwnX, sizeOfBlockX);
    int Y = fmod(OwnY, sizeOfBlockY);
//    int X = (int)ceil(OwnX) % sizeOfBlockX;
//    int Y = (int)ceil(OwnY) % sizeOfBlockY;

//    for (int k = 0; k < 6; k++) {
//        int d = fmod((OwnX + dx_*k), sizeOfBlockX);
//        qDebug() << k << d;
//    }
//    qDebug() << "X = " <<
//                OwnX << ceil(OwnX) << floor(OwnX) <<
//                X << cen_X << speedX;
//    qDebug() << "Y = " <<
//                OwnY << (int)ceil(OwnY) <<
//                Y << cen_Y << speedY << '\n';

    if (X == cen_X && Y == cen_Y){
        OwnX += dx_;
        OwnY += dy_;
    }
    if(dy_){
        if (X == cen_X && Y != cen_Y)
            OwnY += dy_;
        else if(X < cen_X) {
            if(cen_X - X < speedX)
                OwnX += cen_X - X;
            else
                OwnX += speedX;
        } else if(X > cen_X) {
            if(X - cen_X < speedX)
                OwnX -= X - cen_X;
            else
                OwnX -= speedX;
        }
    }
    if (dx_){
        if (Y == cen_Y && X != cen_X)
            OwnX += dx_;
        else if(Y < cen_Y) {
            if(cen_Y - Y < speedY)
                OwnY += cen_Y - Y;
            else
                OwnY += speedY;
        } else if(Y > cen_Y) {
            if(Y - cen_Y < speedY)
                OwnY -= Y - cen_Y;
            else
                OwnY -= speedY;
        }
    }
    whereIAm();
}

void Actor::whereIAm()
{
    switch (course) {
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
    case Right:
        f_CX = OwnX+sizeOfItemX/2;
        Block_X = f_CX / sizeOfBlockX;
        f_CY = OwnY;
        Block_Y = f_CY / sizeOfBlockY;
        break;
    }
}

void Actor::paint(QPainter *painter,
                  const QStyleOptionGraphicsItem *option,
                  QWidget *widget)
{
    painter->drawPixmap(
                OwnX-sizeOfItemX/2, OwnY-sizeOfItemY/2,
                sizeOfItemX, sizeOfItemY,
                *sprite, currentFrame, currentAct,
                sizeOfPictureX, sizeOfPictureY);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}


void Actor::frame()
{
    if (startMove != None){
        switch (startMove) {
        case Up:
            if ((OwnY > (sizeOfBlockY/2)+sizeOfBlockY) &&
                    stopMove != Up) {
                move(0, -speedY, Up);
            }
            break;
        case Down:
            if ((OwnY < (sizeOfBlockY*(blockOnMapY-1) -
                          sizeOfBlockY/2)) &&
                    stopMove != Down){
                move(0, speedY, Down);
            }
            break;
        case Left:
            if ((OwnX > (sizeOfBlockX/2)+sizeOfBlockX) &&
                    stopMove != Left){
                move(-speedX, 0, Left);
            }
            break;
        case Right:
            if ((OwnX < (sizeOfBlockX*(blockOnMapX-1) -
                          sizeOfBlockX/2)) &&
                    stopMove != Right){
                move(speedX, 0, Right);
            }
            break;
        default:
            break;
        }
//        int X = int(OwnX) % sizeOfBlockX;
//        int Y = int(OwnY) % sizeOfBlockY;
//        int X = (int)floor(OwnX) % sizeOfBlockX;
//        int Y = (int)floor(OwnY) % sizeOfBlockY;
        int X = fmod(OwnX, sizeOfBlockX);
        int Y = fmod(OwnY, sizeOfBlockY);
        int cen_X = sizeOfBlockX/2;
        int cen_Y = sizeOfBlockY/2;
        if ((X == cen_X && Y == cen_Y) ||
                (X+1 == cen_X && Y == cen_Y) ||
                (X == cen_X && Y+1 == cen_Y)) {
            checkAfterMove();
        }
    }
}

void Actor::checkAfterMove() {
//    qDebug() << "check";
}

void Actor::stopHere(Course c_) {stopMove = c_;}
void Actor::moveOnBlock(const Course c_){startMove = c_;}
void Actor::stopTimer() {timer->stop();}
void Actor::beginTimer() {if (this) timer->start(msec);}
