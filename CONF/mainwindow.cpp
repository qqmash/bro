#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_btnCalibrate_clicked()
{
    QProcess process;
    process.start("/bin/sh -c \"xinput_calibrator | sed -n '/Section/,/EndSection/p' > /etc/X11/xorg.conf.d/99-calibration.conf\"");
    process.waitForFinished();
    QString output(process.readAllStandardOutput());
    qDebug()<<output;
}

/*

void MainWindow::on_pushButton_2_clicked()
{
    QProcess * exec;
    exec = new QProcess(this);
    exec->start("/bin/sh", "xinput_calibrator");

    QString program = "/bin/sh";
    QString shellFile = "/home/kiosk/shell.sh";
    QProcess *myProcess = new QProcess(this);
    myProcess->setStandardInputFile(shellFile);
    myProcess->start(program);

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

*/

void MainWindow::on_btnSubmit_clicked()
{
    QProcess process;
    process.start("/bin/sh -c \"/home/kiosk/script.sh\"");
    process.start("/home/kiosk/test.sh");
    process.waitForFinished();
    qDebug() << "go-no";

    QStringList argo, list;
    argo.clear();
    list.clear();

    QProcess * exec;
    exec = new QProcess(this);
    list << "PATH=/opt:/opt/p:/bin:";
    exec->setEnvironment(list);
    exec->start("/home/kiosk/test.sh");
    qDebug() << "ne go-no";


    QProcess * proc = new QProcess(this);
    proc->waitForFinished();
    proc->start("sh", QStringList() << "-c" << "echo \"pre\"; ps -aux; echo \"post\"");
    proc->setProcessChannelMode(QProcess::MergedChannels);
    QString str(proc->readAllStandardOutput());
    qDebug() << str;

    //working???
    QProcess pro;
    pro.startDetached("/bin/bash", QStringList() << "/home/kiosk/test.sh");
    qDebug() << "test";

    /*
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
    */

}

void MainWindow::on_webView_linkClicked(const QUrl &arg)
{
    QString link = arg.toString();
    qDebug() << link;
    if (link == "http://localhost/test/calibration")
    {
        QProcess process;
        process.start("/bin/sh -c \"xinput_calibrator | sed -n '/Section/,/EndSection/p' > /etc/X11/xorg.conf.d/99-calibration.conf\"");
        process.waitForFinished();
    }
    else if (link == "http://localhost/test/bro")
    {
        QProcess process;
        process.start("bro");
        process.waitForFinished();
    }
    else if (link == "http://localhost/test/settings" || link == "http://localhost/test/conf")
    {
        QProcess process;
        process.start("conf");
        process.waitForFinished();
    }
    //save bill validator settings
    else if (link == "http://localhost/test/save")
    {
        //QWebFrame frame = ui->webView->page()->mainFrame()->documentElement();

        //qDebug() << ui->webView->page()->mainFrame()->findAllElements("*");
        //doc = frame.documentElement();
        //s = doc.findFirst("select[name=port]");
        //s.getAttribute("value");
        //s = doc.findFirst("select[name=type]");
    }
}
