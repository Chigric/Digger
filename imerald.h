#ifndef IMERALD_H
#define IMERALD_H

#include <QDebug>
#include "graphicpixmapobject.h"

class Imerald : public GraphicPixmapObject
{
    static int quantity;
public:
    Imerald(int pos_x, int pos_y);
    int getQuantity() const {qDebug() << "QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ" << quantity; return --quantity;}
    void growQuantity() {qDebug() << "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL"; ++quantity; }
};

#endif // IMERALD_H
