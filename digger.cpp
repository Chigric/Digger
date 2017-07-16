#include "digger.h"
#include "bigtheater.h"
#include <QDebug>

Digger::Digger(int pos_x, int pos_y, BigTheater* Bt) :
    Actor(pos_x, pos_y, "Digger.png", Bt)
{
    //5 pressure for move on 1 block
    speedX = ((double)sizeOfBlockX/5);
    speedY = ((double)sizeOfBlockY/5);
    //Size of picture
    sizeOfPictureX =  17;
    sizeOfPictureY  = 12;
    sizeOfItemX  = sizeOfPictureX * 2;
    sizeOfItemY = sizeOfPictureY * 2;
    //Delta movement
    dx = 10;
    dy = 0;
    //Animation
    course = Right;
    currentFrame = 0;
    currentAct = 0;
    //Z-Value
    setZValue(2.0);
    //Connect
    connect(timer, SIGNAL(timeout()),
            this, SLOT(nextFrame()));
    qDebug() << "I'am Digger";
}

Digger::~Digger()
{
    qDebug() << "delete Digger";
}

void Digger::keyPressEvent(QKeyEvent* e)
{
    switch (e -> key()) {
    case R_Key_W:
    case Qt::Key_W:
    case Qt::Key_Up:
        startMove = Up;
        break;
    case R_Key_S:
    case Qt::Key_S:
    case Qt::Key_Down:
        startMove = Down;
        break;
    case R_Key_A:
    case Qt::Key_A:
    case Qt::Key_Left:
        startMove = Left;
        break;
    case R_Key_D:
    case Qt::Key_D:
    case Qt::Key_Right:
        startMove = Right;
        break;
    default:
        qDebug() << e -> key();
        break;
    }
}
void Digger::keyReleaseEvent(QKeyEvent *e)
{
    startMove = None;
    Q_UNUSED(e);
}

void Digger::nextFrame()
{
    currentFrame += 17;
    if (currentFrame >= 102 )
        currentFrame = 0;
    if(currentAct == 24 && currentFrame == 85)
        stopTimer();
}



void Digger::paint(
        QPainter *painter,
        const QStyleOptionGraphicsItem *option,
        QWidget *widget )
{
    painter -> save();
    painter -> translate(OwnX, OwnY);
    painter -> rotate( atan2(dx, dy)*180/M_PI - 90 );

    switch (course) {
    case Left:
        painter -> scale(1,-1);
        break;
    case Up:
        painter -> scale(-1,1);
        break;
    case Down:
        painter -> scale(-1,1);
        break;
    case Right:
//        painter -> scale(1,1);
        break;
    default:
        break;
    }
    painter->drawPixmap(-sizeOfItemX/2, -sizeOfItemY/2,
                        sizeOfItemX, sizeOfItemY,
                        *sprite, currentFrame, currentAct,
                        sizeOfPictureX, sizeOfPictureY);
    painter->restore();
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Digger::die()
{
    currentAct =  24;
    currentFrame = 0;
    timer->setInterval(500);
    dx = 10;
    dy = 0;
    course = Right;
}
