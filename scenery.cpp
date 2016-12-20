#include "scenery.h"
#include "bigtheater.h"
#include <QDebug>
//#define nullptr NULL
class BigTheater;
Scenery::Scenery() :  QGraphicsItemGroup(), X(0), Y(0), Block_X(0), Block_Y(0), box(0), vLine(0), hLine(0), imerald(0) {}
Scenery::Scenery(int pos_x, int pos_y, BigTheater* Bt) : QGraphicsItemGroup(),
    X(pos_x * sizeOfBlockX), Y(pos_y * sizeOfBlockY), Block_X(pos_x), Block_Y(pos_y), box(0), vLine(0), hLine(0), imerald(0)
{
    BT = Bt;
    //box
    box = new Pixel(Block_X, Block_Y);
    addToGroup(box);
    box->setVisible(false);

    //vLine
    vLine = new Border(QPoint(X, Y), QPoint(X, Y + sizeOfBlockY - 1));
    addToGroup(vLine);
    vLine->setVisible(false);

    //hLine
    hLine = new Border(QPoint(X, Y), QPoint(X + sizeOfBlockX - 1, Y));
    addToGroup(hLine);
    hLine->setVisible(false);

    //imerald
    imerald = new Imerald(Block_X, Block_Y);
    addToGroup(imerald);
    imerald->setVisible(false);
}

void Scenery::setPos(int pos_x, int pos_y, BigTheater* Bt)
{
    Block_X = pos_x; Block_Y = pos_y; X = pos_x*sizeOfBlockX; Y = pos_y*sizeOfBlockY;

    BT = Bt;
    //box
    if(!box)
        box = new Pixel(Block_X, Block_Y);
    addToGroup(box);
    box->setVisible(false);

    //vLine
    if(!vLine)
        vLine = new Border(QPoint(X, Y), QPoint(X, Y + sizeOfBlockY - 1));
    addToGroup(vLine);
    vLine->setVisible(false);

    //hLine
    if(!hLine)
        hLine = new Border(QPoint(X, Y), QPoint(X + sizeOfBlockX - 1, Y));
    addToGroup(hLine);
    hLine->setVisible(false);

    //imerald
    if(!imerald)
        imerald = new Imerald(Block_X, Block_Y);
    addToGroup(imerald);
    imerald->setVisible(false);
}

void Scenery::eatingBlock(const QPoint Act_, const QPoint C_Act, const Course c_)
{
    int dx = Act_.x() - X;
    int dy = Act_.y() - Y;

    if (dx < sizeOfPixelX)
        setVLine(false);

    if (dy < sizeOfPixelY)
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

            if(Act_.y()/sizeOfBlockY != C_Act.y()/sizeOfBlockY )
                        BT->scenery[Block_Y+1][Block_X].setHLine(false);
            break;
        case Right:
            if (dx - box->SX()*sizeOfPixelX > 0)
                box->grow_SX();
            break;
        case Left:
            if (box->EX()*sizeOfPixelX - dx > 0)
                box->fall_EX();

            if (Act_.x()/sizeOfBlockX != C_Act.x()/sizeOfBlockX)
                    BT->scenery[Block_Y][Block_X+1].setVLine(false);
            break;
        default:
            break;
        }

        if (imerald)
            if (imerald->itIsCollision(Act_, true) && imerald->isVisible())
                setImerald(false);
        box->setFull(false);

        if (box->SY() == numberOfPixelsY || box->SX() == numberOfPixelsX ||
                !box->EX() || !box->EY()){
            setBox(false);
        }
    }
}

void Scenery::setBox(bool b)
{
    if (b){
        box->setVisible(true);
        box->setEmpty(false);
        box->setFull(true);
    }
    else{
        box->hide();
        box->setEmpty(true);
        box->setFull(false);
    }
}

void Scenery::setHLine(bool h)
{
    if (h){
        hLine->setVisible(true);
    }
    else{
        hLine->hide();
    }
}

void Scenery::setVLine(bool v)
{
    if (v){
        vLine->setVisible(true);
    }
    else{
        vLine->hide();
    }
}

void Scenery::setImerald(bool i)
{
    if (i){
        imerald->setVisible(true);
        imerald->growQuantity();
    } else {
        imerald->hide();
        BT->growPoints(costOfEmerald);
        if( !(imerald -> getQuantity()) ){
            BT->setEmoji("╮(︶▽︶)╭ Win");
            BT->stopAllAction();
        }
    }
}

Pixel::Pixel(int pos_x, int pos_y) : GraphicPixmapObject(pos_x, pos_y, "Terra1.png") , start_X(0), start_Y(0), end_X(numberOfPixelsX), end_Y(numberOfPixelsY)
{
    full = false;
    empty = true;
    Block_X = pos_x;
    Block_Y = pos_y;
}

void Pixel::setEmpty(const bool e_) {empty = e_;}
void Pixel::setFull(const bool f_) {full = f_;}
void Pixel::grow_SX() { if (start_X != numberOfPixelsX || end_X) {++start_X; --end_X;}}
void Pixel::grow_SY() { if (start_Y != numberOfPixelsY || end_Y) {++start_Y; --end_Y;}}
void Pixel::fall_EX() { if (end_X) --end_X;}
void Pixel::fall_EY() { if (end_Y) --end_Y;}

void Pixel::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    int penWidth = 1;
    painter -> drawPixmap(OwnX + (start_X * sizeOfPixelX - sizeOfBlockX/2), OwnY + (start_Y * sizeOfPixelY - sizeOfBlockY/2),
                          (end_X * sizeOfPixelX - penWidth), (end_Y * sizeOfPixelY - penWidth),
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
