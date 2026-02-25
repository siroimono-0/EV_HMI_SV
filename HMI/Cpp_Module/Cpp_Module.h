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
    //==================================================================

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

public slots:

signals:
    void sig_SocErr_ToQml(QString msg);
    void sig_SocSuccess_ToQml();
    void sig_SocFailed_ToQml(QString msg);

    void sig_card_success_ToQml();
    void sig_card_failed_ToQml(QString msg);
    void sig_card_compare_ToQml();

    void sig_coil_ready_ok_ToQml();
    void sig_coil234_off_check_ToQml();

    void sig_charging_stop_ToQml();

private:
    StatStore *p_stat = nullptr;

    WK_WebSocket *p_wk_websoc = nullptr;
    QThread *p_th_websoc = nullptr;

    WK_Serial *p_wk_serial = nullptr;
    QThread *p_th_serial = nullptr;
};

#endif // CPP_MODULE_H
