#include "bigtheater.h"

BigTheater::BigTheater(QWidget *parent) : QGraphicsView (parent)
{
    scene1 = new QGraphicsScene(this);
    clock = new QTimer (this);
    this->setFixedSize(750, 500);
    this->setScene(scene1);
    scene1 -> setBackgroundBrush(Qt::black);

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    Hero = new Actor(this);
    scene1 -> addItem(Hero);

    connect(clock, SIGNAL(timeout()), this, SLOT(update()));
    clock -> start(15);

//    Hero -> setPos(200, 200);
//    Hero->dx = 200;
//    Hero->dy = 200;
    connect(clock, SIGNAL(timeout()), Hero, SLOT(move()));
    std::cout << Hero->x() << "\t" << Hero->y() << "\t" << Hero->dx << "\t" << Hero->dy << std::endl;
}

void BigTheater::keyPressEvent(QKeyEvent* e)
{


//    std::cout << "keyPressEvent " << e->key() << std::endl;
    switch (e -> key()) {
    case Qt::Key_F10:
        QApplication::quit();
        break;
    case Qt::Key_Up:
        Hero->setSpeed(0 ,-10);
//        Hero->goUp();
        break;
    case Qt::Key_Down:
        Hero->setSpeed(0 , 10);
//        Hero->goDown();
        break;
    case Qt::Key_Left:
        Hero->setSpeed(-10, 0);
//        Hero->goLeft();
        break;
    case Qt::Key_Right:
        Hero->setSpeed(10, 0);
//        Hero->goRight();
        break;
    default:
        break;
    }
}
