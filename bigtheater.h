#ifndef BIGTHEATER_H
#define BIGTHEATER_H

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QTimer>

#include "actor.h"


class BigTheater : public QGraphicsView
{
    Q_OBJECT
    //int width = 750, height = 500;
        void keyPressEvent(QKeyEvent*);
public:
    explicit BigTheater(QWidget *parent = 0);
        QGraphicsScene *scene1;
        QTimer *clock;
        Actor *Hero;
        bool *horizontalBlocks;
        bool *verticalBlocks;
signals:

public slots:
};

#endif // BIGTHEATER_H
