#include "bigtheater.h"
#include <QDebug>

char Template[12][18] = {
//012345678901234567
 "11111111111111111", //0
 "1.111$11111.....1", //1
 "1.11**11*11.1$111", //2
 "1.$1**11*11.11111", //3
 "1.11**$1*$1.1***1", //4
 "1.11**11*11.1***1", //5
 "1..1**11*11.1***1", //6
 "11.1111$1$1.11111", //7
 "11....11111.11111", //8
 "11111.11111.111*1", //9
 "11111.......11**1", //0
 "11111111111111111", //1
//1 - earth
//$ - monye(is'n cash)
//* - emerald
//. - void
};

BigTheater::BigTheater() : QGraphicsView ()
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(sizeOfBlockX*17, sizeOfBlockY*13);
    this->setFocus(); //トリビュートで

    clock = new QTimer ();
    scene = new QGraphicsScene();

    scene -> setSceneRect(0, sizeOfBlockY/2, sizeOfBlockX*17, sizeOfBlockY*10);
    scene -> setBackgroundBrush(Qt::black);
    setScene(scene);

    qDebug() << "start entry";
//    scenery = new Scenery**[10];
    for (int i = 11; i >= 0; i--){
//        scenery[i] = new Scenery*[15];
        for (int j = 16; j >= 0; j--){
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

    money = new Money(2, 1);
    scene -> addItem(money);

    hero = new Digger(8, 10, this);
    scene -> addItem(hero);

    clock -> start(50);//<20 else digger, money disappears
    connect(clock, SIGNAL(timeout()), scene, SLOT(update()));
}

BigTheater::~BigTheater()
{
    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 17; j++)
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
