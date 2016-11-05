#include "actor.h"

Actor::Actor() : QObject (), QGraphicsPixmapItem()
{
//    setPos(200, 200);
    dx = 0; dy = 0;
    OwnX = 200;
    OwnY= 200;

    currentFrame = 0;
    sprite = new QPixmap(":Orange.png", "png", Qt::PreferDither);
    sprite->setMask(sprite->createHeuristicMask());
    timer = new QTimer();
//    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer -> start(100);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    std::cout << x() << "\t" << y() << "\t" << dx << "\t" << dy << std::endl;
}

//QRectF Actor::boundingRect() const
//{
//    qreal penWidth = 1;//たぶん
////    return QRectF( x()+dx - penWidth, y()+dy - penWidth,
////                  50 - penWidth, 50 - penWidth);
//    return QRectF(OwnX, OwnY,50,50);
//}

void Actor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    std::cout << "paint" << std::endl;
    painter -> drawPixmap(OwnX, OwnY, 50, 50, *sprite, currentFrame, 0, 5, 5);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Actor::nextFrame()
{
    std::cout << "nextFrame " << currentFrame << std::endl;
    qreal penWidth = 0;//たぶん
    currentFrame += 5;
    if (currentFrame >= 25 ) currentFrame = 0;

    this->update(OwnX, OwnY, 50, 50);
//    setPos(200, 200);
//    dx = 0; dy = 0;
}

void Actor::move()
{
//    moveBy(dx,dy);
    OwnX += dx;
    OwnY += dy;
    std::cout << OwnX <<" "<< OwnY << std::endl;
    dx = 0;
    dy = 0;
}

void Actor::setSpeed(int dx_, int dy_)
{
    dx = dx_;
    dy = dy_;
    std::cout << OwnX << "\t" << OwnY << "\t" << dx << "\t" << dy << std::endl;
}
