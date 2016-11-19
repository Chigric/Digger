#include "bigtheater.h"
#include <QDebug>

char Template[10][16] = {
//0123456789012345
 ".111$11111.....", //0
 ".11**11*11.1$11", //1
 ".$1**11*11.1111", //2
 ".11**$1*$1.1***", //3
 ".11**11*11.1***", //4
 "..1**11*11.1***", //5
 "1.1111$1$1.1111", //6
 "1....11111.1111", //7
 "1111.11111.111*", //8
 "1111.......11**", //9
//1 - earth
//$ - monye(is'n cash)
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
    scene = new QGraphicsScene();

    scene -> setSceneRect(0, 0, 1125, 660);
    scene -> setBackgroundBrush(Qt::black);
    setScene(scene);
//    horizontalBlocks = new bool[15];//15*9
//    verticalBlocks = new bool[10];//14*10
//    scene1 = new char*[10];
//    for (int i = 0; i < 10; i++)
//        Field[i] = new char[15];

    qDebug() << "start entry";
    sss = new Scenery*[10];
    for (int i = 9; i >= 0; i--){
        sss[i] = new Scenery[15];
        for (int j = 14; j >= 0; j--){
            sss[i][j].setPos(75 * j, 66 * i);
            switch (Template[i][j]){
            case '1':
                qDebug() << "1";
                sss[i][j].setBox(true);
                break;
            case '$':
                qDebug() << "$";
                //+ Monye(is'n cash)
                sss[i][j].setBox(true);
                break;
            case '*':
                qDebug() << "*";
                //+ Imerald
                sss[i][j].setBox(true);
                break;
            default:
                break;
            }

            if ((Template[i-1][j] != '.' && Template[i][j] == '.') || Template[i][j] != '.')
                sss[i][j].setHLine(true);
            if ((Template[i][j-1] != '.' && Template[i][j] == '.') || Template[i][j] != '.')
                sss[i][j].setVLine(true);
            scene -> addItem(&sss[i][j]);
        }
    }
    qDebug() << "end entry";




//    for (int i = 0; i < 10; i++)
//    {
//        for (int j = 0; j < 15; j++){
//            switch (Field[i][j]) {
//            case '1':
//                std::cout << '1';
//                scene -> addRect(J_, I_, 75 -1, 66 -1, QPen(Qt::darkGreen), /*QBrush(*/QPixmap(":-terra.png"/*)*/)/*Qt::darkGreen*/);
//                break;
//            case '$':
//                std::cout << '$';
//                scene -> addRect(J_, I_, 75 -1, 66 -1, QPen(Qt::darkGreen), /*QBrush(*/QPixmap(":-cash.png"/*)*/)/*Qt::darkGreen*/);
//                break;
//            case '*':
//                std::cout << '*';
//                scene -> addRect(J_, I_, 75 -1, 66 -1, QPen(Qt::darkGreen), /*QBrush(*/QPixmap(":-Imerald.png"/*)*/)/*Qt::darkGreen*/);
//                break;
//            default:
//                std::cout << '.';
//                break;
//            }
//            if (verticalBlocks[i] == true)
//                scene -> addLine(J_, I_, J_+75, I_, QPen(Qt::blue));
//            else
//                std::cout << "false1";

//            if (horizontalBlocks[j] == true)
//                scene -> addLine(J_, I_, J_, I_+66, QPen(Qt::blue));
//            else
//                std::cout << "false2";
////            std::cout << Field[i][j];
//        }
//        std::cout << std::endl;
 //    }

    hero = new Actor();
    scene -> addItem(hero);

    clock -> start(15);
    connect(clock, SIGNAL(timeout()), scene, SLOT(update()));
}

BigTheater::~BigTheater()
{
    for (int i = 0; i < 10; i++)
        delete[] sss[i];
    delete clock;
    delete scene;
}

void BigTheater::keyPressEvent(QKeyEvent* e)
{
//    std::cout << "keyPressEvent " << e->key() << std::endl;
    switch (e -> key()) {
    case Qt::Key_F10:
        QApplication::quit();
        break;
    case Qt::Key_Up:
        if (hero->y() != 33)
            hero->move(0, -speedY, Up);
        break;
    case Qt::Key_Down:
        if (hero->y() != 627)
            hero->move(0, speedY, Down);
        break;
    case Qt::Key_Left:
        if (hero->x() != 37)
            hero->move(-speedX, 0, Left);
        break;
    case Qt::Key_Right:
        if (hero->x() != 1087)
            hero->move(speedX, 0, Right);
        break;
    default:
        break;
    }
}
