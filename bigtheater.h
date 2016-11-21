#ifndef BIGTHEATER_H
#define BIGTHEATER_H

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include <QPaintEvent>

#include "digger.h"
#include "imerald.h"
#include "scenery.h"


class BigTheater : public QGraphicsView
{
    Q_OBJECT
    //int width = 750, height = 500;
    QGraphicsScene *scene;
    QTimer *clock;
    Digger *hero = nullptr;

public:
    explicit BigTheater();
    ~BigTheater();
    void keyPressEvent(QKeyEvent* e);

    Imerald **imeralds;
    Scenery scenery[10][15] /*= nullptr*/;
signals:

public slots:
//    void paintMap();
};

#endif // BIGTHEATER_H
