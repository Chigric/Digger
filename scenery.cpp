#include "scenery.h"

Scenery::Scenery(int pos_x, int pos_y) : QGraphicsRectItem()
{
    setRect(pos_x, pos_y, 75, 66);
}

void Scenery::drawScenery(int level)
{
    QBrush dye;
//    dye.setTexture();
    dye.setStyle(Qt::SolidPattern);
    if (level == 1)
        dye.setColor(QColor(Qt::green) );

    setBrush(dye);
}
