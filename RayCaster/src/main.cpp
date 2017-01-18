#include "RayCaster.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RayCaster w;
    w.show();
    return a.exec();
}
