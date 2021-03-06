#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    //void on_pushButton_clicked();
    //void on_pushButton_2_clicked();
    //void on_btnCalibrate_clicked();
    //void on_btnSubmit_clicked();
    void on_webView_linkClicked(const QUrl &arg1);

private:
    Ui::MainWindow *ui;

protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H
