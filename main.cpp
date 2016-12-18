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
            &a,SIGNAL(lastWindowClosed()),
            &a,SLOT(quit()));

    return a.exec();
}
