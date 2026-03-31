#ifndef HUB_H
#define HUB_H

#include <QFile>
#include <QMap>
#include <QObject>
#include <QSslCertificate>
#include <QSslKey>
#include <QTimer>
#include <QWebSocket>
#include <QWebSocketServer>
#include "../../Common/StatData.h"
// #include "../Common/StatData.h"

class WK_Soc;
class StatModel;
class DB_PostgreSQL;

class Hub : public QObject
{
    Q_OBJECT
public:
    explicit Hub(QObject *parent = nullptr);

    void set_p_md(StatModel *set_md);
    void set_p_db(DB_PostgreSQL *set_db);

    void mp_wk_insert(const QPair<int, QString> key, WK_Soc *val);
    void mp_wk_remove(const QPair<int, QString> key);
    WK_Soc *mp_wk_find(const QPair<int, QString> key);

public slots:
    void slot_start_sv();
    void slot_end();
    void slot_new_connection();
    void slot_del_mpWk(int idx);

    //==============================================================
    // 생성자에서 커넥트
    // connect(this->p_timer, &QTimer::timeout, this, &Hub::slot_timeOut_hartbit);
    void slot_timeOut_heartbit();

    void slot_charging_log_select_ret_From_DB__To_admin(const mp_wk_key,
                                                        QVector<charging_log_admin> ret);
    void slot_hmi_current_stat_select_ret_From_DB__To_admin(const mp_wk_key,
                                                            QVector<hmi_current_stat_admin> ret);
    void slot_hmi_device_select_ret_From_DB__To_admin(const mp_wk_key,
                                                      QVector<hmi_device_admin> ret);
    void slot_membership_card_select_ret_From_DB__To_admin(const mp_wk_key,
                                                           QVector<membership_card_admin> ret);
    void slot_membership_log_select_ret_From_DB__To_admin(const mp_wk_key,
                                                          QVector<membership_log_admin> ret);
    void slot_store_user_select_ret_From_DB__To_admin(const mp_wk_key,
                                                      QVector<store_user_admin> ret);

    void slot_membershipCard_authorized_ack_To_hmi(const mp_wk_key, bool ok, QString msg = "");
    void slot_membershipCard_finished_ack_To_hmi(const mp_wk_key, bool ok);

    void slot_chargingLog_authorized_ack_To_hmi(const mp_wk_key);
    void slot_chargingLog_charging_start_ack_To_hmi(const mp_wk_key, uint32_t ocpp_tx_id);
    void slot_chargingLog_charging_finished_ack_To_hmi(const mp_wk_key);
    void slot_mCard_status_ret_From_DB__To_admin(const mp_wk_key,
                                                 QVector<membership_card_admin> ret);
signals:
    void sig_end();

private:
    QWebSocketServer *p_webSoc_Sv;
    QMap<int, WK_Soc *> qmp_wk;
    StatModel *p_md;
    DB_PostgreSQL *p_obj_db;
    int id_mp = 0;

    // WK_Soc -> hello 에서 insert
    // store_id + hmi_id 순서임
    QMap<QPair<int, QString>, WK_Soc *> mp_hmi;

    // 생성자에서 초기화
    QTimer *p_timer = nullptr;
};
Q_DECLARE_METATYPE(Hub *)

#endif // HUB_H
