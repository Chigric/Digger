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
protected:
    BigTheater* BT;
    QTimer *timer;

    Course course;
    int Block_X;
    int Block_Y;
    qreal dx,dy;
    //front_Coord
    qreal f_CX;
    qreal f_CY;

    void whereIAm();//WhatIsBlock
    void move(qreal dx_, qreal dy_, Course c);

public:
    Actor(int pos_x, int pos_y, QString imageName, BigTheater* Bt);
    ~Actor();

    inline int getBlock_X() const {return Block_X;}
    inline int getBlock_Y() const {return Block_Y;}
    inline qreal getF_CX() const {return f_CX;}
    inline qreal getF_CY() const {return f_CY;}
    inline QPoint getF_C() const {return QPoint(f_CX, f_CY);}
    inline Course getCourse() const {return course;}
};

#endif // ACTOR_H
