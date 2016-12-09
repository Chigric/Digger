#ifndef SCENERY_H
#define SCENERY_H

#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsItemGroup>

#include "graphicpixmapobject.h"
#include "imerald.h"
#include "define.h"


class Pixel : public GraphicPixmapObject
{
    int start_X, start_Y;
    int end_X, end_Y;
    int Block_X, Block_Y;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
public:
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
    qreal X;
    qreal Y;
    int Block_X, Block_Y;

    Pixel *box;
    Border *vLine;
    Border *hLine;
    Imerald *imerald;

public:
    Scenery();
    Scenery(int pos_x, int pos_y);

    void eatingBlock(QPoint Act_, Course c_);

    void setPos(int pos_x, int pos_y);
    void setBox(bool b);
    void setVLine(bool v);
    void setHLine(bool h);
    void setImerald(bool i);
    inline bool existBox() const;
    inline bool existHLine() const;
    inline bool existVLine() const;
    inline QPoint getPos() const;
};


#endif // SCENERY_H
