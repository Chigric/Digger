#include "bigtheater.h"
#include <QDebug>

char Template[blockOnMapY][blockOnMapX+1] = {
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
    setFixedSize(sizeOfBlockX * blockOnMapX, sizeOfBlockY * (blockOnMapY+1) );
    this->setFocus(); //トリビュートで

    scene = new QGraphicsScene();

    scene -> setSceneRect(0, 0, sizeOfBlockX * blockOnMapX, sizeOfBlockY * (blockOnMapY - 1) );
    scene -> setBackgroundBrush(Qt::black);
    setScene(scene);

    display = new QLabel(this);
    display -> setGeometry(10,-5,1000,50);
    D_Style = "QLabel{"
                       "color: green;"
                       "font-family: Courier, monospace;"
                       "font-size:35px;"
                       "}";
    display -> setStyleSheet(D_Style);
//    display -> setAttribute(Qt::WA_TranslucentBackground);

    qDebug() << "start entry";
//    scenery = new Scenery*[blockOnMapY-1];
    for (int i = blockOnMapY-1; i >= 0; i--){
        for (int j = blockOnMapX-1; j >= 0; j--){
//            scenery[i] = new Scenery(sizeOfPixelX * j, sizeOfPixelY * i);
            scenery[i][j].setPos(j, i, this);
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

    points = 0;

    money = new Money(10, 1, this);
    scene -> addItem(money);

    hero = new Digger(8, 10, this);
    scene -> addItem(hero);

    startTimer(50);//<20 else digger, money disappears
}

BigTheater::~BigTheater()
{
    for (int i = 0; i < blockOnMapY; i++)
        for (int j = 0; j < blockOnMapX; j++)
            scene ->removeItem(&scenery[i][j]);

    delete money/*[i]*/;
    delete hero;
    delete scene;
}

void BigTheater::growPoints(uint p_) {points += p_;}

void BigTheater::timerEvent(QTimerEvent*)
{
    scene -> update();
    checkingCollision(hero);
    display -> setText("Points: "+QString::number(points));
}

void BigTheater::checkingCollision(Actor* Act_)
{
    scenery[Act_->getBlock_Y()][Act_->getBlock_X()].eatingBlock(Act_->getF_C(), Act_->getCourse());
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
