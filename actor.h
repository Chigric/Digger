#ifndef ACTOR_H
#define ACTOR_H

#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QBitmap>
#include <QTimer>
#include <iostream>

class Actor : public QObject, public QGraphicsItem
{
    Q_OBJECT
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        QRectF boundingRect() const;
    int dx,dy;
    QPixmap *sprite;
//    QTimer *timer;
    int currentFrame;
public:
    explicit Actor(QObject *parent = 0);
    void goUp()   {std::cout << "Up" << std::endl;
                    dx +=  0; dy -= 50; }
    void goDown() {std::cout << "Down" << std::endl;
                    dx +=  0; dy += 50; }
    void goLeft() {std::cout << "Left" << std::endl;
                    dx -= 50; dy +=  0; }
    void goRight(){std::cout << "Right" << std::endl;
                    dx += 50; dy +=  0; }


public slots:
    void nextFrame();

};

#endif // ACTOR_H
