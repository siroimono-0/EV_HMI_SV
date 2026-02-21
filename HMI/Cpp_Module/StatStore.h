#ifndef STATSTORE_H
#define STATSTORE_H

#include <QDebug>
#include <QObject>
#include "../Common/StatData.h"

enum CHARGING_TYPE { NOT_SET = 0, TIME = 1, WON = 2, KWH = 3, PERSENT = 4 };

class WK_Serial;
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

public:
    explicit StatStore(QObject *parent = nullptr);
    void set_First_stat(stat_data st_stat);


    QString cnv_time(uint32_t time);

    QString get_elapsed_time();
    QString get_remaining_time();
    QString get_charging_speed();
    QString get_charging_capacity();
    QString get_charging_amount();
    QString get_battery_start_persent();
    QString get_battery_current();

    void set_elapsed_time(QString set);
    void set_remaining_time(QString set);
    void set_charging_speed(QString set);
    void set_charging_capacity(QString set);
    void set_charging_amount(QString set);
    void set_battery_start_persent(QString set);
    void set_battery_current(QString set);

public slots:
    void slot_update_FromSoc(stat_data st_stat);
    void slot_update_FromSerial(stat_data st_stat);
    void slot_update_FromModule(stat_data st_stat);
    void slot_update_current();

    stat_data slot_get_stat();

    void slot_set_p_serial(WK_Serial *serial);

    //====================================================
    void slot_update_chargingStat(charging_stat c_stat);

    void slot_set_charging_type(CHARGING_TYPE charging_type, int val);
    void slot_clear_charging_type();

signals:
    // 상태 값 변경시 발생
    void sig_Stat_changed(stat_data st_stat);

    void sig_elapsed_time_change();
    void sig_remaining_time_change();
    void sig_charging_speed_change();
    void sig_charging_capacity_change();
    void sig_charging_amount_change();
    void sig_battery_start_persent_change();
    void sig_battery_current_change();

private:
    struct stat_data st_stat;

    WK_Serial *p_serial = nullptr;
    //===================================================
    QString elapsed_time;
    QString remaining_time;
    QString charging_speed;
    QString charging_capacity;
    QString charging_amount;
    QString battery_start_persent;
    QString battery_current;

    CHARGING_TYPE charging_type = NOT_SET;
    int charging_val = 0;
    //===================================================
};

Q_DECLARE_METATYPE(CHARGING_TYPE)
#endif // STATSTORE_H
