#include "StatStore.h"
#include "WK_Serial.h"

StatStore::StatStore(QObject *parent)
    : QObject{parent}
{
}

void StatStore::set_First_stat(stat_data st_stat)
{
    this->st_stat = st_stat;
    return;
}

void StatStore::slot_set_p_serial(WK_Serial *serial)
{
    this->p_serial = serial;
    return;
}

void StatStore::slot_update_FromSoc(stat_data st_stat)
{
    this->st_stat = st_stat;
    emit this->sig_Stat_changed(this->st_stat);

    qDebug() << Q_FUNC_INFO;
    return;
}

void StatStore::slot_update_FromSerial(stat_data st_stat)
{
    this->st_stat = st_stat;
    emit this->sig_Stat_changed(this->st_stat);

    qDebug() << Q_FUNC_INFO;
    return;
}

void StatStore::slot_update_FromModule(stat_data st_stat)
{
    this->st_stat = st_stat;
    emit this->sig_Stat_changed(this->st_stat);

    qDebug() << Q_FUNC_INFO;
    return;
}

void StatStore::slot_update_current()
{
    emit this->sig_Stat_changed(this->st_stat);

    qDebug() << Q_FUNC_INFO;
    return;
}

stat_data StatStore::slot_get_stat()
{
    return this->st_stat;
}

void StatStore::slot_set_charging_type(CHARGING_TYPE charging_type, int val)
{
    this->charging_type = charging_type;
    this->charging_val = val;
    qDebug() << Q_FUNC_INFO;
    qDebug() << charging_type << " :: " << val;

    return;
}

void StatStore::slot_clear_charging_type()
{
    this->charging_type = NOT_SET;
    this->charging_val = 0;
    qDebug() << Q_FUNC_INFO;
    return;
}

void StatStore::slot_update_chargingStat(charging_stat c_stat)
{
    uint16_t charger_stat = c_stat.charger_stat;
    uint16_t err_code = c_stat.err_code;
    uint16_t voltage = c_stat.voltage;
    uint16_t current = c_stat.current;
    uint32_t battery_current = c_stat.battery_current;
    uint32_t battery_full = c_stat.battery_full;
    uint32_t elapsed_time = c_stat.elapsed_time;

    float f_charging_speed = (voltage * current) / 1000;
    float charging_speed = f_charging_speed;
    float charging_capacity = (f_charging_speed / 3600) * elapsed_time;

    uint32_t charging_amount = charging_capacity * 100;

    float remaining_battery = (battery_full - battery_current);
    float power_wh = voltage * current;
    uint32_t remaining_time = (remaining_battery / power_wh) * 3600;

    this->set_elapsed_time(this->cnv_time(elapsed_time));
    qDebug() << elapsed_time << " :: 경과시간";

    QString qs_c_sp = QString::number(charging_speed, 'f', 2) + " kw";
    this->set_charging_speed(qs_c_sp);
    qDebug() << charging_speed << " :: 충전 속도";

    QString qs_cp = QString::number(charging_capacity, 'f', 2) + " kw";
    this->set_charging_capacity(qs_cp);
    qDebug() << charging_capacity << " :: 충전량";

    QString qs_amount = QString::number(charging_amount) + " 원";
    this->set_charging_amount(qs_amount);
    qDebug() << charging_amount << " :: 충전금액";

    float battery_current_persent = ((float) battery_current / (float) battery_full) * 100;
    if (this->battery_start_persent.isEmpty())
    {
        QString qs_b_st_p = QString::number(battery_current_persent, 'f', 2) + "%";
        this->set_battery_start_persent(qs_b_st_p);
    }
    qDebug() << this->battery_start_persent << " :: 처음 배터리";

    QString qs_b_cur = QString::number(battery_current_persent, 'f', 2) + "%";
    this->set_battery_current(qs_b_cur);
    qDebug() << battery_current << " :: 현재 배터리";

    this->set_remaining_time(this->cnv_time(remaining_time));
    qDebug() << remaining_time << " :: 남은 시간";

    if (this->charging_type == NOT_SET)
    {
        qDebug() << "TYPE NOT SET";
    }
    else if (this->charging_type == TIME)
    {
        if (remaining_time >= this->charging_val)
        {
            this->slot_clear_charging_type();
            uint16_t reg_pos = 0x01;
            uint16_t reg_val = 0x01;
            // 시리얼 통신으로 종료 요청
            QMetaObject::invokeMethod(this->p_serial,
                                      "slot_rs232_cmd",
                                      Qt::QueuedConnection,
                                      Q_ARG(uint16_t, reg_pos),
                                      Q_ARG(uint16_t, reg_val));
            qDebug() << "충전 조건 만족 // 충전 종료";
        }
    }
    else if (this->charging_type == WON)
    {
        if (charging_amount >= this->charging_val)
        {
            this->slot_clear_charging_type();
            uint16_t reg_pos = 0x01;
            uint16_t reg_val = 0x01;
            // 시리얼 통신으로 종료 요청
            QMetaObject::invokeMethod(this->p_serial,
                                      "slot_rs232_cmd",
                                      Qt::QueuedConnection,
                                      Q_ARG(uint16_t, reg_pos),
                                      Q_ARG(uint16_t, reg_val));
            qDebug() << "충전 조건 만족 // 충전 종료";
        }
    }
    else if (this->charging_type == KWH)
    {
        if (charging_capacity >= this->charging_val)
        {
            this->slot_clear_charging_type();
            uint16_t reg_pos = 0x01;
            uint16_t reg_val = 0x01;
            // 시리얼 통신으로 종료 요청
            QMetaObject::invokeMethod(this->p_serial,
                                      "slot_rs232_cmd",
                                      Qt::QueuedConnection,
                                      Q_ARG(uint16_t, reg_pos),
                                      Q_ARG(uint16_t, reg_val));
            qDebug() << "충전 조건 만족 // 충전 종료";
        }
    }
    else if (this->charging_type == PERSENT)
    {
        if (battery_current_persent >= this->charging_val)
        {
            this->slot_clear_charging_type();
            uint16_t reg_pos = 0x01;
            uint16_t reg_val = 0x01;
            // 시리얼 통신으로 종료 요청
            QMetaObject::invokeMethod(this->p_serial,
                                      "slot_rs232_cmd",
                                      Qt::QueuedConnection,
                                      Q_ARG(uint16_t, reg_pos),
                                      Q_ARG(uint16_t, reg_val));

            qDebug() << "충전 조건 만족 // 충전 종료";
        }
    }

    return;
}

//===================================================================
//===================================================================

QString StatStore::cnv_time(uint32_t time)
{
    int h = time / 3600;
    int m = (time % 3600) / 60;
    int s = (time % 60);

    QString qs_h = QString::number(h);
    if (qs_h.size() < 2)
    {
        qs_h.push_front("0");
    }

    QString qs_m = QString::number(m);
    if (qs_m.size() < 2)
    {
        qs_m.push_front("0");
    }

    QString qs_s = QString::number(s);
    if (qs_s.size() < 2)
    {
        qs_s.push_front("0");
    }

    QString ret = qs_h + ":" + qs_m + ":" + qs_s;

    return ret;
}

QString StatStore::get_elapsed_time()
{
    return this->elapsed_time;
}
QString StatStore::get_remaining_time()
{
    return this->remaining_time;
}
QString StatStore::get_charging_speed()
{
    return this->charging_speed;
}
QString StatStore::get_charging_capacity()
{
    return this->charging_capacity;
}
QString StatStore::get_charging_amount()
{
    return this->charging_amount;
}
QString StatStore::get_battery_start_persent()
{
    return this->battery_start_persent;
}
QString StatStore::get_battery_current()
{
    return this->battery_current;
}

void StatStore::set_elapsed_time(const QString set)
{
    this->elapsed_time = set;
    emit this->sig_elapsed_time_change();
    return;
}

void StatStore::set_remaining_time(const QString set)
{
    this->remaining_time = set;
    emit this->sig_remaining_time_change();
    return;
}

void StatStore::set_charging_speed(const QString set)
{
    this->charging_speed = set;
    emit this->sig_charging_speed_change();
    return;
}

void StatStore::set_charging_capacity(const QString set)
{
    this->charging_capacity = set;
    emit this->sig_charging_capacity_change();
    return;
}

void StatStore::set_charging_amount(const QString set)
{
    this->charging_amount = set;
    emit this->sig_charging_amount_change();
    return;
}

void StatStore::set_battery_start_persent(const QString set)
{
    this->battery_start_persent = set;
    emit this->sig_battery_start_persent_change();
    return;
}

void StatStore::set_battery_current(const QString set)
{
    this->battery_current = set;
    emit this->sig_battery_current_change();
    return;
}
