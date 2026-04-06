#include "Hub.h"
#include "DB_PostgreSQL.h"
#include "StatModel.h"
#include "WK_Soc.h"

Hub::Hub(QObject *parent)
    : QObject{parent}
{
    this->p_timer = new QTimer(this);
    connect(this->p_timer, &QTimer::timeout, this, &Hub::slot_timeOut_heartbit);
    this->p_timer->start(10000);
}

void Hub::set_p_md(StatModel *set_md)
{
    this->p_md = set_md;
    return;
}

void Hub::set_p_db(DB_PostgreSQL *set_db)
{
    this->p_obj_db = set_db;
    QMetaObject::invokeMethod(this->p_obj_db,
                              "slot_set_p_soc",
                              Qt::QueuedConnection,
                              Q_ARG(Hub *, this));
    return;
}

void Hub::slot_start_sv()
{
    QString sv_name = "WebSocSv";

    this->p_webSoc_Sv = new QWebSocketServer(sv_name, QWebSocketServer::NonSecureMode, this);

    bool ret_listen = this->p_webSoc_Sv->listen(QHostAddress::Any, 12345);

    if (ret_listen == false)
    {
        qDebug() << Q_FUNC_INFO << " listen Err";
        return;
    }

    connect(this->p_webSoc_Sv, &QWebSocketServer::newConnection, this, &Hub::slot_new_connection);

    if (this->p_webSoc_Sv->isListening())
    {
        qDebug() << Q_FUNC_INFO << " listen OK";
    }
}

void Hub::slot_end()
{
    if (this->p_webSoc_Sv && this->p_webSoc_Sv->isListening())
    {
        this->p_webSoc_Sv->close();
    }

    for (auto wk : qmp_wk)
    {
        wk->deleteLater();
    }

    qmp_wk.clear();
    emit this->sig_end();
    return;
}

void Hub::slot_new_connection()
{
    qDebug() << Q_FUNC_INFO << "새 연결 시작";

    QWebSocket *new_cli = this->p_webSoc_Sv->nextPendingConnection();

    if (!new_cli)
    {
        qDebug() << Q_FUNC_INFO << "nextPendingConnection이 null 반환!";
        return;
    }

    qDebug() << Q_FUNC_INFO << "새 클라이언트 소켓:" << new_cli;
    qDebug() << Q_FUNC_INFO << "소켓 상태:" << new_cli->state();

    WK_Soc *wk = new WK_Soc(this);
    int new_id = this->id_mp++;

    // p_md를 먼저 설정해야 set_p_webSoc 내부의 connect가 정상 작동함
    wk->set_p_md(this->p_md);
    wk->set_p_webSoc(new_cli, new_id);
    wk->set_p_Hub(this);
    wk->set_p_db(this->p_obj_db);

    this->qmp_wk.insert(new_id, wk);
    qDebug() << Q_FUNC_INFO << "워커 추가 완료";

    return;
}

void Hub::slot_del_mpWk(int id_mp)
{
    this->qmp_wk.remove(id_mp);
    return;
}

void Hub::slot_timeOut_heartbit()
{
    for (auto it = qmp_wk.begin(); it != qmp_wk.end(); it++)
    {
        it.value()->occur_heartbit();
    }
    return;
}

void Hub::mp_wk_insert(const QPair<int, QString> key, WK_Soc *val)
{
    this->mp_hmi[key] = val;
    return;
}

void Hub::mp_wk_remove(const QPair<int, QString> key)
{
    this->mp_hmi.remove(key);
    return;
}

WK_Soc *Hub::mp_wk_find(const QPair<int, QString> key)
{
    return this->mp_hmi[key];
}

void Hub::slot_charging_log_select_ret_From_DB__To_admin(const mp_wk_key key,
                                                         QVector<charging_log_admin> ret)
{
    auto wk = this->mp_wk_find({key.id, key.s_id});
    wk->slot_charging_log_select_ret_From_DB__To_admin(ret);
    return;
}

void Hub::slot_hmi_current_stat_select_ret_From_DB__To_admin(const mp_wk_key key,
                                                             QVector<hmi_current_stat_admin> ret)
{
    auto wk = this->mp_wk_find({key.id, key.s_id});
    wk->slot_hmi_current_stat_select_ret_From_DB__To_admin(ret);
    return;
}

void Hub::slot_hmi_device_select_ret_From_DB__To_admin(const mp_wk_key key,
                                                       QVector<hmi_device_admin> ret)
{
    auto wk = this->mp_wk_find({key.id, key.s_id});
    wk->slot_hmi_device_select_ret_From_DB__To_admin(ret);
    return;
}

void Hub::slot_membership_card_select_ret_From_DB__To_admin(const mp_wk_key key,
                                                            QVector<membership_card_admin> ret)
{
    auto wk = this->mp_wk_find({key.id, key.s_id});
    wk->slot_membership_card_select_ret_From_DB__To_admin(ret);
    return;
}

void Hub::slot_membership_log_select_ret_From_DB__To_admin(const mp_wk_key key,
                                                           QVector<membership_log_admin> ret)
{
    auto wk = this->mp_wk_find({key.id, key.s_id});
    wk->slot_membership_log_select_ret_From_DB__To_admin(ret);
    return;
}

void Hub::slot_store_user_select_ret_From_DB__To_admin(const mp_wk_key key,
                                                       QVector<store_user_admin> ret)
{
    auto wk = this->mp_wk_find({key.id, key.s_id});
    wk->slot_store_user_select_ret_From_DB__To_admin(ret);
    return;
}

void Hub::slot_membershipCard_authorized_ack_To_hmi(const mp_wk_key key, bool ok, QString msg)
{
    auto wk = this->mp_wk_find({key.id, key.s_id});
    wk->slot_membershipCard_authorized_ack_To_hmi(ok, msg);
    return;
}

void Hub::slot_membershipCard_finished_ack_To_hmi(const mp_wk_key key, bool ok)
{
    auto wk = this->mp_wk_find({key.id, key.s_id});
    wk->slot_membershipCard_finished_ack_To_hmi(ok);
    return;
}

void Hub::slot_chargingLog_authorized_ack_To_hmi(const mp_wk_key key)
{
    auto wk = this->mp_wk_find({key.id, key.s_id});
    wk->slot_chargingLog_authorized_ack_To_hmi();
    return;
}

void Hub::slot_chargingLog_charging_start_ack_To_hmi(const mp_wk_key key, uint32_t ocpp_tx_id)
{
    auto wk = this->mp_wk_find({key.id, key.s_id});
    wk->slot_chargingLog_charging_start_ack_To_hmi(ocpp_tx_id);
    return;
}

void Hub::slot_chargingLog_charging_finished_ack_To_hmi(const mp_wk_key key)
{
    auto wk = this->mp_wk_find({key.id, key.s_id});
    wk->slot_chargingLog_charging_finished_ack_To_hmi();
    return;
}

void Hub::slot_mCard_status_ret_From_DB__To_admin(const mp_wk_key key,
                                                  QVector<membership_card_admin> ret)
{
    auto wk = this->mp_wk_find({key.id, key.s_id});
    wk->slot_mCard_status_ret_From_DB__To_admin(ret);
    return;
}
