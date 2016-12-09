#include "scenery.h"
#include <QDebug>
//#define nullptr NULL

Scenery::Scenery() :  QGraphicsItemGroup(), X(0), Y(0), Block_X(0), Block_Y(0), box(0), vLine(0), hLine(0), imerald(0) {}
Scenery::Scenery(int pos_x, int pos_y) : QGraphicsItemGroup(),
    X(pos_x * sizeOfBlockX), Y(pos_y * sizeOfBlockY), Block_X(pos_x), Block_Y(pos_y), box(0), vLine(0), hLine(0), imerald(0) {}

inline QPoint Scenery::getPos() const
{
    return QPoint(X, Y);
}

void Scenery::eatingBlock(QPoint Act_, Course c_)
{
    if (box){
        int dx = ( Act_.x() + 17 ) - X;
        int dy = ( Act_.y() + 12 ) - Y;
        if (!dx) setHLine(false);
        if (!dy) setVLine(false);
        switch (c_){
        case Up:
            box->fall_EY();
            break;
        case Down:
            box->grow_SY();
            break;
        case Right:
            box->grow_SX();
            break;
        case Left:
            box->fall_EX();
        }
    }
}

void Scenery::setPos(int pos_x, int pos_y)
{
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
        }
        qDebug() << "box is living";
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
            hLine = new Border(QPoint(X, Y), QPoint(X + sizeOfBlockX-1, Y));
            addToGroup(hLine);
        }
        qDebug() << "hLine is living";
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
        qDebug() << "vLine is living";
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
        qDebug() << "It's imerald";
    } else {
        if (imerald && !i){
            imerald->hide();
        }
    }
}

inline bool Scenery::existBox() const { if (box) return true; else return false;}
inline bool Scenery::existHLine() const { if (hLine) return true; else return false;}
inline bool Scenery::existVLine() const { if (vLine) return true; else return false;}

Pixel::Pixel(int pos_x, int pos_y) : GraphicPixmapObject(pos_x, pos_y, "Terra1.png") , start_X(0), start_Y(0), end_X(numberOfPixelsX), end_Y(numberOfPixelsY)
{
    Block_X = pos_x;
    Block_Y = pos_y;
}

void Pixel::grow_SX() {++start_X; --end_X;}
void Pixel::grow_SY() {++start_Y; --end_Y;}
void Pixel::fall_EX() {--end_X;}
void Pixel::fall_EY() {--end_Y;}

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
