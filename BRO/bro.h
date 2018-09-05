#ifndef BRO_H
#define BRO_H

#include <QMainWindow>

#include <QKeyEvent>
#include <QtGui/QKeyEvent>

#include <QProcess>
#include <QDebug>
#include <QTimer>

//#include <QWebSettings>
#include <QSettings>

//unneeded?
//#include <QWebFrame>
//#include <QFile>

namespace Ui {
class bro;
}

class bro : public QMainWindow
{
    Q_OBJECT

public:
    explicit bro(QWidget *parent = 0);
    ~bro();

    QString url; //make private and change with setter

private slots:
    void on_webView_loadFinished(bool arg1);
    void slotTimerAlarm();
    void on_webView_linkClicked(const QUrl &arg1);
    void zoom(double factor);

private:
    Ui::bro *ui;
    QTimer *timer;


protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // BRO_H
