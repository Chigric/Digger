#ifndef SCENERY_H
#define SCENERY_H

#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsItemGroup>
#include <QPen>

#include "define.h"
#include "imerald.h"

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
    Pixel *box = nullptr;
    Border *vLine = nullptr;
    Border *hLine = nullptr;
    Imerald *imerald = nullptr;

public:
    Scenery();
    Scenery(int pos_x, int pos_y);
    ~Scenery();

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
