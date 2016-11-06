#include "bigtheater.h"

char Template[10][16] = {
//123456787654321
 ".111$11111.....", //1
 ".11**11*11.1$11", //2
 ".$1**11*11.1111", //3
 ".11**$1*$1.1***", //4
 ".11**11*11.1***", //5
 "..1**11*11.1***", //6
 "1.1111$1$1.1111", //7
 "1....11111.1111", //8
 "1111.11111.111*", //9
 "1111.......11**", //10
//1 - earth
//$ - monye(cash)
//* - emerald
//. - void
};

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
    horizontalBlocks = new bool[15];
    verticalBlocks = new bool[10];
    Field = new char*[10];
    for (int i = 0; i < 10; i++)
        Field[i] = new char[15];


    for (int i = 0; i < 1125; i += 75)
    {
        for (int j = 0; j < 660; j += 66){
            switch (Template[j/66][i/75]) {
            case '1':
                scene1 -> addRect(i, j, 75, 66, QPen(Qt::darkGreen), /*QBrush(*/QPixmap(":terra.png"/*)*/)/*Qt::darkGreen*/);
                scene1 -> addLine(i,    j,    i+75,  j,    QPen(Qt::darkBlue));
                scene1 -> addLine(i,    j,    i,     j+66, QPen(Qt::blue));
                break;
            case '$':
                scene1 -> addRect(i, j, 75, 66, QPen(Qt::darkGreen), /*QBrush(*/QPixmap(":cash.png"/*)*/)/*Qt::darkGreen*/);
                scene1 -> addLine(i,    j,    i+75,  j,    QPen(Qt::darkBlue));
                scene1 -> addLine(i,    j,    i,     j+66, QPen(Qt::blue));
                break;
            case '*':
                scene1 -> addRect(i, j, 75, 66, QPen(Qt::darkGreen), /*QBrush(*/QPixmap(":Imerald.png"/*)*/)/*Qt::darkGreen*/);
                scene1 -> addLine(i,    j,    i+75,  j,    QPen(Qt::darkBlue));
                scene1 -> addLine(i,    j,    i,     j+66, QPen(Qt::blue));
                break;
            default:
                break;
            }


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
        if (Hero->y() != 33)
            Hero->move(0, -speedY);
        break;
    case Qt::Key_Down:
        if (Hero->y() != 627)
            Hero->move(0, speedY);
        break;
    case Qt::Key_Left:
        if (Hero->x() != 37)
            Hero->move(-speedX, 0);
        break;
    case Qt::Key_Right:
        if (Hero->x() != 1087)
            Hero->move(speedX, 0);
        break;
    default:
        break;
    }
}
