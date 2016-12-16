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
    //moving
    bool move_D;
    bool move_U;
    bool move_L;
    bool move_R;

    //animation
    int currentFrame;
    int currentAct;
    int msec;

    //determining
    Course course;
    int Block_X;
    int Block_Y;
    qreal speedX;
    qreal speedY;
    qreal dx,dy;

    //front_Coord
    qreal f_CX;
    qreal f_CY;

    QTimer *timer;
    BigTheater* BT;

    void whereIAm();//WhatIsBlock
    void move(qreal dx_, qreal dy_, Course c);

public:
    Actor(int pos_x, int pos_y, QString imageName, BigTheater* Bt);
    ~Actor();

    void moveOnBlock(const Course c_);

    inline int getBlock_X() const {return Block_X;}
    inline int getBlock_Y() const {return Block_Y;}
    inline qreal getF_CX() const {return f_CX;}
    inline qreal getF_CY() const {return f_CY;}
    inline QPoint getF_C() const {return QPoint(f_CX, f_CY);}
    inline Course getCourse() const {return course;}

    virtual void stopHere();
    virtual void die(){this->deleteLater();}
    virtual void stopTimer();
    virtual void beginTimer();
protected slots:
    virtual void frame();
};

#endif // ACTOR_H
