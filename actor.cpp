#include "actor.h"

Actor::Actor() :  QGraphicsPixmapItem()
{
    OwnX = 25;
    OwnY= 25;

    sizeOfItemX  = 50;
    sizeOfItemY = 50;
    sizeOfPictureX =  5;
    sizeOfPictureY  = 5;

    currentFrame = 0;
    sprite = new QPixmap(":Orange.png", "png", Qt::PreferDither);
    sprite->setMask(sprite->createHeuristicMask());
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer -> start(100);
    std::cout << OwnX << "\t" << OwnY << "\t" << std::endl;
}

void Actor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    std::cout << "paint" << std::endl;
    painter -> drawPixmap(OwnX-sizeOfItemX/2, OwnY-sizeOfItemY/2, sizeOfItemX, sizeOfItemY, *sprite, currentFrame, 0, sizeOfPictureX, sizeOfPictureY);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Actor::nextFrame()
{
    std::cout << "nextFrame " << currentFrame << std::endl;
    qreal penWidth = 0;//たぶん
    currentFrame += 5;
    if (currentFrame >= 25 ) currentFrame = 0;
    this->update(OwnX-sizeOfItemX/2, OwnY-sizeOfItemY/2, sizeOfItemX, sizeOfItemY);
}

void Actor::move(int dx_, int dy_)
{
    setTransformOriginPoint(OwnX, OwnY);
    setRotation( atan2(dx_, dy_) *180/M_PI - 90);

    OwnX += dx_;
    OwnY += dy_;
    std::cout << OwnX <<" "<< OwnY << std::endl;
}

Actor::~Actor()
{
    std::cout << "Delete Actor" << std::endl;
}
