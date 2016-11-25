#include <QApplication>
#include "bigtheater.h"
#include <QPainter>

double distance(const QPoint& first, const QPoint& second)
{
    double dy = first.y() - second.y();
    double dx = first.x() - second.x();
    return sqrt(dx*dx + dy*dy);
}

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
