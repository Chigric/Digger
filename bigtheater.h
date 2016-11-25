#ifndef BIGTHEATER_H
#define BIGTHEATER_H

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>
#include <QPaintEvent>

#include "digger.h"
#include "scenery.h"
#include "money.h"


class BigTheater : public QGraphicsView
{
    Q_OBJECT
    //int width = 750, height = 500;
    QTimer *clock;
    Digger *hero = nullptr;

public:
    explicit BigTheater();
    ~BigTheater();
    void keyPressEvent(QKeyEvent* e);

    QGraphicsScene *scene;
    Money *money;
    Scenery scenery[10][15] /*= nullptr*/;
signals:

public slots:
};

#endif // BIGTHEATER_H
