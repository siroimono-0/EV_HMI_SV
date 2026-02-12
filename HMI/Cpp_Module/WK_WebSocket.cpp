#include "WK_WebSocket.h"
#include "Cpp_Module.h"
#include "StatStore.h"

WK_WebSocket::WK_WebSocket(QObject *parent)
    : QObject{parent}
{}

void WK_WebSocket::slot_stop()
{
    this->p_webSoc->close();
    emit sig_end();
    return;
}

void WK_WebSocket::set_p_stat(StatStore *set_p_stat)
{
    this->p_stat = set_p_stat;
    return;
}

void WK_WebSocket::set_p_Module(Cpp_Module *set_p_Module)
{
    this->p_Module = set_p_Module;
    return;
}

void WK_WebSocket::slot_Connect_Sv()
{
    this->p_webSoc = new QWebSocket();
    //*** 맴버변수로 갖고있는 웹소켓 포인터에 부모 설정해주면
    // 종료버튼 눌러서 종료하면
    // QObject::disconnect: wildcard call disconnects from destroyed signal of QTcpSocket::unnamed
    // 에러 뱉어냄
    // this->p_webSoc->setParent(this);
    this->p_webSoc->open(QUrl("ws://192.168.123.103:12345"));

    connect(this->p_stat, &StatStore::sig_Stat_changed, this, &WK_WebSocket::slot_sendData);

    connect(this->p_webSoc, &QWebSocket::connected, this, [&]() {
        // 상태 클래스 초기값 업데이트
        QMetaObject::invokeMethod(this->p_stat,
                                  &StatStore::slot_update_current,
                                  Qt::QueuedConnection);

        // 모듈 -> Qml 통신 시그널 발생
        QMetaObject::invokeMethod(this->p_Module, &Cpp_Module::sig_SocSuccess_ToQml);
    });

    connect(this->p_webSoc, &QWebSocket::errorOccurred, this, &WK_WebSocket::slot_SocErr);
    connect(this->p_webSoc, &QWebSocket::disconnected, this->p_webSoc, &QWebSocket::deleteLater);

    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_WebSocket::slot_SocErr(QAbstractSocket::SocketError error)
{
    if (error == QAbstractSocket::ConnectionRefusedError)
    {
        // 서버 IP는 살아 있음
        // 포트에 리스닝 서버 없음
        // 모듈 -> Qml 통신 시그널 발생
        QMetaObject::invokeMethod(this->p_Module,
                                  &Cpp_Module::sig_SocErr_ToQml,
                                  QString("서버가 열려있지 않습니다."));
    }
    else if (error == QAbstractSocket::HostNotFoundError)
    {
        // DNS 실패
        // IP/도메인 잘못됨
        // 모듈 -> Qml 통신 시그널 발생
        QMetaObject::invokeMethod(this->p_Module,
                                  &Cpp_Module::sig_SocErr_ToQml,
                                  QString("서버 주소를 찾을 수 없습니다."));
    }
    else if (error == QAbstractSocket::NetworkError)
    {
        // 랜 뽑힘
        // Wi-Fi 끊김
        // 모듈 -> Qml 통신 시그널 발생
        QMetaObject::invokeMethod(this->p_Module,
                                  &Cpp_Module::sig_SocErr_ToQml,
                                  QString("네트워크 연결 오류"));
    }
    else if (error == QAbstractSocket::SocketTimeoutError)
    {
        // 서버 응답 없음
        // 모듈 -> Qml 통신 시그널 발생
        QMetaObject::invokeMethod(this->p_Module,
                                  &Cpp_Module::sig_SocErr_ToQml,
                                  QString("연결 시간 초과"));
    }
    qDebug() << "hello?";
    return;
}

void WK_WebSocket::slot_sendData(stat_data st_stat)
{
    QJsonObject json_obj;
    json_obj.insert("number", st_stat.number);
    json_obj.insert("date", st_stat.date);
    json_obj.insert("location", st_stat.location);
    json_obj.insert("id", st_stat.id);
    json_obj.insert("stat", st_stat.stat);

    QJsonDocument json_doc(json_obj);
    QString send_qs = json_doc.toJson(QJsonDocument::Compact);

    this->p_webSoc->sendTextMessage(send_qs);

    qDebug() << Q_FUNC_INFO;
    return;
}
