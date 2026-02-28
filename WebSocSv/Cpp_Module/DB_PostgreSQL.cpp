#include "DB_PostgreSQL.h"
#include "WK_Soc.h"

DB_PostgreSQL::DB_PostgreSQL(QObject *parent)
    : QObject{parent}
{}

DB_PostgreSQL::~DB_PostgreSQL()
{
    return;
}

void DB_PostgreSQL::set_p_Module(Cpp_Module *module)
{
    this->p_Module = module;
    return;
}

void DB_PostgreSQL::slot_set_p_soc(WK_Soc *soc)
{
    this->p_soc = soc;
    return;
}

void DB_PostgreSQL::createDB()
{
    qDebug() << QSqlDatabase::drivers();
    qDebug() << QLibraryInfo::path(QLibraryInfo::PluginsPath);

    this->db = QSqlDatabase::addDatabase("QPSQL", "DB_THREAD_CONN");
    this->db.setHostName("localhost");
    this->db.setDatabaseName("HMI_Users");
    this->db.setUserName("postgres");
    this->db.setPassword("a183153");
    this->db.setPort(5432);

    if (this->db.open())
    {
        qDebug() << "db open";
    }
    else
    {
        // qDebug() << "db false";
        qDebug() << this->db.lastError().text();
    }
    return;
}

void DB_PostgreSQL::slot_end()
{
    emit this->sig_end();
    return;
}

bool DB_PostgreSQL::slot_createStore(int id, QString name, QString location)
{
    QSqlQuery query(this->db);
    // SELECT id FROM 테이블명 WHERE id = 값;
    // 쿼리로 새로 생성하고 성공여부 반환
    query.prepare("SELEC * FROM HMI연결 WHERE id = :id");
    // query.bindValue(":id", find_id);

    return false;
}

/* 수정
store_info DB_PostgreSQL::slot_query_find_id(QString find_id)
{
    QSqlQuery query(this->db);
    // SELECT id FROM 테이블명 WHERE id = 값;
    bool ok_prepare = query.prepare("SELECT * FROM HMI연결 WHERE id = :id");
    if(!this->check_query_prepare(ok_prepare, query))
    {
        return 
    }
    query.bindValue(":id", find_id);

    struct store_info st_info = {0};
    // 만약 값이 있다면
    if (query.exec() && query.next())
    {
        st_info.id = query.value(0).toInt();
        st_info.name = query.value(1).toString();
        st_info.location = query.value(2).toString();

        return st_info;
    }

    st_info.id = -1;
    return st_info;
} */

bool DB_PostgreSQL::slot_query_register(const QString id, const QString name, const QString location)
{
    QString new_id = id;
    qDebug() << id << " :: id";
    qDebug() << name << " :: name";
    qDebug() << location << " :: location";

    QSqlQuery query(this->db);
    // SELECT id FROM 테이블명 WHERE id = 값;
    bool b_ok_prepare = query.prepare(
        "INSERT INTO store_user (id, name, location) VALUES (:id, :name, :location)");

    if (!this->check_query_prepare(b_ok_prepare, query))
    {
        return false;
    }

    query.bindValue(":id", new_id.toInt());
    query.bindValue(":name", name);
    query.bindValue(":location", location);

    bool b_ok_exec = query.exec();

    if (!this->check_query_exec(b_ok_exec, query))
    {
        return false;
    }
    else
    {
        return true;
    }

    return false;
}

bool DB_PostgreSQL::slot_query_register_hmi(const QString storeId, const QString hmiId)
{
    QString new_id = storeId;
    qDebug() << storeId << " :: sotreId";
    qDebug() << hmiId << " :: hmiId";

    QSqlQuery query(this->db);
    // SELECT id FROM 테이블명 WHERE id = 값;
    bool b_ok_prepare = query.prepare(
        "INSERT INTO hmi_device (hmi_id, store_id) VALUES (:hmi_id, :store_id)");

    if (!this->check_query_prepare(b_ok_prepare, query))
    {
        return false;
    }

    query.bindValue(":hmi_id", hmiId);
    query.bindValue(":store_id", new_id.toInt());

    bool b_ok_exec = query.exec();
    if (!this->check_query_exec(b_ok_exec, query))
    {
        return false;
    }

    return true;
}

bool DB_PostgreSQL::slot_query_find_hello_hmi(const QString storeId, const QString hmiId)
{
    QSqlQuery query(this->db);
    // SELECT id FROM 테이블명 WHERE id = 값;
    bool b_ok_prepare = query.prepare("SELECT * FROM hmi_device WHERE hmi_id = :hmi_id");

    if (!this->check_query_prepare(b_ok_prepare, query))
    {
        return false;
    }

    query.bindValue(":hmi_id", hmiId);

    QString compare_hmiId;
    QString compare_storeId;

    bool b_ok_exec = query.exec();

    if (!this->check_query_exec(b_ok_exec, query))
    {
        return false;
    }
    else
    {
        query.next();
        compare_hmiId = query.value(0).toString();
        compare_storeId = query.value(1).toString();
    }

    qDebug() << compare_hmiId << " :: cmp hmiId";
    qDebug() << hmiId << " :: hmiId";

    qDebug() << compare_storeId << " :: cmp storeId";
    qDebug() << storeId << " :: storeId";

    if (compare_storeId == storeId && compare_hmiId == hmiId)
    {
        return true;
    }
    else
    {
        return false;
    }

    return false;
}

void DB_PostgreSQL::slot_chargingLog_From_soc(db_data st_db_data)
{
    QSqlQuery query(this->db);
    qDebug() << st_db_data.store_id << " store_id";
    qDebug() << st_db_data.hmi_id << " hmi_id";
    qDebug() << st_db_data.card_uid << " card";
    qDebug() << st_db_data.start_time << " start_time";
    qDebug() << st_db_data.soc_start << " soc_start";
    qDebug() << st_db_data.advance_payment << " adv";
    qDebug() << st_db_data.unit_price << " unit";
    qDebug() << st_db_data.tariff_type << " tariff";

    qDebug() << Q_FUNC_INFO;
    if (st_db_data.session_status == "authorized")
    {
        bool ok_prepare = query.prepare(
            "INSERT INTO charging_log (store_id, hmi_id, ocpp_tx_id, card_uid, start_time, "
            "end_time, "
            "duration_time, average_kWh, soc_start, soc_end, advance_payment, cancel_payment, "
            "actual_payment, unit_price, tariff_type, session_status, stop_reason) VALUES "
            "(:store_id, "
            ":hmi_id, :ocpp_tx_id, :card_uid, :start_time, :end_time, "
            ":duration_time, :average_kWh, :soc_start, :soc_end, :advance_payment, "
            ":cancel_payment, "
            ":actual_payment, :unit_price, :tariff_type, :session_status, :stop_reason)"
            "RETURNING session_id");

        if (!this->check_query_prepare(ok_prepare, query))
        {
            return;
        }

        query.bindValue(":store_id", st_db_data.store_id);
        query.bindValue(":hmi_id", st_db_data.hmi_id);
        // query.bindValue(":ocpp_tx_id", st_db_data.ocpp_tx_id);
        query.bindValue(":card_uid", st_db_data.card_uid);
        // query.bindValue(":start_time", st_db_data.start_time);
        // query.bindValue(":end_time", st_db_data.end_time);
        // query.bindValue(":duration_time", st_db_data.duration_time);
        // query.bindValue(":average_kWh", st_db_data.average_kWh);
        // query.bindValue(":soc_start", st_db_data.soc_start);
        // query.bindValue(":soc_end", st_db_data.soc_end);
        query.bindValue(":advance_payment", st_db_data.advance_payment);
        // query.bindValue(":cancel_payment", st_db_data.cancel_payment);
        // query.bindValue(":actual_payment", st_db_data.actual_payment);
        query.bindValue(":unit_price", st_db_data.unit_price);
        query.bindValue(":tariff_type", st_db_data.tariff_type);
        query.bindValue(":session_status", st_db_data.session_status);
        // query.bindValue(":stop_reason", st_db_data.stop_reason);

        bool ok_exec = query.exec();

        if (!this->check_query_exec(ok_exec, query))
        {
            return;
        }

        // session_id 리턴값 포함해서 hmi에게 ack 리턴
        query.next();
        uint64_t session_id = query.value(0).toULongLong();
        bool ret = QMetaObject::invokeMethod(this->p_soc,
                                             "slot_chargingLog_authorized_ack_To_hmi",
                                             Qt::QueuedConnection,
                                             Q_ARG(uint64_t, session_id));
        if (!ret)
        {
            qDebug() << "invok err";
        }
        else
        {
            qDebug() << "invok ok";
        }

        qDebug() << session_id << " :: session_id";
        qDebug() << Q_FUNC_INFO;
    }
    else if (st_db_data.session_status == "charging_start")
    {
        bool ok_prepare = query.prepare("UPDATE charging_log "
                                        "SET ocpp_tx_id = nextval('public.ocpp_tx_id_seq'), "
                                        "start_time = :start_time, "
                                        "soc_start = :soc_start, "
                                        "session_status = :session_status "
                                        "WHERE session_id = :session_id "
                                        "RETURNING ocpp_tx_id");

        qDebug() << st_db_data.session_id << " :: session_id";
        qDebug() << Q_FUNC_INFO;

        if (!this->check_query_prepare(ok_prepare, query))
        {
            return;
        }

        query.bindValue(":session_id", st_db_data.session_id);
        // query.bindValue(":store_id", st_db_data.store_id);
        // query.bindValue(":hmi_id", st_db_data.hmi_id);
        // query.bindValue(":ocpp_tx_id", st_db_data.ocpp_tx_id);
        // query.bindValue(":card_uid", st_db_data.card_uid);
        query.bindValue(":start_time", st_db_data.start_time);
        // query.bindValue(":end_time", st_db_data.end_time);
        // query.bindValue(":duration_time", st_db_data.duration_time);
        // query.bindValue(":average_kWh", st_db_data.average_kWh);
        query.bindValue(":soc_start", st_db_data.soc_start);
        // query.bindValue(":soc_end", st_db_data.soc_end);
        // query.bindValue(":advance_payment", st_db_data.advance_payment);
        // query.bindValue(":cancel_payment", st_db_data.cancel_payment);
        // query.bindValue(":actual_payment", st_db_data.actual_payment);
        // query.bindValue(":unit_price", st_db_data.unit_price);
        // query.bindValue(":tariff_type", st_db_data.tariff_type);
        query.bindValue(":session_status", st_db_data.session_status);
        // query.bindValue(":stop_reason", st_db_data.stop_reason);

        bool ok_exec = query.exec();

        if (!this->check_query_exec(ok_exec, query))
        {
            return;
        }

        // session_id 리턴값 포함해서 hmi에게 ack 리턴
        query.next();
        uint32_t ocpp_tx_id = query.value(0).toUInt();

        QMetaObject::invokeMethod(this->p_soc,
                                  "slot_chargingLog_charging_start_ack_To_hmi",
                                  Qt::QueuedConnection,
                                  Q_ARG(uint32_t, ocpp_tx_id));
    }
    else if (st_db_data.session_status == "charging_finished")
    {
        bool ok_prepare = query.prepare("UPDATE charging_log "
                                        "SET end_time = :end_time, "
                                        "duration_time = :duration_time , "
                                        "average_kwh = :average_kWh, "
                                        "soc_end = :soc_end, "
                                        "cancel_payment = :cancel_payment, "
                                        "actual_payment = :actual_payment, "
                                        "session_status = :session_status "
                                        "WHERE session_id = :session_id ");

        qDebug() << st_db_data.session_id << " :: session_id";
        qDebug() << Q_FUNC_INFO;

        if (!this->check_query_prepare(ok_prepare, query))
        {
            return;
        }

        query.bindValue(":session_id", st_db_data.session_id);
        // query.bindValue(":store_id", st_db_data.store_id);
        // query.bindValue(":hmi_id", st_db_data.hmi_id);
        // query.bindValue(":ocpp_tx_id", st_db_data.ocpp_tx_id);
        // query.bindValue(":card_uid", st_db_data.card_uid);
        // query.bindValue(":start_time", st_db_data.start_time);
        query.bindValue(":end_time", st_db_data.end_time);
        query.bindValue(":duration_time", st_db_data.duration_time);
        query.bindValue(":average_kWh", st_db_data.average_kWh);
        // query.bindValue(":soc_start", st_db_data.soc_start);
        query.bindValue(":soc_end", st_db_data.soc_end);
        // query.bindValue(":advance_payment", st_db_data.advance_payment);
        query.bindValue(":cancel_payment", st_db_data.cancel_payment);
        query.bindValue(":actual_payment", st_db_data.actual_payment);
        // query.bindValue(":unit_price", st_db_data.unit_price);
        // query.bindValue(":tariff_type", st_db_data.tariff_type);
        query.bindValue(":session_status", st_db_data.session_status);
        // query.bindValue(":stop_reason", st_db_data.stop_reason);

        bool ok_exec = query.exec();

        if (!this->check_query_exec(ok_exec, query))
        {
            return;
        }

        QMetaObject::invokeMethod(this->p_soc,
                                  &WK_Soc::slot_chargingLog_charging_finished_ack_To_hmi,
                                  Qt::QueuedConnection);
    }
    else if (st_db_data.session_status == "failed")
    {
    }
    else if (st_db_data.session_status == "timeout")
    {
    }

    return;
}

bool DB_PostgreSQL::check_query_prepare(bool ok, QSqlQuery &query)
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

bool DB_PostgreSQL::check_query_exec(bool ok, QSqlQuery &query)
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

void DB_PostgreSQL::slot_heartbitData_From_soc(heartbit_data st_hb_data)
{
    QSqlQuery query(this->db);
    qDebug() << Q_FUNC_INFO;
    bool ok_prepare = query.prepare("INSERT INTO hmi_current_stat ("
                                    "hmi_id, store_id, ws_connected, "
                                    "last_heartbeat_at, "
                                    "screen_name) "
                                    "VALUES ("
                                    ":hmi_id, :store_id, :ws_connected, "
                                    ":last_heartbeat_at, :screen_name)"
                                    "ON CONFLICT (hmi_id) "
                                    "DO UPDATE SET "
                                    "screen_name = EXCLUDED.screen_name, "
                                    "ws_connected = EXCLUDED.ws_connected, "
                                    "last_heartbeat_at = EXCLUDED.last_heartbeat_at");

    if (!this->check_query_prepare(ok_prepare, query))
    {
        return;
    }

    query.bindValue(":hmi_id", st_hb_data.hmi_id);
    query.bindValue(":store_id", st_hb_data.store_id);
    query.bindValue(":ws_connected", st_hb_data.ws_connected);
    query.bindValue(":last_heartbeat_at", st_hb_data.last_heartbeat_at);
    query.bindValue(":screen_name", st_hb_data.screen_name);

    bool ok_exec = query.exec();

    if (!this->check_query_exec(ok_exec, query))
    {
        return;
    }

    // session_id 리턴값 포함해서 hmi에게 ack 리턴
}

void DB_PostgreSQL::slot_membershipCard_authorized_From_soc(int adv_pay,
                                                            QString card_uid,
                                                            QString request_id)
{
    // 수동 트랜잭션 선언
    this->db.transaction();

    QSqlQuery query(this->db);
    qDebug() << Q_FUNC_INFO;
    bool ok_prepare = query.prepare("SELECT "
                                    "balance_total, "
                                    "balance_available, "
                                    "hold_amount, "
                                    "transaction_state "
                                    "FROM membership_card "
                                    "WHERE card_uid = :card_uid");
    if (!this->check_query_prepare(ok_prepare, query))
    {
        return;
    }

    query.bindValue(":card_uid", card_uid);
    bool ok_exec = query.exec();

    // db 일시적 실패시 재전송
    if (!this->query_exec_recursive(ok_exec, query))
    {
        // 재전송 까지 실패했으면
        this->db.rollback();
        this->query_exec_recursive_err(MB_AUTHORIZED);
        return;
    }

    // 디버깅용
    if (!this->check_query_exec(ok_exec, query))
    {
        return;
    }

    // 있는 카드인지도 확인
    int balance_total = 0;
    int balance_available = 0;
    int hold_amount = 0;
    QString transaction_state;

    if (query.next())
    {
        balance_total = query.value(0).toInt();
        balance_available = query.value(1).toInt();
        hold_amount = query.value(2).toInt();
        transaction_state = query.value(3).toString();
    }
    else
    {
        QMetaObject::invokeMethod(this->p_soc,
                                  "slot_membershipCard_authorized_ack_To_hmi",
                                  Qt::QueuedConnection,
                                  Q_ARG(bool, false),
                                  Q_ARG(QString, "미등록 카드"));

        // 미등록 카드
        return;
    }

    struct membership_log st_mb_log = {0};
    st_mb_log.card_uid = card_uid;
    st_mb_log.event_type = "authorized";
    st_mb_log.amount = adv_pay;
    st_mb_log.balance_available_before = balance_available;
    st_mb_log.hold_amount_before = hold_amount;
    st_mb_log.transaction_state_before = transaction_state;
    st_mb_log.request_id = request_id;

    if (balance_available >= adv_pay)
    {
        balance_available -= adv_pay;
        hold_amount += adv_pay;
        transaction_state = "hold";

        bool ok_prepare2 = query.prepare("UPDATE membership_card "
                                         "SET "
                                         "balance_available = :balance_available, "
                                         "hold_amount = :hold_amount, "
                                         "transaction_state = :transaction_state "
                                         "WHERE card_uid = :card_uid");

        if (!this->check_query_prepare(ok_prepare2, query))
        {
            return;
        }

        query.bindValue(":balance_available", balance_available);
        query.bindValue(":hold_amount", hold_amount);
        query.bindValue(":transaction_state", transaction_state);
        query.bindValue(":card_uid", card_uid);

        bool ok_exec2 = query.exec();

        // db 일시적 실패시 재전송
        if (!this->query_exec_recursive(ok_exec2, query))
        {
            // 재전송 까지 실패했으면
            this->db.rollback();
            this->query_exec_recursive_err(MB_AUTHORIZED);
            return;
        }

        // 디버깅
        if (!this->check_query_exec(ok_exec2, query))
        {
            return;
        }

        st_mb_log.balance_available_after = balance_available;
        st_mb_log.hold_amount_after = hold_amount;
        st_mb_log.transaction_state_after = transaction_state;

        auto ret = this->membershipCard_log_insert_authorized(st_mb_log);

        if (ret.first == true)
        {
            this->db.commit();
            QMetaObject::invokeMethod(this->p_soc,
                                      "slot_membershipCard_authorized_ack_To_hmi",
                                      Qt::QueuedConnection,
                                      Q_ARG(bool, ret.first),
                                      Q_ARG(QString, ret.second));
        }
        else
        {
            // 실패 알림
            this->db.rollback();
            // 아래 함수에서 qml 실패 알림 보냄
            // this->membershipCard_log_insert_authorized(st_mb_log)
        }
    }
    else
    {
        this->db.rollback();
        QMetaObject::invokeMethod(this->p_soc,
                                  "slot_membershipCard_authorized_ack_To_hmi",
                                  Qt::QueuedConnection,
                                  Q_ARG(bool, false),
                                  Q_ARG(QString, "사용 가능 금액 부족"));

        // 결제 금액 부족
    }
    // session_id 리턴값 포함해서 hmi에게 ack 리턴
    return;
}
void DB_PostgreSQL::slot_membershipCard_finished_From_soc(
    int adv_pay, int act_pay, int can_pay, QString card_uid, uint32_t t_id, QString request_id)
{
    // 수동 트랜잭션 선언
    this->db.transaction();

    QSqlQuery query(this->db);
    qDebug() << Q_FUNC_INFO;
    bool ok_prepare = query.prepare("SELECT "
                                    "balance_total, "
                                    "balance_available, "
                                    "hold_amount, "
                                    "transaction_state "
                                    "FROM membership_card "
                                    "WHERE card_uid = :card_uid");
    if (!this->check_query_prepare(ok_prepare, query))
    {
        return;
    }

    query.bindValue(":card_uid", card_uid);

    bool ok_exec = query.exec();

    // db 일시적 실패시 재전송
    if (!this->query_exec_recursive(ok_exec, query))
    {
        // 재전송 까지 실패했으면
        this->db.rollback();
        this->query_exec_recursive_err(MB_FINISHED);
        return;
    }

    // 디버깅용
    if (!this->check_query_exec(ok_exec, query))
    {
        return;
    }

    // 있는 카드인지도 확인
    int balance_total = 0;
    int balance_available = 0;
    int hold_amount = 0;
    QString transaction_state;

    if (query.next())
    {
        balance_total = query.value(0).toInt();
        balance_available = query.value(1).toInt();
        hold_amount = query.value(2).toInt();
        transaction_state = query.value(3).toString();
    }
    else
    {
        qDebug() << card_uid << " not find";
        return;
    }

    if (transaction_state != "hold")
    {
        // 홀드가 아닌대 넘어올 수 가 없음
        qDebug() << transaction_state << " != hold";
        return;
    }

    struct membership_log st_mb_log = {0};
    st_mb_log.card_uid = card_uid;
    st_mb_log.transaction_id = t_id;
    st_mb_log.event_type = "captured";
    st_mb_log.amount = adv_pay;
    st_mb_log.balance_available_before = balance_available;
    st_mb_log.hold_amount_before = hold_amount;
    st_mb_log.transaction_state_before = transaction_state;
    st_mb_log.request_id = request_id;

    // qDebug() << act_pay << " act pay";
    // qDebug() << can_pay << " can pay";
    balance_total -= act_pay;
    balance_available += can_pay;
    hold_amount -= (act_pay + can_pay);
    transaction_state = "captured";

    bool ok_prepare2 = query.prepare("UPDATE membership_card "
                                     "SET "
                                     "balance_total = :balance_total, "
                                     "balance_available = :balance_available, "
                                     "hold_amount = :hold_amount, "
                                     "transaction_state = :transaction_state "
                                     "WHERE card_uid = :card_uid");

    if (!this->check_query_prepare(ok_prepare2, query))
    {
        return;
    }

    query.bindValue(":balance_total", balance_total);
    query.bindValue(":balance_available", balance_available);
    query.bindValue(":hold_amount", hold_amount);
    query.bindValue(":transaction_state", transaction_state);
    query.bindValue(":card_uid", card_uid);

    bool ok_exec2 = query.exec();

    // db 일시적 실패시 재전송
    if (!this->query_exec_recursive(ok_exec2, query))
    {
        // 재전송 까지 실패했으면
        this->db.rollback();
        this->query_exec_recursive_err(MB_FINISHED);
        return;
    }

    // 디버깅
    if (!this->check_query_exec(ok_exec2, query))
    {
        return;
    }

    st_mb_log.balance_available_after = balance_available;
    st_mb_log.hold_amount_after = hold_amount;
    st_mb_log.transaction_state_after = transaction_state;
    /*
    query.bindValue(":balance_available", balance_available);
    query.bindValue(":hold_amount", hold_amount);
    query.bindValue(":transaction_state", transaction_state);
    query.bindValue(":card_uid", card_uid);*/

    bool ret = this->membershipCard_log_insert_finished(st_mb_log);

    if (ret == true)
    {
        this->db.commit();
        QMetaObject::invokeMethod(this->p_soc,
                                  "slot_membershipCard_finished_ack_To_hmi",
                                  Qt::QueuedConnection,
                                  Q_ARG(bool, true));
    }
    else
    {
        this->db.rollback();
    }
    return;
}

QPair<bool, QString> DB_PostgreSQL::membershipCard_log_insert_authorized(const membership_log &m_log)
{
    QSqlQuery query(this->db);
    qDebug() << Q_FUNC_INFO;
    bool ok_prepare = query.prepare("INSERT INTO membership_log ("
                                    "card_uid, "
                                    "transaction_id, "
                                    "event_type, "
                                    "amount, "
                                    "balance_available_before, "
                                    "balance_available_after, "
                                    "hold_amount_before, "
                                    "hold_amount_after, "
                                    "transaction_state_before, "
                                    "transaction_state_after, "
                                    "request_id) "
                                    "VALUES ("
                                    ":card_uid, "
                                    "nextval('membership_tx_seq'), "
                                    ":event_type, "
                                    ":amount, "
                                    ":balance_available_before, "
                                    ":balance_available_after, "
                                    ":hold_amount_before, "
                                    ":hold_amount_after, "
                                    ":transaction_state_before, "
                                    ":transaction_state_after, "
                                    ":request_id) "
                                    "RETURNING transaction_id");

    if (!this->check_query_prepare(ok_prepare, query))
    {
        return QPair<bool, QString>({false, ""});
    }

    query.bindValue(":card_uid", m_log.card_uid);
    query.bindValue(":event_type", m_log.event_type);
    query.bindValue(":amount", m_log.amount);
    query.bindValue(":balance_available_before", m_log.balance_available_before);
    query.bindValue(":balance_available_after", m_log.balance_available_after);
    query.bindValue(":hold_amount_before", m_log.hold_amount_before);
    query.bindValue(":hold_amount_after", m_log.hold_amount_after);
    query.bindValue(":transaction_state_before", m_log.transaction_state_before);
    query.bindValue(":transaction_state_after", m_log.transaction_state_after);
    query.bindValue(":request_id", m_log.request_id);

    bool ok_exec = query.exec();

    QSqlError e = query.lastError();
    if (ok_exec == false && e.nativeErrorCode() == "23505")
    {
        qDebug() << "이미 존재하는 request_id";
        // rollback 상위 함수에서 진행
        return QPair<bool, QString>({false, ""});
    }

    // db 일시적 실패시 재전송
    if (!this->query_exec_recursive(ok_exec, query))
    {
        // 재전송 까지 실패했으면
        // rollback 상위 함수에서 진행
        this->query_exec_recursive_err(MB_AUTHORIZED);
        return QPair<bool, QString>({false, ""});
    }

    // 디버깅
    if (!this->check_query_exec(ok_exec, query))
    {
        // rollback 상위 함수에서 진행
        return QPair<bool, QString>({false, ""});
    }

    if (query.next())
    {
        QPair<bool, QString> qp;
        qp.first = true;
        qp.second = query.value(0).toString();
        qDebug() << qp.second << " :: t_id";
        return qp;
    }

    return QPair<bool, QString>({false, ""});
}

bool DB_PostgreSQL::membershipCard_log_insert_finished(const membership_log &m_log)
{
    QSqlQuery query(this->db);
    qDebug() << Q_FUNC_INFO;
    bool ok_prepare = query.prepare("INSERT INTO membership_log ("
                                    "card_uid, "
                                    "transaction_id, "
                                    "event_type, "
                                    "amount, "
                                    "balance_available_before, "
                                    "balance_available_after, "
                                    "hold_amount_before, "
                                    "hold_amount_after, "
                                    "transaction_state_before, "
                                    "transaction_state_after, "
                                    "request_id) "
                                    "VALUES ("
                                    ":card_uid, "
                                    ":transaction_id, "
                                    ":event_type, "
                                    ":amount, "
                                    ":balance_available_before, "
                                    ":balance_available_after, "
                                    ":hold_amount_before, "
                                    ":hold_amount_after, "
                                    ":transaction_state_before, "
                                    ":transaction_state_after, "
                                    ":request_id) ");

    if (!this->check_query_prepare(ok_prepare, query))
    {
        return false;
    }

    query.bindValue(":card_uid", m_log.card_uid);
    query.bindValue(":transaction_id", m_log.transaction_id);
    query.bindValue(":event_type", m_log.event_type);
    query.bindValue(":amount", m_log.amount);
    query.bindValue(":balance_available_before", m_log.balance_available_before);
    query.bindValue(":balance_available_after", m_log.balance_available_after);
    query.bindValue(":hold_amount_before", m_log.hold_amount_before);
    query.bindValue(":hold_amount_after", m_log.hold_amount_after);
    query.bindValue(":transaction_state_before", m_log.transaction_state_before);
    query.bindValue(":transaction_state_after", m_log.transaction_state_after);
    query.bindValue(":request_id", m_log.request_id);

    bool ok_exec = query.exec();

    QSqlError e = query.lastError();
    if (ok_exec == false && e.nativeErrorCode() == "23505")
    {
        qDebug() << "이미 존재하는 request_id";
        // rollback 상위 함수에서 진행
        return false;
    }

    // db 일시적 실패시 재전송
    if (!this->query_exec_recursive(ok_exec, query))
    {
        // 재전송 까지 실패했으면
        // rollback 상위 함수에서 진행
        this->query_exec_recursive_err(MB_FINISHED);
        return false;
    }

    // 디버깅
    if (!this->check_query_exec(ok_exec, query))
    {
        return false;
    }

    return true;
}

bool DB_PostgreSQL::query_exec_recursive(bool ok_exec, QSqlQuery &query)
{
    bool ok_recursive = false;
    if (ok_exec == false)
    {
        QSqlError e = query.lastError();
        QString err_code = e.nativeErrorCode();
        int query_cnt = 0;

        while (query_cnt < 3)
        {
            if (e.type() == QSqlError::ConnectionError)
            {
                // 재전송
                ok_recursive = query.exec();
                if (ok_recursive == true)
                {
                    return true;
                }
            }
            else if (e.type() == QSqlError::TransactionError)
            {
                if (err_code == "40001" || err_code == "40P01")
                {
                    // 재전송
                    ok_recursive = query.exec();
                    if (ok_recursive == true)
                    {
                        return true;
                    }
                }
            }
            QThread::msleep(3000);
            query_cnt++;
        }
    }
    else
    {
        return true;
    }

    return false;
}

void DB_PostgreSQL::query_exec_recursive_err(RECURSIVE_ERR err)
{
    if (err == MB_AUTHORIZED)
    {
        // 실패 알림
        QMetaObject::invokeMethod(this->p_soc,
                                  "slot_membershipCard_authorized_ack_To_hmi",
                                  Qt::QueuedConnection,
                                  Q_ARG(bool, false),
                                  Q_ARG(QString, "DB 연결 실패"));
    }
    else if (err == MB_FINISHED)
    {
        // sqllight에 저장하고 타이머로 재전송 할거 있는지 확인해서 재전송
        // finished는 이미 홀드 잡은거 처리하는거라서
        // 전송에러 말고 다른거 없음

        QMetaObject::invokeMethod(this->p_soc,
                                  "slot_membershipCard_finished_ack_To_hmi",
                                  Qt::QueuedConnection,
                                  Q_ARG(bool, false));
    }
    return;
}
