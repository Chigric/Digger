#ifndef BIGTHEATER_H
#define BIGTHEATER_H

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>

#include <actor.h>
#include "scenery.h"


class BigTheater : public QGraphicsView
{
    Q_OBJECT
    //int width = 750, height = 500;
    QGraphicsScene *scene1;
    QTimer *clock;
    Actor *Hero = nullptr;
    Scenery *terra;

    bool *horizontalBlocks;
    bool *verticalBlocks;
public:
    explicit BigTheater();
    void keyPressEvent(QKeyEvent* e);
signals:

public slots:
};

#endif // BIGTHEATER_H
