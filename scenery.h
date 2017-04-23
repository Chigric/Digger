#ifndef SCENERY_H
#define SCENERY_H

#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsItemGroup>

#include "graphicpixmapobject.h"
#include "imerald.h"
#include "define.h"

class BigTheater;
class Pixel : public GraphicPixmapObject
{
    bool full;
    bool empty;
    int start_X, start_Y;
    int end_X, end_Y;
    int Block_X, Block_Y;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
public:
    Pixel(int pos_x, int pos_y);
    inline bool IsFull() const {return full;}
    inline bool IsEmpty() const {return empty;}
    inline int SX() const {return start_X;}
    inline int SY() const {return start_Y;}
    inline int EX() const {return end_X;}
    inline int EY() const {return end_Y;}
    inline void setEmpty(const bool empty);
    inline void setFull(const bool full);
    void grow_SX();
    void grow_SY();
    void fall_EX();
    void fall_EY();
};

class Border : public QGraphicsLineItem
{
public:
    Border(QPoint start, QPoint finish);
};

class Scenery : public QGraphicsItemGroup
{
    qreal X;
    qreal Y;
    int Block_X, Block_Y;

    Pixel *box;
    Border *vLine;
    Border *hLine;
    Imerald *imerald;

    BigTheater* BT;

public:
    Scenery();
    Scenery(int pos_x, int pos_y, BigTheater *Bt);
    void eatingBlock(const QPoint Act_,
                     const QPoint C_Act,
                     const Course c_);
    void setPos(int pos_x, int pos_y, BigTheater *Bt);
    void setBox(bool b);
    void setVLine(bool v);
    void setHLine(bool h);
    void setImerald(bool i);
    inline bool isBoxFull() const {return box->IsFull();}
    inline bool isBoxEmpty() const {return box->IsEmpty();}
    inline bool existHLine() const {return hLine->isVisible();}
    inline bool existVLine() const {return vLine->isVisible();}
    inline QPoint getPos() const {return QPoint(X, Y);}
};


#endif // SCENERY_H
