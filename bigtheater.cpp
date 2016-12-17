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
//    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->setFocus();

    scene = new QGraphicsScene();

    scene -> setSceneRect(0, 0, sizeOfBlockX * blockOnMapX, sizeOfBlockY * (blockOnMapY - 1) );
    scene -> setBackgroundBrush(Qt::black);
    setScene(scene);

    display = new QLabel(this);
    display -> setGeometry(0, -2.5,sizeOfBlockX*blockOnMapX,sizeOfBlockY);
    D_Style = "QLabel{"
                       "color: green;"
                       "font-family: Courier, monospace;"
                       "font-size:35px;"
                       "}";
    display -> setStyleSheet(D_Style);

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
            if (i)
                if (( (Template[i-1][j] != '.' && Template[i][j] == '.') || Template[i][j] != '.') && i)
                    scenery[i][j].setHLine(true);
            if (j)
                if (( (Template[i][j-1] != '.' && Template[i][j] == '.') || Template[i][j] != '.') && j)
                    scenery[i][j].setVLine(true);
            scene -> addItem(&scenery[i][j]);
        }
    }
    qDebug() << "end entry";

    score = 0;
    lives_D = 3;

    timer = new QTimer();
    timer -> start(25);//<20 else digger, money disappears
    connect(timer, SIGNAL(timeout()), scene, SLOT(update(/*QRectF(x,y,w,h)*/)));

    timer->singleShot(0, this, SLOT(startLevel()));
}



BigTheater::~BigTheater()
{
    for (int i = 0; i < blockOnMapY; i++)
        for (int j = 0; j < blockOnMapX; j++)
            scene ->removeItem(&scenery[i][j]);
    scene -> deleteLater();
}

void BigTheater::startLevel()
{
    Emoji = "( ͡° ͜ʖ ͡°)";
    if (lives_D == 1) Emoji = "( ≖ ͜ʖ ≖)";

    money = new Money(10, 1, this);
    scene -> addItem(money);
    bags.push_back(money);

    hero = new Digger(8, 10, this);
    scene -> addItem(hero);
    characters.push_back(hero);

    startGame = true;

    timer -> setInterval(25);
    connect(timer, SIGNAL(timeout()), this, SLOT(frame()));
}

void BigTheater::clearLevel()
{
    scene -> removeItem(money);
    money/*[i]*/ -> deleteLater();
    scene -> removeItem(hero);
    hero -> deleteLater();

    cash.clear();
    lethalSubjects.clear();
    characters.clear();
    bags.clear();

    timer->singleShot(0, this, SLOT(startLevel()));
}

void BigTheater::growPoints(uint p_) {score += p_;}

void BigTheater::frame()
{
    for (auto ch_ : characters)
        checkingCollision(ch_);


    display -> setText("<b>Score: "+QString::number(score)+
                       "\tLives: "+QString::number(lives_D, 2)+
                       "\t"+Emoji+"<b>");
}

void BigTheater::stopAction()
{
    disconnect(timer, SIGNAL(timeout()), this, SLOT(frame()));
    startGame = false;

    for (auto ch_ : characters)
        if (!dynamic_cast<Digger*>(ch_))
            ch_->stopTimer();

    timer->singleShot(3500, this, SLOT(clearLevel()));
}

void BigTheater::checkingCollision(Actor* Act_)
{
    scenery[Act_->getBlock_Y()][Act_->getBlock_X()].eatingBlock(Act_->getF_C(), Act_->pos(),Act_->getCourse());
    for (auto i : bags)
    {
        Act_->stopHere(None);
        if (i->itIsCollision(Act_->getF_C(), true)){
            if (Act_ -> getCourse() == Right)
                qDebug() << "from Right";
            else if (Act_ -> getCourse() == Left){
                i-> moveOnBlock(Left);
                qDebug() << "from Left";
            }
            else if (Act_ -> getCourse() == Down){
                Act_->stopHere(Down);
                qDebug() << "from Down";
            }
        }
    }
    //
    for (auto i : cash)
    {
        if (i->itIsCollision(Act_->getF_C(), true)){
            cash.removeOne(i);
            i->deleteLater();
            growPoints(costOfCash);
        }
    }
    //falling bag
    for (auto i : lethalSubjects)
    {
        if (i->itIsCollision(Act_->pos(), false) || Act_->itIsCollision(i->pos(), false)){
            Act_->die();
            if(dynamic_cast<Digger*>(Act_)){
                --lives_D;
                stopAction();
                Emoji = "( ͡ᵔ ͜ʖ ͡ᵔ)";
            }
        }
        qDebug() << i->pos() << Act_->pos();
    }
}


void BigTheater::keyPressEvent(QKeyEvent* e)
{
//    std::cout << "keyPressEvent " << e->key() << std::endl;
    switch (e -> key()) {
    case Qt::Key_Escape:
    case Qt::Key_F10:
        QApplication::quit();
        break;
    case Qt::Key_Space:
        stopAction();  // restart
    default:
        if (startGame)
            hero -> keyPressEvent(e);
        break;
    }
}

void BigTheater::keyReleaseEvent(QKeyEvent *e)
{
    hero -> keyReleaseEvent(e);
}

void BigTheater::addToCash(Money *m_)
{
    cash.push_back(m_);
}
void BigTheater::addToLethalSubjects(Actor *a_)
{
    bags.removeOne(dynamic_cast<Money*>(a_));
    lethalSubjects.push_back(a_);
    Emoji = "( ͠° ͟ʖ ͡°)";
}

void BigTheater::deleteFromLethalSubjects(Actor *a_)
{
    lethalSubjects.removeOne(a_);
}
