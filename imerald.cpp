#include "imerald.h"
#include <QDebug>

Imerald::Imerald(int pos_x, int pos_y) : GraphicPixmapObject(pos_x, pos_y, "Imerald.png")
{
    sizeOfPictureX = 8;
    sizeOfPictureY = 7;
    sizeOfItemX = sizeOfPictureX * 4;
    sizeOfItemY = sizeOfPictureY * 4;
}
