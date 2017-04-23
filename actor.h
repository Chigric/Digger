#ifndef ACTOR_H
#define ACTOR_H

#include <QObject>
#include <QTimer>
#include <QKeyEvent>

#include <QDebug>

#include "graphicpixmapobject.h"


class BigTheater;
class Actor : public QObject, public GraphicPixmapObject
{
    Q_OBJECT
protected:
    //Moving
    Course startMove;
    Course stopMove;
    //Animation
    int currentFrame;
    int currentAct;
    int msec;
    //Determining
    Course course;
    int Block_X;
    int Block_Y;
    qreal speedX;
    qreal speedY;
    qreal dx,dy;
    //Front_Coord
    qreal f_CX;
    qreal f_CY;

    QTimer *timer;
    BigTheater* BT;

    void whereIAm();//WhatIsBlock
    void move(qreal dx_, qreal dy_, Course c);
    virtual void checkAfterMove();

public:
    Actor(int pos_x, int pos_y, QString imageName,
          BigTheater* Bt);
    ~Actor();
    friend class BigTheater;

    inline int getBlock_X() const {return Block_X;}
    inline int getBlock_Y() const {return Block_Y;}
    inline qreal getF_CX() const {return f_CX;}
    inline qreal getF_CY() const {return f_CY;}
    inline QPoint getF_C() const {return QPoint(f_CX, f_CY);}
    inline Course getCourse() const {return course;}

    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget);
    virtual void moveOnBlock(const Course c_);
    virtual void stopHere(const Course c_);
    virtual void die(){qDebug() << "Actor is dies";
                       /*this->deleteLater();*/}
    virtual void stopTimer();
    virtual void beginTimer();
protected slots:
    virtual void frame();
};

#endif // ACTOR_H
