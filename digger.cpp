#include "digger.h"
#include <QDebug>
#include "bigtheater.h"

Digger::Digger(int pos_x, int pos_y, BigTheater* Bt) : Actor(pos_x, pos_y, "Digger.png", Bt)
{
    //paramof_block*#block + center_of_block

    sizeOfPictureX =  17;
    sizeOfPictureY  = 12;
    sizeOfItemX  = sizeOfPictureX * 2;
    sizeOfItemY = sizeOfPictureY * 2;


    dx = 10;
    dy = 0;

    course = Right;
    currentFrame = 0;
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer -> start(50);
    qDebug() << "I'am Digger";
}

void Digger::nextFrame()
{
//    std::cout << "nextFrame " << currentFrame << std::endl;
    currentFrame += 17;
    if (currentFrame >= 102 ) currentFrame = 0;
}

Digger::~Digger()
{
    qDebug() << "delete Digger";
}

void Digger::keyPressEvent(QKeyEvent *k)
{
    switch (k -> key()){
    case Qt::Key_Up:
        if (OwnY != (sizeOfBlockY/2) + sizeOfBlockY){
            move(0, -speedY, Up);
        }
        break;
    case Qt::Key_Down:
        if (OwnY != (sizeOfBlockY*(blockOnMapY-2) - sizeOfBlockY/2) + sizeOfBlockY){
            move(0, speedY, Down);
        }
        break;
    case Qt::Key_Left:
        if (OwnX != (sizeOfBlockX/2) + sizeOfBlockX){
            move(-speedX, 0, Left);

        }
        break;
    case Qt::Key_Right:
        if (OwnX != (sizeOfBlockX*(blockOnMapX-2) - sizeOfBlockX/2) + sizeOfBlockX){
            move(speedX, 0, Right);
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
