#ifndef ACTOR_H
#define ACTOR_H

#include <QObject>
#include <QTimer>
#include <QKeyEvent>

#include <QDebug>

#include <cmath>
#include <iostream>

#include "graphicpixmapobject.h"

class BigTheater;
class Actor : public QObject, public GraphicPixmapObject
{
    Q_OBJECT

protected:
    QTimer *timer;
    BigTheater* BT;
    int currentFrame;

    int course;
    int Block_X;
    int Block_Y;
    qreal dx,dy;

    void whereIAm();//WhatIsBlock
    void move(qreal dx_, qreal dy_, int c);

public:
    Actor(int pos_x, int pos_y, QString imageName);
    ~Actor();

private slots:
    void nextFrame();
};

#endif // ACTOR_H
