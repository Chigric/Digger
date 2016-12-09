#ifndef BIGTHEATER_H
#define BIGTHEATER_H

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include <QTimerEvent>
#include <QPaintEvent>

#include "digger.h"
#include "scenery.h"
#include "money.h"


class BigTheater : public QGraphicsView
{
    Q_OBJECT
    //int width = 750, height = 500;
    Digger *hero;

    void checkingCollision(Actor *Act_);

public:
    explicit BigTheater();
    ~BigTheater();
    void keyPressEvent(QKeyEvent* e);
    void timerEvent(QTimerEvent*);

    QGraphicsScene *scene;
    Money *money;
    Scenery scenery[blockOnMapY][blockOnMapX];
signals:

public slots:
};

#endif // BIGTHEATER_H
