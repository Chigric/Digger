#include "digger.h"

Digger::Digger(QObject *parent): Actor(parent)
{
//    setPos(200, 200);
    ownX = 0/*x()*/; ownY = 0/*y()*/;

    sprite = new QPixmap(":Orange.png", "png", Qt::PreferDither);
    sprite->setMask(sprite->createHeuristicMask());

    timer -> start(100);
}
