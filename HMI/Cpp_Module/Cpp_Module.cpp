#include "Cpp_Module.h"
#include "./Cpp_Module/StatStore.h"
#include "./Cpp_Module/WK_Serial.h"
#include "./Cpp_Module/WK_WebSocket.h"

Cpp_Module::Cpp_Module(QObject *parent)
    : QObject{parent}
{
    // this->set_p_wk_websoc();
    this->p_stat = new StatStore(this);
    this->p_stat->set_p_module(this);
    this->create_Serial();
}

StatStore *Cpp_Module::statStore() const
{
    return this->p_stat;
}

Cpp_Module::~Cpp_Module()
{
    this->end_p_wk_websoc();
    this->end_p_wk_serial();
    return;
}

void Cpp_Module::end_p_wk_websoc()
{
    if (this->p_wk_websoc && this->p_th_websoc->isRunning())
    {
        QMetaObject::invokeMethod(this->p_wk_websoc, &WK_WebSocket::slot_stop, Qt::QueuedConnection);
    }

    this->p_th_websoc->quit();

    this->p_th_websoc->wait(3000);

    return;
}

void Cpp_Module::end_p_wk_serial()
{
    return;
}

Q_INVOKABLE void Cpp_Module::join_WebSv(QString id)
{
    struct stat_data st_stat = {0};

    // QString qs_date = QDate::currentDate().toString("yyyy-MM-dd");

    st_stat.id = id.toInt();
    // st_stat.location = "";
    // st_stat.date = qs_date;
    // st_stat.stat = 0;

    // 처음 상태 값 설정 - ID만 존재
    this->p_stat->set_First_stat(st_stat);

    //========================================
    this->p_stat->set_store_id(id.toInt());

    if (this->p_wk_websoc == nullptr)
    {
        this->create_WebSoc();
    }
    else
    {
        QMetaObject::invokeMethod(this->p_wk_websoc,
                                  &WK_WebSocket::slot_ID_Check,
                                  Qt::QueuedConnection);
    }

    qDebug() << Q_FUNC_INFO;
    return;
}

void Cpp_Module::create_WebSoc()
{
    this->p_th_websoc = new QThread(this);
    this->p_wk_websoc = new WK_WebSocket();
    this->p_wk_websoc->set_p_stat(this->p_stat);
    this->p_wk_websoc->set_p_Module(this);

    this->p_wk_websoc->moveToThread(this->p_th_websoc);
    connect(this->p_th_websoc, &QThread::started, this->p_wk_websoc, &WK_WebSocket::slot_Connect_Sv);
    connect(this->p_wk_websoc, &WK_WebSocket::sig_end, this->p_th_websoc, &QThread::quit);
    connect(this->p_th_websoc, &QThread::finished, this->p_wk_websoc, &WK_WebSocket::deleteLater);
    connect(this->p_th_websoc, &QThread::finished, this->p_th_websoc, &QThread::deleteLater);

    this->p_th_websoc->start();

    // serial 객체에 soc객체 주소 전달
    QMetaObject::invokeMethod(this->p_wk_serial,
                              "slot_set_p_soc",
                              Qt::QueuedConnection,
                              Q_ARG(WK_WebSocket *, this->p_wk_websoc));

    // statStore 객체에 soc객체 주소 전달
    this->p_stat->set_p_soc(this->p_wk_websoc);

    qDebug() << Q_FUNC_INFO;
    return;
}

void Cpp_Module::create_Serial()
{
    this->p_th_serial = new QThread();
    this->p_wk_serial = new WK_Serial();
    this->p_wk_serial->set_p_module(this);
    this->p_wk_serial->set_p_stat(this->p_stat);

    // StatStore에 Serial클래스 주소 전달
    QMetaObject::invokeMethod(this->p_stat,
                              "slot_set_p_serial",
                              Qt::QueuedConnection,
                              Q_ARG(WK_Serial *, this->p_wk_serial));

    this->p_wk_serial->moveToThread(this->p_th_serial);

    this->p_th_serial->start();
    return;
}

Q_INVOKABLE void Cpp_Module::set_card_stat_To_serial(bool stat)
{
    QMetaObject::invokeMethod(this->p_wk_serial,
                              "slot_set_card_stat",
                              Qt::QueuedConnection,
                              Q_ARG(bool, stat));
    qDebug() << Q_FUNC_INFO;
    return;
}

Q_INVOKABLE void Cpp_Module::chargingConnecter_open_To_serial()
{
    QMetaObject::invokeMethod(this->p_wk_serial,
                              "slot_rs485_coil1_on_off",
                              Qt::QueuedConnection,
                              Q_ARG(bool, true));
    return;
}

Q_INVOKABLE void Cpp_Module::chargingConnecter_ready_To_serial()
{
    QMetaObject::invokeMethod(this->p_wk_serial,
                              "slot_rs485_coil234_on_off",
                              Qt::QueuedConnection,
                              Q_ARG(bool, true));
    return;
}

Q_INVOKABLE void Cpp_Module::charging_start_To_serial()
{
    QMetaObject::invokeMethod(this->p_wk_serial,
                              "slot_rs232_cmd",
                              Qt::QueuedConnection,
                              Q_ARG(uint16_t, 0),
                              Q_ARG(uint16_t, 1));

    return;
}

Q_INVOKABLE void Cpp_Module::charging_stop_To_serial()
{
    QMetaObject::invokeMethod(this->p_wk_serial,
                              "slot_rs232_cmd",
                              Qt::QueuedConnection,
                              Q_ARG(uint16_t, 1),
                              Q_ARG(uint16_t, 1));

    return;
}

Q_INVOKABLE void Cpp_Module::chargingConnecter_close_To_serial()
{
    QMetaObject::invokeMethod(this->p_wk_serial,
                              "slot_rs485_coil1_on_off",
                              Qt::QueuedConnection,
                              Q_ARG(bool, false));

    return;
}

Q_INVOKABLE void Cpp_Module::chargingConnecter_off_To_serial()
{
    QMetaObject::invokeMethod(this->p_wk_serial,
                              "slot_rs485_coil234_on_off",
                              Qt::QueuedConnection,
                              Q_ARG(bool, false));

    return;
}

Q_INVOKABLE void Cpp_Module::charging_type_To_statStore(QString type, qint32 val)
{
    CHARGING_TYPE charging_type;
    if (type == "time")
    {
        charging_type = TIME;
    }
    else if (type == "won")
    {
        charging_type = WON;
    }
    else if (type == "kWh")
    {
        charging_type = KWH;
    }
    else if (type == "persent")
    {
        charging_type = PERSENT;
    }

    QMetaObject::invokeMethod(this->p_stat,
                              "slot_set_charging_type",
                              Qt::QueuedConnection,
                              Q_ARG(CHARGING_TYPE, charging_type),
                              Q_ARG(qint32, val));
    return;
}

Q_INVOKABLE void Cpp_Module::charging_type_clear_To_statStore()
{
    this->p_stat->slot_clear_charging_type();
    /*
    QMetaObject::invokeMethod(this->p_stat,
                              &StatStore::slot_clear_charging_type,
                              Qt::QueuedConnection);
*/
    return;
}

Q_INVOKABLE void Cpp_Module::set_payment_To_statStore()
{
    // 환불 금액 확인도 같이해줌
    this->p_stat->slot_set_payment();

    /*
    QMetaObject::invokeMethod(this->p_stat, &StatStore::slot_set_payment, Qt::QueuedConnection);*/
    return;
}

Q_INVOKABLE void Cpp_Module::charging_start_To_statStore()
{
    this->p_stat->slot_set_charging_start_time();
    /*j
    QMetaObject::invokeMethod(this->p_stat,
                              &StatStore::slot_set_charging_start_time,
                              Qt::QueuedConnection);*/
    return;
}

Q_INVOKABLE void Cpp_Module::chard_ok_To_statStore()
{
    this->p_stat->slot_card_ok_db_update();
    /*
    QMetaObject::invokeMethod(this->p_stat,
                              &StatStore::slot_card_ok_db_update,
                              Qt::QueuedConnection);*/
    return;
}

Q_INVOKABLE void Cpp_Module::charging_end_stat_clear_To_statStore()
{
    this->p_stat->slot_charging_end_stat_clear();
    /*
    QMetaObject::invokeMethod(this->p_stat,
                              &StatStore::slot_charging_end_stat_clear,
                              Qt::QueuedConnection);*/
    return;
}

Q_INVOKABLE void Cpp_Module::charging_finished_To_statStore()
{
    this->p_stat->charging_finished_db_update();
    return;
}

Q_INVOKABLE void Cpp_Module::set_screen_name(QString set)
{
    this->p_stat->set_screen_name(set);
    return;
}

Q_INVOKABLE void Cpp_Module::set_heartbit_storeId_hmiId()
{
    this->p_stat->set_heartbit_storeId_hmiId();
    return;
}

Q_INVOKABLE void Cpp_Module::set_card_type_To_serial(QString set)
{
    QMetaObject::invokeMethod(this->p_wk_serial,
                              "slot_set_card_type",
                              Qt::QueuedConnection,
                              Q_ARG(QString, set));

    return;
}

Q_INVOKABLE void Cpp_Module::set_card_type_To_statStore(QString set)
{
    this->p_stat->set_card_type(set);
    return;
}
