#ifndef SCENERY_H
#define SCENERY_H

#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QGraphicsItemGroup>

#include "define.h"
#include "imerald.h"

class Pixel : public QGraphicsRectItem
{
    int OwnX, OwnY;
public:
    Pixel(qreal pos_x, qreal pos_y, bool flag);
    QPoint getPos();
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

    Pixel ***box = nullptr;
    Border *vLine = nullptr;
    Border *hLine = nullptr;
    Imerald *imerald = nullptr;

public:
    Scenery();
    Scenery(int pos_x, int pos_y);

    QPoint getPos() const;
    void setPos(int pos_x, int pos_y);
    void setBox(bool b);
    void hidebox(int i_, int j_);
    void setVLine(bool v);
    void setHLine(bool h);
    void setImerald(bool i);
    bool existBox() const;
    bool existHLine() const;
    bool existVLine() const;
};


#endif // SCENERY_H
