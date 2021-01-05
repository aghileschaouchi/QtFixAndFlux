#include "FixAndFlux.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FixAndFlux w;
    w.show();
    return a.exec();
}
