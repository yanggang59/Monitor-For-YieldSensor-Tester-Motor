#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //初始化函数
    void initialize();
    bool getSerialStatus();
    void setSerialStatus(bool status);

private slots:

    void on_Btn_openSerial_clicked();

    void on_Btn_Stop_clicked();

    void on_Btn_SetSpeed_clicked();

private:
    Ui::MainWindow *ui;
    /*新建一个QSerialPort类型的变量*/
     QSerialPort *MotorControlSerial;

     bool isSerialOpen;
};

#endif // MAINWINDOW_H
