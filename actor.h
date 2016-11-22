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

#include "define.h"

class BigTheater;
class Actor : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

protected:
    QPixmap *sprite;
    QTimer *timer;
    BigTheater* BT;
    int currentFrame;

    int course;
    int Block_X;
    int Block_Y;
    qreal OwnX, OwnY;
    int sizeOfItemX;
    int sizeOfItemY;
    int sizeOfPictureX;
    int sizeOfPictureY;
    qreal dx,dy;

    void whereIAm();//WhatIsBlock
    void move(qreal dx_, qreal dy_, int c);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:
    Actor();
    ~Actor();

    QPoint pos() const;
    qreal x() const;
    qreal y() const;

private slots:
    void nextFrame();
};

#endif // ACTOR_H
