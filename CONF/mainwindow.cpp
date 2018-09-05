#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QProcess>
#include <QDebug>
#include <QWebFrame>
#include <QFile>

#include <QKeyEvent>
#include <QtGui/QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //set the manual handling of link click
    ui->webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_webView_linkClicked(const QUrl &arg1)
{
    QString link = arg1.toString();
    qDebug() << link;
    QString basePath = "http://localhost/admin/";
    if (link == basePath + "cali" || link == basePath + "calibrate" || link == basePath + "calibration")
    {
        QProcess process;
        process.start("/bin/sh -c \"xinput_calibrator | sed -n '/Section/,/EndSection/p' > /etc/X11/xorg.conf.d/99-calibration.conf\"");
        process.waitForFinished();
    }
    else if (link == basePath + "bro"|| link == basePath + "browser")
    {
        QProcess process;
        process.start("killall -s 9 bro");
        process.waitForFinished();
        //process.start("bro");
        process.startDetached("bro");
        process.waitForFinished();
    }
    else if (link == basePath + "conf" || link == basePath + "settings")
    {
        QProcess process;
        process.start("killall -s 9 conf");
        process.waitForFinished();
        //process.start("conf");
        process.startDetached("conf");
        process.waitForFinished();
    }
    else if (link == basePath + "reboot")
    {
        QProcess process;
        process.start("sudo reboot");
        process.waitForFinished();
    }
    else if (link == basePath + "poweroff")
    {
        QProcess process;
        process.start("sudo poweroff");
        process.waitForFinished();
    }
    else if (link == basePath + "refresh")
    {
        ui->webView->load(QUrl("http://localhost/admin/"));
        qDebug() << "Refreshed";
    }
    else if (link == basePath + "firefox")
    {
        QProcess process;
        process.start("firefox");
        process.waitForFinished();
    }
    else if (link == basePath + "close" || link == basePath + "quit" || link == basePath + "exit")
    {
        QApplication::quit();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *k)
{
    switch(k->key())
    {
    case Qt::Key_F5:
    case Qt::Key_5:
    case Qt::Key_R:
    case QKeySequence::Refresh:
            k->accept();
            ui->webView->load(QUrl("http://localhost/admin/"));
            qDebug() << "Refreshed";
            break;
    case Qt::Key_F11:
            k->accept();
            qDebug() << "Fullscreen";
            break;
    default:
        k->ignore();
        break;
    }

    QWidget::keyPressEvent(k);
}
