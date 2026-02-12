#include "Cpp_Sv.h"

Cpp_Sv::Cpp_Sv(QObject *parent)
    : QObject{parent}
{
    this->sv = new QWebSocketServer("hello", QWebSocketServer::NonSecureMode, this);
    bool ret = this->sv->listen(QHostAddress::Any, 12345);
    if (ret == true)
    {
        qDebug() << "listen ok";
    }
    connect(this->sv, &QWebSocketServer::newConnection, this, &Cpp_Sv::connectSv);
}
void Cpp_Sv::connectSv()
{
    this->soc = this->sv->nextPendingConnection();
    this->soc->setParent(this);

    return;
}
