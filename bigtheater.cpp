#include "bigtheater.h"

BigTheater::BigTheater(QWidget *parent) : QGraphicsView (parent)
{
    scene1 = new QGraphicsScene(this);
    clock = new QTimer (this);
    this->setFixedSize(750, 500);
    this->setScene(scene1);
    scene1 -> setBackgroundBrush(Qt::black);

    Hero = new Actor(this);
    scene1 -> addItem(Hero);
    connect(clock, &QTimer::timeout, Hero, &Actor::nextFrame);
    clock -> start(100);

}

void BigTheater::keyPressEvent(QKeyEvent* e)
{
    switch (e -> key()) {
    case Qt::Key_F10:
        QApplication::quit();
        break;
    case Qt::Key_Up:
        Hero->goUp();
        break;
    case Qt::Key_Down:
        Hero->goDown();
        break;
    case Qt::Key_Left:
        Hero->goLeft();
        break;
    case Qt::Key_Right:
        Hero->goRight();
        break;
    default:
        break;
    }
}
