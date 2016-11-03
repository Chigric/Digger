#include "actor.h"

Actor::Actor(QObject *parent) : QObject (parent), QGraphicsPixmapItem()
{
//    setPos(200, 200);
    dx = 0; dy = 0;

    currentFrame = 0;
    sprite = new QPixmap(":Orange.png", "png", Qt::PreferDither);
    sprite->setMask(sprite->createHeuristicMask());
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
//    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer -> start(100);
    std::cout << x() << "\t" << y() << "\t" << dx << "\t" << dy << std::endl;
}

QRectF Actor::boundingRect() const
{
    qreal penWidth = 1;//???
//    return QRectF( x()+dx - penWidth, y()+dy - penWidth,
//                  50 - penWidth, 50 - penWidth);
    return QRectF(x()/*+dx*/, y()/*+dy*/,50,50);
}

void Actor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter -> drawPixmap(x()/*+dx*/, y()/*+dy*/, 50, 50, *sprite, currentFrame, 0, 5, 5);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Actor::nextFrame()
{
    qreal penWidth = 0;//???
    currentFrame += 5;
    if (currentFrame >= 25 ) currentFrame = 0;

    this->update( x()/*+dx*/+penWidth, y()/*+dy*/+penWidth, 50, 50);
//    setPos(200, 200);
//    dx = 0; dy = 0;
}

void Actor::move()
{
    moveBy(dx,dy);
    std::cout << x() <<" "<< y() << std::endl;
    dx = 0;
    dy = 0;
}

void Actor::setSpeed(int dx_, int dy_)
{
    dx = dx_;
    dy = dy_;
}
