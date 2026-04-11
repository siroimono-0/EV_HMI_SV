#include "WK_WebSocket.h"
#include "Cpp_Module.h"
#include "StatStore.h"
#include "WK_Serial.h"

WK_WebSocket::WK_WebSocket(QObject *parent)
    : QObject{parent}
{
    this->create_netAccess();

    // QString url = "http://192.168.123.102:8080/compare";
#if defined(Q_OS_WIN)
    QString url = "http://127.0.0.1:8080/compare";
#elif defined(Q_OS_LINUX)
    QString url = "http://3.107.105.0:8080/compare";
#endif
    this->set_httpSv_url(url);
}

void WK_WebSocket::slot_stop()
{
    if (this->p_webSoc != nullptr)
    {
        this->p_webSoc->close();
    }
    // emit sig_end();

    QThread::currentThread()->quit();
    return;
}

void WK_WebSocket::slot_set_p_serial(WK_Serial *set)
{
    this->p_serial = set;
    return;
}

void WK_WebSocket::set_p_stat(StatStore *set_p_stat)
{
    this->p_stat = set_p_stat;
    connect(this,
            &WK_WebSocket::sig_heartbit_ping_To_statStore,
            this->p_stat,
            &StatStore::slot_heartbit_ping);

    connect(this->p_stat,
            &StatStore::sig_heartbit_pong,
            this,
            &WK_WebSocket::slot_send_heartbit_pong);

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
    QString reply_header = reply->header(QNetworkRequest::ContentTypeHeader).toString();
    if (reply_header == "application/mp4/download")
    {
        QString s_data_dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

        QByteArray qba = reply->readAll();
        int find_idx = qba.indexOf("\r\n");
        if (find_idx == -1)
        {
            qDebug() << "ERR";
        }
        QString name = QString::fromUtf8(qba.left(find_idx));

        QFile down_file(s_data_dir + "/" + name);
        down_file.open(QIODevice::ReadWrite);
        down_file.write(qba.right(qba.size() - (find_idx + 2)));
        down_file.close();

        // 무조건 인설트 성공 이라고 가정함
        QMetaObject::invokeMethod(this->p_stat,
                                  "slot_insert_ad",
                                  Qt::BlockingQueuedConnection,
                                  Q_ARG(QString, name),
                                  Q_ARG(bool, true));

        QMetaObject::invokeMethod(this->p_stat,
                                  "slot_find_ad",
                                  Qt::QueuedConnection,
                                  Q_ARG(QString, name));
    }
    else if ("application/json")
    {
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

                    this->pay_ack = true;

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
        else if (qs_type == "cancle_ack")
        {
            if (jsObj["role"].toString() == "creditCard")
            {
                if (jsObj["ok"].toBool() == true)
                {
                    this->cancle_ack = true;

                    // qml에 결제 부분취소 신호 보내야댐
                    QMetaObject::invokeMethod(this->p_Module,
                                              &Cpp_Module::sig_cancle_payment_ok_ToQml,
                                              Qt::QueuedConnection);
                    qDebug() << "결제 취소 완료";
                }
                else
                {
                    QMetaObject::invokeMethod(this->p_Module,
                                              "sig_card_failed_ToQml",
                                              Qt::QueuedConnection,
                                              Q_ARG(QString, jsObj["err"].toString()));
                    qDebug() << "승인취소 실패";
                    qDebug() << "Err :: " << jsObj["err"].toString();
                }
            }
            // 다른 타입 아직 없음
        }

        return;
    }
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

    QNetworkRequest req(this->httpSv_url);

    //서버에서 어떻게 파싱할지 헤더 정의
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    this->p_netAccess->post(req, jsDoc.toJson(QJsonDocument::Compact));

    // ack 못받을 시 재전송 위한 정보 저장
    this->slot_netAccess_post_Data = qba;

    // ack못받으면 재전송 타이머
    QTimer::singleShot(3000, this, &WK_WebSocket::slot_timeOut_pay_ack);
    return;
}

void WK_WebSocket::slot_netAccess_post_cancle(QString card_uid)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << card_uid;

    QJsonObject jsObj;
    jsObj.insert("type", "cancle");
    jsObj.insert("role", "creditCard");
    jsObj.insert("uid", card_uid);

    QJsonDocument jsDoc(jsObj);

    QNetworkRequest req(this->httpSv_url);

    //서버에서 어떻게 파싱할지 헤더 정의
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    this->p_netAccess->post(req, jsDoc.toJson(QJsonDocument::Compact));

    // ack 못받을 시 재전송 위한 정보 저장
    this->slot_netAccess_post_cancle_Data = card_uid;

    // ack못받으면 재전송 타이머
    QTimer::singleShot(3000, this, &WK_WebSocket::slot_timeOut_cancle_ack);

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
#if defined(Q_OS_WIN)
    this->p_webSoc->open(QUrl("ws://127.0.0.1:12345"));
#elif defined(Q_OS_LINUX)
    this->p_webSoc->open(QUrl("ws://3.107.105.0:12345"));
#endif
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
    QJsonObject jsObj;

    jsObj.insert("type", "chargingLog");
    jsObj.insert("role", "hmi");

    // session_id 안씀 수정
    // QString qs_session_id = QString::number(st_db_data.session_id);
    // jsObj.insert("session_id", qs_session_id);
    jsObj.insert("store_id", static_cast<int>(st_db_data.store_id));
    jsObj.insert("hmi_id", st_db_data.hmi_id);
    jsObj.insert("ocpp_tx_id", static_cast<int>(st_db_data.ocpp_tx_id));
    jsObj.insert("card_uid", st_db_data.card_uid);

    jsObj.insert("start_time", st_db_data.start_time);
    jsObj.insert("end_time", st_db_data.end_time);
    jsObj.insert("duration_time", st_db_data.duration_time);
    jsObj.insert("average_kWh", static_cast<double>(st_db_data.average_kWh));

    jsObj.insert("soc_start", static_cast<double>(st_db_data.soc_start));
    jsObj.insert("soc_end", static_cast<double>(st_db_data.soc_end));

    jsObj.insert("advance_payment", static_cast<int>(st_db_data.advance_payment));
    jsObj.insert("cancel_payment", static_cast<int>(st_db_data.cancel_payment));
    jsObj.insert("actual_payment", static_cast<int>(st_db_data.actual_payment));
    jsObj.insert("unit_price", static_cast<int>(st_db_data.unit_price));
    jsObj.insert("tariff_type", st_db_data.tariff_type);

    jsObj.insert("session_status", st_db_data.session_status);
    jsObj.insert("stop_reason", st_db_data.stop_reason);
    jsObj.insert("local_tx_id", st_db_data.local_tx_id);

    QJsonDocument jsDoc(jsObj);
    this->p_webSoc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));

    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_WebSocket::slot_Recv_TextData(QString recvData)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << recvData;
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
        else if (qs_type == "chargingLog_ack")
        {
            if (jsObj["session_status"] == "authorized")
            {
                /* 세션 아이디 안씀 수정
                uint64_t session_id = jsObj["session_id"].toString().toULongLong();
                QMetaObject::invokeMethod(this->p_stat,
                                          "slot_set_session_id",
                                          Qt::QueuedConnection,
                                          Q_ARG(uint64_t, session_id));
*/

                QMetaObject::invokeMethod(this->p_Module,
                                          &Cpp_Module::sig_card_authorized_db_update_ack_ToQml,
                                          Qt::QueuedConnection);
            }
            else if (jsObj["session_status"] == "charging_start")
            {
                uint32_t ocpp_tx_id = jsObj["ocpp_tx_id"].toInt();
                QMetaObject::invokeMethod(this->p_stat,
                                          "slot_set_ocpp_tx_id",
                                          Qt::QueuedConnection,
                                          Q_ARG(uint32_t, ocpp_tx_id));
            }
            else if (jsObj["session_status"] == "charging_finished")
            {
                QMetaObject::invokeMethod(this->p_Module,
                                          &Cpp_Module::sig_charging_finished_ack_ToQml,
                                          Qt::QueuedConnection);
            }
        }
        else if (qs_type == "heartbit_ping")
        {
            emit this->sig_heartbit_ping_To_statStore();
            qDebug() << "heartbit ping";
        }
        else if (qs_type == "membershipCard_authorized_ack")
        {
            this->member_ack = true;
            bool ok = jsObj["ok"].toBool();
            if (ok == true)
            {
                uint32_t t_id = jsObj["transaction_id"].toString().toInt();
                QMetaObject::invokeMethod(this->p_stat,
                                          "slot_set_membership_t_id",
                                          Qt::QueuedConnection,
                                          Q_ARG(uint32_t, t_id));

                QMetaObject::invokeMethod(this->p_Module,
                                          &Cpp_Module::sig_card_success_ToQml,
                                          Qt::QueuedConnection);
            }
            else
            {
                QString failed_msg = jsObj["failed_msg"].toString();
                QMetaObject::invokeMethod(this->p_Module,
                                          "sig_card_failed_ToQml",
                                          Qt::QueuedConnection,
                                          Q_ARG(QString, failed_msg));
            }
        }
        else if (qs_type == "membershipCard_finished_ack")
        {
            this->member_finished_ack = true;
            bool ok = jsObj["ok"].toBool();
            if (ok == true)
            {
                bool stat = true;
                QMetaObject::invokeMethod(this->p_Module,
                                          "sig_cancle_payment_ok_member_ToQml",
                                          Qt::QueuedConnection,
                                          Q_ARG(bool, stat));
            }
            else
            {
                // SQLITE에 백업하고 지속갱신
                // QML에서는 결과 화면에 팝업 띄워줌
                bool stat = false;
                QMetaObject::invokeMethod(this->p_Module,
                                          "sig_cancle_payment_ok_member_ToQml",
                                          Qt::QueuedConnection,
                                          Q_ARG(bool, stat));
            }
        }
        else if (qs_type == "revision_HMI")
        {
            this->parsing_revision_HMI(jsObj);
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

void WK_WebSocket::slot_send_heartbit_pong(heartbit_data st_hb_data)
{
    QJsonObject jsObj;

    jsObj.insert("type", "heartbit_pong");
    jsObj.insert("role", "hmi");

    jsObj.insert("hmi_id", st_hb_data.hmi_id);
    jsObj.insert("store_id", static_cast<qint32>(st_hb_data.store_id));
    jsObj.insert("screen_name", st_hb_data.screen_name);

    qDebug() << st_hb_data.screen_name << " heartbit";

    QJsonDocument jsDoc(jsObj);

    this->p_webSoc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));
    return;
}

void WK_WebSocket::slot_send_membership_authorized_textData(int adv_pay,
                                                            QByteArray card_uid,
                                                            QString request_id)
{
    // QString request_id = hmi_id +
    QJsonObject jsObj;

    jsObj.insert("type", "membershipCard_authorized");
    jsObj.insert("role", "hmi");
    jsObj.insert("card_uid", QString::fromUtf8(card_uid));
    jsObj.insert("adv_pay", adv_pay);
    jsObj.insert("request_id", request_id);

    QJsonDocument jsDoc(jsObj);

    this->p_webSoc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));

    // 타임아웃 함수 데이터 저장
    this->membership_authorized_Data = QPair<int, QByteArray>({adv_pay, card_uid});
    this->membership_authorized_requestId_Data = request_id;

    // 타임아웃 설정
    QTimer::singleShot(10000, this, &WK_WebSocket::slot_timeOut_membership_authorized_ack);

    return;
}

void WK_WebSocket::slot_send_membership_finished_textData(
    int adv_pay, int act_pay, int can_pay, QString card_uid, uint32_t t_id, QString request_id)
{
    QJsonObject jsObj;

    jsObj.insert("type", "membershipCard_finished");
    jsObj.insert("role", "hmi");
    jsObj.insert("card_uid", card_uid);
    jsObj.insert("adv_pay", adv_pay);
    jsObj.insert("act_pay", act_pay);
    jsObj.insert("can_pay", can_pay);
    jsObj.insert("transaction_id", static_cast<qint32>(t_id));
    jsObj.insert("request_id", request_id);
    qDebug() << t_id << " :: tid";

    QJsonDocument jsDoc(jsObj);

    this->p_webSoc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));

    this->adv_pay = adv_pay;
    this->act_pay = act_pay;
    this->can_pay = can_pay;
    this->card_uid = card_uid;
    this->t_id = t_id;
    this->membership_finished_requestId_Data = request_id;

    // 타임아웃 설정
    QTimer::singleShot(10000, this, &WK_WebSocket::slot_timeOut_membership_finished_ack);

    return;
}

void WK_WebSocket::slot_timeOut_pay_ack()
{
    this->pay_ack_cnt++;
    if (this->pay_ack == true)
    {
        this->pay_ack = false;
        this->pay_ack_cnt = 0;
        return;
    }

    if (this->pay_ack_cnt > 2)
    {
        this->pay_ack_cnt = 0;

        QMetaObject::invokeMethod(this->p_Module,
                                  "sig_card_failed_ToQml",
                                  Qt::QueuedConnection,
                                  Q_ARG(QString, "http SV 미응답\n 고객센터에 문의 해주세요"));

        return;
    }

    this->slot_netAccess_post(this->slot_netAccess_post_Data);
    return;
}

void WK_WebSocket::slot_timeOut_cancle_ack()
{
    this->cancle_ack_cnt++;
    if (this->cancle_ack == true)
    {
        this->cancle_ack = false;
        this->cancle_ack_cnt = 0;
        return;
    }

    if (this->cancle_ack_cnt > 2)
    {
        this->cancle_ack_cnt = 0;

        QMetaObject::invokeMethod(this->p_Module,
                                  "sig_card_failed_ToQml",
                                  Qt::QueuedConnection,
                                  Q_ARG(QString, "http SV 미응답\n 고객센터에 문의 해주세요"));

        return;
    }

    this->slot_netAccess_post_cancle(this->slot_netAccess_post_cancle_Data);
    return;
}

void WK_WebSocket::slot_timeOut_membership_authorized_ack()
{
    this->member_ack_cnt++;
    if (this->member_ack == true)
    {
        this->member_ack = false;
        this->member_ack_cnt = 0;
        return;
    }

    if (this->member_ack_cnt > 2)
    {
        this->member_ack_cnt = 0;

        QMetaObject::invokeMethod(this->p_Module,
                                  "sig_card_failed_ToQml",
                                  Qt::QueuedConnection,
                                  Q_ARG(QString, "OCPP SV 미응답\n 고객센터에 문의 해주세요"));

        return;
    }

    // 재전송
    int adv_pay = this->membership_authorized_Data.first;
    QByteArray card_uid = this->membership_authorized_Data.second;
    this->slot_send_membership_authorized_textData(adv_pay,
                                                   card_uid,
                                                   this->membership_authorized_requestId_Data);
    return;
}

void WK_WebSocket::slot_timeOut_membership_finished_ack()
{
    this->member_finished_ack_cnt++;
    if (this->member_finished_ack == true)
    {
        this->member_finished_ack = false;
        this->member_finished_ack_cnt = 0;
        return;
    }

    if (this->member_finished_ack_cnt > 2)
    {
        this->member_finished_ack_cnt = 0;

        QMetaObject::invokeMethod(this->p_Module,
                                  "sig_card_failed_ToQml",
                                  Qt::QueuedConnection,
                                  Q_ARG(QString, "OCPP SV 미응답\n 고객센터에 문의 해주세요"));

        return;
    }

    // 재전송
    this->slot_send_membership_finished_textData(this->adv_pay,
                                                 this->act_pay,
                                                 this->can_pay,
                                                 this->card_uid,
                                                 this->t_id,
                                                 this->membership_finished_requestId_Data);

    return;
}

void WK_WebSocket::parsing_revision_HMI(const QJsonObject jo)
{
    // int store_id = jo["store_id"].toInt();
    // QString hmi_id = jo["hmi_id"].toString();
    QString cmd = jo["cmd"].toString();
    QString val = jo["val"].toString();

    if (cmd == "screen_move")
    {
        if (val == "home")
        {
            QMetaObject::invokeMethod(this->p_Module,
                                      &Cpp_Module::sig_screen_move_home_ToQml,
                                      Qt::QueuedConnection);
        }
        else if (val == "maintenance")
        {
            QMetaObject::invokeMethod(this->p_Module,
                                      &Cpp_Module::sig_screen_move_maintenance_ToQml,
                                      Qt::QueuedConnection);
        }
    }
    else if (cmd == "price")
    {
        QMetaObject::invokeMethod(this->p_stat,
                                  "slot_set_charge_price_kWh",
                                  Qt::QueuedConnection,
                                  Q_ARG(int, val.toInt()));
    }
    else if (cmd == "method")
    {
        qDebug() << val;
        if (val == "회원 / 비회원")
        {
            qDebug() << val;
            QMetaObject::invokeMethod(this->p_stat,
                                      "slot_set_m_type",
                                      Qt::QueuedConnection,
                                      Q_ARG(int, ALL));
        }
        else if (val == "회원")
        {
            qDebug() << val;
            QMetaObject::invokeMethod(this->p_stat,
                                      "slot_set_m_type",
                                      Qt::QueuedConnection,
                                      Q_ARG(int, MEMBER));
        }
        else if (val == "비회원")
        {
            qDebug() << val;
            QMetaObject::invokeMethod(this->p_stat,
                                      "slot_set_m_type",
                                      Qt::QueuedConnection,
                                      Q_ARG(int, NONMEMBER));
        }
    }
    else if (cmd == "connector_case")
    {
        if (val == "unlock")
        {
            bool b = QMetaObject::invokeMethod(this->p_serial,
                                               "slot_rs485_coil1_on_off",
                                               Qt::QueuedConnection,
                                               Q_ARG(bool, true));
            if (!b)
            {
                qDebug() << "invok Err";
                if (this->p_serial == nullptr)
                {
                    qDebug() << "nullptr";
                }
            }
        }
    }
    else if (cmd == "connector")
    {
        if (val == "unlock")
        {
            uint16_t reg_pos = 0x01;
            uint16_t reg_val = 0x01;
            // 시리얼 통신으로 종료 요청
            QMetaObject::invokeMethod(this->p_serial,
                                      "slot_rs232_cmd",
                                      Qt::QueuedConnection,
                                      Q_ARG(uint16_t, reg_pos),
                                      Q_ARG(uint16_t, reg_val));
        }
    }
    else if (cmd == "ad_add")
    {
        this->update_ad(val);
    }
    else if (cmd == "ad_remove")
    {
        this->remove_ad(val);
    }
    else if (cmd == "shutdown")
    {
        if (val == "nomal")
        {
            this->shutdown_nomal();
        }
        else if (val == "restart")
        {
            this->shutdown_restart();
        }
    }

    return;
}

void WK_WebSocket::remove_ad(const QString name)
{
    QMetaObject::invokeMethod(this->p_stat,
                              "slot_remove_ad",
                              Qt::QueuedConnection,
                              Q_ARG(QString, name));
    return;
}

void WK_WebSocket::update_ad(const QString name)
{
    qDebug() << Q_FUNC_INFO;
    int need;
    QMetaObject::invokeMethod(this->p_stat,
                              "slot_find_ad",
                              Qt::BlockingQueuedConnection,
                              Q_RETURN_ARG(int, need),
                              Q_ARG(QString, name));

    if (need == NEED_DOWNLOAD)
    {
        qDebug() << Q_FUNC_INFO << " NEED_DOWNLOAD";
        // 그냥 무조건 다운 성공
        this->netAccess_get_download(name);
    }
    return;
}

void WK_WebSocket::netAccess_get_download(const QString name)
{
    QNetworkRequest req(this->httpSv_url);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/mp4/download");

    this->p_netAccess->get(req, name.toUtf8());

    return;
}

void WK_WebSocket::set_httpSv_url(const QString set)
{
    this->httpSv_url = QUrl(set);
    return;
}

void WK_WebSocket::slot_update_ad(const QString name)
{
    qDebug() << Q_FUNC_INFO;
    int need;
    QMetaObject::invokeMethod(this->p_stat,
                              "slot_find_ad",
                              Qt::BlockingQueuedConnection,
                              Q_RETURN_ARG(int, need),
                              Q_ARG(QString, name));

    if (need == NEED_DOWNLOAD)
    {
        qDebug() << Q_FUNC_INFO << " NEED_DOWNLOAD";
        // 그냥 무조건 다운 성공
        this->netAccess_get_download(name);
    }
    return;
}

void WK_WebSocket::shutdown_nomal()
{
    QMetaObject::invokeMethod(this->p_Module, &Cpp_Module::slot_nomal_exit, Qt::QueuedConnection);
    return;
}

void WK_WebSocket::shutdown_restart()
{
    QMetaObject::invokeMethod(this->p_Module, &Cpp_Module::slot_restart_exit, Qt::QueuedConnection);
    return;
}
