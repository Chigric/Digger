#ifndef ACTOR_H
#define ACTOR_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QBitmap>
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
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:
    Actor(qreal pos_x, qreal pos_y, QString imageName);
    ~Actor();

private slots:
    void nextFrame();
};

#endif // ACTOR_H
