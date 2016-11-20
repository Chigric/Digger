#include <QApplication>
#include "bigtheater.h"

int main(int argc, char** argv)
{
    QApplication a(argc, argv);

    BigTheater BT;
    BT.show();

    QObject::connect(
            &a,SIGNAL(lastWindowClosed()),
            &a,SLOT(quit()));

    return a.exec();
}
