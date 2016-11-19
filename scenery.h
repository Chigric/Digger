#ifndef SCENERY_H
#define SCENERY_H

#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsItemGroup>
#include <QBrush>
#include <QPen>

class Pixel : public QGraphicsRectItem
{
public:
    Pixel(int pos_x, int pos_y);
    ~Pixel();
};

class Border : public QGraphicsLineItem
{
public:
    Border(QPoint start, QPoint finish);
    ~Border();
};

class Scenery : public QGraphicsItemGroup
{
    int X;
    int Y;
    Pixel *box;
    Border *vLine;
    Border *hLine;

public:
    Scenery();
    Scenery(int pos_x, int pos_y);
    ~Scenery();

    void setPos(int pos_x, int pos_y);
    void setBox(bool b);
    void setVLine(bool v);
    void setHLine(bool h);
};


#endif // SCENERY_H
