#include "WK_WebSocket.h"
#include "Cpp_Module.h"
#include "StatStore.h"

WK_WebSocket::WK_WebSocket(QObject *parent)
    : QObject{parent}
{
    this->create_netAccess();
}

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

void WK_WebSocket::create_netAccess()
{
    this->p_netAccess = new QNetworkAccessManager(this);
    connect(this->p_netAccess,
            &QNetworkAccessManager::finished,
            this,
            &WK_WebSocket::slot_netAccess_reply);
    return;
}

void WK_WebSocket::slot_netAccess_reply(QNetworkReply *reply)
{
    qDebug() << Q_FUNC_INFO;

    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << "error =" << reply->errorString();
    }

    int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

    qDebug() << "status =" << status;

    QByteArray qba = reply->readAll();
    // qDebug() << qba;
    QJsonParseError json_err;
    QJsonDocument json_doc = QJsonDocument::fromJson(qba, &json_err);

    if (json_err.error != QJsonParseError::NoError)
    {
        qDebug() << "Json Err";
    }

    QJsonObject jsObj = json_doc.object();
    QString qs_type = jsObj["type"].toString();

    if (qs_type == "pay_ack")
    {
        if (jsObj["role"].toString() == "creditCard")
        {
            if (jsObj["ok"].toBool() == true)
            {
                // 카드 승인 statStore에 카드 uid 업데이트
                QString qs_card_uid = jsObj["uid"].toString();
                QMetaObject::invokeMethod(this->p_stat,
                                          "slot_set_card_uid",
                                          Qt::QueuedConnection,
                                          Q_ARG(QString, qs_card_uid));

                // qml에 결제완료 신호 보내야댐
                QMetaObject::invokeMethod(this->p_Module,
                                          &Cpp_Module::sig_card_success_ToQml,
                                          Qt::QueuedConnection);
                qDebug() << "결제 완료";
            }
            else
            {
                QMetaObject::invokeMethod(this->p_Module,
                                          "sig_card_failed_ToQml",
                                          Qt::QueuedConnection,
                                          Q_ARG(QString, jsObj["err"].toString()));
                qDebug() << "결제 실패";
                qDebug() << "Err :: " << jsObj["err"].toString();
            }
        }
        else
        {
            // 멤버쉽 카드는 httpSv로 안보냄
        }
    }
    else
    {
        // 다른 타입 아직 없음
    }

    return;
}

void WK_WebSocket::slot_netAccess_post(QByteArray qba)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << qba;

    QJsonObject jsObj;
    jsObj.insert("type", "pay");
    jsObj.insert("role", "creditCard");
    jsObj.insert("uid", QString::fromUtf8(qba));

    QJsonDocument jsDoc(jsObj);

    QUrl url("http://127.0.0.1:8080/compare");
    QNetworkRequest req(url);

    //서버에서 어떻게 파싱할지 헤더 정의
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    this->p_netAccess->post(req, jsDoc.toJson(QJsonDocument::Compact));
    return;
}

////////////////////////////////////////////////////////////////

void WK_WebSocket::slot_Connect_Sv()
{
    this->p_webSoc = new QWebSocket();
    //*** 맴버변수로 갖고있는 웹소켓 포인터에 부모 설정해주면
    // 종료버튼 눌러서 종료하면
    // QObject::disconnect: wildcard call disconnects from destroyed signal of QTcpSocket::unnamed
    // 에러 뱉어냄
    // this->p_webSoc->setParent(this);

    // 서버 연결 완료 시
    connect(this->p_webSoc, &QWebSocket::connected, this, &WK_WebSocket::slot_ID_Check);

    /*
     수정 부분 안씀
    // 상태 클래스 상태값 변경시 SV 데이터 전송
    connect(this->p_stat, &StatStore::sig_Stat_changed, this, &WK_WebSocket::slot_Send_TextData);
    */

    // statStore db_data 전송
    connect(this->p_stat,
            &StatStore::sig_stat_db_update,
            this,
            &WK_WebSocket::slot_send_db_update_textData);

    // 텍스트 메시지 수신시 발생 슬롯
    connect(this->p_webSoc,
            &QWebSocket::textMessageReceived,
            this,
            &WK_WebSocket::slot_Recv_TextData);

    connect(this->p_webSoc, &QWebSocket::errorOccurred, this, &WK_WebSocket::slot_SocErr);
    connect(this->p_webSoc, &QWebSocket::disconnected, this->p_webSoc, &QWebSocket::deleteLater);

    // 커넥트 다 걸고  open
    this->p_webSoc->open(QUrl("ws://192.168.123.100:12345"));

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

void WK_WebSocket::slot_send_db_update_textData(db_data st_db_data)
{
    qDebug() << Q_FUNC_INFO;
    return;
}

/*
 수정부분 안씀
void WK_WebSocket::slot_Send_TextData(stat_data st_stat)
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
*/

void WK_WebSocket::slot_Recv_TextData(QString recvData)
{
    qDebug() << Q_FUNC_INFO;
    QByteArray qba = recvData.toUtf8();
    QJsonParseError json_err;
    QJsonDocument json_doc = QJsonDocument::fromJson(qba, &json_err);

    if (json_err.error != QJsonParseError::NoError)
    {
        qDebug() << "Json Err";
    }

    QJsonObject jsObj = json_doc.object();
    QString qs_type = jsObj["type"].toString();

    if (jsObj.contains("type"))
    {
        if (qs_type == "hello_ack")
        {
            if (jsObj["ok"] == true)
            {
                this->slot_ID_Resert(true);
            }
            else
            {
                this->slot_ID_Resert(false);
            }
        }
    }
    else
    {
    }

    return;
}

void WK_WebSocket::slot_ID_Check()
{
    qDebug() << Q_FUNC_INFO;

    /* 수정필요 구현 삭제 예정
    struct stat_data st_stat = {0};

    // stat클래스에서 상태 값 확인
    // 블록킹
    QMetaObject::invokeMethod(this->p_stat,
                              &StatStore::slot_get_stat,
                              Qt::BlockingQueuedConnection,
                              Q_RETURN_ARG(stat_data, st_stat));
    */

    int store_id;
    QMetaObject::invokeMethod(this->p_stat,
                              &StatStore::slot_get_store_id,
                              Qt::BlockingQueuedConnection,
                              Q_RETURN_ARG(int, store_id));

    QString hmi_id;
    QMetaObject::invokeMethod(this->p_stat,
                              &StatStore::slot_get_mac_addr,
                              Qt::BlockingQueuedConnection,
                              Q_RETURN_ARG(QString, hmi_id));

    QJsonObject jsObj;
    jsObj.insert("type", "hello");
    jsObj.insert("role", "hmi");
    jsObj.insert("token", "");
    jsObj.insert("store_id", QString::number(store_id));
    jsObj.insert("hmi_id", hmi_id);

    QJsonDocument jsDoc(jsObj);
    QString send_qs = jsDoc.toJson(QJsonDocument::Compact);

    this->p_webSoc->sendTextMessage(send_qs);

    qDebug() << Q_FUNC_INFO;

    return;
}

void WK_WebSocket::slot_ID_Resert(bool resert)
{
    if (resert)
    {
        /*
     구현 수정
        // 상태 클래스 초기값 업데이트
        QMetaObject::invokeMethod(this->p_stat,
                                  &StatStore::slot_update_current,
                                  Qt::QueuedConnection);
    */

        // 모듈 -> Qml 통신 시그널 발생
        QMetaObject::invokeMethod(this->p_Module,
                                  &Cpp_Module::sig_SocSuccess_ToQml,
                                  Qt::QueuedConnection);
    }
    else
    {
        // 모듈 -> Qml ID 없음
        QString qs_id = "ID를 찾을 수 없습니다.";
        QMetaObject::invokeMethod(this->p_Module,
                                  "sig_SocFailed_ToQml",
                                  Qt::QueuedConnection,
                                  Q_ARG(QString, qs_id));
    }
    qDebug() << Q_FUNC_INFO;
    return;
}
