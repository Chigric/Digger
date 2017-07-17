#include "bigtheater.h"
#include <QDebug>

extern char Template[blockOnMapY][blockOnMapX+1];
extern char Template_2[blockOnMapY][blockOnMapX+1];

BigTheater::BigTheater() : QGraphicsView ()
{
    //Window
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(sizeOfBlockX * blockOnMapX,
                 sizeOfBlockY * (blockOnMapY+1) );
    this->setFocus();
    //"Scene"
    scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, sizeOfBlockX * blockOnMapX,
                        sizeOfBlockY * (blockOnMapY-1));
    scene->setBackgroundBrush(Qt::black);
    setScene(scene);
    //"Display"
    display = new QLabel(this);
    display->setGeometry(0, -2.5, sizeOfBlockX*blockOnMapX,
                           sizeOfBlockY);
    D_Style = "QLabel{"
                       "color: green;"
                       "font-family: Courier, monospace;"
                       "font-size:35px;"
                       "}";
    display -> setStyleSheet(D_Style);
    //Keyboard
    NumberOfKeystrokes = 0;
    //Level
    currentLevel = 0;
    setStatistic();
    loaderOfLevel(currentLevel);
}

BigTheater::~BigTheater()
{
    for (int i = 0; i < blockOnMapY; i++)
        for (int j = 0; j < blockOnMapX; j++)
            scene ->removeItem(&scenery[i][j]);
    scene->deleteLater();
}

void BigTheater::setStatistic(){
    score = 0;
    lives_D = 3;
}

void BigTheater::loaderOfLevel(uint num)
{
    memcpy(plan, Template_2, sizeof(Template_2));
    currentLevel = num;
    qDebug() << "start entry";
//    scenery = new Scenery*[blockOnMapY-1];
    for (int i = blockOnMapY-1; i >= 0; i--){
        for (int j = blockOnMapX-1; j >= 0; j--){
//            scenery[i] = new Scenery(j, i, this);
            scenery[i][j].setPos(j, i, this);
            switch (plan[i][j]){
            case '#':
                //just Terra
                qDebug() << '#';
                scenery[i][j].setBox(true);
                break;
            case 'B':{
                qDebug() << 'B';
                //Monye(is'n cash)
                scenery[i][j].setBox(true);
                auto m_ = new Money(j, i, this);
                money.push_back(m_);
                scene->addItem(m_);
                break;
            }
            case '^':
                qDebug() << '^';
                //Imerald
                scenery[i][j].setBox(true);
                scenery[i][j].setImerald(true);
                break;
            default:
                qDebug() << '.';

                break;
            }
            if (i)
                if (( ( plan[i-1][j] != '.' &&
                       plan[i][j] == '.' ) ||
                      plan[i][j] != '.') && i)
                    scenery[i][j].setHLine(true);
            if (j)
                if (( (plan[i][j-1] != '.' &&
                       plan[i][j] == '.') ||
                      plan[i][j] != '.') && j)
                    scenery[i][j].setVLine(true);
            scene->addItem(&scenery[i][j]);
        }
    }
    qDebug() << "end entry";
    timer = new QTimer();
    timer -> start(MSEC);
    connect(timer, SIGNAL(timeout()),
            scene, SLOT(update(/*QRectF(x,y,w,h)*/)));
    numbersAllEnem = num+0  ;//6
    numbersNowEnem = num+0  ;//3
    if(!num){
        start_X = 8; start_Y = 10;
    }
    startLevel(start_X, start_Y);
}

void BigTheater::startLevel(uint X, uint Y)
{
    if(lives_D){
        Emoji = "( ͡° ͜ʖ ͡°)";
        if (lives_D == 1) Emoji = "( ≖ ͜ʖ ≖)";
        //Hero
        hero = new Digger(X, Y, this);
        scene -> addItem(hero);
        characters.push_back(hero);
        //Number_of_Enemies
        addingEnem = 0;
        //Flags
        heroLives = true;
        stopGame = false;
        //Timers
        connect(timer, SIGNAL(timeout()),
                this, SLOT(frame()));
        timerForEnem = new QTimer();
        timerForEnem->start(MSEC*100);
        timerForEnem->
                singleShot(0, this,
                           SLOT(addEnemy()));
    }
    else {
        //Game_Over
        Emoji = "Game_Over";
        stopGame = true;
        timer->singleShot(0, this, SLOT(frame()));
    }
}

void BigTheater::addEnemy()
{
    if ((addingEnem != numbersNowEnem) &&
            numbersAllEnem){
        auto N_= new Nobbin(15, 1, this);
        scene -> addItem(N_);
        characters.push_back(N_);
        ++addingEnem;
        --numbersAllEnem;
        connect(timerForEnem, SIGNAL(timeout()),
                this, SLOT(addEnemy()));
        timerForEnem->setInterval(MSEC*100);
    }
    else{
        disconnect(timerForEnem, SIGNAL(timeout()),
                   this, SLOT(addEnemy()));
        timerForEnem->stop();
    }
    remaining = 0;
}

void BigTheater::clearLevel()
{
    //Without_Money, except "Cash"
    for (auto i : money) {
        if (i->getStat() == 4) {
            //if (i == Cash)
            scene -> removeItem(i);
            money.removeOne(i);
            i->deleteLater();
        }
    }
    for (auto i : characters) {
        scene -> removeItem(i);
    }
    characters.clear();
    startLevel(start_X, start_Y);
}

void BigTheater::clearAllLevel()
{
    //With_Money
    for (auto i : money) {
        scene -> removeItem(i);
        money.removeOne(i);
        i->deleteLater();
    }
    for (auto i : characters) {
        scene -> removeItem(i);
    }
    characters.clear();
    startLevel(start_X, start_Y);
}

void BigTheater::growPoints(uint p_) {score += p_;}

void BigTheater::frame()
//Calculation_All_Action and Change_"display"
{
    for (auto ch_ : characters)
        checkingCollision(ch_);

    display->setText("<b>Score: " +
                     QString::number(score) +
                     "\tLives: " +
                     QString::number(lives_D, 2) +
                     "\t"+Emoji+"<b>");
}

void BigTheater::stopAllAction()
{
//    disconnect(timer, SIGNAL(timeout()),
//               this, SLOT(frame()));
    stopGame = true;
    timer->stop();
    remaining = timerForEnem->remainingTime();
    timerForEnem->stop();
    display -> setText("<b>Score: " +
                       QString::number(score) +
                       "\tLives: " +
                       QString::number(lives_D, 2) +
                       "\t"+Emoji+"<b>");
    for (auto ch_ : characters)
        ch_ -> stopTimer();
    for (auto i : money)
        i -> stopTimer();
}

void BigTheater::setEmoji(const QString e_)
{
    Emoji = e_;
}

void BigTheater::beginAllAction()
{
//    connect(timer, SIGNAL(timeout()),
//            this, SLOT(frame()));
    stopGame = false;
    timer->start(MSEC);
    //***MAGIC_QT-Timer(remaining)***
    if (remaining > 0)
        timerForEnem->start(remaining);
    setEmoji("( ͡° ͜ʖ ͡°)");
    if (lives_D == 1) setEmoji("( ≖ ͜ʖ ≖)");

    for (auto ch_ : characters)
        ch_ -> beginTimer();
    for (auto i : money)
        i -> beginTimer();
}

void BigTheater::afterDeath_Hero()
{
    disconnect(timer, SIGNAL(timeout()),
               this, SLOT(frame()));
    heroLives = false;
    setEmoji("( ͡ᵔ ͜ʖ ͡ᵔ)");
    //For correct adding
    numbersAllEnem += addingEnem;

    for (auto ch_ : characters)
        if (!dynamic_cast<Digger*>(ch_))
            ch_->stopTimer();
    timer->singleShot(3500, this, SLOT(clearLevel()));
}

void BigTheater::checkingCollision(Actor* Act_)
{
    if (dynamic_cast<Digger*>(Act_)){
        //eating block by Digger
        scenery[Act_->block_Y()][Act_->block_X()].
                eatingBlock(
                    Act_->getF_C(),
                    Act_->pos(),
                    Act_->getCourse()
                    );
    }
    else{
        if (hero->itIsCollision(Act_->getF_C(), true))
        //collision enemy with Digger
        {
            hero->die();
            --lives_D;
            afterDeath_Hero();
        }
    }
    Act_ -> stopHere(None);
    for (auto i : money)
    {
        switch (i->getStat()) {
        case 0:
            //just bag
        case 1:
            //bag is moving on horiz
//            Act_->stopHere(None);
            if (i->itIsCollision(Act_->getF_C(), true)){
                qDebug() << "Collision";
                switch (Act_ -> getCourse()) {
                case Right:
                    i -> moveOnBlock(Right);
//                    qDebug() << "from Right";
                    break;
                case Left:
                    i -> moveOnBlock(Left);
//                    qDebug() << "from Left";
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
                    Act_ -> stopHere(None);
                    break;
                }
            }
            break;
        case 3:
            //falling bag
            if ( i->itIsCollision(Act_->pos(), false) ||
                    Act_->itIsCollision(i->pos(), false) )
            {
                Act_->die();
                if(dynamic_cast<Digger*>(Act_)){
                    --lives_D;
                    afterDeath_Hero();
                }
            }
            break;
        case 4:
            //cash
            if (i->itIsCollision(Act_->getF_C(), true)){
                scene->removeItem(i);
                money.removeOne(i);
                i->deleteLater();
                if (dynamic_cast<Nobbin*>(Act_))
                    setEmoji("[̲̅$̲̅(̲̅ ͡° ͜ʖ ͡°̲̅)̲̅$̲̅]");
                else growPoints(costOfCash);
            }
            break;
        default:
            break;
        }
    }
}


void BigTheater::keyPressEvent(QKeyEvent* e)
{
    if (!stopGame){
        switch (e -> key()) {
        case Qt::Key_Escape:
        case Qt::Key_F10:
            QApplication::quit();
            break;
        case Qt::Key_Space:
            setEmoji("(∪｡∪)｡｡｡zzZ");
            stopAllAction();
            break;
        case Qt::Key_Tab:
            //restart Game
            disconnect(timer, SIGNAL(timeout()),
                       this, SLOT(frame()));
            clearAllLevel();
            setStatistic();
            loaderOfLevel(0);
            break;
        default:
            if (heroLives)
                hero->keyPressEvent(e);
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
    ++NumberOfKeystrokes;
}

void BigTheater::keyReleaseEvent(QKeyEvent *e)
{
    --NumberOfKeystrokes;
    if (!NumberOfKeystrokes)
        hero->keyReleaseEvent(e);
    Q_UNUSED(e);
}

void BigTheater::deleteFromCharacters(Actor *a_)
{
    scene -> removeItem(a_);
    characters.removeOne(a_);
    if (dynamic_cast<Nobbin*> (a_)){
        --addingEnem;
        if(numbersAllEnem != 0){
            if (timerForEnem->isActive())
                timerForEnem->setInterval(MSEC*20);
            else
                timerForEnem->start(MSEC*20);
            connect(timerForEnem, SIGNAL(timeout()),
                    this, SLOT(addEnemy()));
            growPoints(costOfNobbin);
            setEmoji("(•ิ-•ิ)?");
        } else {
            setEmoji("(╬ Ò﹏Ó) Win");
            stopAllAction();
        }
    }
    a_->deleteLater();
}

void BigTheater::deleteFromMoney(Money *m_)
{
    scene -> removeItem(m_);
    money.removeOne(m_);
    m_->deleteLater();
}
