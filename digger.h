#ifndef DIGGER_H
#define DIGGER_H

#include "actor.h"

class Digger : public Actor
{
    Q_OBJECT
public:
    Digger(int pos_x, int pos_y, BigTheater* Bt);
    ~Digger();

    //Keyboard
    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent* e);

    virtual void paint(
            QPainter *painter,
            const QStyleOptionGraphicsItem *option,
            QWidget *widget);
public slots:
    void die();
private slots:
    void nextFrame();
};

#endif // DIGGER_H
