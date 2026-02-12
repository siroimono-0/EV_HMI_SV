#include "Cpp_cli.h"

Cpp_cli::Cpp_cli(QObject *parent)
    : QObject{parent}
{
    this->soc = new QWebSocket();
    this->soc->setParent(this);
    this->soc->open(QUrl("ws://192.168.123.103:12345"));
    connect(this->soc, &QWebSocket::connected, this, []() { qDebug() << "connect ok"; });
    // this
}

Cpp_cli::~Cpp_cli()
{
    this->shutdown();
    return;
}

void Cpp_cli::shutdown()
{
    if (!this->soc)
        return;

    // 이미 닫혀있으면 스킵
    // (QWebSocket은 state()가 있는 Qt 버전도 있고 없는 버전도 있어서,
    //  안전하게 그냥 close() 호출해도 됨)
    this->soc->close();

    // disconnected까지 잠깐 기다려서 내부 QTcpSocket 정리 시간을 줌
    QEventLoop ev_loop;
    QTimer tmr_to;

    tmr_to.setSingleShot(true);
    connect(&tmr_to, &QTimer::timeout, &ev_loop, &QEventLoop::quit);
    connect(this->soc, &QWebSocket::disconnected, &ev_loop, &QEventLoop::quit);

    tmr_to.start(300); // 0.3초 정도만 (너무 길 필요 없음)
    ev_loop.exec();
    return;
}
