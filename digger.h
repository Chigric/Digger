#ifndef DIGGER_H
#define DIGGER_H

#include "actor.h"

class Digger : public Actor
{
    Q_OBJECT

    int currentFrame;
public:
    Digger(int pos_x, int pos_y, BigTheater* Bt);
    ~Digger();
    void keyPressEvent(QKeyEvent* k);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
private slots:
    void nextFrame();
};

#endif // DIGGER_H
