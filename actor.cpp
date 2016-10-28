#include "actor.h"

Actor::Actor(QObject *parent) : QObject (parent), QGraphicsItem()
{
    dx = 0; dy = 0;

    currentFrame = 0;
    sprite = new QPixmap(":Orange.png", "png", Qt::PreferDither);
    sprite->setMask(sprite->createHeuristicMask());
//    timer = new QTimer();
//    connect(timer, &QTimer::timeout, this, &Actor::nextFrame);
//    timer -> start(100);
}

QRectF Actor::boundingRect() const
{
    return QRectF(x()+dx, y()+dy,50,50);
}

void Actor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter -> drawPixmap(x()+dx, y()+dy, 50, 50, *sprite, currentFrame, 0, 5, 5);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Actor::nextFrame()
{
    currentFrame += 5;
    if (currentFrame >= 25 ) currentFrame = 0;

    this->update(x()+dx,y()+dy,50,50);
//    dx = 0; dy = 0;
}
