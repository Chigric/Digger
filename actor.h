#ifndef ACTOR_H
#define ACTOR_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QPixmap>
#include <QPainter>
#include <QBitmap>
#include <QTimer>
#include <iostream>
#include <QKeyEvent>

class Actor : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
        QRectF boundingRect() const;
    int dx,dy;
    QPixmap *sprite;
//    QTimer *timer;
    int currentFrame;

//    void keyPressEvent(QKeyEvent*);
public:
    explicit Actor(QObject *parent = 0);
    void goUp()   {
          /*dx +=  0; dy -= 50;*/ setPos(x() + 0, y() -50);
          std::cout << "Up" << std::endl;
          std::cout << x() << "\t" << y() << "\t" << dx << "\t" << dy << std::endl;
    }
    void goDown() {
        /*dx +=  0; dy += 50;*/ setPos(x() + 0, y() + 30);
        std::cout << "Down" << std::endl;
        std::cout << x() << "\t" << y() << "\t" << dx << "\t" << dy << std::endl;
    }
    void goLeft() {
        moveBy(-50,0); /*dx -= 50; dy +=  0;*/
        std::cout << "Left" << std::endl;
        std::cout << x() << "\t" << y() << "\t" << dx << "\t" << dy << std::endl;
    }
    void goRight(){
        moveBy(50, 0); /*dx += 50; dy +=  0;*/
        std::cout << "Right" << std::endl;
        std::cout << x() << "\t" << y() << "\t" << dx << "\t" << dy << std::endl;
    }

    void move();


public slots:
    void nextFrame();

};

#endif // ACTOR_H
