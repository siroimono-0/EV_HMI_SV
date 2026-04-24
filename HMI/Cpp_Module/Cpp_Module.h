#ifndef CPP_MODULE_H
#define CPP_MODULE_H

#include <QDebug>
#include <QObject>
#include <QThread>
#include "../Common/StatData.h"
#include "StatStore.h"

class WK_Serial;
class WK_WebSocket;
class StatStore;

class Cpp_Module : public QObject
{
    Q_OBJECT
    Q_PROPERTY(StatStore *statStore READ statStore CONSTANT)
public:
    explicit Cpp_Module(QObject *parent = nullptr);
    ~Cpp_Module();

    StatStore *statStore() const;

    Q_INVOKABLE void join_WebSv(QString id);

    void create_WebSoc();
    void create_Serial();

    void end_p_wk_websoc();
    void end_p_wk_serial();

    //==================================================================
    Q_INVOKABLE void set_card_stat_To_serial(bool stat);
    Q_INVOKABLE void set_card_type_To_serial(QString set);
    Q_INVOKABLE void set_card_type_To_statStore(QString set);
    //==================================================================

    Q_INVOKABLE void set_screen_name(QString set);
    Q_INVOKABLE void set_heartbit_storeId_hmiId();

    //==================================================================
    Q_INVOKABLE void chargingConnecter_open_To_serial();
    Q_INVOKABLE void chargingConnecter_ready_To_serial();
    Q_INVOKABLE void charging_start_To_serial();
    Q_INVOKABLE void charging_stop_To_serial();
    Q_INVOKABLE void chargingConnecter_close_To_serial();
    Q_INVOKABLE void chargingConnecter_off_To_serial();

    Q_INVOKABLE void charging_start_To_statStore();

    Q_INVOKABLE void charging_type_To_statStore(QString type, qint32 val);
    Q_INVOKABLE void charging_type_clear_To_statStore();
    // 시작 베터리 초기화
    Q_INVOKABLE void charging_end_stat_clear_To_statStore();

    //==================================================================
    Q_INVOKABLE void set_payment_To_statStore();
    //==================================================================

    Q_INVOKABLE void chard_ok_To_statStore();
    // 충전 종료시 요청 db업데이트 요청
    Q_INVOKABLE void charging_finished_To_statStore();

    Q_INVOKABLE QString get_card_type();

    Q_INVOKABLE int get_charging_type_To_StatStore();

    Q_INVOKABLE void ems_Charging_Ready_To_StatStore();

    Q_INVOKABLE void set_stop_reason(QString set);

    Q_INVOKABLE void next_ad_To_statStore();

    Q_INVOKABLE void first_ad_To_Soc();

    Q_INVOKABLE void netErr_Card_save_To_StatStore(const NET_ERR_CHARGING_TYPE type);
    Q_INVOKABLE void netErr_Charging_ready_save_To_StatStore();
    Q_INVOKABLE void netErr_Charging_monitoring_save_To_StatStore();

public slots:

    void slot_nomal_exit();
    void slot_restart_exit();

signals:
    void sig_SocErr_ToQml(QString msg);
    void sig_SocSuccess_ToQml();
    void sig_SocFailed_ToQml(QString msg);

    void sig_card_success_ToQml();
    // 카드 결제완료 후 db 업데이트 완료대면 받는 ack
    void sig_card_authorized_db_update_ack_ToQml();
    void sig_card_failed_ToQml(QString msg);
    void sig_card_compare_ToQml();

    // void sig_membership_ack_ToQml(bool ok, QString failed_msg = "");

    void sig_coil_ready_ok_ToQml();
    void sig_coil234_off_check_ToQml();

    void sig_charging_stop_ToQml();

    void sig_cancle_payment_ok_ToQml();
    void sig_cancle_payment_ok_member_ToQml(bool stat);
    void sig_charging_finished_ack_ToQml();

    void sig_ems_ToQml();

    void sig_screen_move_maintenance_ToQml();
    void sig_screen_move_home_ToQml();

    void sig_ad_play_ToQml();

    void sig_Re_connect_UpTo_5_ToQml();
    void sig_Re_connect_Success_ToQml();

private:
    StatStore *p_stat = nullptr;

    WK_WebSocket *p_wk_websoc = nullptr;
    QThread *p_th_websoc = nullptr;

    WK_Serial *p_wk_serial = nullptr;
    QThread *p_th_serial = nullptr;
};

#endif // CPP_MODULE_H
