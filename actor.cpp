#include "actor.h"

Actor::Actor() :  QGraphicsPixmapItem()
{
    //paramof_block*#block + center_of_block
    OwnX = 75*0 + 37;
    OwnY= 66*0 + 33;

    sizeOfItemX  = 51;
    sizeOfItemY = 36;
    sizeOfPictureX =  17;
    sizeOfPictureY  = 12;

    currentFrame = 0;
    sprite = new QPixmap(":Digger.png", "png", Qt::PreferDither);
    sprite->setMask(sprite->createHeuristicMask());
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer -> start(50);
    std::cout << OwnX << "\t" << OwnY << "\t" << std::endl;
}

void Actor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    std::cout << "paint" << std::endl;
    painter -> drawPixmap(OwnX-sizeOfItemX/2, OwnY-sizeOfItemY/2, sizeOfItemX, sizeOfItemY, *sprite, currentFrame, 0, sizeOfPictureX, sizeOfPictureY);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Actor::nextFrame()
{
//    std::cout << "nextFrame " << currentFrame << std::endl;
    qreal penWidth = 0;//たぶん
    currentFrame += 17;
    if (currentFrame >= 102 ) currentFrame = 0;
    this->update(OwnX-sizeOfItemX/2, OwnY-sizeOfItemY/2, sizeOfItemX, sizeOfItemY);
}

int Actor::x() const {return OwnX;}
int Actor::y() const {return OwnY;}

void Actor::move(int dx_, int dy_)
{
//    setTransformOriginPoint(OwnX, OwnY);
//    setRotation( atan2(dx_, dy_) *180/M_PI - 90);
    int X = OwnX % 75;
    int Y = OwnY % 66;
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
    std::cout << OwnX <<"\t"<< OwnY << std::endl;
}

Actor::~Actor()
{
    std::cout << "Delete Actor" << std::endl;
}
