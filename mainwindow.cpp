#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::black);
    this->setPalette(palette);

    this->setFixedSize(1920,1040);
    ui->setupUi(this);
    serilaport = new QSerialPort(this);
    getSerilaInfo();
    bar1 = new StorageDisplay(this);
    bar1->setUsedValue(3333);
    bar1->get_currentvalue(0);
    bar1->move_place(width()/3,height()/3);
    bar1->show();

    bar2 = new StorageDisplay(this);
    bar2->setUsedValue(555);
    bar2->get_currentvalue(3);
    bar2->move_place(width()/3*2,height()/3);
    bar2->show();

    bar3 = new StorageDisplay(this);
    bar3->setUsedValue(555);
    bar3->get_currentvalue(3);
    bar3->move_place(width(),height()/3);
    bar3->show();

    if(serilaport->isOpen()){
        serilaport->clear();
        serilaport->close();
    }
    recive_timer = new QTimer(this);
    QFont font;
    font.setFamily(":/pic/FreeSans.ttf");
    font.setPointSize(16);

    connect(ui->con_button,&QPushButton::released,[=](){
        serilaport->setPortName(ui->serialselect->currentText());
        if(con_flag==false){
            if(serilaport->open(QIODevice::ReadWrite)){
            serilaport->setBaudRate(QSerialPort::Baud19200,QSerialPort::AllDirections);//设置波特率和读写方向
                serilaport->setDataBits(QSerialPort::Data8);      //数据位为8位
                serilaport->setFlowControl(QSerialPort::NoFlowControl);//无流控制
                serilaport->setParity(QSerialPort::NoParity); //无校验位
                serilaport->setStopBits(QSerialPort::OneStop); //一位停止位
                ui->con_button->setText("断开");
                con_flag = true;
            }
            else {
                qDebug()<<"open false!";
            }
        }
        else if(true == con_flag){
            serilaport->clear();
            serilaport->close();
            ui->con_button->setText("连接");
            con_flag = false;
        }
    });
    connect(serilaport,&QSerialPort::readyRead,[=](){
        recive_timer->start(130);
       Recive_Buf.append(serilaport->readAll());
    });
    connect(recive_timer,&QTimer::timeout,[=](){
        recive_timer->stop();
        if(Recive_Buf.size()==8){
        qDebug()<<Recive_Buf.toHex();
        qDebug()<<QString::number(CRC16(Recive_Buf,6),16);
        QString num = Recive_Buf.mid(2,2).toHex();
//        ui->label->setText(QString::number(num.toInt(NULL,16)));
        bar1->hide();
       bar1->get_currentvalue(num.toInt(NULL,16));
       bar1->show();

        }
        Recive_Buf.clear();
    });

}

MainWindow::~MainWindow()
{
    delete ui;
    delete serilaport;
    delete bar1;
}

uint16_t MainWindow::CRC16(const QByteArray &data, int len)
{
    unsigned int crc16 = 0xffff;
    unsigned char a, f;
    for (a = 0; a < len; a++)
    {
        crc16 = crc16 ^ (unsigned int)data[a];
        for (f = 0; f < 8; f++) {
            if (crc16 & 1) {
                crc16 = crc16 >> 1;
            crc16 ^= 0xa001;
            }
            else crc16 = crc16 >> 1;
        }
    }
        return crc16;
}
void MainWindow::getSerilaInfo(void)
{
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        serila_name << info.portName();
    }

    ui->serialselect->addItems(serila_name);
}
