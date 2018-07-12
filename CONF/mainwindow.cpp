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
        process.start("bro");
        process.waitForFinished();
    }
    else if (link == basePath + "conf" || link == basePath + "settings")
    {
        QProcess process;
        process.start("killall -s 9 conf");
        process.waitForFinished();
        process.start("conf");
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


    //save bill validator settings
    else if (link == basePath + "save")
    {
        //QWebFrame frame = ui->webView->page()->mainFrame()->documentElement();

        //qDebug() << ui->webView->page()->mainFrame()->findAllElements("*");
        //doc = frame.documentElement();
        //s = doc.findFirst("select[name=port]");
        //s.getAttribute("value");
        //s = doc.findFirst("select[name=type]");
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


/*


void MainWindow::on_btnCalibrate_clicked()
{
    QProcess process;
    process.start("/bin/sh -c \"xinput_calibrator | sed -n '/Section/,/EndSection/p' > /etc/X11/xorg.conf.d/99-calibration.conf\"");
    process.waitForFinished();
    QString output(process.readAllStandardOutput());
    qDebug()<<output;
}

void MainWindow::on_pushButton_2_clicked()
{
    //QProcess * exec;
    //exec = new QProcess(this);
//    exec->start("/bin/sh", "xinput_calibrator");

//    QString program = "/bin/sh";
//    QString shellFile = "/home/kiosk/shell.sh";
//    QProcess *myProcess = new QProcess(this);
//    myProcess->setStandardInputFile(shellFile);
//    myProcess->start(program);

    QProcess process;
    process.start("xinput_calibrator | sed -n '/Section/,/EndSection/p' > /etc/X11/xorg.conf.d/99-calibration.conf");
    process.waitForFinished();
    QString output(process.readAllStandardOutput());
    qDebug()<<output;
}

void MainWindow::on_pushButton_clicked()
{
    QProcess process;
    process.start("xinput_calibrator | sed -n '/Section/,/EndSection/p' > /etc/X11/xorg.conf.d/99-calibration.conf");
    process.waitForFinished();
    QString output(process.readAllStandardOutput());
    qDebug()<<output;
}


void MainWindow::on_btnSubmit_clicked()
{

    QByteArray fileData;
    QFile file("/srv/final/dispatcher.properties");
    if(file.open(stderr, QIODevice::ReadWrite))
    {
        fileData = file.readAll();
        QString text(fileData);

        text.replace(QString("HUi"), QString("mei"));

        file.seek(0); //go to beginning of the file
        file.write(text.toUtf8());

        file.close();
    }
    else
    {
        qDebug() << "cannot read the file!";
    }

    QString ports[] = {"ttyS0","ttyS2","ttyS3","ttyS4","ttyS5","ttyS6","ttyS7"};
    if (ui->comboBox->currentText() == "MEI") //ccnet")
    {
        QProcess process;
        QString dispatcher = "A";
        process.start("sed", QStringList() << "'s/mei/ccnet/g' /srv/final/dispatcher.properties");
        QProcess::execute("sed 's/mei/ccnet/g' /srv/final/dispatcher.properties");
        //process.waitForFinished();
        qDebug() << dispatcher;

        QString port = "B";
        process.start("dmesg | grep ttyS");
        qDebug() << port;

        //QString res_port[] = {"Cs", "ttyS2", "ttyS2", "ttyS2", "ttyS2", "ttyS2", "ttyS2"};
        QStringList res_port = port.split(" ");
        qDebug() << res_port;
        //for (int i = 0; i < sizeof(ports); i++)
        for (int i = 0; i < 7; i++)
        {
            //if (preg_match("/$ports[$i]/", res_port[i]))
            //if (res_port[i].contains(QRegExp("\\b" + ports[i] + "\\b")))
            if (res_port[i].contains(ports[i]))
            {
                QString result = ports[i];
                qDebug() << result;
            }
        }
    }
    if (false)
    {
        QProcess process;
        process.start("xinput_calibrator | sed -n '/Section/,/EndSection/p' > /etc/X11/xorg.conf.d/99-calibration.conf");
    }

}
*/

