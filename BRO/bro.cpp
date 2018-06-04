#include "bro.h"
#include "ui_bro.h"
#include <QWebSettings>
#include <QFile>

bro::bro(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::bro)
{
    ui->setupUi(this);

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
    /*
    QTimer::singleShot(15000, this, SLOT(slotTimerAlarm()));
    ui->webView->reload();
    QTimer::singleShot(15000, this, SLOT(slotTimerAlarm()));
    ui->webView->reload();
    ui->webView->repaint();
    ui->webView->update();
    QTimer::singleShot(1000, this, SLOT(slotTimerAlarm()));
    ui->webView->load(QUrl("http://127.0.0.1/"));
    */

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
    qDebug() << "first start!";//QTime::currentTime().toString("hh:mm:ss"));
}


void bro::keyPressEvent(QKeyEvent *k)
{
    QFile settings("bro.conf");
    if (settings.open(QIODevice::ReadWrite))
    {
        QTextStream stream (&settings);
        stream << "something" << endl;
    }

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
    //case Qt::Key_plusminus:
            k->accept();
            ui->webView->setZoomFactor(ui->webView->zoomFactor() + 0.1);
            qDebug() << "Zoom +";
            /*if (settings.open(QIODevice::ReadWrite))
            {
                QDataStream stream (&settings);
                stream << ui->webView->zoomFactor() << endl;
            }*/
            break;
    case Qt::Key_Minus:
            k->accept();
            ui->webView->setZoomFactor(ui->webView->zoomFactor() - 0.1);
            qDebug() << "Zoom -";
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
     if (link == "http://localhost/test/calibration")
     {
         QProcess process;
         process.start("/bin/sh -c \"xinput_calibrator | sed -n '/Section/,/EndSection/p' > /etc/X11/xorg.conf.d/99-calibration.conf\"");
     }
     else if (link == "http://localhost/test/bro")
     {
         QProcess process;
         process.start("bro");
     }
     else if (link == "http://localhost/test/settings" || link == "http://localhost/test/conf")
     {
         QProcess process;
         process.start("conf");
     }
}
