#ifndef STATSTORE_H
#define STATSTORE_H

#include <QDebug>
#include <QNetworkInterface>
#include <QObject>
#include <QTime>
#include "../Common/StatData.h"

enum CHARGING_TYPE { NOT_SET = 0, TIME = 1, WON = 2, KWH = 3, PERSENT = 4 };

class WK_Serial;
class WK_WebSocket;
class Cpp_Module;
class StatStore : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString elapsed_time READ get_elapsed_time WRITE set_elapsed_time NOTIFY
                   sig_elapsed_time_change)

    Q_PROPERTY(QString remaining_time READ get_remaining_time WRITE set_remaining_time NOTIFY
                   sig_remaining_time_change)

    Q_PROPERTY(QString charging_speed READ get_charging_speed WRITE set_charging_speed NOTIFY
                   sig_charging_speed_change)

    Q_PROPERTY(QString charging_capacity READ get_charging_capacity WRITE set_charging_capacity
                   NOTIFY sig_charging_capacity_change)

    Q_PROPERTY(QString charging_amount READ get_charging_amount WRITE set_charging_amount NOTIFY
                   sig_charging_amount_change)

    Q_PROPERTY(QString battery_start_persent READ get_battery_start_persent WRITE
                   set_battery_start_persent NOTIFY sig_battery_start_persent_change)

    Q_PROPERTY(QString battery_current READ get_battery_current WRITE set_battery_current NOTIFY
                   sig_battery_current_change FINAL)

    //==================================================

    Q_PROPERTY(QString advance_payment READ get_advance_payment WRITE set_advance_payment NOTIFY
                   sig_advance_payment_change FINAL)

    Q_PROPERTY(QString actual_payment READ get_actual_payment WRITE set_actual_payment NOTIFY
                   sig_actual_payment_change FINAL)

    Q_PROPERTY(QString cancle_payment READ get_cancle_payment WRITE set_cancle_payment NOTIFY
                   sig_cancle_payment_change FINAL)

public:
    explicit StatStore(QObject *parent = nullptr);
    void set_First_stat(stat_data st_stat);


    QString cnv_time(uint32_t time);
    float reverse_cnv_time(QString s_time);

    QString get_elapsed_time();
    QString get_remaining_time();
    QString get_charging_speed();
    QString get_charging_capacity();
    QString get_charging_amount();
    QString get_battery_start_persent();
    QString get_battery_current();
    //===========================================
    QString get_advance_payment();
    QString get_actual_payment();
    QString get_cancle_payment();

    int get_i_can_pay();

    void set_card_type(QString set);
    // QString advance_payment; // 카드 승인시 초기화
    // QString actual_payment;  // 충전 완료시 초기화
    // QString cancle_payment;  // 충전 완료시 초기화
    void set_screen_name(QString set);
    void set_heartbit_storeId_hmiId();

    void set_p_module(Cpp_Module *set);
    void set_p_soc(WK_WebSocket *set);
    //=============================================
    void set_elapsed_time(QString set);
    void set_remaining_time(QString set);
    void set_charging_speed(QString set);
    void set_charging_capacity(QString set);
    void set_charging_amount(QString set);
    void set_battery_start_persent(QString set);
    void set_battery_current(QString set);
    //=============================================
    void set_advance_payment(QString set);
    void set_actual_payment(QString set);
    void set_cancle_payment(QString set);
    //=============================================
    void set_store_id(int set);
    //=============================================
    void charging_start_db_update(double start_persent);
    void charging_finished_db_update();
    void cancle_pay_check();

public slots:
    /*
    void slot_update_FromSoc(stat_data st_stat);
    void slot_update_FromSerial(stat_data st_stat);
    void slot_update_FromModule(stat_data st_stat);
    void slot_update_current();

    stat_data slot_get_stat();
    */

    int slot_get_store_id();
    QString slot_get_mac_addr();
    QPair<int, QString> slot_get_advPay_hmiId();

    void slot_set_p_serial(WK_Serial *serial);
    int slot_get_i_adv_pay();

    //====================================================
    void slot_update_chargingStat(charging_stat c_stat);

    void slot_set_charging_type(CHARGING_TYPE charging_type, int val);
    void slot_clear_charging_type();
    void slot_set_payment();             // qml 충전완료 시
    void slot_set_card_uid(QString set); // http sv 카드 승인 rep발생시 업뎃
                                         // 멤버쉽 카드 경우 카드 태깅시 업뎃

    void slot_set_charging_start_time(); // 차징 시작 시 생성
    void slot_charging_end_stat_clear(); // qml 차징 종료시

    //====================================================
    void slot_card_ok_db_update();
    // soc에서 온 chargingLog_ack msg 에서 session_id 등록
    void slot_set_session_id(uint64_t set);
    void slot_set_ocpp_tx_id(uint32_t set);

    // soc set_p_stat 에서 커넥트
    //  sig_hartbit_ping_To_statStore 받음
    // sig_hartbit_pong 호출 -> soc slot
    void slot_heartbit_ping();
    //====================================================
    void slot_set_membership_t_id(uint32_t set);

signals:
    // 상태 값 변경시 발생
    // void sig_Stat_changed(stat_data st_stat);

    // soc slot_send_textData 연결
    void sig_stat_db_update(struct db_data st_db_data);

    void sig_elapsed_time_change();
    void sig_remaining_time_change();
    void sig_charging_speed_change();
    void sig_charging_capacity_change();
    void sig_charging_amount_change();
    void sig_battery_start_persent_change();
    void sig_battery_current_change();
    //====================================================
    void sig_advance_payment_change();
    void sig_actual_payment_change();
    void sig_cancle_payment_change();
    //====================================================

    // set_p_stat 에서 커넥트
    // connect(this->p_stat, &StatStore::sig_hartbit_pong, this, &WK_WebSocket::slot_send_hartbit_pong);
    void sig_heartbit_pong(heartbit_data st_hb_data);

private:
    struct stat_data st_stat = {0};
    struct db_data st_db_data = {0};
    struct heartbit_data st_hb_data = {0};
    struct membership_log st_mb_log = {0};

    WK_Serial *p_serial = nullptr;
    Cpp_Module *p_module = nullptr;
    WK_WebSocket *p_soc = nullptr;
    //===================================================
    QString elapsed_time;          // 경과 시간
    QString remaining_time;        // 남은 시간
    QString charging_speed;        // 충전 속도
    QString charging_capacity;     // 충전 용량
    QString charging_amount;       // 충전 금액
    QString battery_start_persent; // 시작 배터리
    float battery_start = 0;       // 시작 배터리
    QString battery_current;       // 현재 배터리

    QString advance_payment; // 카드 승인시 초기화
    int i_adv_pay = 0;
    QString actual_payment;  // 충전 완료시 초기화
    int i_act_pay = 0;       // 마지막 업데이트 값 참조
    QString cancle_payment;  // 충전 완료시 초기화
    int i_can_pay = 0;

    CHARGING_TYPE charging_type = NOT_SET;
    int charging_val = 0;       // 차징 타입에 따른 값
    int charge_price_kWh = 350; // voltage 150 current 400 기준
    int charge_price_min = 350; // voltage 150 current 400 기준
    //===================================================

    int store_id;                // hmi 로그인시 입력 승인된 id
    QString mac_addr = "hmi_01"; // hmi_01
    QString card_uid;            // http sv 카드 승인 rep발생시 업뎃
    QString charging_start_time; // 차징 시작 시 생성

    float accumulate_kWh = 0; // 누적 충전량 // 충전 중 지속 +=
    //===================================================
};

Q_DECLARE_METATYPE(CHARGING_TYPE)
#endif // STATSTORE_H
