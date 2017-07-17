#ifndef NOBBIN_H
#define NOBBIN_H

#include "actor.h"
#include <ctime>


class Nobbin : public Actor
{
    Q_OBJECT
public:
    Nobbin(int pos_x, int pos_y, BigTheater* Bt);
    ~Nobbin();

    virtual void checkAfterMove();
public slots:
    virtual void die();
private slots:
    void nextFrame();
};

#endif // NOBBIN_H
