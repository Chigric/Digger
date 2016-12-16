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


class BigTheater : public QGraphicsView
{
    Q_OBJECT

    bool startGame;
    uint lives_D;
    uint score;
//    qreal x,y,w,h;

    Digger *hero;
    QString D_Style;
    QLabel *display;
    QString Emoji;

    QList<Money*> cash;
    QList<Money*> bags;
    QList<Actor*> lethalSubjects;
    QList<Actor*> characters;

    void checkingCollision(Actor *Act_);

    QTimer* timer;
public:

    QGraphicsScene *scene;
    Money *money;
    Scenery scenery[blockOnMapY][blockOnMapX];

    explicit BigTheater();
    ~BigTheater();
    void growPoints(uint p_);
    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent* e);

    void stopAction();

    void addToCash(Money *m_);
    void addToLethalSubjects(Actor *a_);
    void deleteFromLethalSubjects(Actor* a_);
signals:

public slots:
    void frame();
    void startLevel();
    void clearLevel();
};

#endif // BIGTHEATER_H
