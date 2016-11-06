#ifndef SCENERY_H
#define SCENERY_H

#include <QGraphicsRectItem>
#include <QBrush>

class Scenery : public QGraphicsRectItem
{
public:
    Scenery(int pos_x, int pos_y);
    void drawScenery(int level);
};

#endif // SCENERY_H
