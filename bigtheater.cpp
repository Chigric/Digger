#include "bigtheater.h"
#include <QDebug>

char Template[blockOnMapY][blockOnMapX+1] = {
//012345678901234567
 "#################", //0
 "#.###B#####.....#", //1
 "#.##^^##^##.#B###", //2
 "#.B#^^##^##.#####", //3
 "#.##^^##^B#.#^^^#", //4
 "#.##^^##^##.#^^^#", //5
 "#..#^^##^##.#^^^#", //6
 "##.####B#B#.#####", //7
 "##....#####.#####", //8
 "#####.#####.###^#", //9
 "#####.......##^^#", //0
 "#################", //1
//# - earth
//B - bag of monye
//^ - emerald
//. - void
};

BigTheater::BigTheater() : QGraphicsView ()
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(sizeOfBlockX * blockOnMapX, sizeOfBlockY * (blockOnMapY+1) );
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
            case '#':
                qDebug() << "#";
                scenery[i][j].setBox(true);
                break;
            case 'B':{
                qDebug() << "B";
                //+ Monye(is'n cash)
                scenery[i][j].setBox(true);
                auto m_ = new Money(j, i, this);
                money.push_back(m_);
                scene->addItem(m_);
                break;
            }
            case '^':
                qDebug() << "^";
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
    timer -> start(25);
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
    if(lives_D){
        Emoji = "( ͡° ͜ʖ ͡°)";
        if (lives_D == 1) Emoji = "( ≖ ͜ʖ ≖)";

        hero = new Digger(8, 10, this);
        scene -> addItem(hero);
        characters.push_back(hero);

        enemy = new Nobbin(15, 1, this);
        scene -> addItem(enemy);
        characters.push_back(enemy);

        startGame = true;
        stopGame = false;

        timer -> setInterval(25);
        connect(timer, SIGNAL(timeout()), this, SLOT(frame()));
    }
    else {Emoji = "Game_Over"; stopGame = true; timer->singleShot(0, this, SLOT(frame()));}
}

void BigTheater::clearLevel()
{
    for (auto i : characters)
    {
        scene -> removeItem(i);
    }
    characters.clear();

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

void BigTheater::stopAllAction()
{
    disconnect(timer, SIGNAL(timeout()), this, SLOT(frame()));
    stopGame = true;

    for (auto ch_ : characters)
        ch_ -> stopTimer();

    for (auto i : money)
        i -> stopTimer();
}

void BigTheater::beginAllAction()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(frame()));
    stopGame = false;

    for (auto ch_ : characters)
        ch_ -> beginTimer();
    for (auto i : money)
        i -> beginTimer();
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
    if (dynamic_cast<Digger*>(Act_))
        scenery[Act_->getBlock_Y()][Act_->getBlock_X()].eatingBlock(Act_->getF_C(), Act_->pos(),Act_->getCourse());
    else{
        if (hero -> itIsCollision(Act_->getF_C(), true))
        {
            hero -> die();
            --lives_D;
            stopAction();
            Emoji = "( ͡ᵔ ͜ʖ ͡ᵔ)";
        }
    }
    for (auto i : money)
    {
        switch (i->getStat()) {
        case 0:
            //just bag
            Act_ -> stopHere(None);
            if (i->itIsCollision(Act_->getF_C(), true)){
                qDebug() << "Collision";

                switch (Act_ -> getCourse()) {
                case Right:
                    i -> moveOnBlock(Right);
                    qDebug() << "from Right";
                    break;
                case Left:
                    i -> moveOnBlock(Left);
                    qDebug() << "from Left";
                    break;
                case Down:
                    Act_ -> stopHere(Down);
                    qDebug() << "from Down";
                    break;
                case Up:
                    Act_ -> stopHere(Up);
                    qDebug() << "from Up";
                    break;
                default:
                    break;
                }
            }
            break;
        case 1:
            //falling bag
            if (i->itIsCollision(Act_->pos(), false) || Act_->itIsCollision(i->pos(), false)){
                Act_->die();
                if(dynamic_cast<Digger*>(Act_)){
                    --lives_D;
                    stopAction();
                    Emoji = "( ͡ᵔ ͜ʖ ͡ᵔ)";
                }
            }
            break;
        case 2:
            //cash
            if (i->itIsCollision(Act_->getF_C(), true)){
                scene -> removeItem(i);
                money.removeOne(i);
                growPoints(costOfCash);
            }
            break;
        default:
            break;
        }
    }
}


void BigTheater::keyPressEvent(QKeyEvent* e)
{
//    std::cout << "keyPressEvent " << e->key() << std::endl;
    if (!stopGame){
        switch (e -> key()) {
        case Qt::Key_Escape:
        case Qt::Key_F10:
            QApplication::quit();
            break;
        case Qt::Key_Space:
            stopAllAction();
        default:
            if (startGame)
                hero -> keyPressEvent(e);
            break;
        }
    }
    else
        switch (e -> key()) {
        case Qt::Key_Escape:
        case Qt::Key_F10:
            QApplication::quit();
            break;
        case Qt::Key_Space:
            beginAllAction();
        default:
            break;
        }
}

void BigTheater::keyReleaseEvent(QKeyEvent *e)
{
    hero -> keyReleaseEvent(e);
}

void BigTheater::deleteFromCharacters(Actor *a_)
{
    scene -> removeItem(a_);
    characters.removeOne(a_);
}
