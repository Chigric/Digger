#ifndef ACTOR_H
#define ACTOR_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QBitmap>
#include <QTimer>
#include <QKeyEvent>

#include <QDebug>

#include <cmath>
#include <iostream>

#define speedX 15
#define speedY 11
enum Course{Up, Left, Down, Right};

class Actor : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

    QPixmap *sprite;
    QTimer *timer;
    int currentFrame;

    int course;
    int Block_X;
    int Block_Y;
    int OwnX, OwnY;
    int sizeOfItemX;
    int sizeOfItemY;
    int sizeOfPictureX;
    int sizeOfPictureY;
    int dx,dy;

public:
    Actor();
    ~Actor();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void move(int dx_, int dy_, int c);
    QPoint pos() const;
    int x() const;
    int y() const;

private slots:
    void nextFrame();
};

#endif // ACTOR_H
