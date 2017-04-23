#include <QApplication>
#include <ctime>
#include "bigtheater.h"
int main(int argc, char** argv)
{
    QApplication a(argc, argv);

    BigTheater* BT;

    BT = new BigTheater();
    BT->show();

    QObject::connect(
            &a, SIGNAL(lastWindowClosed()),
            &a, SLOT(quit()));

    return a.exec();
}

char Template[blockOnMapY][blockOnMapX+1] = {
//   012345678901234567
    "#################", //0
    "#.###B#####.....#", //1
    "#.##^^##^##.#B###", //2
    "#.B#^^##^##.#####", //3
    "#.##^^##^B#.#^^^#", //4
    "#.##^^##^##.#^^^#", //5
    "#..#^^##^##.#^^^#", //6
    "##.####B#B#.#####", //7
    "##....#####.#####", //8
    "#####.#####.###^#", //9
    "#####.......##^^#", //0
    "#################", //1
//# - earth
//B - bag of monye
//^ - emerald
//. - void
};

char Template_2[blockOnMapY][blockOnMapX+1] = {
//   012345678901234567
    "#################", //0
    "####B#^^^^^^#...#", //1
    "#^^^#######B#.#B#", //2
    "#^^^##B#^^B##.#^#", //3
    "#^^^#########.^^#", //4
    "#.............^^#", //5
    "#.B####B####B.^^#", //6
    "#.#^^^B^^^B^#.^^#", //7
    "#.^^^^^^^^^^..^^#", //8
    "#.##########.####", //9
    "#............####", //0
    "#################", //1
//# - earth
//B - bag of monye
//^ - emerald
//. - void
};
