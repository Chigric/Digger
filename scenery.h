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
    int start_X, start_Y;
    int end_X, end_Y;
    int Block_X, Block_Y;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public:
    inline int SX() const {return start_X;}
    inline int SY() const {return start_Y;}
    inline int EX() const {return end_X;}
    inline int EY() const {return end_Y;}
    void grow_SX();
    void grow_SY();
    void fall_EX();
    void fall_EY();
    Pixel(int pos_x, int pos_y);
};

class Border : public QGraphicsLineItem
{
public:
    Border(QPoint start, QPoint finish);
};

class Scenery : public QGraphicsItemGroup
{
    bool full;

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
    Scenery(int pos_x, int pos_y);

    void eatingBlock(QPoint Act_, Course c_);

    void setPos(int pos_x, int pos_y, BigTheater* Bt);
    void setBox(bool b);
    void setVLine(bool v);
    void setHLine(bool h);
    void setImerald(bool i);
    inline bool isFull() const {return full;}
    inline bool existBox() const { if (box) return true; else return false;}
    inline bool existHLine() const { if (hLine) return true; else return false;}
    inline bool existVLine() const { if (vLine) return true; else return false;}
    inline QPoint getPos() const
    {
        return QPoint(X, Y);
    }
};


#endif // SCENERY_H
