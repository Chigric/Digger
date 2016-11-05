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

#include <iostream>

#define speed 50
#define sizeOfItemX 50
#define sizeOfItemY 50
#define sizeOfPictureX 5
#define sizeOfPictureY 5

class Actor : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
//        QRectF boundingRect() const;
    QPixmap *sprite;
    QTimer *timer;
    int currentFrame;
    int OwnX, OwnY;

public:
    explicit Actor();
    void goUp()   {
          /*dx +=  0; dy -= 50;*/ moveBy(0, -10); /*setPos(x() + 0, y() - 50)*/
          std::cout << "Up" << std::endl;
          std::cout << OwnX << "\t" << OwnY << "\t" << dx << "\t" << dy << std::endl;
    }
    void goDown() {
        /*dx +=  0; dy += 50;*/ moveBy(0, 10); /* setPos(x() + 0, y() + 50)*/
        std::cout << "Down" << std::endl;
        std::cout << OwnX << "\t" << OwnY << "\t" << dx << "\t" << dy << std::endl;
    }
    void goLeft() {
        moveBy(-10,0); /*dx -= 50; dy +=  0;*/
        std::cout << "Left" << std::endl;
        std::cout << OwnX << "\t" << OwnY << "\t" << dx << "\t" << dy << std::endl;
    }
    void goRight(){
        moveBy(10, 0); /*dx += 50; dy +=  0;*/
        std::cout << "Right" << std::endl;
        std::cout << OwnX << "\t" << OwnY << "\t" << dx << "\t" << dy << std::endl;
    }
    void setSpeed(int dx_, int dy_);
    int dx,dy;


public slots:
    void nextFrame();
    void move();

};

#endif // ACTOR_H
