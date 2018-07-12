#include "bro.h"
#include "ui_bro.h"

bro::bro(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::bro)
{
    ui->setupUi(this);

    QSettings *settings = new QSettings("settings.conf", QSettings::NativeFormat);
    settings->sync();
    qDebug() << settings->value("settings/size", 1).toReal();

    ui->webView->setZoomFactor(settings->value("settings/size", 1).toReal());
    qDebug() << ui->webView->zoomFactor();

    QWebSettings::clearMemoryCaches();
    //QWebSettings::setLocalStoragePath(QString("~/.cache/bro/"));

    //set the manual handling of link click
    ui->webView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);

    //timer = new QTimer();
    //connect(timer, SIGNAL(timeout()), this, SLOT(slotTimerAlarm()));
    //timer->start(1000);

    /*
    QKeySequence keys_refresh(Qt::Key_F5);
    QAction* actionReload = new QAction(this);
    actionReload->setShortcut(keys_refresh);
    QObject::connect(actionReload, SIGNAL(triggered(bool)), this, SLOT(reload()));
    ui->webView->addAction(actionReload);
    */

    //QTimer::singleShot(1000, this, SLOT(slotTimerAlarm()));
    //ui->webView->setHtml("<div text-align=\"center\"><span vertical-align=\"middle\"><h1>UMAI</h1><br><h1>Loading...</h1></span><div>");
    ui->webView->show();
    //ui->webView->load(QUrl("http://127.0.0.1/"));
    //ui->webView->show();
    QTimer::singleShot(5000, this, SLOT(slotTimerAlarm()));
    ui->webView->load(QUrl("http://127.0.0.1/"));

}

bro::~bro()
{
    delete ui;
}

void bro::slotTimerAlarm()
{
    //after 27 second refresh page
    //if (ui->webView->page() && ui->webView->loadFinished())
    //if (ui->webView->page()->networkAccessManager())
    ui->webView->load(QUrl("http://127.0.0.1/"));
    ui->webView->show();
    qDebug() << "first start!";
}


void bro::keyPressEvent(QKeyEvent *k)
{
    QSettings *settings = new QSettings("settings.conf", QSettings::NativeFormat);
/*
    QFile settings("bro.conf");
    if (settings.open(QIODevice::ReadWrite))
    {
        QTextStream stream (&settings);
        stream << "something" << endl;
    }*/

    switch(k->key())
    {
    case Qt::Key_F5:
    case Qt::Key_5:
    case Qt::Key_R:
    case QKeySequence::Refresh:
            k->accept();
            ui->webView->load(QUrl("http://127.0.0.1/"));
            qDebug() << "Refreshed";
            break;
    case Qt::Key_F11:
            k->accept();
            qDebug() << "Fullscreen";
            break;
    case Qt::Key_F1:
    case Qt::Key_1:
    case Qt::Key_Q:
            k->accept();
            ui->webView->load(QUrl("http://127.0.0.1/test/index.php"));
            qDebug() << "Settings";
            break;
    case Qt::Key_Plus:
            k->accept();
            if (ui->webView->zoomFactor() < 3)
            {
                ui->webView->setZoomFactor(ui->webView->zoomFactor() + 0.05);
                qDebug() << "Zoom +";

                settings->setValue("settings/size",ui->webView->zoomFactor());
                qDebug() << settings->value("settings/size", 1).toReal();
            }
            /*if (settings.open(QIODevice::ReadWrite))
            {
                QDataStream stream (&settings);
                stream << ui->webView->zoomFactor() << endl;
            }*/
            break;
    case Qt::Key_Minus:
            k->accept();
            if (ui->webView->zoomFactor() > 0.5)
            {
                ui->webView->setZoomFactor(ui->webView->zoomFactor() - 0.05);
                qDebug() << "Zoom -";

                settings->setValue("settings/size",ui->webView->zoomFactor());
                qDebug() << settings->value("settings/size", 1).toReal();
            }
            /*if (settings.open(QIODevice::ReadWrite))
            {
                QDataStream stream (&settings);
                QTextStream stream (&settings);
                stream << ui->webView->zoomFactor().toString() << endl;
            }*/
            break;
    default:
        k->ignore();
        break;
    }

    QWidget::keyPressEvent(k);
}

void bro::on_webView_loadFinished(bool ok)
{
    //QWebFrame frame = ui->webView->page()->mainFrame();
    //QWebElement variable;
    //variable = frame->findChild("#GridView1 td:nth-child(1)");

    //QString content = ui->webView->page()->mainFrame()->toHtml();

    if (!ok) // && !(ui->webView->page()->mainFrame()) )
    {
        //ui->webView->load(QUrl("http://127.0.0.1/"));
        //ui->webView->show();
        qDebug() << "not loaded!";
    }
    else
    {
        qDebug() << "refreshed!";
    }

}

void bro::on_webView_linkClicked(const QUrl &arg1)
{
    QString link = arg1.toString();
    qDebug() << link;
    QString basePath = "http://127.0.0.1/";
    //QString basePath = "http://localhost/test/";
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
