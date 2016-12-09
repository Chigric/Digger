#ifndef DEFINE_H
#define DEFINE_H

#define sizeOfBlockX 50//75
#define sizeOfBlockY 44//66
enum Course{Left, Up,  Right, Down};
#define numberOfPixelsX 5//3 //int
#define numberOfPixelsY 4//3 //int
#define sizeOfPixelX 10//25 //qreal
#define sizeOfPixelY 11//22 //qreal
#define blockOnMapX 17//15+2
#define blockOnMapY 12//10+2


#define speedX ((double)sizeOfBlockX/10)//10 pressure for move on 1 block
#define speedY ((double)sizeOfBlockY/11)//11 pressure for move on 1 block

#endif // DEFINE_H
