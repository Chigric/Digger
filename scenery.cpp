#include "scenery.h"
#include "bigtheater.h"
#include <QDebug>
//#define nullptr NULL
class BigTheater;
Scenery::Scenery() :  QGraphicsItemGroup(), full(false), X(0), Y(0), Block_X(0), Block_Y(0), box(0), vLine(0), hLine(0), imerald(0) {}
Scenery::Scenery(int pos_x, int pos_y) : QGraphicsItemGroup(),
    full(false), X(pos_x * sizeOfBlockX), Y(pos_y * sizeOfBlockY), Block_X(pos_x), Block_Y(pos_y), box(0), vLine(0), hLine(0), imerald(0) {}

void Scenery::eatingBlock(QPoint Act_, Course c_)
{
    int dx = Act_.x() - X;
    int dy = Act_.y() - Y;

    if (dx - sizeOfPixelX < 0)
        setVLine(false);
    if (dy - sizeOfPixelY < 0)
        setHLine(false);

    if (box){
        switch (c_){
        case Down:
            if (dy - box->SY()*sizeOfPixelY > 0)
                box->grow_SY();
            break;
        case Up:
            if (box->EY()*sizeOfPixelY - dy > 0)
                box->fall_EY();
            break;
        case Right:
            if (dx - box->SX()*sizeOfPixelX > 0)
                box->grow_SX();
            break;
        case Left:
            if (box->EX()*sizeOfPixelX - dx > 0)
                box->fall_EX();
        }
        if (imerald)
            if (imerald->itIsCollision(Act_) && imerald->isVisible())
                setImerald(false);
        full = false;
    }
}

void Scenery::setPos(int pos_x, int pos_y, BigTheater* Bt)
{
    BT = Bt;
    Block_X = pos_x;
    Block_Y = pos_y;
    X = pos_x * sizeOfBlockX;
    Y = pos_y * sizeOfBlockY;
}

void Scenery::setBox(bool b)
{
    if (b){
        if (!box){
            box = new Pixel(Block_X, Block_Y);
            addToGroup(box);
            full = true;
        }
    }
    else{
        if (box && !b){
            box -> hide();
            setImerald(false);
        }
    }
}

void Scenery::setHLine(bool h)
{
    if (h){
        if (!hLine){
            hLine = new Border(QPoint(X, Y), QPoint(X + sizeOfBlockX - 1, Y));
            addToGroup(hLine);
        }
    }
    else{
        if (hLine && !h){
            hLine -> hide();
        }
    }
}

void Scenery::setVLine(bool v)
{
    if (v){
        if (!vLine){
            vLine = new Border(QPoint(X, Y), QPoint(X, Y + sizeOfBlockY - 1));
            addToGroup(vLine);
        }
    }
    else{
        if (vLine && !v){
            vLine ->hide();
        }
    }
}

void Scenery::setImerald(bool i)
{
    if (i){
        if (!imerald){
            imerald = new Imerald(Block_X, Block_Y);
            addToGroup(imerald);
        }
    } else {
        if (imerald && !i){
            imerald->hide();
            BT->growPoints(50);
        }
    }
}

Pixel::Pixel(int pos_x, int pos_y) : GraphicPixmapObject(pos_x, pos_y, "Terra1.png") , start_X(0), start_Y(0), end_X(numberOfPixelsX), end_Y(numberOfPixelsY)
{
    Block_X = pos_x;
    Block_Y = pos_y;
}

void Pixel::grow_SX() { if (start_X == numberOfPixelsX || end_X) {++start_X; --end_X;}}
void Pixel::grow_SY() { if (start_Y == numberOfPixelsY || end_Y) {++start_Y; --end_Y;}}
void Pixel::fall_EX() { if (end_X) --end_X;}
void Pixel::fall_EY() { if (end_Y) --end_Y;}

void Pixel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter -> drawPixmap(OwnX + (start_X * sizeOfPixelX - sizeOfBlockX/2), OwnY + (start_Y * sizeOfPixelY - sizeOfBlockY/2),
                          (end_X * sizeOfPixelX), (end_Y * sizeOfPixelY),
                          *sprite, start_X, start_Y, end_X, end_Y);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

Border::Border(QPoint start, QPoint finish) : QGraphicsLineItem()
{
    //    QColor color(225, 128, 64);   // orange
    //    QColor(163, 73, 164);         // purple
    setLine(start.x(), start.y(), finish.x(), finish.y());
    setPen(QPen(Qt::white));
}
