#include "bro.h"
#include <QApplication>

//QString url;

int main(int argc, char *argv[])
{
#ifdef DEBUG
    qDebug()<<"This is debug build";
#endif

    QApplication a(argc, argv);

    bro w;
    w.showFullScreen();

//    QString url;

    const QStringList &args = a.arguments();
    for (int i = 0; i < args.size(); i++)
    {
        if (args.at(i) == "-a")
        {
            w.url = "http://127.0.0.1/admin/";
        }
        else
        {
            w.url = "http://127.0.0.1/";
        }
    }

    return a.exec();
}
