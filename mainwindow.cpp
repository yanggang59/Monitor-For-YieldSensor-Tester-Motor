#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initialize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize()
{
    isSerialOpen= false;
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
        {
            QSerialPort serial;
            serial.setPort(info);

            if(serial.open(QIODevice::ReadWrite))
            {
                ui->CB_port->addItem(serial.portName());
                serial.close();
            }
        }

    ui->CB_databit->setCurrentIndex(8);
    ui->CB_baudrate->setCurrentIndex(4);



}

void MainWindow::on_Btn_openSerial_clicked()
{
    if(ui->CB_port->count() == 0)
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("No Serial Pot found");
        msgBox.exec();
        return;
    }

    if(ui->Btn_openSerial->text()==tr("Open Serial"))
        {
            //QMessageBox::information(this,"title","test");

            MotorControlSerial=new QSerialPort;

            /*设置串口名*/
            MotorControlSerial->setPortName("/dev/"+ui->CB_port->currentText());


            /*打开串口*/
            MotorControlSerial->open(QIODevice::ReadWrite);

            /*设置波特率*/
            MotorControlSerial->setBaudRate(ui->CB_baudrate->currentText().toInt());


            /*设置数据位*/
            switch (ui->CB_databit->currentIndex())
            {
                case 8:MotorControlSerial->setDataBits(QSerialPort::Data8);
                default:break;

            }

            /*Set Parity*/
            switch (ui->CB_paritybit->currentIndex())
            {
                case 0:MotorControlSerial->setParity(QSerialPort::NoParity);
                case 1:MotorControlSerial->setParity(QSerialPort::OddParity);
                case 2:MotorControlSerial->setParity(QSerialPort::EvenParity);
                default:break;

            }


            switch(ui->CB_stopbit->currentIndex())
            {
                case 1:MotorControlSerial->setStopBits(QSerialPort::OneStop);
                case 2:MotorControlSerial->setStopBits(QSerialPort::TwoStop);
                default:break;
            }

            /*无流控*/
            MotorControlSerial->setFlowControl(QSerialPort::NoFlowControl);

            ui->CB_port->setEnabled(false);
            ui->CB_baudrate->setEnabled(false);
            ui->CB_databit->setEnabled(false);
            ui->CB_stopbit->setEnabled(false);
            ui->CB_paritybit->setEnabled(false);

            ui->Btn_openSerial->setText("Close Serial");

            setSerialStatus(true);
            ui->status->setAlignment(Qt::AlignRight);
            ui->status->setText("Serial Opened");
            //connect(MotorControlSerial,SIGNAL(readyRead()),this,SLOT(Read_Weight_Data_And_Plot()));


        }

        else
        {
            MotorControlSerial->clear();
            MotorControlSerial->close();
            MotorControlSerial->deleteLater();

            ui->CB_port->setEnabled(true);
            ui->CB_baudrate->setEnabled(true);
            ui->CB_databit->setEnabled(true);
            ui->CB_stopbit->setEnabled(true);
            ui->CB_paritybit->setEnabled(true);

            setSerialStatus(false);
            ui->Btn_openSerial->setText("Open Serial");
            ui->status->setText("Serial Closed");
        }

}

bool MainWindow::getSerialStatus()
{
    return isSerialOpen;
}

void MainWindow::setSerialStatus(bool status)
{
    isSerialOpen=status;
}

void MainWindow::on_Btn_Stop_clicked()
{
    /*If serial port is closed,alert*/
    if(!getSerialStatus())
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Serial Closed");
        msgBox.exec();
        return;
    }

    /*Send 'X' to Stop */
    MotorControlSerial->write("X",1);


}

void MainWindow::on_Btn_SetSpeed_clicked()
{
    /*If serial port is closed,alert*/
    if(!getSerialStatus())
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Serial Closed");
        msgBox.exec();
        return;
    }
    int i =ui->speedSetting->value();
    switch (i)
    {
        case 0:MotorControlSerial->write("X",1);
        case 1:MotorControlSerial->write("A",1); //60r/min
        case 2:MotorControlSerial->write("B",1); //120r/min
        case 3:MotorControlSerial->write("C",1); //180r/min
        case 4:MotorControlSerial->write("D",1); //240r/min
        case 5:MotorControlSerial->write("E",1); //300r/min
        case 6:MotorControlSerial->write("F",1); //360r/min
        case 7:MotorControlSerial->write("G",1); //420r/min
        case 8:MotorControlSerial->write("H",1); //480r/min
        case 9:MotorControlSerial->write("I",1); //540r/min
        default:break;
    }
}
