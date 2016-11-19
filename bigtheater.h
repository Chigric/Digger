#ifndef BIGTHEATER_H
#define BIGTHEATER_H

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include <QPaintEvent>

#include <actor.h>
#include "scenery.h"


class BigTheater : public QGraphicsView
{
    Q_OBJECT
    //int width = 750, height = 500;
    QGraphicsScene *scene;
    QTimer *clock;
    Actor *hero /*= nullptr*/;
    Scenery **sss/*[10][15]*/ = nullptr;

public:
    explicit BigTheater();
    ~BigTheater();
    void keyPressEvent(QKeyEvent* e);
signals:

public slots:
//    void paintMap();
};

#endif // BIGTHEATER_H
