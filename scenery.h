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

    Pixel *box = nullptr;
    Border *vLine = nullptr;
    Border *hLine = nullptr;
    Imerald *imerald = nullptr;

public:
    Scenery();
    Scenery(int pos_x, int pos_y);

    QPoint getPos() const;
    void setPos(int pos_x, int pos_y);
    void setBox(bool b);
    void setVLine(bool v);
    void setHLine(bool h);
    void setImerald(bool i);
    bool existBox() const;
    bool existHLine() const;
    bool existVLine() const;
};


#endif // SCENERY_H
