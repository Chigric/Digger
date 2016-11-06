#include "bigtheater.h"

BigTheater::BigTheater() : QGraphicsView ()
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1125, 660);
    this->setFocus(); //トリビュートで

    clock = new QTimer ();
    scene1 = new QGraphicsScene();

    scene1 -> setSceneRect(0, 0, 1125, 660);
    scene1 -> setBackgroundBrush(Qt::black);
    setScene(scene1);


    terra = new Scenery(300, 300);
    terra->drawScenery(1);
    scene1 -> addItem(terra);
    scene1 -> addLine(300, 300, 375, 300, QPen(Qt::blue));
    scene1 -> addLine(300, 300, 300, 366, QPen(Qt::blue));
    scene1 -> addLine(375, 300, 375, 366, QPen(Qt::blue));
    scene1 -> addLine(300, 366, 375, 366, QPen(Qt::blue));
    scene1 -> addRect(225, 234, 75, 66, QPen(Qt::blue), QBrush(Qt::green) );

    for (int i = 0; i < 1125; i += 75)
    {
        for (int j = 0; j < 660; j += 66){
            scene1 -> addRect(i, j, 75, 66, QPen(Qt::darkGreen), QBrush(Qt::darkGreen) );
            scene1 -> addLine(i,    j,    i+75,  j,    QPen(Qt::darkBlue));
            scene1 -> addLine(i,    j,    i,     j+66, QPen(Qt::blue));
//            scene1 -> addLine(i+75, j,    i+75,  j+66, QPen(Qt::blue));
//            scene1 -> addLine(i,    j+66, i+75,  j+66, QPen(Qt::blue));
        }
    }

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
//        if (Hero->y() != 33)
            Hero->move(0, -speedY);
        break;
    case Qt::Key_Down:
//        if (Hero->y() != 627)
            Hero->move(0, speedY);
        break;
    case Qt::Key_Left:
//        if (Hero->x() != 37)
            Hero->move(-speedX, 0);
        break;
    case Qt::Key_Right:
//        if (Hero->x() != 1087)
            Hero->move(speedX, 0);
        break;
    default:
        break;
    }
}
