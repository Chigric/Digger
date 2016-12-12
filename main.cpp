#include <QApplication>
#include "bigtheater.h"
#include <QPainter>

double distance(const QPoint& first, const QPoint& second)
{
    double dy = first.y() - second.y();
    double dx = first.x() - second.x();
    return sqrt(dx*dx + dy*dy);
}

BigTheater* BT;

int main(int argc, char** argv)
{
    QApplication a(argc, argv);

    BT = new BigTheater();
    BT->show();

    QObject::connect(
            &a,SIGNAL(lastWindowClosed()),
            &a,SLOT(quit()));

    return a.exec();
}
