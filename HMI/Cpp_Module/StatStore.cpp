#include "StatStore.h"
#include "Cpp_Module.h"
#include "WK_Serial.h"
#include "WK_WebSocket.h"

StatStore::StatStore(QObject *parent)
    : QObject{parent}
{
    this->set_charge_price_min();
    this->create_db_lite();

    this->p_tm_backUp = new QTimer(this);
    this->p_tm_backUp->start(60000);
    connect(this->p_tm_backUp, &QTimer::timeout, this, &StatStore::slot_check_netErr);
}

void StatStore::set_charge_price_min()
{
    this->charge_price_min = ((this->charge_price_kWh * 400 * 150) / 60) / 1000;
    return;
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

void StatStore::set_p_module(Cpp_Module *set)
{
    this->p_module = set;
}

void StatStore::set_p_soc(WK_WebSocket *set)
{
    this->p_soc = set;
    return;
}

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
    // 충전 종류에 따라서 ~원으로 변환
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
        QString hmi_id = this->mac_addr;
        QString request_id;
        QDateTime dt_utc = QDateTime::currentDateTimeUtc();
        request_id = hmi_id + dt_utc.toString();

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
        // second로 변환 안해서그럼
        if (elapsed_time >= (this->charging_val * 60))
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

int StatStore::get_m_type()
{
    return this->m_type;
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

int StatStore::get_charge_price_kWh()
{
    return this->charge_price_kWh;
}

void StatStore::slot_set_m_type(int set)
{
    this->m_type = set;
    emit this->sig_m_type();
    return;
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

void StatStore::slot_set_charge_price_kWh(int set)
{
    this->charge_price_kWh = set;
    this->set_charge_price_min();
    emit this->sig_charge_price_kWh();
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

    QString local_tx_id;
    QDateTime dt_utc = QDateTime::currentDateTimeUtc();
    local_tx_id = this->mac_addr + dt_utc.toString();
    this->st_db_data.local_tx_id = local_tx_id;

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

QString StatStore::get_card_type()
{
    return this->st_db_data.card_type;
}

void StatStore::ems_Charging_Ready()
{
    this->i_act_pay = 0;
    this->i_can_pay = this->i_adv_pay;

    if (this->st_db_data.card_type == "creditCard")
    {
        // 환불 금액 있으면 환불해줌
        this->cancle_pay_check();
    }
    else if (this->st_db_data.card_type == "membershipCard")
    {
        QString hmi_id = this->mac_addr;
        QString request_id;
        QDateTime dt_utc = QDateTime::currentDateTimeUtc();
        request_id = hmi_id + dt_utc.toString();

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

void StatStore::netErr_Card_save(const NET_ERR_CHARGING_TYPE type)
{
    if (this->db_card_save_stat == true)
    {
        return;
    }
    this->db_card_save_stat = true;

    if (type == CHARGING_READY)
    {
        this->i_act_pay = 0;
        this->i_can_pay = this->i_adv_pay;

        if (this->st_db_data.card_type == "creditCard")
        {
            // this->cancle_pay_check();

            netErr_creditCard st_credit = {0};
            st_credit.act_pay = 0;
            st_credit.can_pay = this->i_can_pay;
            st_credit.adv_pay = this->i_adv_pay;
            st_credit.card_uid = this->card_uid;
            this->insert_db_credit(st_credit);
        }
        else if (this->st_db_data.card_type == "membershipCard")
        {
            QString hmi_id = this->mac_addr;
            QString request_id;
            QDateTime dt_utc = QDateTime::currentDateTimeUtc();
            request_id = hmi_id + dt_utc.toString();

            netErr_membershipCard st_membership = {0};
            st_membership.act_pay = 0;
            st_membership.can_pay = this->i_can_pay;
            st_membership.adv_pay = this->i_adv_pay;
            st_membership.card_uid = this->st_db_data.card_uid;
            st_membership.transaction_id = this->st_mb_log.transaction_id;
            st_membership.request_id = request_id;
            this->insert_db_membership(st_membership);
            /*
        QMetaObject::invokeMethod(this->p_soc,
                                  "slot_send_membership_finished_textData",
                                  Qt::QueuedConnection,
                                  Q_ARG(int, this->i_adv_pay),
                                  Q_ARG(int, this->i_act_pay),
                                  Q_ARG(int, this->i_can_pay),
                                  Q_ARG(QString, this->st_db_data.card_uid),
                                  Q_ARG(uint32_t, this->st_mb_log.transaction_id),
                                  Q_ARG(QString, request_id));
        */
        }
    }
    else if (type == CHARGING_FINISHED)
    {
        this->i_can_pay = this->i_adv_pay - this->i_act_pay;

        if (this->st_db_data.card_type == "creditCard")
        {
            netErr_creditCard st_credit = {0};
            st_credit.act_pay = this->i_act_pay;
            st_credit.can_pay = this->i_can_pay;
            st_credit.adv_pay = this->i_adv_pay;
            st_credit.card_uid = this->card_uid;
            this->insert_db_credit(st_credit);
        }
        else if (this->st_db_data.card_type == "membershipCard")
        {
            QString hmi_id = this->mac_addr;
            QString request_id;
            QDateTime dt_utc = QDateTime::currentDateTimeUtc();
            request_id = hmi_id + dt_utc.toString();

            netErr_membershipCard st_membership = {0};
            st_membership.act_pay = this->i_act_pay;
            st_membership.can_pay = this->i_can_pay;
            st_membership.adv_pay = this->i_adv_pay;
            st_membership.card_uid = this->st_db_data.card_uid;
            st_membership.transaction_id = this->st_mb_log.transaction_id;
            st_membership.request_id = request_id;
            this->insert_db_membership(st_membership);
        }
    }

    // this->p_module->set_stop_reason("Network Err");
    // this->insert_db_charging();
}

void StatStore::set_stop_reason(QString set)
{
    this->st_db_data.stop_reason = set;
    return;
}

QString StatStore::get_cur_advertisement()
{
    return this->cur_advertisement;
}

void StatStore::set_cur_advertisement(QString set)
{
    qDebug() << set << "set_______________";
    this->cur_advertisement = set;
    emit this->sig_cur_advertisement();
    emit this->p_module->sig_ad_play_ToQml();
    return;
}

void StatStore::create_db_lite()
{
    QString s_data_dir;
    QString s_db_path;
    QDir qd_dir;

    s_data_dir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    s_db_path = s_data_dir + "/db_lite.sqlite3";
    qDebug() << s_db_path;
    qd_dir.mkpath(s_data_dir);

    this->db_lite = QSqlDatabase::addDatabase("QSQLITE", "DB_THREAD_CONN_SQLITE");
    this->db_lite.setDatabaseName(s_db_path);

    this->cur_path = s_data_dir;
    if (this->db_lite.open())
    {
        qDebug() << "db_light open";
    }
    else
    {
        // qDebug() << "db false";
        qDebug() << this->db_lite.lastError().text();
    }

    this->create_db_table();
    this->create_db_table_credit();
    this->create_db_table_membership();
    this->create_db_table_charging();

    return;
}

void StatStore::create_db_table()
{
    QSqlQuery query(this->db_lite);
    QString sql = "CREATE TABLE ad_list ("
                  "name TEXT PRIMARY KEY "
                  "NOT NULL,"
                  "path TEXT,"
                  "stat BOOL);";
    bool ok_prepare = query.prepare(sql);

    /*
    if (!this->check_query_prepare(ok_prepare, query))
    {
        return;
    }*/

    bool ok_exec = query.exec();

    /*
    if (!this->check_query_exec(ok_exec, query))
    {
        return;
    }*/
    return;
}

void StatStore::create_db_table_credit()
{
    QSqlQuery query(this->db_lite);
    QString sql = "CREATE TABLE credit ("
                  "row_id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "card_uid TEXT NOT NULL,"
                  "act_pay INTEGER,"
                  "can_pay INTEGER,"
                  "adv_pay INTEGER,"
                  "stat BOOL"
                  ");";
    bool ok_prepare = query.prepare(sql);

    /*
    if (!this->check_query_prepare(ok_prepare, query))
    {
        return;
    }*/

    bool ok_exec = query.exec();

    /*
    if (!this->check_query_exec(ok_exec, query))
    {
        return;
    }*/
    return;
}

void StatStore::create_db_table_membership()
{
    QSqlQuery query(this->db_lite);
    QString sql = "CREATE TABLE membership ("
                  "row_id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "card_uid TEXT NOT NULL,"
                  "act_pay INTEGER,"
                  "can_pay INTEGER,"
                  "adv_pay INTEGER,"
                  "transaction_id INTEGER,"
                  "request_id TEXT,"
                  "stat BOOL"
                  ");";

    bool ok_prepare = query.prepare(sql);

    /*
    if (!this->check_query_prepare(ok_prepare, query))
    {
        return;
    }*/

    bool ok_exec = query.exec();

    /*
    if (!this->check_query_exec(ok_exec, query))
    {
        return;
    }*/
    return;
}

void StatStore::create_db_table_charging()
{
    QSqlQuery query(this->db_lite);

    QString sql = "CREATE TABLE charging ("
                  "row_id INTEGER PRIMARY KEY AUTOINCREMENT, "
                  "store_id INTEGER, "
                  "hmi_id TEXT, "
                  "ocpp_tx_id INTEGER, "
                  "card_uid TEXT, "
                  "start_time TEXT, "
                  "end_time TEXT, "
                  "duration_time TEXT, "
                  "average_kwh REAL, "
                  "soc_start REAL, "
                  "soc_end REAL, "
                  "advance_payment INTEGER, "
                  "cancel_payment INTEGER, "
                  "actual_payment INTEGER, "
                  "unit_price INTEGER, "
                  "tariff_type TEXT, "
                  "session_status TEXT, "
                  "stop_reason TEXT, "
                  "local_tx_id TEXT, "
                  "stat BOOL"
                  ");";

    bool ok_prepare = query.prepare(sql);

    if (!this->check_query_prepare(ok_prepare, query))
    {
        return;
    }

    bool ok_exec = query.exec();

    if (!this->check_query_exec(ok_exec, query))
    {
        return;
    }
    return;
}

void StatStore::insert_db_first_data()
{
    QSqlQuery query(this->db_lite);
    QString sql = "INSERT INTO ad_list ("
                  "name, path, stat) VALUES ("
                  ":name, :path, :stat)";
    bool ok_prepare = query.prepare(sql);

    if (!this->check_query_prepare(ok_prepare, query))
    {
        return;
    }

    query.bindValue(":name", "first.mp4");
    query.bindValue(":path", this->cur_path);
    query.bindValue(":stat", true);
    bool ok_exec = query.exec();

    if (!this->check_query_exec(ok_exec, query))
    {
        return;
    }

    return;
}

void StatStore::update_ad()
{
    qDebug() << Q_FUNC_INFO;

    QSqlQuery query(this->db_lite);

    QString sql = "SELECT * FROM ad_list "
                  "WHERE stat = :stat";
    bool ok_prepare = query.prepare(sql);

    if (!this->check_query_prepare(ok_prepare, query))
    {
        return;
    }

    query.bindValue(":stat", true);
    bool ok_exec = query.exec();

    if (!this->check_query_exec(ok_exec, query))
    {
        return;
    }

    while (query.next())
    {
        QString name = query.value(0).toString();
        QString path = query.value(1).toString();
        QString val = path + '/' + name;
        if (!vec_ad.contains(val))
        {
            this->vec_ad.push_back(val);
        }
    }

    for (auto &v : vec_ad)
    {
        qDebug() << v << "  " << vec_ad.size();
    }

    this->next_ad();
    return;
}

void StatStore::next_ad()
{
    std::rotate(this->vec_ad.begin(), this->vec_ad.begin() + 1, this->vec_ad.end());
    this->set_cur_advertisement(vec_ad.front());
    qDebug() << Q_FUNC_INFO;
    return;
}

bool StatStore::check_query_prepare(bool ok, QSqlQuery &query)
{
    if (!ok)
    {
        QSqlError e = query.lastError();
        qDebug() << "DB prepare failed";
        qDebug() << "driverText =" << e.driverText();
        qDebug() << "databaseText =" << e.databaseText();
        qDebug() << "lastQuery =" << query.lastQuery();
        return false;
    }

    return true;
}

bool StatStore::check_query_exec(bool ok, QSqlQuery &query)
{
    if (!ok)
    {
        QSqlError e = query.lastError();
        qDebug() << "DB exec failed";
        qDebug() << "driverText =" << e.driverText();
        qDebug() << "databaseText =" << e.databaseText();
        qDebug() << "type =" << e.type();
        qDebug() << "lastQuery =" << query.lastQuery();
        qDebug() << "boundValues =" << query.boundValues();
        return false;
    }
    return true;
}

int StatStore::slot_find_ad(const QString name)
{
    QSqlQuery query(this->db_lite);

    QString sql = "SELECT * FROM ad_list "
                  "WHERE name = :name";
    bool ok_prepare = query.prepare(sql);

    if (!this->check_query_prepare(ok_prepare, query))
    {
        return false;
    }

    query.bindValue(":name", name);
    bool ok_exec = query.exec();

    if (!this->check_query_exec(ok_exec, query))
    {
        return false;
    }

    if (query.next())
    {
        QString ret_name = query.value(0).toString();
        QString ret_path = query.value(1).toString();
        bool ret_stat = query.value(2).toBool();
        if (ret_stat == false)
        {
            this->marking_ad(ret_name, (!ret_stat));
        }

        this->update_ad();
        return NEED_NOT;
    }

    return NEED_DOWNLOAD;
}

void StatStore::marking_ad(const QString name, const bool stat)
{
    QSqlQuery query(this->db_lite);

    QString sql = "UPDATE ad_list "
                  "SET "
                  "stat = :stat "
                  "WHERE name = :name";

    bool ok_prepare = query.prepare(sql);

    if (!this->check_query_prepare(ok_prepare, query))
    {
        return;
    }

    query.bindValue(":stat", stat);
    query.bindValue(":name", name);
    bool ok_exec = query.exec();

    if (!this->check_query_exec(ok_exec, query))
    {
        return;
    }

    return;
}

void StatStore::slot_insert_ad(const QString name, const bool stat)
{
    QSqlQuery query(this->db_lite);

    QString sql = "INSERT INTO ad_list ("
                  "name, path, stat) VALUES ("
                  ":name, :path, :stat)";

    bool ok_prepare = query.prepare(sql);

    if (!this->check_query_prepare(ok_prepare, query))
    {
        return;
    }

    query.bindValue(":name", name);
    query.bindValue(":path", this->cur_path);
    query.bindValue(":stat", stat);
    bool ok_exec = query.exec();

    if (!this->check_query_exec(ok_exec, query))
    {
        return;
    }

    return;
}

void StatStore::slot_remove_ad(const QString name)
{
    QSqlQuery query(this->db_lite);

    QString sql = "SELECT * FROM ad_list "
                  "WHERE name = :name";
    bool ok_prepare = query.prepare(sql);

    if (!this->check_query_prepare(ok_prepare, query))
    {
        return;
    }

    query.bindValue(":name", name);
    bool ok_exec = query.exec();

    if (!this->check_query_exec(ok_exec, query))
    {
        return;
    }

    if (query.next())
    {
        QString ret_name = query.value(0).toString();
        QString ret_path = query.value(1).toString();
        bool ret_stat = query.value(2).toBool();
        if (ret_stat == true)
        {
            this->marking_ad(ret_name, (!ret_stat));
        }
    }

    QString val = this->cur_path + "/" + name;
    while (this->vec_ad.contains(val))
    {
        this->vec_ad.removeOne(val);
    }

    for (auto &v : this->vec_ad)
    {
        qDebug() << v << " after remove";
    }

    return;
}

int StatStore::get_charging_type()
{
    return this->charging_type;
}

bool StatStore::get_soc_connect_stat()
{
    return this->soc_connect_stat;
}

void StatStore::set_soc_connect_stat(bool set)
{
    this->soc_connect_stat = set;
    emit this->sig_soc_connect_stat();
    return;
}

void StatStore::slot_set_soc_connect_stat(const bool set)
{
    this->set_soc_connect_stat(set);
}

void StatStore::insert_db_credit(const netErr_creditCard st_data)
{
    QSqlQuery query(this->db_lite);
    QString sql = "INSERT INTO credit ("
                  "card_uid, act_pay, can_pay, adv_pay, stat) VALUES ("
                  ":card_uid, :act_pay, :can_pay, :adv_pay, :stat)";
    bool ok_prepare = query.prepare(sql);

    if (!this->check_query_prepare(ok_prepare, query))
    {
        return;
    }

    query.bindValue(":card_uid", st_data.card_uid);
    query.bindValue(":act_pay", st_data.act_pay);
    query.bindValue(":can_pay", st_data.can_pay);
    query.bindValue(":adv_pay", st_data.adv_pay);
    query.bindValue(":stat", true);
    bool ok_exec = query.exec();

    if (!this->check_query_exec(ok_exec, query))
    {
        return;
    }

    return;
}

void StatStore::insert_db_membership(const netErr_membershipCard st_data)
{
    QSqlQuery query(this->db_lite);
    QString sql = "INSERT INTO membership ("
                  "card_uid, act_pay, can_pay, adv_pay, transaction_id, request_id, stat) VALUES ("
                  ":card_uid, :act_pay, :can_pay, :adv_pay, :transaction_id, :request_id, :stat)";
    bool ok_prepare = query.prepare(sql);

    if (!this->check_query_prepare(ok_prepare, query))
    {
        return;
    }

    query.bindValue(":card_uid", st_data.card_uid);
    query.bindValue(":act_pay", st_data.act_pay);
    query.bindValue(":can_pay", st_data.can_pay);
    query.bindValue(":adv_pay", st_data.adv_pay);
    query.bindValue(":transaction_id", st_data.transaction_id);
    query.bindValue(":request_id", st_data.request_id);
    query.bindValue(":stat", true);
    bool ok_exec = query.exec();

    if (!this->check_query_exec(ok_exec, query))
    {
        return;
    }

    return;
}

void StatStore::insert_db_charging(const NET_ERR_CHARGING_TYPE type)
{
    if (this->db_charging_save_stat == true)
    {
        return;
    }

    this->db_charging_save_stat = true;

    if (type == CHARGING_READY)
    {
        QString qs_time = QTime::currentTime().toString("hh:mm:ss");
        this->st_db_data.end_time = qs_time;
        this->st_db_data.duration_time = 0;

        float total_kwh = 0;
        float total_time_h = 0;
        float ave_kwh = 0;
        this->st_db_data.average_kWh = 0;

        this->st_db_data.soc_end = this->st_db_data.soc_start;
        this->st_db_data.cancel_payment = (uint32_t) this->i_can_pay;
        this->st_db_data.actual_payment = (uint32_t) this->i_act_pay;
        this->st_db_data.session_status = "charging_finished";

        qDebug() << this->st_db_data.cancel_payment << " can";
        qDebug() << this->st_db_data.actual_payment << " act";
        qDebug() << this->st_db_data.average_kWh << " ave";
    }
    else if (type == CHARGING_FINISHED)
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
    }

    QSqlQuery query(this->db_lite);

    QString sql
        = "INSERT INTO charging ("
          "store_id, hmi_id, ocpp_tx_id, card_uid, start_time, end_time, duration_time, "
          "average_kwh, soc_start, soc_end, advance_payment, cancel_payment, actual_payment, "
          "unit_price, tariff_type, session_status, stop_reason, local_tx_id, stat) VALUES ("
          ":store_id, :hmi_id, :ocpp_tx_id, :card_uid, :start_time, :end_time, :duration_time, "
          ":average_kwh, :soc_start, :soc_end, :advance_payment, :cancel_payment, :actual_payment, "
          ":unit_price, :tariff_type, :session_status, :stop_reason, :local_tx_id, :stat)";

    bool ok_prepare = query.prepare(sql);

    if (!this->check_query_prepare(ok_prepare, query))
    {
        return;
    }

    query.bindValue(":store_id", this->st_db_data.store_id);
    query.bindValue(":hmi_id", this->st_db_data.hmi_id);
    query.bindValue(":ocpp_tx_id", this->st_db_data.ocpp_tx_id);
    query.bindValue(":card_uid", this->st_db_data.card_uid);
    query.bindValue(":start_time", this->st_db_data.start_time);
    query.bindValue(":end_time", this->st_db_data.end_time);
    query.bindValue(":duration_time", this->st_db_data.duration_time);
    query.bindValue(":average_kwh", this->st_db_data.average_kWh);
    query.bindValue(":soc_start", this->st_db_data.soc_start);
    query.bindValue(":soc_end", this->st_db_data.soc_end);
    query.bindValue(":advance_payment", this->st_db_data.advance_payment);
    query.bindValue(":cancel_payment", this->st_db_data.cancel_payment);
    query.bindValue(":actual_payment", this->st_db_data.actual_payment);
    query.bindValue(":unit_price", this->st_db_data.unit_price);
    query.bindValue(":tariff_type", this->st_db_data.tariff_type);
    query.bindValue(":session_status", this->st_db_data.session_status);
    query.bindValue(":stop_reason", this->st_db_data.stop_reason);
    query.bindValue(":local_tx_id", this->st_db_data.local_tx_id);
    query.bindValue(":stat", true);

    bool ok_exec = query.exec();

    if (!this->check_query_exec(ok_exec, query))
    {
        return;
    }

    return;
}

void StatStore::slot_check_netErr()
{
    if (this->soc_connect_stat == false)
    {
        return;
    }

    qDebug() << Q_FUNC_INFO;
    this->check_netErr_credit();
    this->check_netErr_membership();
    this->check_netErr_charging();
    return;
}

void StatStore::check_netErr_credit()
{
    qDebug() << Q_FUNC_INFO;

    QSqlQuery query(this->db_lite);

    QString sql = "SELECT * FROM credit "
                  "WHERE stat = :stat";
    bool ok_prepare = query.prepare(sql);

    if (!this->check_query_prepare(ok_prepare, query))
    {
        return;
    }

    query.bindValue(":stat", true);
    bool ok_exec = query.exec();

    if (!this->check_query_exec(ok_exec, query))
    {
        return;
    }

    while (query.next())
    {
        struct netErr_creditCard st_data = {0};
        int row_id = query.value(0).toInt();
        st_data.card_uid = query.value(1).toString();
        st_data.act_pay = query.value(2).toInt();
        st_data.can_pay = query.value(3).toInt();
        st_data.adv_pay = query.value(4).toInt();

        if (st_data.can_pay > 0)
        {
            QMetaObject::invokeMethod(this->p_soc,
                                      "slot_netAccess_post_cancle",
                                      Qt::QueuedConnection,
                                      Q_ARG(QString, this->card_uid));
        }
        else
        {
            // emit this->p_module->sig_cancle_payment_ok_ToQml();
        }

        this->marking_row(CREDIT, row_id);
    }

    return;
}

void StatStore::check_netErr_membership()
{
    qDebug() << Q_FUNC_INFO;

    QSqlQuery query(this->db_lite);

    QString sql = "SELECT * FROM membership "
                  "WHERE stat = :stat";
    bool ok_prepare = query.prepare(sql);

    if (!this->check_query_prepare(ok_prepare, query))
    {
        return;
    }

    query.bindValue(":stat", true);
    bool ok_exec = query.exec();

    if (!this->check_query_exec(ok_exec, query))
    {
        return;
    }

    while (query.next())
    {
        struct netErr_membershipCard st_data = {0};
        int row_id = query.value(0).toInt();
        st_data.card_uid = query.value(1).toString();
        st_data.act_pay = query.value(2).toInt();
        st_data.can_pay = query.value(3).toInt();
        st_data.adv_pay = query.value(4).toInt();
        st_data.transaction_id = query.value(5).toInt();
        st_data.request_id = query.value(6).toString();

        QMetaObject::invokeMethod(this->p_soc,
                                  "slot_send_membership_finished_textData",
                                  Qt::QueuedConnection,
                                  Q_ARG(int, st_data.adv_pay),
                                  Q_ARG(int, st_data.act_pay),
                                  Q_ARG(int, st_data.can_pay),
                                  Q_ARG(QString, st_data.card_uid),
                                  Q_ARG(uint32_t, st_data.transaction_id),
                                  Q_ARG(QString, st_data.request_id));

        this->marking_row(MEMBERSHIP, row_id);
    }

    return;
}

void StatStore::check_netErr_charging()
{
    qDebug() << Q_FUNC_INFO;

    QSqlQuery query(this->db_lite);

    QString sql = "SELECT * FROM charging "
                  "WHERE stat = :stat";
    bool ok_prepare = query.prepare(sql);

    if (!this->check_query_prepare(ok_prepare, query))
    {
        return;
    }

    query.bindValue(":stat", true);
    bool ok_exec = query.exec();

    if (!this->check_query_exec(ok_exec, query))
    {
        return;
    }

    while (query.next())
    {
        qDebug() << "???????????__________";
        struct db_data st_data = {0};
        int row_id = query.value(0).toInt();
        st_data.store_id = query.value(1).toInt();
        st_data.hmi_id = query.value(2).toString();
        st_data.ocpp_tx_id = query.value(3).toInt();
        st_data.card_uid = query.value(4).toString();
        QString start_time = query.value(5).toString();
        if (start_time.isEmpty())
        {
            start_time = "00:00";
        }
        st_data.start_time = start_time;
        st_data.end_time = query.value(6).toString();
        QString duration_time = query.value(7).toString();
        if (duration_time.isEmpty())
        {
            duration_time = "00:00";
        }
        st_data.duration_time = duration_time;
        st_data.average_kWh = query.value(8).toDouble();
        st_data.soc_start = query.value(9).toDouble();
        st_data.soc_end = query.value(10).toDouble();
        st_data.advance_payment = query.value(11).toInt();
        st_data.cancel_payment = query.value(12).toInt();
        st_data.actual_payment = query.value(13).toInt();
        st_data.unit_price = query.value(14).toInt();
        st_data.tariff_type = query.value(15).toString();
        st_data.session_status = query.value(16).toString();
        st_data.stop_reason = query.value(17).toString();
        st_data.local_tx_id = query.value(18).toString();

        emit this->sig_stat_db_update(st_data);
        this->marking_row(CHARGING, row_id);
    }

    return;
}

void StatStore::marking_row(const TABLE_TYPE type, int row_id)
{
    qDebug() << Q_FUNC_INFO;

    QSqlQuery query(this->db_lite);

    QString sql;

    if (type == CREDIT)
    {
        sql = "UPDATE credit "
              "SET "
              "stat = :stat "
              "WHERE row_id = :row_id";
    }
    else if (type == MEMBERSHIP)
    {
        sql = "UPDATE membership "
              "SET "
              "stat = :stat "
              "WHERE row_id = :row_id";
    }
    else if (type == CHARGING)
    {
        sql = "UPDATE charging "
              "SET "
              "stat = :stat "
              "WHERE row_id = :row_id";
    }

    bool ok_prepare = query.prepare(sql);

    if (!this->check_query_prepare(ok_prepare, query))
    {
        return;
    }

    query.bindValue(":stat", false);
    query.bindValue(":row_id", row_id);
    bool ok_exec = query.exec();

    if (!this->check_query_exec(ok_exec, query))
    {
        return;
    }

    return;
}

bool StatStore::slot_get_soc_connect_stat()
{
    return this->soc_connect_stat;
}
