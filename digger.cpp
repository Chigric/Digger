#include "digger.h"
#include <QDebug>
#include "bigtheater.h"

Digger::Digger(int pos_x, int pos_y, BigTheater* Bt) : Actor(pos_x, pos_y, "Digger.png", Bt)
{
    //paramof_block*#block + center_of_block
    speedX = ((double)sizeOfBlockX/5);//10 pressure for move on 1 block
    speedY = ((double)sizeOfBlockY/5);//11 pressure for move on 1 block

    sizeOfPictureX =  17;
    sizeOfPictureY  = 12;
    sizeOfItemX  = sizeOfPictureX * 2;
    sizeOfItemY = sizeOfPictureY * 2;

    dx = 10;
    dy = 0;

    course = Right;
    currentFrame = 0;
    currentAct = 0;

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    connect(timer, SIGNAL(timeout()), this, SLOT(frame()));
    timer -> start(50);
    qDebug() << "I'am Digger";
}

void Digger::nextFrame()
{
    currentFrame += 17;
    if (currentFrame >= 102 )
        currentFrame = 0;

    if(currentAct == 24 && currentFrame == 85)
        stopTimer();
}

Digger::~Digger()
{
    qDebug() << "delete Digger";
}

void Digger::keyPressEvent(QKeyEvent *k)
{
    switch (k -> key()){

    case R_Key_W:
    case Qt::Key_W:
    case Qt::Key_Up:
        move_U = true;
        break;
    case R_Key_S:
    case Qt::Key_S:
    case Qt::Key_Down:
        move_D = true;
        break;
    case R_Key_A:
    case Qt::Key_A:
    case Qt::Key_Left:
        move_L = true;
        break;
    case R_Key_D:
    case Qt::Key_D:
    case Qt::Key_Right:
        move_R = true;
        break;
    default:
        qDebug() << k -> key();
        break;
    }
}

void Digger::keyReleaseEvent(QKeyEvent *k)
{
    switch (k -> key()){

    case R_Key_W:
    case Qt::Key_W:
    case Qt::Key_Up:
        move_U = false;
        break;
    case R_Key_S:
    case Qt::Key_S:
    case Qt::Key_Down:
        move_D = false;
        break;
    case R_Key_A:
    case Qt::Key_A:
    case Qt::Key_Left:
        move_L = false;
        break;
    case R_Key_D:
    case Qt::Key_D:
    case Qt::Key_Right:
        move_R = false;
        break;
    default:
        break;
    }
}

void Digger::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
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
    painter -> drawPixmap(-sizeOfItemX/2, -sizeOfItemY/2, sizeOfItemX, sizeOfItemY, *sprite, currentFrame, currentAct, sizeOfPictureX, sizeOfPictureY);
    painter -> restore();
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
