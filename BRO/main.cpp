#include "bro.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    bro w;
    w.showFullScreen();

    return a.exec();
}
