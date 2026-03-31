#include "WK_Soc.h"
#include "DB_PostgreSQL.h"
#include "Hub.h"
#include "StatModel.h"

WK_Soc::WK_Soc(QObject *parent)
    : QObject{parent}
{}

void WK_Soc::set_p_webSoc(QWebSocket *set_webSoc, int id_mp)
{
    this->p_WebSoc = set_webSoc;
    this->id_Mp = id_mp;
    // nextpending 으로 받은 소켓 객체 부모설정
    // WK객체 죽을 때 소켓 같이 삭제 유도

    this->p_WebSoc->setParent(this);

    connect(this->p_WebSoc, &QWebSocket::textMessageReceived, this, &WK_Soc::slot_Recv_TextData);

    // 소켓 연결 끊어지면 소켓 삭제 + 워커 객체 삭제
    // 소켓 연결 끊어지면 Hub qvec에서 wk* 삭제
    // 소켓 연결 끊어지면 Model 에서 st_stat 삭제

    // QObject::disconnect: wildcard call disconnects from destroyed signal of QTcpSocket::unnamed
    // 에러 방지용 QueuedConnection로 이벤트 루프 돌린 후 진행
    connect(this->p_WebSoc,
            &QWebSocket::disconnected,
            this,
            &WK_Soc::slot_Disconnect_Soc,
            Qt::QueuedConnection);

    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_Soc::set_p_md(StatModel *set_md)
{
    this->p_Md = set_md;

    // p_md 설정 후 모델 업데이트 시그널 연결
    if (this->p_Md)
    {
        connect(this, &WK_Soc::sig_update_md, this->p_Md, &StatModel::slot_qvec_update);
    }

    return;
}

void WK_Soc::set_p_Hub(Hub *set_Hub)
{
    this->p_Hub = set_Hub;
    return;
}

void WK_Soc::set_p_db(DB_PostgreSQL *set_db)
{
    this->p_obj_db = set_db;
    // db에 wk 주소 전달

    /*
    QMetaObject::invokeMethod(this->p_obj_db,
                              "slot_set_p_soc",
                              Qt::QueuedConnection,
                              Q_ARG(WK_Soc *, this));*/

    connect(this,
            &WK_Soc::sig_chargingLog_To_DB,
            this->p_obj_db,
            &DB_PostgreSQL::slot_chargingLog_From_soc);

    connect(this,
            &WK_Soc::sig_heartbitData_To_DB,
            this->p_obj_db,
            &DB_PostgreSQL::slot_heartbitData_From_soc);

    connect(this, &WK_Soc::sig_select_To_DB, this->p_obj_db, &DB_PostgreSQL::slot_select_From_soc);

    return;
}

void WK_Soc::slot_Disconnect_Soc()
{
    // 중복 호출 방지
    if (this->stat_Disconnect == true)
    {
        return;
    }
    this->stat_Disconnect = true;

    // 소켓 연결 끊어지면 Hub qvec에서 wk* 삭제
    this->p_Hub->slot_del_mpWk(this->id_Mp);

    if (this->connectRole == "admin")
    {
        // 소켓 연결 끊어지면 mp_hmi에서 삭제
        QPair<int, QString> p = {this->adminId, this->connectRole};
        this->p_Hub->mp_wk_remove(p);
    }
    else
    {
        // 소켓 연결 끊어지면 mp_hmi에서 삭제
        QPair<int, QString> p = {this->storeId, this->roleId};
        this->p_Hub->mp_wk_remove(p);
    }

    // 소켓 연결 끊어지면 Model 에서 st_stat 삭제
    QMetaObject::invokeMethod(this->p_Md,
                              &StatModel::slot_qvec_del,
                              Qt::QueuedConnection,
                              this->id_Common);

    // 소켓 연결 끊어지면 워커객체 삭제 + 소유중 WebSoc삭제
    QTimer::singleShot(0, this, &QObject::deleteLater);

    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_Soc::slot_Recv_TextData(QString recvData)
{
    qDebug() << Q_FUNC_INFO;

    QByteArray qba = recvData.toUtf8();
    QJsonParseError jsErr;
    QJsonDocument jsDoc = QJsonDocument::fromJson(qba, &jsErr);

    if (jsErr.error != QJsonParseError::NoError)
    {
        qDebug() << "Json Err";
    }

    QJsonObject jsObj = jsDoc.object();

    QString qs_type = jsObj["type"].toString();

    // 연결 안댄 상태로 다른 요청 받으면 리턴
    if (qs_type != "hello" && this->connectRole.isEmpty())
    {
        this->p_WebSoc->disconnect();
        return;
    }

    if (jsObj.contains("type"))
    {
        // 소켓 연결대상 확인용 타입
        if (qs_type == "hello")
        {
            // 연결대상 확정
            if (jsObj["role"].toString() == "admin")
            {
                this->connectRole = "admin";
                this->roleId = jsObj["adminId"].toString();

                this->adminId = this->roleId.toInt();
                this->key.id = this->adminId;
                this->key.s_id = "admin";

                this->p_Hub->mp_wk_insert({this->key.id, this->key.s_id}, this);
                this->slot_helloAck(true);
            }
            // 연결대상 확정
            else if (jsObj["role"].toString() == "hmi")
            {
                this->connectRole = "hmi";

                // hmiId 있는지 확인
                // storeId 확인
                bool ret_hello = false;

                QString storeId = jsObj["store_id"].toString();
                QString hmiId = jsObj["hmi_id"].toString();

                qDebug() << hmiId << " :: hmiId";
                qDebug() << storeId << " :: storeId";

                QMetaObject::invokeMethod(this->p_obj_db,
                                          "slot_query_find_hello_hmi",
                                          Qt::BlockingQueuedConnection,
                                          Q_RETURN_ARG(bool, ret_hello),
                                          Q_ARG(QString, storeId),
                                          Q_ARG(QString, hmiId));

                if (ret_hello == true)
                {
                    // this->roleId = jsObj["hmiId"].toString();
                    this->roleId = hmiId;
                    this->storeId = storeId.toInt();

                    this->key.id = this->storeId;
                    this->key.s_id = this->roleId;

                    this->p_Hub->mp_wk_insert({this->key.id, this->key.s_id}, this);
                    this->slot_helloAck(true);
                }
                else
                {
                    this->slot_helloAck(false);
                }
            }
        }
        else if (qs_type == "register") // admin
        {
            // register은 admin의 타입
            // admin이 아닌 소켓 연결에서 요청시 무시
            if (this->connectRole != "admin")
            {
                return;
            }
            else if (this->connectRole == "admin")
            {
                // db 등록요청
                bool ret_query = this->slot_registerReq(jsObj);
                // 등록 여부 반환
                this->slot_registerAck(ret_query);
            }
        }
        else if (qs_type == "register_hmi") // admin
        {
            // register은 admin의 타입
            // admin이 아닌 소켓 연결에서 요청시 무시
            if (this->connectRole != "admin")
            {
                return;
            }
            else if (this->connectRole == "admin")
            {
                // db 등록요청
                bool ret_query = this->slot_registerReq_hmi(jsObj);
                // 등록 여부 반환
                this->slot_registerAck_hmi(ret_query);
            }
        }
        else if (qs_type == "select") // admin
        {
            if (this->connectRole != "admin")
            {
                return;
            }
            else if (this->connectRole == "admin")
            {
                this->req_select_To_DB(jsObj);
            }
        }
        else if (qs_type == "select_mCard_status") // admin
        {
            if (this->connectRole != "admin")
            {
                return;
            }
            else if (this->connectRole == "admin")
            {
                this->req_select_mCard_status_To_DB(jsObj);
            }
        }
        else if (qs_type == "revision_mCard_status") // admin
        {
            if (this->connectRole != "admin")
            {
                return;
            }
            else if (this->connectRole == "admin")
            {
                this->req_revision_mCard_status_To_DB(jsObj);
            }
        }
        else if (qs_type == "revision_HMI") // admin
        {
            if (this->connectRole != "admin")
            {
                return;
            }
            else if (this->connectRole == "admin")
            {
                this->find_revision_HMI(jsObj);
            }
        }
        else if (qs_type == "chargingLog") // hmi
        {
            if (this->connectRole != "hmi")
            {
                return;
            }

            // jsobj 파싱 -> st로 만듬
            // db클래스에 st 전달 // connect 로 sig
            // db클래스에서 st파싱 -> query 등록 요청
            // 등록 여부 sv로 응답
            // sv -> hmi ack 발생
            this->req_chargingLog_To_DB(jsObj);
        }
        else if (qs_type == "heartbit_pong") // hmi
        {
            if (this->connectRole != "hmi")
            {
                return;
            }

            this->req_heartbitData_To_DB(jsObj);
        }
        else if (qs_type == "membershipCard_authorized") // hmi
        {
            if (this->connectRole != "hmi")
            {
                return;
            }

            this->req_membershipCard_authorized_To_DB(jsObj);
        }
        else if (qs_type == "membershipCard_finished")
        {
            if (this->connectRole != "hmi")
            {
                return;
            }

            this->req_membershipCard_finished_To_DB(jsObj);
        }
    }


    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_Soc::slot_helloAck(bool ret)
{
    if (ret == true)
    {
        QJsonObject jsObj;
        jsObj.insert("type", "hello_ack");
        jsObj.insert("ok", true);

        QJsonDocument jsDoc(jsObj);

        this->p_WebSoc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));
    }
    else
    {
        QJsonObject jsObj;
        jsObj.insert("type", "hello_ack");
        jsObj.insert("ok", false);

        QJsonDocument jsDoc(jsObj);

        this->p_WebSoc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));
    }
    qDebug() << Q_FUNC_INFO;
    return;
}

bool WK_Soc::slot_registerReq(const QJsonObject &jsObj)
{
    QString qs_id = jsObj["registerId"].toString();
    QString qs_name = jsObj["registerName"].toString();
    QString qs_location = jsObj["registerLocation"].toString();

    qDebug() << qs_id << " :: id";
    qDebug() << qs_name << " :: name";
    qDebug() << qs_location << " :: location";

    bool ret_query = false;

    QMetaObject::invokeMethod(this->p_obj_db,
                              "slot_query_register",
                              Qt::BlockingQueuedConnection,
                              Q_RETURN_ARG(bool, ret_query),
                              Q_ARG(QString, qs_id),
                              Q_ARG(QString, qs_name),
                              Q_ARG(QString, qs_location));

    qDebug() << Q_FUNC_INFO;
    return ret_query;
}

void WK_Soc::slot_registerAck(bool ret)
{
    if (ret == true)
    {
        QJsonObject jsObj;
        jsObj.insert("type", "register_ack");
        jsObj.insert("ok", true);

        QJsonDocument jsDoc(jsObj);

        this->p_WebSoc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));
    }
    else
    {
        QJsonObject jsObj;
        jsObj.insert("type", "register_ack");
        jsObj.insert("ok", false);

        QJsonDocument jsDoc(jsObj);

        this->p_WebSoc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));
    }
    qDebug() << Q_FUNC_INFO;
    return;
}

bool WK_Soc::slot_registerReq_hmi(const QJsonObject &jsObj)
{
    QString qs_storeId = jsObj["registerId_store"].toString();
    QString qs_hmiId = jsObj["registerId_hmi"].toString();

    bool ret_query = false;

    QMetaObject::invokeMethod(this->p_obj_db,
                              "slot_query_register_hmi",
                              Qt::BlockingQueuedConnection,
                              Q_RETURN_ARG(bool, ret_query),
                              Q_ARG(QString, qs_storeId),
                              Q_ARG(QString, qs_hmiId));

    qDebug() << Q_FUNC_INFO;
    return ret_query;
}

void WK_Soc::slot_registerAck_hmi(bool ret)
{
    if (ret == true)
    {
        QJsonObject jsObj;
        jsObj.insert("type", "register_hmi_ack");
        jsObj.insert("ok", true);

        QJsonDocument jsDoc(jsObj);

        this->p_WebSoc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));
    }
    else
    {
        QJsonObject jsObj;
        jsObj.insert("type", "register_hmi_ack");
        jsObj.insert("ok", false);

        QJsonDocument jsDoc(jsObj);

        this->p_WebSoc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));
    }
    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_Soc::req_chargingLog_To_DB(const QJsonObject &jsObj)
{
    struct db_data st_db_data = {0};

    // session_id는 보내는 쪽에서 문자열로 보냄
    // session_id 안씀 수정
    // st_db_data.session_id = jsObj["session_id"].toString().toULongLong();

    // uint32_t들은 unsigned로 받는 게 안전
    st_db_data.store_id = jsObj["store_id"].toVariant().toUInt();
    st_db_data.hmi_id = jsObj["hmi_id"].toString();
    st_db_data.ocpp_tx_id = jsObj["ocpp_tx_id"].toVariant().toUInt();
    st_db_data.card_uid = jsObj["card_uid"].toString();

    st_db_data.start_time = jsObj["start_time"].toString();
    st_db_data.end_time = jsObj["end_time"].toString();
    st_db_data.duration_time = jsObj["duration_time"].toString();
    st_db_data.average_kWh = jsObj["average_kWh"].toDouble();

    st_db_data.soc_start = jsObj["soc_start"].toVariant().toDouble();
    st_db_data.soc_end = jsObj["soc_end"].toVariant().toDouble();

    st_db_data.advance_payment = jsObj["advance_payment"].toVariant().toUInt();
    st_db_data.cancel_payment = jsObj["cancel_payment"].toVariant().toUInt();
    st_db_data.actual_payment = jsObj["actual_payment"].toVariant().toUInt();
    st_db_data.unit_price = jsObj["unit_price"].toVariant().toUInt();
    st_db_data.tariff_type = jsObj["tariff_type"].toString();

    st_db_data.session_status = jsObj["session_status"].toString();
    st_db_data.stop_reason = jsObj["stop_reason"].toString();

    st_db_data.local_tx_id = jsObj["local_tx_id"].toString();

    emit this->sig_chargingLog_To_DB(this->key, st_db_data);
    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_Soc::slot_chargingLog_authorized_ack_To_hmi()
{
    QJsonObject jsObj;
    jsObj.insert("type", "chargingLog_ack");
    jsObj.insert("session_status", "authorized");
    // jsObj.insert("session_id", qs_session_id);

    QJsonDocument jsDoc(jsObj);
    this->p_WebSoc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));

    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_Soc::slot_chargingLog_charging_start_ack_To_hmi(uint32_t ocpp_tx_id)
{
    qDebug() << ocpp_tx_id << "ocpp val";
    QJsonObject jsObj;
    jsObj.insert("type", "chargingLog_ack");
    jsObj.insert("session_status", "charging_start");
    jsObj.insert("ocpp_tx_id", static_cast<qint32>(ocpp_tx_id));

    QJsonDocument jsDoc(jsObj);
    this->p_WebSoc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));

    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_Soc::slot_chargingLog_charging_finished_ack_To_hmi()
{
    QJsonObject jsObj;
    jsObj.insert("type", "chargingLog_ack");
    jsObj.insert("session_status", "charging_finished");

    QJsonDocument jsDoc(jsObj);
    this->p_WebSoc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));

    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_Soc::occur_heartbit()
{
    QJsonObject jsObj;
    jsObj.insert("type", "heartbit_ping");

    QJsonDocument jsDoc(jsObj);
    this->p_WebSoc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));

    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_Soc::req_heartbitData_To_DB(const QJsonObject &jsObj)
{
    struct heartbit_data st_hb_data;
    st_hb_data.hmi_id = jsObj["hmi_id"].toString();
    st_hb_data.store_id = jsObj["store_id"].toInt();
    st_hb_data.ws_connected = this->p_WebSoc->isValid();
    st_hb_data.last_heartbeat_at = QDateTime::currentDateTimeUtc();
    st_hb_data.screen_name = jsObj["screen_name"].toString();

    qDebug() << "json " << jsObj["screen_name"].toString();
    emit this->sig_heartbitData_To_DB(st_hb_data);
    return;
}

void WK_Soc::req_membershipCard_authorized_To_DB(const QJsonObject &jsObj)
{
    int adv_pay = jsObj["adv_pay"].toInt();
    QString card_uid = jsObj["card_uid"].toString();
    QString request_id = jsObj["request_id"].toString();

    QMetaObject::invokeMethod(this->p_obj_db,
                              "slot_membershipCard_authorized_From_soc",
                              Qt::QueuedConnection,
                              Q_ARG(mp_wk_key, this->key),
                              Q_ARG(int, adv_pay),
                              Q_ARG(QString, card_uid),
                              Q_ARG(QString, request_id));
    return;
}

void WK_Soc::slot_membershipCard_authorized_ack_To_hmi(bool ok, QString msg)
{
    QJsonObject jsObj;
    if (ok == true)
    {
        jsObj.insert("type", "membershipCard_authorized_ack");
        jsObj.insert("ok", ok);
        jsObj.insert("transaction_id", msg);
    }
    else
    {
        jsObj.insert("type", "membershipCard_authorized_ack");
        jsObj.insert("ok", ok);
        jsObj.insert("failed_msg", msg);
    }

    QJsonDocument jsDoc(jsObj);
    // ack 미전송 테스트 완료
    this->p_WebSoc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));
    return;
}

void WK_Soc::req_membershipCard_finished_To_DB(const QJsonObject &jsObj)
{
    int adv_pay = jsObj["adv_pay"].toInt();
    int act_pay = jsObj["act_pay"].toInt();
    int can_pay = jsObj["can_pay"].toInt();
    QString card_uid = jsObj["card_uid"].toString();
    uint32_t t_id = jsObj["transaction_id"].toInt();
    QString request_id = jsObj["request_id"].toString();

    QMetaObject::invokeMethod(this->p_obj_db,
                              "slot_membershipCard_finished_From_soc",
                              Qt::QueuedConnection,
                              Q_ARG(mp_wk_key, this->key),
                              Q_ARG(int, adv_pay),
                              Q_ARG(int, act_pay),
                              Q_ARG(int, can_pay),
                              Q_ARG(QString, card_uid),
                              Q_ARG(uint32_t, t_id),
                              Q_ARG(QString, request_id));
    return;
}

void WK_Soc::slot_membershipCard_finished_ack_To_hmi(bool ok)
{
    // finished는 이미 홀드 잡은거 처리하는거라서
    // 전송에러 말고 다른거 없음
    // ok false 이면 나중에 처리댈거임 알려주면댐
    QJsonObject jsObj;
    jsObj.insert("type", "membershipCard_finished_ack");
    jsObj.insert("ok", ok);

    QJsonDocument jsDoc(jsObj);
    this->p_WebSoc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));
    return;
}

void WK_Soc::req_select_To_DB(const QJsonObject &jsObj)
{
    int filter_num = jsObj["filter_num"].toInt();
    QString table = jsObj["table"].toString();
    QVector<QPair<QString, QString>> vp;

    QJsonArray jsArr = jsObj["filter_arr"].toArray();

    for (int i = 0; i < jsArr.size(); i++)
    {
        QJsonObject tmp_jo = jsArr[i].toObject();
        QStringList sl_key = tmp_jo.keys();

        for (auto &v : sl_key)
        {
            QString val = tmp_jo[v].toString();
            vp.push_back({v, val});
        }
    }

    if (filter_num == 0)
    {
        emit this->sig_select_To_DB(this->key, table, filter_num);
    }
    else if (filter_num == 1 && vp.size() == 1)
    {
        emit this->sig_select_To_DB(this->key, table, filter_num, vp[0].first, vp[0].second);
    }
    else if (filter_num == 2 && vp.size() == 2)
    {
        emit this->sig_select_To_DB(this->key,
                                    table,
                                    filter_num,
                                    vp[0].first,
                                    vp[0].second,
                                    vp[1].first,
                                    vp[1].second);
    }
    else if (filter_num == 3 && vp.size() == 3)
    {
        emit this->sig_select_To_DB(this->key,
                                    table,
                                    filter_num,
                                    vp[0].first,
                                    vp[0].second,
                                    vp[1].first,
                                    vp[1].second,
                                    vp[2].first,
                                    vp[2].second);
    }
    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_Soc::slot_charging_log_select_ret_From_DB__To_admin(QVector<charging_log_admin> ret)
{
    QJsonObject jo_root;
    jo_root.insert("type", "select_ack");
    jo_root.insert("table", "charging_log");
    jo_root.insert("cnt", ret.size());

    QJsonArray jArry;

    for (auto &v : ret)
    {
        QJsonObject jo_tmp;
        jo_tmp.insert("created_at", v.created_at);
        jo_tmp.insert("updated_at", v.updated_at);
        jo_tmp.insert("row_id", v.row_id);
        jo_tmp.insert("store_id", v.store_id);
        jo_tmp.insert("hmi_id", v.hmi_id);
        jo_tmp.insert("ocpp_tx_id", v.ocpp_tx_id);
        jo_tmp.insert("card_uid", v.card_uid);
        jo_tmp.insert("start_time", v.start_time);
        jo_tmp.insert("end_time", v.end_time);
        jo_tmp.insert("duration_time", v.duration_time);
        jo_tmp.insert("average_kwh", v.average_kwh);
        jo_tmp.insert("soc_start", v.soc_start);
        jo_tmp.insert("soc_end", v.soc_end);
        jo_tmp.insert("advance_payment", v.advance_payment);
        jo_tmp.insert("cancel_payment", v.cancel_payment);
        jo_tmp.insert("actual_payment", v.actual_payment);
        jo_tmp.insert("unit_price", v.unit_price);
        jo_tmp.insert("tariff_type", v.tariff_type);
        jo_tmp.insert("session_status", v.session_status);
        jo_tmp.insert("stop_reason", v.stop_reason);
        jo_tmp.insert("local_tx_id", v.local_tx_id);

        jArry.append(jo_tmp);
    }

    if (!jArry.empty())
    {
        jo_root.insert("select_arr", jArry);
    }

    QJsonDocument jsDoc(jo_root);
    this->p_WebSoc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));
    qDebug() << jsDoc.toJson(QJsonDocument::Compact);
    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_Soc::slot_hmi_current_stat_select_ret_From_DB__To_admin(QVector<hmi_current_stat_admin> ret)
{
    QJsonObject jo_root;
    jo_root.insert("type", "select_ack");
    jo_root.insert("table", "hmi_current_stat");
    jo_root.insert("cnt", ret.size());

    QJsonArray jArry;

    for (auto &v : ret)
    {
        QJsonObject jo_tmp;
        jo_tmp.insert("hmi_id", v.hmi_id);
        jo_tmp.insert("store_id", v.store_id);
        jo_tmp.insert("ws_connected", v.ws_connected);
        jo_tmp.insert("last_heartbeat_at", v.last_heartbeat_at);
        jo_tmp.insert("screen_name", v.screen_name);
        jo_tmp.insert("updated_at", v.updated_at);

        jArry.append(jo_tmp);
    }

    if (!jArry.empty())
    {
        jo_root.insert("select_arr", jArry);
    }

    QJsonDocument jsDoc(jo_root);
    this->p_WebSoc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));
    qDebug() << jsDoc.toJson(QJsonDocument::Compact);
    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_Soc::slot_hmi_device_select_ret_From_DB__To_admin(QVector<hmi_device_admin> ret)
{
    QJsonObject jo_root;
    jo_root.insert("type", "select_ack");
    jo_root.insert("table", "hmi_device");
    jo_root.insert("cnt", ret.size());

    QJsonArray jArry;

    for (auto &v : ret)
    {
        QJsonObject jo_tmp;
        jo_tmp.insert("hmi_id", v.hmi_id);
        jo_tmp.insert("store_id", v.store_id);

        jArry.append(jo_tmp);
    }

    if (!jArry.empty())
    {
        jo_root.insert("select_arr", jArry);
    }

    QJsonDocument jsDoc(jo_root);
    this->p_WebSoc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));
    qDebug() << jsDoc.toJson(QJsonDocument::Compact);
    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_Soc::slot_membership_card_select_ret_From_DB__To_admin(QVector<membership_card_admin> ret)
{
    QJsonObject jo_root;
    jo_root.insert("type", "select_ack");
    jo_root.insert("table", "membership_card");
    jo_root.insert("cnt", ret.size());

    QJsonArray jArry;

    for (auto &v : ret)
    {
        QJsonObject jo_tmp;
        jo_tmp.insert("card_uid", v.card_uid);
        jo_tmp.insert("balance_total", v.balance_total);
        jo_tmp.insert("balance_available", v.balance_available);
        jo_tmp.insert("hold_amount", v.hold_amount);
        jo_tmp.insert("transaction_state", v.transaction_state);

        jArry.append(jo_tmp);
    }

    if (!jArry.empty())
    {
        jo_root.insert("select_arr", jArry);
    }

    QJsonDocument jsDoc(jo_root);
    this->p_WebSoc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));
    qDebug() << jsDoc.toJson(QJsonDocument::Compact);
    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_Soc::slot_membership_log_select_ret_From_DB__To_admin(QVector<membership_log_admin> ret)
{
    QJsonObject jo_root;
    jo_root.insert("type", "select_ack");
    jo_root.insert("table", "membership_log");
    jo_root.insert("cnt", ret.size());

    QJsonArray jArry;

    for (auto &v : ret)
    {
        QJsonObject jo_tmp;

        jo_tmp.insert("card_uid", v.card_uid);
        jo_tmp.insert("transaction_id", v.transaction_id);
        jo_tmp.insert("event_type", v.event_type);
        jo_tmp.insert("amount", v.amount);
        jo_tmp.insert("balance_available_before", v.balance_available_before);
        jo_tmp.insert("balance_available_after", v.balance_available_after);
        jo_tmp.insert("hold_amount_before", v.hold_amount_before);
        jo_tmp.insert("hold_amount_after", v.hold_amount_after);
        jo_tmp.insert("transaction_state_before", v.transaction_state_before);
        jo_tmp.insert("transaction_state_after", v.transaction_state_after);
        jo_tmp.insert("created_at", v.created_at);
        jo_tmp.insert("request_id", v.request_id);

        jArry.append(jo_tmp);
    }

    if (!jArry.empty())
    {
        jo_root.insert("select_arr", jArry);
    }

    QJsonDocument jsDoc(jo_root);
    this->p_WebSoc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));
    qDebug() << jsDoc.toJson(QJsonDocument::Compact);
    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_Soc::slot_store_user_select_ret_From_DB__To_admin(QVector<store_user_admin> ret)
{
    QJsonObject jo_root;
    jo_root.insert("type", "select_ack");
    jo_root.insert("table", "store_user");
    jo_root.insert("cnt", ret.size());

    QJsonArray jArry;

    for (auto &v : ret)
    {
        QJsonObject jo_tmp;

        jo_tmp.insert("id", v.id);
        jo_tmp.insert("name", v.name);
        jo_tmp.insert("location", v.location);
        jArry.append(jo_tmp);
    }

    if (!jArry.empty())
    {
        jo_root.insert("select_arr", jArry);
    }

    QJsonDocument jsDoc(jo_root);
    this->p_WebSoc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));
    qDebug() << jsDoc.toJson(QJsonDocument::Compact);
    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_Soc::req_select_mCard_status_To_DB(const QJsonObject &jsObj)
{
    QString table = "membership_card";
    QMetaObject::invokeMethod(this->p_obj_db,
                              "slot_select_mCard_status_From_soc",
                              Qt::QueuedConnection,
                              Q_ARG(mp_wk_key, this->key),
                              Q_ARG(QString, table),
                              Q_ARG(QString, jsObj["card_uid"].toString()));
    return;
}

void WK_Soc::slot_mCard_status_ret_From_DB__To_admin(QVector<membership_card_admin> ret)
{
    QJsonObject jo_root;
    jo_root.insert("type", "select_mCard_status_ack");
    jo_root.insert("table", "membership_card");
    jo_root.insert("cnt", ret.size());

    QJsonArray jArry;

    for (auto &v : ret)
    {
        QJsonObject jo_tmp;
        jo_tmp.insert("card_uid", v.card_uid);
        jo_tmp.insert("balance_total", v.balance_total);
        jo_tmp.insert("balance_available", v.balance_available);
        jo_tmp.insert("hold_amount", v.hold_amount);
        jo_tmp.insert("transaction_state", v.transaction_state);

        jArry.append(jo_tmp);
    }

    if (!jArry.empty())
    {
        jo_root.insert("select_arr", jArry);
    }

    QJsonDocument jsDoc(jo_root);
    this->p_WebSoc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));
    qDebug() << jsDoc.toJson(QJsonDocument::Compact);
    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_Soc::req_revision_mCard_status_To_DB(const QJsonObject &jsObj)
{
    qDebug() << Q_FUNC_INFO;
    // QString table = "membership_card";
    QMetaObject::invokeMethod(this->p_obj_db,
                              "slot_revision_mCard_status_From_soc",
                              Qt::QueuedConnection,
                              Q_ARG(QString, jsObj["card_uid"].toString()),
                              Q_ARG(int, jsObj["balance_total"].toInt()),
                              Q_ARG(int, jsObj["balance_available"].toInt()),
                              Q_ARG(int, jsObj["hold_amount"].toInt()),
                              Q_ARG(QString, jsObj["transaction_state"].toString()));
    return;
}

void WK_Soc::find_revision_HMI(const QJsonObject &jsObj)
{
    qDebug() << Q_FUNC_INFO;
    int store_id = jsObj["store_id"].toInt();
    QString hmi_id = jsObj["hmi_id"].toString();
    QPair<int, QString> key = {store_id, hmi_id};

    auto p_target = this->p_Hub->mp_wk_find(key);
    p_target->echo_revision_HMI_To_hmi(jsObj);

    /*
        일단 이게 어떤 HMI한태? 부터 알아야댐
        서버는 걍 전달만 하면댐 마지막에 파싱하면댐
    */
    return;
}

void WK_Soc::echo_revision_HMI_To_hmi(const QJsonObject &jsObj)
{
    QJsonDocument jsDoc(jsObj);

    this->p_WebSoc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));
    qDebug() << jsDoc.toJson(QJsonDocument::Compact);
    qDebug() << Q_FUNC_INFO;
    return;
}
