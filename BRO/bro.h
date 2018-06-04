#ifndef BRO_H
#define BRO_H

#include <QMainWindow>

#include <QTimer>
#include <QTime>
#include <QKeyEvent>
#include <QtGui/QKeyEvent>

#include <QProcess>

namespace Ui {
class bro;
}

class bro : public QMainWindow
{
    Q_OBJECT

public:
    explicit bro(QWidget *parent = 0);
    ~bro();

private slots:
    void on_webView_loadFinished(bool arg1);
    void slotTimerAlarm();

    void on_webView_linkClicked(const QUrl &arg1);

private:
    Ui::bro *ui;
    QTimer *timer;

protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // BRO_H
