#include "bigtheater.h"

BigTheater::BigTheater() : QGraphicsView ()
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(750, 500);
    this->setFocus(); //トリビュートで

    clock = new QTimer ();
    scene1 = new QGraphicsScene();

    scene1 -> setSceneRect(0, 0, 750, 500);
    scene1 -> setBackgroundBrush(Qt::black);
    setScene(scene1);

    Hero = new Actor();
    scene1 -> addItem(Hero);


    clock -> start(15);
    connect(clock, SIGNAL(timeout()), scene1, SLOT(update()));
}

void BigTheater::keyPressEvent(QKeyEvent* e)
{
//    std::cout << "keyPressEvent " << e->key() << std::endl;
    switch (e -> key()) {
    case Qt::Key_F10:
        QApplication::quit();
        break;
    case Qt::Key_Up:
        Hero->move(0, -10);
        break;
    case Qt::Key_Down:
        Hero->move(0, 10);
        break;
    case Qt::Key_Left:
        Hero->move(-10, 0);
        break;
    case Qt::Key_Right:
        Hero->move(10, 0);
        break;
    default:
        break;
    }
}
