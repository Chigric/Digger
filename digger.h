#ifndef DIGGER_H
#define DIGGER_H

#include "actor.h"

class Digger : public Actor
{
    void collidesInBlock();
public:
    Digger(BigTheater* Bt);
    ~Digger();
    void keyPressEvent(QKeyEvent* k);
};

#endif // DIGGER_H
