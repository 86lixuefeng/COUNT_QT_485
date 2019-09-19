#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QPushButton>
#include <QDebug>
#include <QList>
#include <QTimer>
#include <QDateTime>
#include <QImage>
#include <QVector>
#include "roundbar.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QVector<int> floorbuf;

private:
    Ui::MainWindow *ui;
    QStringList serila_name;
    QSerialPort * serilaport;
    QByteArray Recive_Buf;
    QByteArray tmp;
    bool con_flag = false;
    uint16_t CRC16(const QByteArray &data,int len);
    void getSerilaInfo(void);
    QTimer *recive_timer;
    StorageDisplay *bar1;
    StorageDisplay *bar2;
    StorageDisplay *bar3;
};



#endif // MAINWINDOW_H
