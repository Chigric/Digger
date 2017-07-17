#ifndef BIGTHEATER_H
#define BIGTHEATER_H

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include <QTimerEvent>
#include <QPaintEvent>
#include <QLabel>

#include "digger.h"
#include "scenery.h"
#include "money.h"
#include "nobbin.h"

#define MSEC 25

class BigTheater : public QGraphicsView
{
    Q_OBJECT
    //Flags
    bool heroLives;
    bool stopGame;
    //Statistic
    int lives_D;
    uint score;
    uint currentLevel;
    //Start_Digger
    uint start_X;
    uint start_Y;
    //Number_Of_Keystrokes
    int NumberOfKeystrokes;
    //Number_for_Timer
    int remaining;
    //Enemy
    int numbersNowEnem;
    int numbersAllEnem;
    int addingEnem;
    //Info
    QString D_Style;
    QLabel *display;
    QString Emoji;
    //Characters
    QList<Money*> money;
    QList<Actor*> characters;
    Digger *hero;
    //Timers
    QTimer* timer;
    QTimer* timerForEnem;
    //Map
    char plan[blockOnMapY][blockOnMapX+1];
    //Function ...
    //OF Level
    void setStatistic();
    void loaderOfLevel(uint num);
    void startLevel(uint X, uint Y);
    void clearAllLevel();//with money
    //OF Collision
    void checkingCollision(Actor *Act_);
public:
    explicit BigTheater();
    ~BigTheater();
    QGraphicsScene *scene;
    Scenery/****/ scenery[blockOnMapY][blockOnMapX];
    //Score
    void growPoints(uint p_);
    //Keyboard
    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent* e);
    //Action
    void afterDeath_Hero();
    void stopAllAction();
    void beginAllAction();
    void setEmoji(const QString e_);
    //Arrays
    void deleteFromCharacters(Actor* a_);
    void deleteFromMoney(Money* m_);
signals:

private slots:
    void frame();
    void clearLevel();//without money, except "Cash"
    void addEnemy();
};

#endif // BIGTHEATER_H
