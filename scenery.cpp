#include "scenery.h"
#include <QDebug>
//#define nullptr NULL

Scenery::Scenery() :  QGraphicsItemGroup(), X(0), Y(0), box(0), vLine(0), hLine(0) {}
Scenery::Scenery(int pos_x, int pos_y) : QGraphicsItemGroup()
{
    X = pos_x;
    Y = pos_y;
}

void Scenery::setPos(int pos_x, int pos_y)
{
    X = pos_x; //time
    Y = pos_y; //time
}

void Scenery::setBox(bool b)
{
    if (b && !box){
        box = new Pixel(X, Y);
        addToGroup(box);
        qDebug() << "box is living";
    }
    else{
        if (box && !b){
            removeFromGroup(box);
            delete box;
            box = nullptr;
            qDebug() << box;
        }
    }
}

void Scenery::setHLine(bool h)
{
    if (h && !hLine){
        hLine = new Border(QPoint(X, Y), QPoint(X + 75-1, Y));
        addToGroup(hLine);
        qDebug() << "hLine is living";
    }
    else{
        if (hLine && !h){
            qDebug() << hLine;
            removeFromGroup(hLine);
            delete hLine;
            hLine = nullptr;
            qDebug() << hLine;
        }
    }
}

void Scenery::setVLine(bool v)
{
    if (v && !vLine){
        vLine = new Border(QPoint(X, Y), QPoint(X, Y + 66 - 1));
        addToGroup(vLine);
        qDebug() << "vLine is living";
    }
    else{
        if (vLine && !v){
            removeFromGroup(vLine);
            delete vLine;
            vLine = nullptr;
            qDebug() << vLine;
        }
    }
}

Scenery::~Scenery(){
    if (box) {removeFromGroup(box); delete box;}
    if (vLine) {removeFromGroup(vLine); delete vLine;}
    if (hLine) {removeFromGroup(hLine); delete hLine;}
}

Pixel::Pixel(int pos_x, int pos_y) : QGraphicsRectItem()
{
    setRect(pos_x, pos_y, 75-1, 66-1);

//    QColor color(225, 128, 64, 255); // orange
    setBrush(QBrush(QColor(163, 73, 164), Qt::SolidPattern));
}

Pixel::~Pixel()
{
    qDebug() << "delete Pixel";
}

Border::Border(QPoint start, QPoint finish) : QGraphicsLineItem()
{
    setLine(start.x(), start.y(), finish.x(), finish.y());
    setPen(QPen(Qt::white));
}

Border::~Border()
{
    qDebug() << "delete border";
}
