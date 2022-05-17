#include "tip.h"
#include <QApplication>
#include <QtWidgets>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    tip w;
    w.show();
    return a.exec();
}
