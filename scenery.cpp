#include "scenery.h"
#include <QDebug>
//#define nullptr NULL

Scenery::Scenery() :  QGraphicsItemGroup(), X(0), Y(0), Block_X(0), Block_Y(0), box(0), vLine(0), hLine(0) {}
Scenery::Scenery(int pos_x, int pos_y) : QGraphicsItemGroup(),
    X(pos_x * sizeOfBlockX), Y(pos_y * sizeOfBlockY), Block_X(pos_x), Block_Y(pos_y), box(0), vLine(0), hLine(0) {}

QPoint Scenery::getPos() const
{
    return QPoint(X, Y);
}

void Scenery::setPos(int pos_x, int pos_y)
{
    Block_X = pos_x;
    Block_Y = pos_y;
    X = pos_x * sizeOfBlockX; //time
    Y = pos_y * sizeOfBlockY; //time
}

void Scenery::hidebox(int i_, int j_) {box[i_][j_]->hide();}

void Scenery::setBox(bool b)
{
    if (b){
        if (!box){
            box = new Pixel**[numberOfBlockY];
            for (int i = 0; i < numberOfBlockY; i++){
                box[i] = new Pixel*[numberOfBlockX];
                for (int j = 0; j < numberOfBlockX; j++){
                    box[i][j] = new Pixel(X + j*sizeOfPixelX, Y + i*sizeOfPixelY);
                    addToGroup(box[i][j]);
                }
            }
        }
        qDebug() << "box is living";
    }
    else{
        if (box && !b){
            for (int i = 0; i < numberOfBlockY; i++)
                for (int j = 0; j < numberOfBlockX; j++)
                    hidebox(i, j);
            setImerald(false);
//            removeFromGroup(box);
//            delete box;
//            box = nullptr;
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
//            removeFromGroup(hLine);
//            delete hLine;
//            hLine = nullptr;
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
//            removeFromGroup(vLine);
//            delete vLine;
//            vLine = nullptr;
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
//            removeFromGroup(imerald);
//            delete imerald;
//            imerald = nullptr;
        }
    }
}

bool Scenery::existBox() const { if (box) return true; else return false;}
bool Scenery::existHLine() const { if (hLine) return true; else return false;}
bool Scenery::existVLine() const { if (vLine) return true; else return false;}

Scenery::~Scenery(){
    if (imerald) {qDebug() << "imerald = " << imerald;
        removeFromGroup(imerald); delete imerald;}
    if (box) {
        qDebug() << "box = " << box;
        for (int i = 0; i < numberOfBlockY; i++)
            for (int j = 0; j < numberOfBlockX; j++){
                removeFromGroup(box[i][j]);
                delete box[i][j];
            }
    }
    if (vLine) {qDebug() << "vLine = " << vLine;
        removeFromGroup(vLine); delete vLine;}
    if (hLine) {qDebug() << "hLine = " << hLine;
        removeFromGroup(hLine); delete hLine;}
    qDebug() << "delete Scenery";
}

uint Pixel::color = 0;

Pixel::Pixel(int pos_x, int pos_y) : QGraphicsRectItem()
{
    //    QColor color(225, 128, 64, 255); // orange
    //    setBrush(QBrush(QColor(163, 73, 164), Qt::SolidPattern)); // purple

    if(color != numberOfBlockX)
        ++color;
    else --color;

    qreal penWidth = 1;//たぶん
    OwnX = pos_x - sizeOfPixelX/2;
    OwnY = pos_x - sizeOfPixelY/2;
    setRect(pos_x, pos_y, sizeOfPixelX - penWidth, sizeOfPixelY - penWidth);
    if ((color)%2 == 0) {
        setBrush(QBrush(QColor(163, 73, 164), Qt::SolidPattern));
        setPen(QColor(163, 73, 164));
    } else {
        setBrush(QBrush(QColor(225, 128, 64), Qt::SolidPattern));
        setPen(QColor(225, 128, 64));
    }


//    setPen(QPen(QColor(163, 73, 164)));
}

QPoint Pixel::getPos() {return QPoint(OwnX, OwnY);}

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
