#ifndef WK_SOC_H
#define WK_SOC_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QObject>
#include <QTimer>
#include <QWebSocket>
#include "../../Common/StatData.h"
// #include "../Common/StatData.h"

struct details;
class StatModel;
class Hub;
class DB_PostgreSQL;

class WK_Soc : public QObject
{
    Q_OBJECT
public:
    explicit WK_Soc(QObject *parent = nullptr);
    void set_p_webSoc(QWebSocket *set_webSoc, int id_mp);
    void set_p_md(StatModel *set_md);
    void set_p_Hub(Hub *set_Hub);
    void set_p_db(DB_PostgreSQL *set_db);

    // hmi에서 log업데이트 요청 받으면
    // recv_textData 에서 발생
    void req_chargingLog_To_DB(const QJsonObject &jsObj);

    void req_heartbitData_To_DB(const QJsonObject &jsObj);

    void req_membershipCard_authorized_To_DB(const QJsonObject &jsObj);
    void req_membershipCard_finished_To_DB(const QJsonObject &jsObj);

    void req_select_To_DB(const QJsonObject &jsObj);

    void req_select_mCard_status_To_DB(const QJsonObject &jsObj);
    void req_revision_mCard_status_To_DB(const QJsonObject &jsObj);

    void find_revision_HMI(const QJsonObject &jsObj);
    void echo_revision_HMI_To_hmi(const QJsonObject &jsObj);

    //===============================================
    void occur_heartbit();
public slots:
    void slot_Recv_TextData(QString recvData);
    void slot_Disconnect_Soc();

    void slot_helloAck(bool ret);

    bool slot_registerReq(const QJsonObject &jsObj);
    void slot_registerAck(bool ret);

    bool slot_registerReq_hmi(const QJsonObject &jsObj);
    void slot_registerAck_hmi(bool ret);

    void slot_chargingLog_authorized_ack_To_hmi();
    void slot_chargingLog_charging_start_ack_To_hmi(uint32_t ocpp_tx_id);
    void slot_chargingLog_charging_finished_ack_To_hmi();
    // void slot_chargingLog_charging_fist_ack_To_hmi(bool ret);
    // void slot_chargingLog_charging_second_ack_To_hmi(bool ret);
    // void slot_chargingLog_finished_ack_To_hmi(bool ret);
    // void slot_chargingLog_failed_ack_To_hmi(bool ret);
    // void slot_chargingLog_timeout_ack_To_hmi(bool ret);

    void slot_membershipCard_authorized_ack_To_hmi(bool ok, QString msg = "");
    void slot_membershipCard_finished_ack_To_hmi(bool ok);

    // DB -> slot_set_p_soc에서 커넥트
    void slot_charging_log_select_ret_From_DB__To_admin(QVector<charging_log_admin> ret);

    // DB -> slot_set_p_soc에서 커넥트
    void slot_hmi_current_stat_select_ret_From_DB__To_admin(QVector<hmi_current_stat_admin> ret);

    // DB -> slot_set_p_soc에서 커넥트
    void slot_hmi_device_select_ret_From_DB__To_admin(QVector<hmi_device_admin> ret);

    // DB -> slot_set_p_soc에서 커넥트
    void slot_membership_card_select_ret_From_DB__To_admin(QVector<membership_card_admin> ret);

    // DB -> slot_set_p_soc에서 커넥트
    void slot_membership_log_select_ret_From_DB__To_admin(QVector<membership_log_admin> ret);

    // DB -> slot_set_p_soc에서 커넥트
    void slot_store_user_select_ret_From_DB__To_admin(QVector<store_user_admin> ret);

    void slot_mCard_status_ret_From_DB__To_admin(QVector<membership_card_admin> ret);

signals:
    void sig_update_md(stat_data st_stat);

    // set_p_db에서 커넥트
    //  >>  slot_chargingLog_From_soc
    void sig_chargingLog_To_DB(const mp_wk_key, db_data st_db_data);

    // set_p_db에서 커넥트
    // connect(this,
    // &WK_Soc::sig_hartbitData_To_DB,
    // this->p_obj_db,
    // &DB_PostgreSQL::slot_hartbitData_From_soc);
    void sig_heartbitData_To_DB(heartbit_data st_db_data);

    // set_p_db에서 커넥트
    void sig_select_To_DB(const mp_wk_key,
                          QString table,
                          int total,
                          QString col1 = "",
                          QString val1 = "",
                          QString col2 = "",
                          QString val2 = "",
                          QString col3 = "",
                          QString val3 = "");

private:
    QWebSocket *p_WebSoc;
    StatModel *p_Md;
    Hub *p_Hub;
    DB_PostgreSQL *p_obj_db;

    QString connectRole = "";
    QString token = "";
    QString roleId = ""; // hmi_id
    int storeId;
    int adminId; // key 에서 string은 admin 통일
    mp_wk_key key;

    int id_Common = 0;
    int id_Mp = 0;
    bool stat_Disconnect = false;
};

Q_DECLARE_METATYPE(WK_Soc *)
// Q_DECLARE_METATYPE(QVector<membership_card_admin>)

#endif // WK_SOC_H
