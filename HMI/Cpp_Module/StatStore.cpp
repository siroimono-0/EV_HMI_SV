#include "StatStore.h"
#include "Cpp_Module.h"
#include "WK_Serial.h"
#include "WK_WebSocket.h"

StatStore::StatStore(QObject *parent)
    : QObject{parent}
{}

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

void StatStore::set_p_module(Cpp_Module *set)
{
    this->p_module = set;
}

void StatStore::set_p_soc(WK_WebSocket *set)
{
    this->p_soc = set;
    return;
}

/*
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
*/

int StatStore::get_i_can_pay()
{
    return this->i_can_pay;
}

QPair<int, QString> StatStore::slot_get_advPay_hmiId()
{
    QPair<int, QString> qp({this->i_adv_pay, this->mac_addr});
    return qp;
}

void StatStore::slot_set_charging_type(CHARGING_TYPE charging_type, int val)
{
    this->charging_type = charging_type;
    this->charging_val = val;

    // enum CHARGING_TYPE { NOT_SET = 0, TIME = 1, WON = 2, KWH = 3, PERSENT = 4 };

    if (charging_type == TIME)
    {
        this->i_adv_pay = val * this->charge_price_min;
    }
    else if (charging_type == WON)
    {
        this->i_adv_pay = val;
    }
    else if (charging_type == KWH)
    {
        this->i_adv_pay = val * this->charge_price_kWh;
    }
    else if (charging_type == PERSENT)
    {
        this->i_adv_pay = 20000;
    }

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

void StatStore::slot_set_payment()
{
    QString qs_adv = QString::number(this->i_adv_pay);
    if (qs_adv.size() > 3)
    {
        qs_adv.insert(qs_adv.size() - 3, ",");
    }
    qs_adv += " 원";
    this->set_advance_payment(qs_adv);

    QString qs_act = QString::number(this->i_act_pay);
    if (qs_act.size() > 3)
    {
        qs_act.insert(qs_act.size() - 3, ",");
    }
    this->set_actual_payment(qs_act + " 원");

    this->i_can_pay = this->i_adv_pay - this->i_act_pay;
    QString qs_can = QString::number(this->i_can_pay);
    if (qs_can.size() > 3)
    {
        qs_can.insert(qs_can.size() - 3, ",");
    }
    this->set_cancle_payment(qs_can + " 원");

    if (this->st_db_data.card_type == "creditCard")
    {
        // 환불 금액 있으면 환불해줌
        this->cancle_pay_check();
    }
    else if (this->st_db_data.card_type == "membershipCard")
    {
        QString request_id = this->mac_addr + QTime::currentTime().toString();

        QMetaObject::invokeMethod(this->p_soc,
                                  "slot_send_membership_finished_textData",
                                  Qt::QueuedConnection,
                                  Q_ARG(int, this->i_adv_pay),
                                  Q_ARG(int, this->i_act_pay),
                                  Q_ARG(int, this->i_can_pay),
                                  Q_ARG(QString, this->st_db_data.card_uid),
                                  Q_ARG(uint32_t, this->st_mb_log.transaction_id),
                                  Q_ARG(QString, request_id));
    }
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

    if (this->battery_start_persent.isEmpty())
    {
        this->battery_start = battery_current;
    }
    // 초당 과금액
    // float charging_amount_second = (f_charging_speed * this->charge_price_kWh) / 3600;

    // 과금액으로 충전 가능한 배터리
    float tmp = (float) this->i_adv_pay / (float) this->charge_price_kWh;

    // 목표 배터리
    float charging_end_battery = this->battery_start + (tmp * 1000);

    uint32_t charging_amount = charging_capacity * this->charge_price_kWh;

    float remaining_battery = (charging_end_battery - battery_current);
    float power_wh = voltage * current;
    uint32_t remaining_time = (remaining_battery / power_wh) * 3600;
    // uint32_t remaining_time = this->i_adv_pay / charging_amount_second;

    this->set_elapsed_time(this->cnv_time(elapsed_time));
    qDebug() << elapsed_time << " :: 경과시간";

    QString qs_c_sp = QString::number(charging_speed, 'f', 2) + " kw";
    this->set_charging_speed(qs_c_sp);
    qDebug() << charging_speed << " :: 충전 속도";

    QString qs_cp = QString::number(charging_capacity, 'f', 2) + " kWh";
    this->set_charging_capacity(qs_cp);
    // 누적 충전량 증가
    this->accumulate_kWh += charging_capacity;
    qDebug() << charging_capacity << " :: 충전량";

    QString qs_amount = QString::number(charging_amount);
    if (qs_amount.size() > 3)
    {
        qs_amount.insert(qs_amount.size() - 3, ",");
    }

    this->set_charging_amount(qs_amount + " 원");
    this->i_act_pay = charging_amount;
    qDebug() << charging_amount << " :: 충전금액";

    float battery_current_persent = ((float) battery_current / (float) battery_full) * 100;

    //================================================
    if (this->battery_start_persent.isEmpty())
    {
        QString qs_b_st_p = QString::number(battery_current_persent, 'f', 2) + "%";
        this->set_battery_start_persent(qs_b_st_p);

        // statStore 업데이트 충전시작 -> soc -> sv  ...
        this->charging_start_db_update((double) battery_current_persent);
    }
    qDebug() << this->battery_start_persent << " :: 처음 배터리";
    //================================================

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
            if (this->i_adv_pay < this->i_act_pay)
            {
                // 충전금액 over시 보정 필요
                QString qs_amount = QString::number(this->i_adv_pay);
                if (qs_amount.size() > 3)
                {
                    qs_amount.insert(qs_amount.size() - 3, ",");
                }

                this->set_charging_amount(qs_amount + " 원");
                this->i_act_pay = this->i_adv_pay;
            }

            this->slot_clear_charging_type();
            // this->slot_charging_end_stat_clear();
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
            if (this->i_adv_pay < this->i_act_pay)
            {
                // 충전금액 over시 보정 필요
                QString qs_amount = QString::number(this->i_adv_pay);
                if (qs_amount.size() > 3)
                {
                    qs_amount.insert(qs_amount.size() - 3, ",");
                }

                this->set_charging_amount(qs_amount + " 원");
                this->i_act_pay = this->i_adv_pay;
            }

            this->slot_clear_charging_type();
            // this->slot_charging_end_stat_clear();
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
            if (this->i_adv_pay < this->i_act_pay)
            {
                // 충전금액 over시 보정 필요
                QString qs_amount = QString::number(this->i_adv_pay);
                if (qs_amount.size() > 3)
                {
                    qs_amount.insert(qs_amount.size() - 3, ",");
                }

                this->set_charging_amount(qs_amount + " 원");
                this->i_act_pay = this->i_adv_pay;
            }

            this->slot_clear_charging_type();
            // this->slot_charging_end_stat_clear();
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
            if (this->i_adv_pay < this->i_act_pay)
            {
                // 충전금액 over시 보정 필요
                QString qs_amount = QString::number(this->i_adv_pay);
                if (qs_amount.size() > 3)
                {
                    qs_amount.insert(qs_amount.size() - 3, ",");
                }

                this->set_charging_amount(qs_amount + " 원");
                this->i_act_pay = this->i_adv_pay;
            }

            this->slot_clear_charging_type();
            // this->slot_charging_end_stat_clear();
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

float StatStore::reverse_cnv_time(QString s_time)
{
    std::string s = s_time.toStdString();
    std::vector<std::string> vec;

    size_t start = 0;
    size_t eend = s.find(':');

    while (1)
    {
        std::string tmp = s.substr(start, eend + start);
        vec.push_back(tmp);
        start = eend + 1;
        eend = s.find(':', start);

        if (eend == std::string::npos)
        {
            std::string tmp = s.substr(start);
            vec.push_back(tmp);
            break;
        }
    }

    int hh = std::stoi(vec[0]);
    int mm = std::stoi(vec[1]);
    int ss = std::stoi(vec[2]);
    int total_second = (hh * 3600) + (mm * 60) + ss;
    return total_second;
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

QString StatStore::get_advance_payment()
{
    return this->advance_payment;
}

QString StatStore::get_actual_payment()
{
    return this->actual_payment;
}

QString StatStore::get_cancle_payment()
{
    return this->cancle_payment;
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
    // db 업데이트 요청 필요
    emit this->sig_battery_start_persent_change();
    return;
}

void StatStore::set_battery_current(const QString set)
{
    this->battery_current = set;
    emit this->sig_battery_current_change();
    return;
}

void StatStore::set_advance_payment(QString set)
{
    this->advance_payment = set;
    emit this->sig_advance_payment_change();
}

void StatStore::set_actual_payment(QString set)
{
    this->actual_payment = set;
    emit this->sig_actual_payment_change();
}

void StatStore::set_cancle_payment(QString set)
{
    this->cancle_payment = set;
    emit this->sig_cancle_payment_change();
}

void StatStore::set_store_id(int set)
{
    this->store_id = set;
    return;
}

int StatStore::slot_get_store_id()
{
    return this->store_id;
}

QString StatStore::slot_get_mac_addr()
{
    return this->mac_addr;
}

void StatStore::slot_set_card_uid(QString set)
{
    this->card_uid = set;
    return;
}

void StatStore::slot_set_charging_start_time()
{
    this->charging_start_time = QTime::currentTime().toString("hh:mm:ss");
    return;
}

void StatStore::slot_card_ok_db_update()
{
    this->st_db_data.store_id = this->store_id;
    this->st_db_data.hmi_id = this->mac_addr;
    this->st_db_data.card_uid = this->card_uid;
    this->st_db_data.advance_payment = this->i_adv_pay;
    this->st_db_data.unit_price = this->charge_price_kWh;
    if (this->charging_type == TIME)
    {
        this->st_db_data.tariff_type = "TIME";
    }
    else if (this->charging_type == WON)
    {
        this->st_db_data.tariff_type = "WON";
    }
    else if (this->charging_type == KWH)
    {
        this->st_db_data.tariff_type = "KWH";
    }
    else if (this->charging_type == PERSENT)
    {
        this->st_db_data.tariff_type = "PERSENT";
    }
    this->st_db_data.session_status = "authorized";

    qDebug() << this->st_db_data.store_id << " store_id";
    qDebug() << this->st_db_data.hmi_id << " hmi_id";
    qDebug() << this->st_db_data.card_uid << " card";
    qDebug() << this->st_db_data.advance_payment << " adv";
    qDebug() << this->st_db_data.unit_price << " unit";
    qDebug() << this->st_db_data.tariff_type << " tariff";

    emit this->sig_stat_db_update(this->st_db_data);

    return;
}

void StatStore::slot_charging_end_stat_clear()
{
    this->battery_start_persent.clear();
    return;
}

void StatStore::charging_start_db_update(double start_persent)
{
    QString qs_time = QTime::currentTime().toString("hh:mm:ss");
    this->st_db_data.start_time = qs_time;
    this->st_db_data.soc_start = start_persent;
    this->st_db_data.session_status = "charging_start";

    qDebug() << this->st_db_data.start_time << " start_time";
    qDebug() << this->st_db_data.soc_start << " soc_start";

    emit this->sig_stat_db_update(this->st_db_data);
    return;
}

void StatStore::slot_set_session_id(uint64_t set)
{
    this->st_db_data.session_id = set;

    qDebug() << set << " :: session_id";
    qDebug() << Q_FUNC_INFO;
    return;
}

void StatStore::slot_set_ocpp_tx_id(uint32_t set)
{
    this->st_db_data.ocpp_tx_id = set;

    qDebug() << set << " :: ocpp_tx_id";
    qDebug() << Q_FUNC_INFO;
    return;
}

void StatStore::charging_finished_db_update()
{
    QString qs_time = QTime::currentTime().toString("hh:mm:ss");
    this->st_db_data.end_time = qs_time;
    this->st_db_data.duration_time = this->elapsed_time;

    float total_kwh = this->accumulate_kWh / 3600;
    float total_time_h = this->reverse_cnv_time(this->elapsed_time) / 3600;
    float ave_kwh = total_kwh / total_time_h;
    this->st_db_data.average_kWh = ave_kwh;

    QString number_current;
    for (auto &v : this->battery_current)
    {
        if (v >= '0' && v <= '9' || v == '.')
        {
            number_current += v;
        }
    }

    this->st_db_data.soc_end = number_current.toDouble();
    this->st_db_data.cancel_payment = (uint32_t) this->i_can_pay;
    this->st_db_data.actual_payment = (uint32_t) this->i_act_pay;
    this->st_db_data.session_status = "charging_finished";

    qDebug() << this->st_db_data.cancel_payment << " can";
    qDebug() << this->st_db_data.actual_payment << " act";
    qDebug() << this->st_db_data.average_kWh << " ave";

    emit this->sig_stat_db_update(this->st_db_data);
    return;
}

void StatStore::cancle_pay_check()
{
    if (this->i_can_pay > 0)
    {
        QMetaObject::invokeMethod(this->p_soc,
                                  "slot_netAccess_post_cancle",
                                  Qt::QueuedConnection,
                                  Q_ARG(QString, this->card_uid));
    }
    else
    {
        emit this->p_module->sig_cancle_payment_ok_ToQml();
    }
    return;
}

void StatStore::set_screen_name(QString set)
{
    this->st_hb_data.screen_name = set;
    return;
}

void StatStore::slot_heartbit_ping()
{
    emit this->sig_heartbit_pong(this->st_hb_data);
    return;
}

void StatStore::set_heartbit_storeId_hmiId()
{
    this->st_hb_data.store_id = this->store_id;
    this->st_hb_data.hmi_id = this->mac_addr;
    return;
}

int StatStore::slot_get_i_adv_pay()
{
    return this->i_adv_pay;
}

void StatStore::set_card_type(QString set)
{
    this->st_db_data.card_type = set;
    return;
}

void StatStore::slot_set_membership_t_id(uint32_t set)
{
    this->st_mb_log.transaction_id = set;
    qDebug() << this->st_mb_log.transaction_id << " t_id";
    return;
}
