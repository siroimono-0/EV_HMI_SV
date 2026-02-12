#include "WK_Serial.h"

WK_Serial::WK_Serial(QObject *parent)
    : QObject{parent}
{
    this->test_open();
}

void WK_Serial::test_open()
{
    this->p_serial = new QSerialPort(this);
    this->p_serial->setPortName("COM5"); // 장치관리자에서 본 COM 번호
    this->p_serial->setBaudRate(QSerialPort::Baud9600);
    this->p_serial->setDataBits(QSerialPort::Data8);
    this->p_serial->setParity(QSerialPort::NoParity);
    this->p_serial->setStopBits(QSerialPort::OneStop);
    this->p_serial->setFlowControl(QSerialPort::NoFlowControl);

    connect(this->p_serial, &QSerialPort::readyRead, this, &WK_Serial::test_read);

    if (this->p_serial->open(QIODevice::ReadWrite))
    {
        qDebug() << "this->p_serial open OK";
    }
    else
    {
        qDebug() << "this->p_serial open FAIL:" << this->p_serial->errorString();
    }
    this->slot_modbus_write();
    return;
}

void WK_Serial::test_read()
{
    QByteArray qba = this->p_serial->readAll();
    qDebug() << QString::fromUtf8(qba);
    // qDebug() << "hello?";
    return;
}

void WK_Serial::slot_modbus_write()
{
    QByteArray modbus;
    modbus.append(char(0x01)); // Slave ID
    modbus.append(char(0x03)); // Function code
    modbus.append(char(0x00)); // Address
    modbus.append(char(0x01)); // quantity

    this->p_serial->write(modbus);
    return;
}
