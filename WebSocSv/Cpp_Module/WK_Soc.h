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

signals:
    void sig_update_md(stat_data st_stat);

    // set_p_db에서 커넥트
    //  >>  slot_chargingLog_From_soc
    void sig_chargingLog_To_DB(db_data st_db_data);

    // set_p_db에서 커넥트
    // connect(this,
    // &WK_Soc::sig_hartbitData_To_DB,
    // this->p_obj_db,
    // &DB_PostgreSQL::slot_hartbitData_From_soc);
    void sig_heartbitData_To_DB(heartbit_data st_db_data);

private:
    QWebSocket *p_WebSoc;
    StatModel *p_Md;
    Hub *p_Hub;
    DB_PostgreSQL *p_obj_db;

    QString connectRole = "";
    QString token = "";
    QString roleId = "";

    int id_Common = 0;
    int id_Mp = 0;
    bool stat_Disconnect = false;
};

Q_DECLARE_METATYPE(WK_Soc *)

#endif // WK_SOC_H
