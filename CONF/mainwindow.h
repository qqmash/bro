#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QProcess>
#include <QDebug>
#include <QWebFrame>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_btnCalibrate_clicked();
    void on_btnSubmit_clicked();
    void on_webView_linkClicked(const QUrl &arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
