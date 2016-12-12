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
    //int width = 750, height = 500;
    uint points;
    Digger *hero;
    QString D_Style;
    QLabel *display;

    void checkingCollision(Actor *Act_);

public:

    QGraphicsScene *scene;
    Money *money;
    Scenery scenery[blockOnMapY][blockOnMapX];

    explicit BigTheater();
    ~BigTheater();
    void growPoints(uint p_);
    void keyPressEvent(QKeyEvent* e);
    void timerEvent(QTimerEvent*);
signals:

public slots:
};

#endif // BIGTHEATER_H
