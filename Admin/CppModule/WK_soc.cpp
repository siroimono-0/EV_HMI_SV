#include "WK_soc.h"
#include "Dia_HMI.h"
#include "Dia_membership_card.h"
#include "MD_charging_log.h"
#include "MD_hmi_current_stat.h"
#include "MD_hmi_device.h"
#include "MD_membership_card.h"
#include "MD_membership_log.h"
#include "MD_store_user.h"

WK_soc::WK_soc(QObject *parent)
    : QObject{parent}
{
    this->p_netAccess = new QNetworkAccessManager(this);
}

void WK_soc::slot_netAccess_post(QString file_path)
{
    qDebug() << Q_FUNC_INFO;
    QFile *p_file = new QFile(file_path);
    if (!p_file->open(QIODevice::ReadOnly))
    {
        qDebug() << "file open fail";
        delete p_file;
        return;
    }

    QString fileName = QFileInfo(*p_file).fileName();
    qDebug() << QFileInfo(*p_file).fileName();

    // strcpy(st_data.name, fileName.constData());
    QByteArray qba = p_file->readAll();
    QByteArray name_qba = fileName.toUtf8();
    qba = name_qba + "\r\n" + qba;

    QUrl url("http://127.0.0.1:8080/compare");
    QNetworkRequest req(url);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/mp4/upload");

    QNetworkReply *p_reply = this->p_netAccess->post(req, qba);

    connect(p_reply, &QNetworkReply::finished, this, [p_reply]() {
        QByteArray ba_res = p_reply->readAll();

        p_reply->deleteLater();
    });

    return;
}

void WK_soc::slot_end()
{
    if (this->p_soc)
    {
        // 정상 close (필요하면 closeCode/Reason도)
        this->p_soc->close();

        this->p_soc = nullptr;
    }

    emit this->sig_end();
    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_soc::slot_start()
{
    this->p_soc = new QWebSocket();
    this->p_soc->setParent(this);

    connect(this->p_soc, &QWebSocket::connected, this, &WK_soc::slot_connect_hello);
    connect(this->p_soc, &QWebSocket::disconnected, this, &WK_soc::slot_disconnected);

    connect(this->p_soc, &QWebSocket::textMessageReceived, this, &WK_soc::slot_recvText);

    this->p_soc->open(QUrl("ws://192.168.123.102:12345/ws/admin"));
    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_soc::slot_disconnected()
{
    // QTimer::singleShot(0, this, &QObject::deleteLater);
    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_soc::slot_connect_hello()
{
    QJsonObject jsObj;
    jsObj.insert("type", "hello");
    jsObj.insert("role", "admin");
    jsObj.insert("token", "");
    jsObj.insert("adminId", "001");

    QJsonDocument jsDoc(jsObj);
    this->p_soc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));
    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_soc::slot_register_store(const QString id, const QString name, const QString location)
{
    QJsonObject jsObj;
    qDebug() << id << " :: id";
    qDebug() << name << " :: name";
    qDebug() << location << " :: location";

    jsObj.insert("type", "register");
    jsObj.insert("registerId", id);
    jsObj.insert("registerName", name);
    jsObj.insert("registerLocation", location);

    QJsonDocument jsDoc(jsObj);
    this->p_soc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));
    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_soc::slot_register_hmi(const QString storeId, const QString hmiId)
{
    QJsonObject jsObj;
    qDebug() << storeId << " :: id";
    qDebug() << hmiId << " :: name";

    jsObj.insert("type", "register_hmi");
    jsObj.insert("registerId_store", storeId);
    jsObj.insert("registerId_hmi", hmiId);

    QJsonDocument jsDoc(jsObj);
    this->p_soc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));
    qDebug() << Q_FUNC_INFO;

    return;
}

void WK_soc::slot_recvText(QString recvMsg)
{
    // qDebug() << recvMsg;

    QByteArray qba = recvMsg.toUtf8();
    QJsonParseError jsErr;
    QJsonDocument jsDoc = QJsonDocument::fromJson(qba, &jsErr);

    if (jsErr.error != QJsonParseError::NoError)
    {
        qDebug() << "Json Err";
    }

    QJsonObject jsObj = jsDoc.object();

    if (jsObj.contains("type"))
    {
        if (jsObj["type"].toString() == "hello_ack")
        {
            if (jsObj["ok"].toBool() == true)
            {
                qDebug() << "hello ok";
            }
            else if (jsObj["ok"].toBool() == false)
            {
                qDebug() << "hello X";
            }
        }
        else if (jsObj["type"].toString() == "register_ack")
        {
            if (jsObj["ok"].toBool() == true)
            {
                qDebug() << "register ok";
            }
            else if (jsObj["ok"].toBool() == false)
            {
                qDebug() << "register X";
            }
        }
        else if (jsObj["type"].toString() == "register_hmi_ack")
        {
            if (jsObj["ok"].toBool() == true)
            {
                qDebug() << "register ok";
            }
            else if (jsObj["ok"].toBool() == false)
            {
                qDebug() << "register X";
            }
        }
        else if (jsObj["type"].toString() == "select_ack")
        {
            this->parsing_select(jsObj);
        }
        else if (jsObj["type"].toString() == "select_mCard_status_ack")
        {
            this->parsing_mCard(jsObj);
        }
    }
    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_soc::slot_req_select_db(QString table,
                                int total,
                                QString col_1,
                                QString val_1,
                                QString col_2,
                                QString val_2,
                                QString col_3,
                                QString val_3)
{
    // 제이슨 만들어서 sv에 넘겨야댐
    // 타입
    // 무슨 테이블 조회인지
    // when 필터 몇 개 인지
    // when 컬럼, 값
    QJsonObject jsObj_root;

    QJsonObject jsObj_filter;
    QJsonArray jsArr;

    if (total == 0)
    {
        jsObj_root.insert("type", "select");
        jsObj_root.insert("table", table);
        jsObj_root.insert("filter_num", total);
    }
    else if (total == 1)
    {
        jsObj_root.insert("type", "select");
        jsObj_root.insert("table", table);
        jsObj_root.insert("filter_num", total);

        jsObj_filter.insert(col_1, val_1);
        jsArr.append(jsObj_filter);

        jsObj_root.insert("filter_arr", jsArr);
    }
    else if (total == 2)
    {
        jsObj_root.insert("type", "select");
        jsObj_root.insert("table", table);
        jsObj_root.insert("filter_num", total);

        jsObj_filter.insert(col_1, val_1);
        jsObj_filter.insert(col_2, val_2);
        jsArr.append(jsObj_filter);

        jsObj_root.insert("filter_arr", jsArr);
    }
    else if (total == 3)
    {
        jsObj_root.insert("type", "select");
        jsObj_root.insert("table", table);
        jsObj_root.insert("filter_num", total);

        jsObj_filter.insert(col_1, val_1);
        jsObj_filter.insert(col_2, val_2);
        jsObj_filter.insert(col_3, val_3);
        jsArr.append(jsObj_filter);

        jsObj_root.insert("filter_arr", jsArr);
    }

    QJsonDocument jsDoc(jsObj_root);
    this->p_soc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));
    qDebug() << jsDoc.toJson(QJsonDocument::Compact);
    qDebug() << Q_FUNC_INFO;

    return;
}

void WK_soc::parsing_select(const QJsonObject jo)
{
    QString table = jo["table"].toString();
    int cnt = jo["cnt"].toInt();

    if (table == "charging_log")
    {
        QVector<charging_log_admin> vec;
        // QVector<charging_log_admin_cnv> vec;
        if (cnt == 0)
        {
            charging_log_admin empty = {0};
            // charging_log_admin_cnv empty = {0};
            empty.created_at = "조회된 결과가";
            empty.updated_at = " 없습니다";
            vec.push_back(empty);
            emit this->sig_update_charging_log(vec);
        }
        else
        {
            QJsonArray jArr = jo["select_arr"].toArray();

            for (int i = 0; i < jArr.size(); i++)
            {
                charging_log_admin st_log = {0};
                // charging_log_admin_cnv st_log = {0};

                QJsonObject tmp_jo = jArr[i].toObject();
                st_log.created_at = tmp_jo["created_at"].toString().left(19);
                st_log.updated_at = tmp_jo["updated_at"].toString().left(19);
                st_log.row_id = tmp_jo["row_id"].toInt();
                st_log.store_id = tmp_jo["store_id"].toInt();
                st_log.hmi_id = tmp_jo["hmi_id"].toString();
                st_log.ocpp_tx_id = tmp_jo["ocpp_tx_id"].toInt();
                st_log.card_uid = tmp_jo["card_uid"].toString();
                st_log.start_time = tmp_jo["start_time"].toString().left(8);
                st_log.end_time = tmp_jo["end_time"].toString().left(8);
                st_log.duration_time = tmp_jo["duration_time"].toString().left(8);

                st_log.average_kwh = tmp_jo["average_kwh"].toDouble();
                int tmp = (int) (tmp_jo["soc_start"].toDouble() * 100);
                st_log.soc_start = (double) ((double) tmp / 100.0);
                st_log.soc_end = tmp_jo["soc_end"].toDouble();

                st_log.advance_payment = tmp_jo["advance_payment"].toInt();
                st_log.cancel_payment = tmp_jo["cancel_payment"].toInt();
                st_log.actual_payment = tmp_jo["actual_payment"].toInt();
                st_log.unit_price = tmp_jo["unit_price"].toInt();
                st_log.tariff_type = tmp_jo["tariff_type"].toString();
                st_log.session_status = tmp_jo["session_status"].toString();
                st_log.stop_reason = tmp_jo["stop_reason"].toString();
                st_log.local_tx_id = tmp_jo["local_tx_id"].toString();

                vec.push_back(st_log);
            }
            emit this->sig_update_charging_log(vec);
        }
        return;
    }
    else if (table == "hmi_current_stat")
    {
        QVector<hmi_current_stat_admin> vec;
        // QVector<charging_log_admin_cnv> vec;
        if (cnt == 0)
        {
            hmi_current_stat_admin empty = {0};
            // charging_log_admin_cnv empty = {0};
            empty.last_heartbeat_at = "조회된 결과가";
            empty.screen_name = " 없습니다";
            vec.push_back(empty);
        }
        else
        {
            QJsonArray jArr = jo["select_arr"].toArray();

            for (int i = 0; i < jArr.size(); i++)
            {
                hmi_current_stat_admin st_log = {0};
                // charging_log_admin_cnv st_log = {0};

                QJsonObject tmp_jo = jArr[i].toObject();
                st_log.hmi_id = tmp_jo["hmi_id"].toString();
                st_log.store_id = tmp_jo["store_id"].toInt();
                st_log.ws_connected = tmp_jo["ws_connected"].toBool();
                st_log.last_heartbeat_at = tmp_jo["last_heartbeat_at"].toString().left(19);
                st_log.screen_name = tmp_jo["screen_name"].toString();
                st_log.updated_at = tmp_jo["updated_at"].toString().left(19);

                vec.push_back(st_log);
            }
        }
        if (this->dia_hmi_reqStat == true)
        {
            this->dia_hmi_reqStat = false;
            emit this->sig_update_hmi_current_stat_To_Dia_HMI(vec);
        }
        else
        {
            emit this->sig_update_hmi_current_stat(vec);
        }
        return;
    }
    else if (table == "hmi_device")
    {
        QVector<hmi_device_admin> vec;
        // QVector<charging_log_admin_cnv> vec;
        if (cnt == 0)
        {
            hmi_device_admin empty = {0};
            // charging_log_admin_cnv empty = {0};
            empty.hmi_id = "조회 X";
            vec.push_back(empty);
            emit this->sig_update_hmi_device(vec);
        }
        else
        {
            QJsonArray jArr = jo["select_arr"].toArray();

            for (int i = 0; i < jArr.size(); i++)
            {
                hmi_device_admin st_log = {0};
                // charging_log_admin_cnv st_log = {0};

                QJsonObject tmp_jo = jArr[i].toObject();
                st_log.hmi_id = tmp_jo["hmi_id"].toString();
                st_log.store_id = tmp_jo["store_id"].toInt();

                vec.push_back(st_log);
            }
            emit this->sig_update_hmi_device(vec);
        }
        return;
    }
    else if (table == "membership_card")
    {
        QVector<membership_card_admin> vec;
        // QVector<charging_log_admin_cnv> vec;
        if (cnt == 0)
        {
            membership_card_admin empty = {0};
            // charging_log_admin_cnv empty = {0};
            empty.card_uid = "조회 X";
            vec.push_back(empty);
            emit this->sig_update_membership_card(vec);
        }
        else
        {
            QJsonArray jArr = jo["select_arr"].toArray();

            for (int i = 0; i < jArr.size(); i++)
            {
                membership_card_admin st_log = {0};
                // charging_log_admin_cnv st_log = {0};

                QJsonObject tmp_jo = jArr[i].toObject();
                st_log.card_uid = tmp_jo["card_uid"].toString();
                st_log.balance_total = tmp_jo["balance_total"].toInt();
                st_log.balance_available = tmp_jo["balance_available"].toInt();
                st_log.hold_amount = tmp_jo["hold_amount"].toInt();
                st_log.transaction_state = tmp_jo["transaction_state"].toString();

                vec.push_back(st_log);
            }
            emit this->sig_update_membership_card(vec);
        }
        return;
    }
    else if (table == "membership_log")
    {
        QVector<membership_log_admin> vec;
        if (cnt == 0)
        {
            membership_log_admin empty = {0};
            empty.card_uid = "조회 X";
            vec.push_back(empty);
            emit this->sig_update_membership_log(vec);
        }
        else
        {
            QJsonArray jArr = jo["select_arr"].toArray();

            for (int i = 0; i < jArr.size(); i++)
            {
                membership_log_admin st_log = {0};
                // charging_log_admin_cnv st_log = {0};

                QJsonObject tmp_jo = jArr[i].toObject();

                st_log.card_uid = tmp_jo["card_uid"].toString();
                st_log.transaction_id = tmp_jo["transaction_id"].toInt();
                st_log.event_type = tmp_jo["event_type"].toString();
                st_log.amount = tmp_jo["amount"].toInt();
                st_log.balance_available_before = tmp_jo["balance_available_before"].toInt();
                st_log.balance_available_after = tmp_jo["balance_available_after"].toInt();
                st_log.hold_amount_before = tmp_jo["hold_amount_before"].toInt();
                st_log.hold_amount_after = tmp_jo["hold_amount_after"].toInt();
                st_log.transaction_state_before = tmp_jo["transaction_state_before"].toString();
                st_log.transaction_state_after = tmp_jo["transaction_state_after"].toString();
                st_log.created_at = tmp_jo["created_at"].toString().left(19);
                st_log.request_id = tmp_jo["request_id"].toString();

                vec.push_back(st_log);
            }
            std::sort(vec.begin(), vec.end(), [](membership_log_admin a, membership_log_admin b) {
                if (a.transaction_id == b.transaction_id)
                {
                    return a.created_at < b.created_at;
                }
                return a.transaction_id < b.transaction_id;
            });
            emit this->sig_update_membership_log(vec);
        }
        return;
    }
    else if (table == "store_user")
    {
        QVector<store_user_admin> vec;
        // QVector<charging_log_admin_cnv> vec;
        if (cnt == 0)
        {
            store_user_admin empty = {0};
            // charging_log_admin_cnv empty = {0};
            empty.name = "조회 X";
            vec.push_back(empty);
            emit this->sig_update_store_user(vec);
        }
        else
        {
            QJsonArray jArr = jo["select_arr"].toArray();

            for (int i = 0; i < jArr.size(); i++)
            {
                store_user_admin st_log = {0};
                // charging_log_admin_cnv st_log = {0};

                QJsonObject tmp_jo = jArr[i].toObject();
                st_log.id = tmp_jo["id"].toInt();
                st_log.name = tmp_jo["name"].toString();
                st_log.location = tmp_jo["location"].toString();

                vec.push_back(st_log);
            }
            emit this->sig_update_store_user(vec);
        }
        return;
    }
    return;
}

void WK_soc::slot_set_p_md_charging_log(MD_charging_log *set)
{
    this->p_md_charging_log = set;
    connect(this,
            &WK_soc::sig_update_charging_log,
            this->p_md_charging_log,
            &MD_charging_log::slot_qvec_update);
    return;
}

void WK_soc::slot_set_p_md_hmi_current_stat(MD_hmi_current_stat *set)
{
    this->p_md_hmi_current_stat = set;
    connect(this,
            &WK_soc::sig_update_hmi_current_stat,
            this->p_md_hmi_current_stat,
            &MD_hmi_current_stat::slot_qvec_update);
    return;
}

void WK_soc::slot_set_p_md_hmi_device(MD_hmi_device *set)
{
    this->p_md_hmi_device = set;
    connect(this,
            &WK_soc::sig_update_hmi_device,
            this->p_md_hmi_device,
            &MD_hmi_device::slot_qvec_update);
    return;
}

void WK_soc::slot_set_p_md_membership_card(MD_membership_card *set)
{
    this->p_md_membership_card = set;
    connect(this,
            &WK_soc::sig_update_membership_card,
            this->p_md_membership_card,
            &MD_membership_card::slot_qvec_update);
    return;
}

void WK_soc::slot_set_p_md_membership_log(MD_membership_log *set)
{
    this->p_md_membership_log = set;
    connect(this,
            &WK_soc::sig_update_membership_log,
            this->p_md_membership_log,
            &MD_membership_log::slot_qvec_update);
    return;
}

void WK_soc::slot_set_p_md_store_user(MD_store_user *set)
{
    this->p_md_store_user = set;
    connect(this,
            &WK_soc::sig_update_store_user,
            this->p_md_store_user,
            &MD_store_user::slot_qvec_update);
    return;
}

void WK_soc::slot_set_p_dia_mCard(Dia_membership_card *set)
{
    this->p_dia_mCard = set;
    return;
}

void WK_soc::slot_set_p_dia_hmi(Dia_HMI *set)
{
    this->p_dia_hmi = set;
    connect(this,
            &WK_soc::sig_update_hmi_current_stat_To_Dia_HMI,
            this->p_dia_hmi,
            &Dia_HMI::slot_update_hmi_current_stat_From_Soc);
    return;
}

void WK_soc::slot_req_mCard_status_db(QString card_uid)
{
    QString table = "membership_card";

    QJsonObject jsObj_root;

    jsObj_root.insert("type", "select_mCard_status");
    jsObj_root.insert("table", table);
    jsObj_root.insert("card_uid", card_uid);

    QJsonDocument jsDoc(jsObj_root);
    this->p_soc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));
    qDebug() << jsDoc.toJson(QJsonDocument::Compact);
    qDebug() << Q_FUNC_INFO;

    return;
}

void WK_soc::parsing_mCard(const QJsonObject jo)
{
    QString table = jo["table"].toString();
    int cnt = jo["cnt"].toInt();

    if (table == "membership_card")
    {
        QVector<membership_card_admin> vec;
        // QVector<charging_log_admin_cnv> vec;
        if (cnt == 0)
        {
            membership_card_admin empty = {0};
            // charging_log_admin_cnv empty = {0};
            empty.card_uid = "조회 X";
            vec.push_back(empty);

            QMetaObject::invokeMethod(this->p_dia_mCard,
                                      "slot_display_select_ret",
                                      Qt::QueuedConnection,
                                      Q_ARG(QVector<membership_card_admin>, vec));
        }
        else
        {
            QJsonArray jArr = jo["select_arr"].toArray();

            for (int i = 0; i < jArr.size(); i++)
            {
                membership_card_admin st_log = {0};
                // charging_log_admin_cnv st_log = {0};

                QJsonObject tmp_jo = jArr[i].toObject();
                st_log.card_uid = tmp_jo["card_uid"].toString();
                st_log.balance_total = tmp_jo["balance_total"].toInt();
                st_log.balance_available = tmp_jo["balance_available"].toInt();
                st_log.hold_amount = tmp_jo["hold_amount"].toInt();
                st_log.transaction_state = tmp_jo["transaction_state"].toString();

                vec.push_back(st_log);
            }
            // emit this->sig_update_membership_card(vec);
            QMetaObject::invokeMethod(this->p_dia_mCard,
                                      "slot_display_select_ret",
                                      Qt::QueuedConnection,
                                      Q_ARG(QVector<membership_card_admin>, vec));
        }
        return;
    }
    return;
}

void WK_soc::slot_req_mCard_revision_db(membership_card_admin st_mCard)
{
    QString table = "membership_card";

    QJsonObject jsObj_root;

    jsObj_root.insert("type", "revision_mCard_status");
    jsObj_root.insert("table", table);
    jsObj_root.insert("card_uid", st_mCard.card_uid);
    jsObj_root.insert("balance_total", st_mCard.balance_total);
    jsObj_root.insert("balance_available", st_mCard.balance_available);
    jsObj_root.insert("hold_amount", st_mCard.hold_amount);
    jsObj_root.insert("transaction_state", st_mCard.transaction_state);

    QJsonDocument jsDoc(jsObj_root);
    this->p_soc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));
    qDebug() << jsDoc.toJson(QJsonDocument::Compact);
    qDebug() << Q_FUNC_INFO;

    return;
}

void WK_soc::slot_revision_hmi_To_SV(const revision_hmi_admin st_revision)
{
    QJsonObject jo;
    jo.insert("type", "revision_HMI");
    jo.insert("store_id", st_revision.store_id);
    jo.insert("hmi_id", st_revision.hmi_id);
    jo.insert("cmd", st_revision.cmd);
    jo.insert("val", st_revision.val);

    QJsonDocument jsDoc(jo);
    this->p_soc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));
    qDebug() << jsDoc.toJson(QJsonDocument::Compact);
    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_soc::slot_set_dia_hmi_reqStat(bool set)
{
    this->dia_hmi_reqStat = set;
    return;
}

void WK_soc::slot_set_p_dia_ad(Dia_ad *set)
{
    this->p_dia_ad = set;
}
