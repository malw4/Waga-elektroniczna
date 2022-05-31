#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->device = new QSerialPort;
    ui->textEdit->setFontPointSize(36);
    ui->textEdit->setAlignment(Qt::AlignCenter);

    //  ui->textEdit->setFont;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete device;
}

QList<QSerialPortInfo> devices;
QFile file("result_storage.txt");

void MainWindow::addToLogs(QString message)
{
    ui->textEdit->append(message);
}


void MainWindow::on_Connect_clicked()
{
    if(switcher==0){

        QString message="1\r\n";
        devices = QSerialPortInfo::availablePorts();
        this->device->setPortName(devices.at(0).portName());
        if(!device->isOpen()) {
            // OTWÓRZ I SKONFIGURUJ PORT:
            if(device->open(QSerialPort::ReadWrite)) {
                this->device->setBaudRate(QSerialPort::Baud115200);
                this->device->setDataBits(QSerialPort::Data8);
                this->device->setParity(QSerialPort::NoParity);
                this->device->setStopBits(QSerialPort::OneStop);
                this->device->setFlowControl(QSerialPort::NoFlowControl);
                this->addToLogs("HELLO :)");
                this->device->write(message.toStdString().c_str());
                // CONNECT:
                connect(this->device, SIGNAL(readyRead()), this, SLOT(readFromPort()));
            }
        }
        switcher=1;
    }else if(switcher==1){
        if(this->device->isOpen()) {
            this->device->close();
            this->addToLogs("GOODBYE :)");
        }
        switcher=0;
    }
}


void MainWindow::readFromPort() {
    while(this->device->canReadLine()) {
        QString line = this->device->readLine();
        //qDebug() << line;

        QString terminator = "\r";
        int pos = line.lastIndexOf(terminator);
        //qDebug() << line.left(pos);

        this->addToLogs(line.left(pos));
    }
}


void MainWindow::on_TensButton_2_clicked()
{
    if(file.open(QIODevice::WriteOnly |QIODevice::Append |QIODevice::Text))
    {
        QTextStream stream(&file);
        stream << "Waga: " << ui->textEdit_3->toPlainText()<<'\n';
        ui->textEdit_3->clear();

        file.close();
        qDebug() << "Writing finished";
    }
}

