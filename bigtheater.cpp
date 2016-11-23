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

    qDebug() << "start entry";
//    scenery = new Scenery**[10];
    for (int i = 9; i >= 0; i--){
//        scenery[i] = new Scenery*[15];
        for (int j = 14; j >= 0; j--){
//            scenery[i][j] = new Scenery(sizeOfPixelX * j, sizeOfPixelY * i);
            scenery[i][j].setPos(j, i);
            switch (Template[i][j]){
            case '1':
                qDebug() << "1";
                scenery[i][j].setBox(true);
                break;
            case '$':
                qDebug() << "$";
                //+ Monye(is'n cash)
                scenery[i][j].setBox(true);
                break;
            case '*':
                qDebug() << "*";
                //+ Imerald
                scenery[i][j].setBox(true);
                scenery[i][j].setImerald(true);
                break;
            default:
                qDebug() << '.';
                break;
            }
            if (( (Template[i-1][j] != '.' && Template[i][j] == '.') || Template[i][j] != '.') && i)
                scenery[i][j].setHLine(true);
            if (( (Template[i][j-1] != '.' && Template[i][j] == '.') || Template[i][j] != '.') && j)
                scenery[i][j].setVLine(true);
            scene -> addItem(&scenery[i][j]);
        }
    }
    qDebug() << "end entry";

    money = new Money(1, 0);
    scene -> addItem(money);

    hero = new Digger(0, 0, this);
    scene -> addItem(hero);

    clock -> start(50);//<20 else digger, money disappears
    connect(clock, SIGNAL(timeout()), scene, SLOT(update()));
}

BigTheater::~BigTheater()
{
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 15; j++)
            scene ->removeItem(&scenery[i][j]);

    delete money/*[i]*/;
    delete clock;
    delete hero;
    delete scene;
}

void BigTheater::keyPressEvent(QKeyEvent* e)
{
//    std::cout << "keyPressEvent " << e->key() << std::endl;
    switch (e -> key()) {
    case Qt::Key_F10:
        QApplication::quit();
        break;
    default:
        hero -> keyPressEvent(e);
        break;
    }
}
