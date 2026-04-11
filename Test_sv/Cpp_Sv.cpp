#include "Cpp_Sv.h"

Cpp_Sv::Cpp_Sv(QObject *parent)
    : QObject{parent}
{
    /*
    this->sv = new QWebSocketServer("hello", QWebSocketServer::NonSecureMode, this);
    bool ret = this->sv->listen(QHostAddress::Any, 12345);
    if (ret == true)
    {
        qDebug() << "listen ok";
    }
    connect(this->sv, &QWebSocketServer::newConnection, this, &Cpp_Sv::connectSv);
*/
    this->PrintPortInfo();
}
void Cpp_Sv::connectSv()
{
    this->soc = this->sv->nextPendingConnection();
    this->soc->setParent(this);

    return;
}

void Cpp_Sv::PrintPortInfo()
{
    QList<QSerialPortInfo> l_ports = QSerialPortInfo::availablePorts();

    qDebug() << "port count =" << l_ports.size();

    for (const QSerialPortInfo &sp_port : l_ports)
    {
        if (!sp_port.portName().contains("ttyUSB"))
        {
            continue;
        }

        qDebug() << "==============================";
        qDebug() << "portName       =" << sp_port.portName();
        qDebug() << "systemLocation =" << sp_port.systemLocation();
        qDebug() << "description    =" << sp_port.description();
        qDebug() << "manufacturer   =" << sp_port.manufacturer();
        qDebug() << "serialNumber   =" << sp_port.serialNumber();

        if (sp_port.hasVendorIdentifier())
            qDebug() << "vendorId       ="
                     << QString("0x%1").arg(sp_port.vendorIdentifier(), 4, 16, QChar('0'));

        if (sp_port.hasProductIdentifier())
            qDebug() << "productId      ="
                     << QString("0x%1").arg(sp_port.productIdentifier(), 4, 16, QChar('0'));
    }
}
