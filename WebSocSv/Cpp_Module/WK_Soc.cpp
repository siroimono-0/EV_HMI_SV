#include "WK_Soc.h"
#include "DB_PostgreSQL.h"
#include "Hub.h"
#include "StatModel.h"

WK_Soc::WK_Soc(QObject *parent)
    : QObject{parent}
{
}

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
        if (qs_type == "hello")
        {
            if (jsObj["role"].toString() == "admin")
            {
                this->connectRole = "admin";
                this->roleId = jsObj["adminId"].toString();
                this->slot_helloAck(true);
            }
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
                    this->roleId = jsObj["hmiId"].toString();
                    this->slot_helloAck(true);
                }
                else
                {
                    this->slot_helloAck(false);
                }
            }
        }
        else if (qs_type == "register")
        {
            // register은 admin의 타입
            // admin이 아닌 소켓 연결에서 요청시 무시
            if (this->connectRole != "admin")
            {
                return;
            }
            else if (this->connectRole == "admin")
            {
                bool ret_query = this->slot_registerReq(jsObj);
                this->slot_registerAck(ret_query);
            }
        }
        else if (qs_type == "register_hmi")
        {
            // register은 admin의 타입
            // admin이 아닌 소켓 연결에서 요청시 무시
            if (this->connectRole != "admin")
            {
                return;
            }
            else if (this->connectRole == "admin")
            {
                bool ret_query = this->slot_registerReq_hmi(jsObj);
                this->slot_registerAck_hmi(ret_query);
            }
        }
    }

    if (jsObj.contains("id_Check"))
    {
        QString find_id = jsObj["id"].toString();
        // db에서 id체크하고 답장함
        struct store_info st_info = {0};

        // 못찾았으면 id -1 반환함
        QMetaObject::invokeMethod(this->p_obj_db,
                                  "slot_query_find_id",
                                  Qt::BlockingQueuedConnection,
                                  Q_RETURN_ARG(store_info, st_info),
                                  Q_ARG(QString, find_id));

        if (st_info.id != -1)
        {
            QJsonObject json_obj_ID;
            json_obj_ID.insert("id_Check", true);
            json_obj_ID.insert("id", st_info.id);
            json_obj_ID.insert("name", st_info.name);
            json_obj_ID.insert("location", st_info.location);

            QJsonDocument json_doc_ID(json_obj_ID);
            QString send_qs = json_doc_ID.toJson(QJsonDocument::Compact);

            this->p_WebSoc->sendTextMessage(send_qs);
        }
        else
        {
            QJsonObject json_obj_ID;
            json_obj_ID.insert("id_Check", false);

            QJsonDocument json_doc_ID(json_obj_ID);
            QString send_qs = json_doc_ID.toJson(QJsonDocument::Compact);

            this->p_WebSoc->sendTextMessage(send_qs);
        }
    }
    else
    {
        struct stat_data st_stat;
        st_stat.number = jsObj["number"].toInt();
        st_stat.id = jsObj["id"].toInt();
        st_stat.location = jsObj["location"].toString();
        st_stat.date = jsObj["date"].toString();
        st_stat.stat = jsObj["stat"].toInt();

        qDebug() << st_stat.id;
        qDebug() << st_stat.location;
        qDebug() << st_stat.date;

        // 구별자 id 설정
        this->id_Common = st_stat.id;
        emit sig_update_md(st_stat);
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
