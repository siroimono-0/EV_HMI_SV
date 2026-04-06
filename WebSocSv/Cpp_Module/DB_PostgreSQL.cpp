#include "DB_PostgreSQL.h"
#include "Hub.h"
#include "WK_Soc.h"

DB_PostgreSQL::DB_PostgreSQL(QObject *parent)
    : QObject{parent}
{
    this->path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    this->p_timer_lite = new QTimer();
    this->p_timer_lite->start(60000);
    connect(this->p_timer_lite, &QTimer::timeout, this, &DB_PostgreSQL::backUp_register_chargingLog);
    connect(this->p_timer_lite,
            &QTimer::timeout,
            this,
            &DB_PostgreSQL::backUp_register_membershipCard_finished);
}

DB_PostgreSQL::~DB_PostgreSQL()
{
    return;
}

void DB_PostgreSQL::set_p_Module(Cpp_Module *module)
{
    this->p_Module = module;
    return;
}

void DB_PostgreSQL::slot_set_p_soc(Hub *soc)
{
    this->p_soc = soc;
    connect(this,
            &DB_PostgreSQL::sig_charging_log_select_ret,
            this->p_soc,
            &Hub::slot_charging_log_select_ret_From_DB__To_admin);

    connect(this,
            &DB_PostgreSQL::sig_hmi_current_stat_select_ret,
            this->p_soc,
            &Hub::slot_hmi_current_stat_select_ret_From_DB__To_admin);

    connect(this,
            &DB_PostgreSQL::sig_hmi_device_select_ret,
            this->p_soc,
            &Hub::slot_hmi_device_select_ret_From_DB__To_admin);

    connect(this,
            &DB_PostgreSQL::sig_membership_card_select_ret,
            this->p_soc,
            &Hub::slot_membership_card_select_ret_From_DB__To_admin);

    connect(this,
            &DB_PostgreSQL::sig_membership_log_select_ret,
            this->p_soc,
            &Hub::slot_membership_log_select_ret_From_DB__To_admin);

    connect(this,
            &DB_PostgreSQL::sig_store_user_select_ret,
            this->p_soc,
            &Hub::slot_store_user_select_ret_From_DB__To_admin);
    return;
}

void DB_PostgreSQL::createDB()
{
    qDebug() << QSqlDatabase::drivers();
    qDebug() << QLibraryInfo::path(QLibraryInfo::PluginsPath);

    this->db = QSqlDatabase::addDatabase("QPSQL", "DB_THREAD_CONN_PG");
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

    this->db_lite = QSqlDatabase::addDatabase("QSQLITE", "DB_THREAD_CONN_SQLITE");
    this->db_lite.setDatabaseName(this->path + "/db_lite.sqlite3");

    qDebug() << "db path =" << db_lite.databaseName();

    if (this->db_lite.open())
    {
        qDebug() << "db_light open";
    }
    else
    {
        // qDebug() << "db false";
        qDebug() << this->db_lite.lastError().text();
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

// 백업 X
bool DB_PostgreSQL::slot_query_find_hello_hmi(const QString storeId, const QString hmiId)
{
    if (!this->db_openCheck())
    {
        return false;
    }

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

// 백업 O // HMI 메시지 전달 없음
void DB_PostgreSQL::slot_chargingLog_From_soc(const mp_wk_key key, db_data st_db_data)
{
    if (!this->db_openCheck())
    {
        // db 에러 났어도 qml일단 진행
        if (st_db_data.session_status == "authorized")
        {
            this->chargingLog_sqlite_backUp(st_db_data);
            this->chargingLog_authorized_invok(key);
        }
        else if (st_db_data.session_status == "charging_start")
        {
            this->chargingLog_sqlite_backUp(st_db_data);
            this->chargingLog_start_invok(key, -1);
        }
        else if (st_db_data.session_status == "charging_finished")
        {
            this->chargingLog_sqlite_backUp(st_db_data);
            this->chargingLog_finished_invok(key);
        }

        return;
    }

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
        qDebug() << "충전로그 인증 업데이트 ::::::::::::::::::::";
        bool ok_prepare = query.prepare(
            "INSERT INTO charging_log (store_id, hmi_id, ocpp_tx_id, card_uid, start_time, "
            "end_time, "
            "duration_time, average_kWh, soc_start, soc_end, advance_payment, cancel_payment, "
            "actual_payment, unit_price, tariff_type, session_status, stop_reason, local_tx_id) "
            "VALUES "
            "(:store_id, "
            ":hmi_id, :ocpp_tx_id, :card_uid, :start_time, :end_time, "
            ":duration_time, :average_kWh, :soc_start, :soc_end, :advance_payment, "
            ":cancel_payment, "
            ":actual_payment, :unit_price, :tariff_type, :session_status, :stop_reason, "
            ":local_tx_id)");

        // 디버깅
        if (!this->check_query_prepare(ok_prepare, query))
        {
            this->chargingLog_sqlite_backUp(st_db_data);
            this->chargingLog_authorized_invok(key);
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
        query.bindValue(":local_tx_id", st_db_data.local_tx_id);

        bool ok_exec = query.exec();

        if (!this->check_query_exec(ok_exec, query))
        {
            this->chargingLog_sqlite_backUp(st_db_data);
            this->chargingLog_authorized_invok(key);
            return;
        }

        this->chargingLog_authorized_invok(key);
        qDebug() << Q_FUNC_INFO;
    }
    else if (st_db_data.session_status == "charging_start")
    {
        qDebug() << "충전로그 시작 업데이트 ::::::::::::::::::::";
        bool ok_prepare = query.prepare(
            "INSERT INTO charging_log (store_id, hmi_id, ocpp_tx_id, card_uid, start_time, "
            "end_time, "
            "duration_time, average_kWh, soc_start, soc_end, advance_payment, cancel_payment, "
            "actual_payment, unit_price, tariff_type, session_status, stop_reason, local_tx_id) "
            "VALUES "
            "(:store_id, "
            ":hmi_id, nextval('public.ocpp_tx_id_seq'), :card_uid, :start_time, :end_time, "
            ":duration_time, :average_kWh, :soc_start, :soc_end, :advance_payment, "
            ":cancel_payment, "
            ":actual_payment, :unit_price, :tariff_type, :session_status, :stop_reason, "
            ":local_tx_id) "
            "RETURNING ocpp_tx_id");

        if (!this->check_query_prepare(ok_prepare, query))
        {
            // 아직 ocpp_tx 못받음 그런대 에러나도 일단 qml 진행 시켜야댐
            // 어자피 노답임
            // 일관성 있게 null
            /*
             -1 처리 -> HMI에서 받고 -1이면 set 안함
             해당 함수 백업 실행 인지 아닌지 매개변수 판별
            백업 실행이면 ocpp << insert안시킴 -> null 통일
             */

            this->chargingLog_sqlite_backUp(st_db_data);
            this->chargingLog_start_invok(key, -1);

            return;
        }

        query.bindValue(":store_id", st_db_data.store_id);
        query.bindValue(":hmi_id", st_db_data.hmi_id);
        // query.bindValue(":ocpp_tx_id", st_db_data.ocpp_tx_id);
        query.bindValue(":card_uid", st_db_data.card_uid);
        query.bindValue(":start_time", st_db_data.start_time);
        // query.bindValue(":end_time", st_db_data.end_time);
        // query.bindValue(":duration_time", st_db_data.duration_time);
        // query.bindValue(":average_kWh", st_db_data.average_kWh);
        query.bindValue(":soc_start", st_db_data.soc_start);
        // query.bindValue(":soc_end", st_db_data.soc_end);
        query.bindValue(":advance_payment", st_db_data.advance_payment);
        // query.bindValue(":cancel_payment", st_db_data.cancel_payment);
        // query.bindValue(":actual_payment", st_db_data.actual_payment);
        query.bindValue(":unit_price", st_db_data.unit_price);
        query.bindValue(":tariff_type", st_db_data.tariff_type);
        query.bindValue(":session_status", st_db_data.session_status);
        // query.bindValue(":stop_reason", st_db_data.stop_reason);
        query.bindValue(":local_tx_id", st_db_data.local_tx_id);

        bool ok_exec = query.exec();

        if (!this->check_query_exec(ok_exec, query))
        {
            this->chargingLog_sqlite_backUp(st_db_data);
            this->chargingLog_start_invok(key, -1);
            return;
        }

        // session_id 리턴값 포함해서 hmi에게 ack 리턴
        query.next();
        uint32_t ocpp_tx_id = query.value(0).toUInt();

        this->chargingLog_start_invok(key, ocpp_tx_id);
    }
    else if (st_db_data.session_status == "charging_finished")
    {
        qDebug() << "충전로그 끝 업데이트 ::::::::::::::::::::";
        bool ok_prepare = query.prepare(
            "INSERT INTO charging_log (store_id, hmi_id, ocpp_tx_id, card_uid, start_time, "
            "end_time, "
            "duration_time, average_kWh, soc_start, soc_end, advance_payment, cancel_payment, "
            "actual_payment, unit_price, tariff_type, session_status, stop_reason, local_tx_id) "
            "VALUES "
            "(:store_id, "
            ":hmi_id, :ocpp_tx_id, :card_uid, :start_time, :end_time, "
            ":duration_time, :average_kWh, :soc_start, :soc_end, :advance_payment, "
            ":cancel_payment, "
            ":actual_payment, :unit_price, :tariff_type, :session_status, :stop_reason, "
            ":local_tx_id) "
            "RETURNING ocpp_tx_id");

        if (!this->check_query_prepare(ok_prepare, query))
        {
            this->chargingLog_sqlite_backUp(st_db_data);
            this->chargingLog_finished_invok(key);
            return;
        }

        query.bindValue(":store_id", st_db_data.store_id);
        query.bindValue(":hmi_id", st_db_data.hmi_id);
        query.bindValue(":ocpp_tx_id", st_db_data.ocpp_tx_id);
        query.bindValue(":card_uid", st_db_data.card_uid);
        query.bindValue(":start_time", st_db_data.start_time);
        query.bindValue(":end_time", st_db_data.end_time);
        query.bindValue(":duration_time", st_db_data.duration_time);
        query.bindValue(":average_kWh", st_db_data.average_kWh);
        query.bindValue(":soc_start", st_db_data.soc_start);
        query.bindValue(":soc_end", st_db_data.soc_end);
        query.bindValue(":advance_payment", st_db_data.advance_payment);
        query.bindValue(":cancel_payment", st_db_data.cancel_payment);
        query.bindValue(":actual_payment", st_db_data.actual_payment);
        query.bindValue(":unit_price", st_db_data.unit_price);
        query.bindValue(":tariff_type", st_db_data.tariff_type);
        query.bindValue(":session_status", st_db_data.session_status);
        query.bindValue(":stop_reason", st_db_data.stop_reason);
        query.bindValue(":local_tx_id", st_db_data.local_tx_id);

        bool ok_exec = query.exec();

        if (!this->check_query_exec(ok_exec, query))
        {
            this->chargingLog_sqlite_backUp(st_db_data);
            this->chargingLog_finished_invok(key);
            return;
        }

        this->chargingLog_finished_invok(key);
    }
    else if (st_db_data.session_status == "failed")
    {
        // ??
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

// 백업 X
void DB_PostgreSQL::slot_heartbitData_From_soc(heartbit_data st_hb_data)
{
    if (!this->db_openCheck())
    {
        return;
    }

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

// 백업 X
// 이게 처음 시작하는 트랜젝션인대 어떻게 다른게 먼져 동작?
void DB_PostgreSQL::slot_membershipCard_authorized_From_soc(const mp_wk_key key,
                                                            int adv_pay,
                                                            QString card_uid,
                                                            QString request_id)
{
    // qDebug() << " 1_____ ";
    if (!this->db_openCheck())
    {
        this->membershipCard_authorized_false_msg(key);
        return;
    }

    // qDebug() << " 2_____ ";
    // qDebug() << "before transaction, lastError =" << this->db.lastError().text();
    // 수동 트랜잭션 선언
    bool ok_tx = this->db.transaction();
    // qDebug() << "ok_tx =" << ok_tx;
    // qDebug() << "after transaction, lastError =" << this->db.lastError().text();
    if (ok_tx == false)
    {
        qDebug() << "transaction failed:" << this->db.lastError().text();
        this->db.rollback();
        this->membershipCard_authorized_false_msg(key);

        return;
    }

    QSqlQuery query(this->db);
    qDebug() << Q_FUNC_INFO;
    bool ok_prepare = query.prepare("SELECT "
                                    "balance_total, "
                                    "balance_available, "
                                    "hold_amount, "
                                    "transaction_state "
                                    "FROM membership_card "
                                    "WHERE card_uid = :card_uid");

    // 디버깅
    if (!this->check_query_prepare(ok_prepare, query))
    {
        this->db.rollback();
        this->membershipCard_authorized_false_msg(key);
        return;
    }

    query.bindValue(":card_uid", card_uid);
    bool ok_exec = query.exec();

    // db 일시적 실패시 재전송
    if (!ok_exec)
    {
        this->db.rollback();
        this->membershipCard_authorized_false_msg(key);
        return;
    }

    // 디버깅용
    if (!this->check_query_exec(ok_exec, query))
    {
        this->db.rollback();
        this->membershipCard_authorized_false_msg(key);
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

        if (transaction_state == "hold")
        {
            this->db.rollback();
            QMetaObject::invokeMethod(this->p_soc,
                                      "slot_membershipCard_authorized_ack_To_hmi",
                                      Qt::QueuedConnection,
                                      Q_ARG(mp_wk_key, key),
                                      Q_ARG(bool, false),
                                      Q_ARG(QString, "현재 충전중인 카드입니다."));
            return;
        }
    }
    else
    {
        this->db.rollback();
        QMetaObject::invokeMethod(this->p_soc,
                                  "slot_membershipCard_authorized_ack_To_hmi",
                                  Qt::QueuedConnection,
                                  Q_ARG(mp_wk_key, key),
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
            this->db.rollback();
            this->membershipCard_authorized_false_msg(key);
            return;
        }

        query.bindValue(":balance_available", balance_available);
        query.bindValue(":hold_amount", hold_amount);
        query.bindValue(":transaction_state", transaction_state);
        query.bindValue(":card_uid", card_uid);

        bool ok_exec2 = query.exec();

        // 디버깅
        if (!this->check_query_exec(ok_exec2, query))
        {
            this->db.rollback();
            this->membershipCard_authorized_false_msg(key);
            return;
        }

        // db 일시적 실패시 재전송
        if (!ok_exec2)
        {
            // 재전송 까지 실패했으면
            this->db.rollback();
            this->membershipCard_authorized_false_msg(key);
            return;
        }

        st_mb_log.balance_available_after = balance_available;
        st_mb_log.hold_amount_after = hold_amount;
        st_mb_log.transaction_state_after = transaction_state;

        auto ret = this->membershipCard_log_insert_authorized(st_mb_log);

        if (ret.first == true)
        {
            bool commit_ret = this->db.commit();
            if (commit_ret == false)
            {
                this->db.rollback();
                this->membershipCard_authorized_false_msg(key);
                qDebug() << "commit failed:" << this->db.lastError().text();
            }
            else
            {
                qDebug() << "커밋 성공함 ....";
            }
            QMetaObject::invokeMethod(this->p_soc,
                                      "slot_membershipCard_authorized_ack_To_hmi",
                                      Qt::QueuedConnection,
                                      Q_ARG(mp_wk_key, key),
                                      Q_ARG(bool, ret.first),
                                      Q_ARG(QString, ret.second));
        }
        else
        {
            // 실패 알림
            this->db.rollback();
            this->membershipCard_authorized_false_msg(key);
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
                                  Q_ARG(mp_wk_key, key),
                                  Q_ARG(bool, false),
                                  Q_ARG(QString, "사용 가능 금액 부족"));

        // 결제 금액 부족
    }
    // session_id 리턴값 포함해서 hmi에게 ack 리턴
    return;
}

// 백업 X
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

// 백업 O
void DB_PostgreSQL::slot_membershipCard_finished_From_soc(const mp_wk_key key,
                                                          int adv_pay,
                                                          int act_pay,
                                                          int can_pay,
                                                          QString card_uid,
                                                          uint32_t t_id,
                                                          QString request_id)
{
    // 전송 실패 대비용 struct 초기화
    struct membership_backUp_sqlite st_back = {0};
    st_back.card_uid = card_uid;
    st_back.adv_pay = adv_pay;
    st_back.act_pay = act_pay;
    st_back.can_pay = can_pay;
    st_back.t_id = t_id;
    st_back.request_id = request_id;

    if (!this->db_openCheck())
    {
        this->membershipCard_finished_sqlite_backUp(st_back);
        this->membershipCard_finished_stat(key, false);
        return;
    }

    // 수동 트랜잭션 선언
    if (!this->db.transaction())
    {
        this->membershipCard_finished_sqlite_backUp(st_back);
        this->membershipCard_finished_stat(key, false);
        this->db.rollback();
        return;
    }

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
        this->membershipCard_finished_sqlite_backUp(st_back);
        this->membershipCard_finished_stat(key, false);
        this->db.rollback();
        return;
    }

    query.bindValue(":card_uid", card_uid);

    bool ok_exec = query.exec();

    // 디버깅용
    if (!this->check_query_exec(ok_exec, query))
    {
        this->membershipCard_finished_sqlite_backUp(st_back);
        this->membershipCard_finished_stat(key, false);
        this->db.rollback();
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
        // this->membershipCard_finished_stat(false);
        this->db.rollback();
        qDebug() << card_uid << " not find";
        return;
    }

    if (transaction_state != "hold")
    {
        this->db.rollback();
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

    // 디버깅용
    if (!this->check_query_prepare(ok_prepare2, query))
    {
        this->membershipCard_finished_sqlite_backUp(st_back);
        this->membershipCard_finished_stat(key, false);
        this->db.rollback();
        return;
    }

    query.bindValue(":balance_total", balance_total);
    query.bindValue(":balance_available", balance_available);
    query.bindValue(":hold_amount", hold_amount);
    query.bindValue(":transaction_state", transaction_state);
    query.bindValue(":card_uid", card_uid);

    bool ok_exec2 = query.exec();

    // 디버깅
    if (!this->check_query_exec(ok_exec2, query))
    {
        this->membershipCard_finished_sqlite_backUp(st_back);
        this->membershipCard_finished_stat(key, false);
        this->db.rollback();
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
        bool ret_commit = this->db.commit();
        if (!ret_commit)
        {
            this->membershipCard_finished_sqlite_backUp(st_back);
            this->membershipCard_finished_stat(key, false);
        }
        else
        {
            this->membershipCard_finished_stat(key, true);
        }
    }
    else
    {
        this->membershipCard_finished_sqlite_backUp(st_back);
        this->membershipCard_finished_stat(key, false);
        this->db.rollback();
        // this->membershipCard_finished_sqlite_backUp(st_back);
    }
    return;
}

// 상단 함수에서 백업한거 기반으로 재실행댐
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

    // 디버깅
    if (!this->check_query_exec(ok_exec, query))
    {
        return false;
    }

    return true;
}

void DB_PostgreSQL::membershipCard_finished_sqlite_backUp(const membership_backUp_sqlite back_data)
{
    qDebug() << Q_FUNC_INFO;
    QSqlQuery query(this->db_lite);

    bool ok_prepare = query.prepare("INSERT INTO membership_card "
                                    "(card_uid, adv_pay, act_pay, can_pay, "
                                    "t_id, request_id, state) "
                                    "VALUES (:card_uid, :adv_pay, "
                                    ":act_pay, :can_pay, "
                                    ":t_id, :request_id, :state)");

    // 디버깅
    if (!this->check_query_prepare(ok_prepare, query))
    {
        return;
    }

    query.bindValue(":card_uid", back_data.card_uid);
    query.bindValue(":adv_pay", back_data.adv_pay);
    query.bindValue(":act_pay", back_data.act_pay);
    query.bindValue(":can_pay", back_data.can_pay);
    query.bindValue(":t_id", back_data.t_id);
    query.bindValue(":request_id", back_data.request_id);
    query.bindValue(":state", "pending");

    bool ok_exec = query.exec();

    // 디버깅
    if (!this->check_query_exec(ok_exec, query))
    {
        return;
    }

    return;
}

void DB_PostgreSQL::chargingLog_sqlite_backUp(const db_data back_data)
{
    qDebug() << Q_FUNC_INFO;
    QSqlQuery query(this->db_lite);

    bool ok_prepare = query.prepare(
        "INSERT INTO charging_log (store_id, hmi_id, ocpp_tx_id, card_uid, start_time, "
        "end_time, "
        "duration_time, average_kWh, soc_start, soc_end, advance_payment, cancel_payment, "
        "actual_payment, unit_price, tariff_type, session_status, stop_reason, local_tx_id, state) "
        "VALUES "
        "(:store_id, "
        ":hmi_id, :ocpp_tx_id, :card_uid, :start_time, :end_time, "
        ":duration_time, :average_kWh, :soc_start, :soc_end, :advance_payment, "
        ":cancel_payment, "
        ":actual_payment, :unit_price, :tariff_type, :session_status, :stop_reason, "
        ":local_tx_id, :state) "
        "RETURNING ocpp_tx_id");

    if (!this->check_query_prepare(ok_prepare, query))
    {
        return;
    }

    query.bindValue(":store_id", back_data.store_id);
    query.bindValue(":hmi_id", back_data.hmi_id);
    query.bindValue(":ocpp_tx_id", back_data.ocpp_tx_id);
    query.bindValue(":card_uid", back_data.card_uid);
    query.bindValue(":start_time", back_data.start_time);
    query.bindValue(":end_time", back_data.end_time);
    query.bindValue(":duration_time", back_data.duration_time);
    query.bindValue(":average_kWh", back_data.average_kWh);
    query.bindValue(":soc_start", back_data.soc_start);
    query.bindValue(":soc_end", back_data.soc_end);
    query.bindValue(":advance_payment", back_data.advance_payment);
    query.bindValue(":cancel_payment", back_data.cancel_payment);
    query.bindValue(":actual_payment", back_data.actual_payment);
    query.bindValue(":unit_price", back_data.unit_price);
    query.bindValue(":tariff_type", back_data.tariff_type);
    query.bindValue(":session_status", back_data.session_status);
    query.bindValue(":stop_reason", back_data.stop_reason);
    query.bindValue(":local_tx_id", back_data.local_tx_id);
    query.bindValue(":state", "pending");

    bool ok_exec = query.exec();

    // 디버깅
    if (!this->check_query_exec(ok_exec, query))
    {
        return;
    }

    return;
}

bool DB_PostgreSQL::db_openCheck()
{
    if (!this->db.isOpen())
    {
        if (!this->db.open())
        {
            return false;
        }
    }
    return true;
}

void DB_PostgreSQL::membershipCard_authorized_false_msg(const mp_wk_key key)
{
    QMetaObject::invokeMethod(this->p_soc,
                              "slot_membershipCard_authorized_ack_To_hmi",
                              Qt::QueuedConnection,
                              Q_ARG(mp_wk_key, key),
                              Q_ARG(bool, false),
                              Q_ARG(QString, "잠시 후 재시도 해주세요"));
    return;
}

void DB_PostgreSQL::membershipCard_finished_stat(const mp_wk_key key, bool stat)
{
    QMetaObject::invokeMethod(this->p_soc,
                              "slot_membershipCard_finished_ack_To_hmi",
                              Qt::QueuedConnection,
                              Q_ARG(mp_wk_key, key),
                              Q_ARG(bool, stat));
    return;
}

void DB_PostgreSQL::chargingLog_authorized_invok(const mp_wk_key key)
{
    QMetaObject::invokeMethod(this->p_soc,
                              "slot_chargingLog_authorized_ack_To_hmi",
                              Qt::QueuedConnection,
                              Q_ARG(mp_wk_key, key));
    return;
}

void DB_PostgreSQL::chargingLog_start_invok(const mp_wk_key key, uint32_t ocpp_tx)
{
    QMetaObject::invokeMethod(this->p_soc,
                              "slot_chargingLog_charging_start_ack_To_hmi",
                              Qt::QueuedConnection,
                              Q_ARG(mp_wk_key, key),
                              Q_ARG(uint32_t, ocpp_tx));
    return;
}

void DB_PostgreSQL::chargingLog_finished_invok(const mp_wk_key key)
{
    QMetaObject::invokeMethod(this->p_soc,
                              "slot_chargingLog_charging_finished_ack_To_hmi",
                              Qt::QueuedConnection,
                              Q_ARG(mp_wk_key, key));
    return;
}

// sqlite 업데이트 할 때 구분할 키 필요함
// pq 에서 row 뽑을필요 없음
// sqlite 에서 row 자동 생성함
// 등록하고 그 값으로 업데이트 시키면댐
int DB_PostgreSQL::chargingLog_backUp_upDate_QPSQL(db_data st_db_data)
{
    if (!this->db_openCheck())
    {
        return -1;
    }

    QSqlQuery query(this->db);

    qDebug() << Q_FUNC_INFO;
    if (st_db_data.session_status == "authorized")
    {
        qDebug() << "충전로그 인증 백업 큐 실행 ::::::::::::::::::::";
        bool ok_prepare = query.prepare(
            "INSERT INTO charging_log (store_id, hmi_id, ocpp_tx_id, card_uid, start_time, "
            "end_time, "
            "duration_time, average_kWh, soc_start, soc_end, advance_payment, cancel_payment, "
            "actual_payment, unit_price, tariff_type, session_status, stop_reason, local_tx_id) "
            "VALUES "
            "(:store_id, "
            ":hmi_id, :ocpp_tx_id, :card_uid, :start_time, :end_time, "
            ":duration_time, :average_kWh, :soc_start, :soc_end, :advance_payment, "
            ":cancel_payment, "
            ":actual_payment, :unit_price, :tariff_type, :session_status, :stop_reason, "
            ":local_tx_id) "
            "RETURNING row_id");

        // 디버깅
        if (!this->check_query_prepare(ok_prepare, query))
        {
            return -1;
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
        query.bindValue(":local_tx_id", st_db_data.local_tx_id);

        bool ok_exec = query.exec();

        if (!this->check_query_exec(ok_exec, query))
        {
            return -1;
        }

        qDebug() << Q_FUNC_INFO;
    }
    else if (st_db_data.session_status == "charging_start")
    {
        qDebug() << "충전로그 시작 백업 큐 ::::::::::::::::::::";
        bool ok_prepare = query.prepare(
            "INSERT INTO charging_log (store_id, hmi_id, card_uid, start_time, "
            "end_time, "
            "duration_time, average_kWh, soc_start, soc_end, advance_payment, cancel_payment, "
            "actual_payment, unit_price, tariff_type, session_status, stop_reason, local_tx_id) "
            "VALUES "
            "(:store_id, "
            ":hmi_id, :card_uid, :start_time, :end_time, "
            ":duration_time, :average_kWh, :soc_start, :soc_end, :advance_payment, "
            ":cancel_payment, "
            ":actual_payment, :unit_price, :tariff_type, :session_status, :stop_reason, "
            ":local_tx_id) "
            "RETURNING row_id");

        if (!this->check_query_prepare(ok_prepare, query))
        {
            return -1;
        }

        query.bindValue(":store_id", st_db_data.store_id);
        query.bindValue(":hmi_id", st_db_data.hmi_id);
        // query.bindValue(":ocpp_tx_id", st_db_data.ocpp_tx_id);
        query.bindValue(":card_uid", st_db_data.card_uid);
        query.bindValue(":start_time", st_db_data.start_time);
        // query.bindValue(":end_time", st_db_data.end_time);
        // query.bindValue(":duration_time", st_db_data.duration_time);
        // query.bindValue(":average_kWh", st_db_data.average_kWh);
        query.bindValue(":soc_start", st_db_data.soc_start);
        // query.bindValue(":soc_end", st_db_data.soc_end);
        query.bindValue(":advance_payment", st_db_data.advance_payment);
        // query.bindValue(":cancel_payment", st_db_data.cancel_payment);
        // query.bindValue(":actual_payment", st_db_data.actual_payment);
        query.bindValue(":unit_price", st_db_data.unit_price);
        query.bindValue(":tariff_type", st_db_data.tariff_type);
        query.bindValue(":session_status", st_db_data.session_status);
        // query.bindValue(":stop_reason", st_db_data.stop_reason);
        query.bindValue(":local_tx_id", st_db_data.local_tx_id);

        bool ok_exec = query.exec();

        if (!this->check_query_exec(ok_exec, query))
        {
            return -1;
        }
    }
    else if (st_db_data.session_status == "charging_finished")
    {
        qDebug() << "충전로그 끝 업데이트 ::::::::::::::::::::";
        bool ok_prepare = query.prepare(
            "INSERT INTO charging_log (store_id, hmi_id, card_uid, start_time, "
            "end_time, "
            "duration_time, average_kWh, soc_start, soc_end, advance_payment, cancel_payment, "
            "actual_payment, unit_price, tariff_type, session_status, stop_reason, local_tx_id) "
            "VALUES "
            "(:store_id, "
            ":hmi_id, :card_uid, :start_time, :end_time, "
            ":duration_time, :average_kWh, :soc_start, :soc_end, :advance_payment, "
            ":cancel_payment, "
            ":actual_payment, :unit_price, :tariff_type, :session_status, :stop_reason, "
            ":local_tx_id) "
            "RETURNING row_id");

        if (!this->check_query_prepare(ok_prepare, query))
        {
            return -1;
        }

        query.bindValue(":store_id", st_db_data.store_id);
        query.bindValue(":hmi_id", st_db_data.hmi_id);
        // query.bindValue(":ocpp_tx_id", st_db_data.ocpp_tx_id);
        query.bindValue(":card_uid", st_db_data.card_uid);
        query.bindValue(":start_time", st_db_data.start_time);
        query.bindValue(":end_time", st_db_data.end_time);
        query.bindValue(":duration_time", st_db_data.duration_time);
        query.bindValue(":average_kWh", st_db_data.average_kWh);
        query.bindValue(":soc_start", st_db_data.soc_start);
        query.bindValue(":soc_end", st_db_data.soc_end);
        query.bindValue(":advance_payment", st_db_data.advance_payment);
        query.bindValue(":cancel_payment", st_db_data.cancel_payment);
        query.bindValue(":actual_payment", st_db_data.actual_payment);
        query.bindValue(":unit_price", st_db_data.unit_price);
        query.bindValue(":tariff_type", st_db_data.tariff_type);
        query.bindValue(":session_status", st_db_data.session_status);
        query.bindValue(":stop_reason", st_db_data.stop_reason);
        query.bindValue(":local_tx_id", st_db_data.local_tx_id);

        bool ok_exec = query.exec();

        if (!this->check_query_exec(ok_exec, query))
        {
            return -1;
        }

        // this->chargingLog_finished_invok();
    }
    else if (st_db_data.session_status == "failed")
    {
        // ??
    }
    else if (st_db_data.session_status == "timeout")
    {
    }
    query.next();
    int row_id = query.value(0).toInt();

    return row_id;
}

// pq에서 실패했으면 카드 홀드 상태임
bool DB_PostgreSQL::membershipCard_finished_backup_upDate_QPSQL(
    int adv_pay, int act_pay, int can_pay, QString card_uid, uint32_t t_id, QString request_id)
{
    if (!this->db_openCheck())
    {
        return false;
    }

    // 수동 트랜잭션 선언
    if (!this->db.transaction())
    {
        this->db.rollback();
        return false;
    }

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
        this->db.rollback();
        return false;
    }

    query.bindValue(":card_uid", card_uid);

    bool ok_exec = query.exec();

    // 디버깅용
    if (!this->check_query_exec(ok_exec, query))
    {
        this->db.rollback();
        return false;
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

    // 디버깅용
    if (!this->check_query_prepare(ok_prepare2, query))
    {
        this->db.rollback();
        return false;
    }

    query.bindValue(":balance_total", balance_total);
    query.bindValue(":balance_available", balance_available);
    query.bindValue(":hold_amount", hold_amount);
    query.bindValue(":transaction_state", transaction_state);
    query.bindValue(":card_uid", card_uid);

    bool ok_exec2 = query.exec();

    // 디버깅
    if (!this->check_query_exec(ok_exec2, query))
    {
        this->db.rollback();
        return false;
    }

    st_mb_log.balance_available_after = balance_available;
    st_mb_log.hold_amount_after = hold_amount;
    st_mb_log.transaction_state_after = transaction_state;

    bool ret = this->membershipCard_log_insert_finished(st_mb_log);

    if (ret == true)
    {
        bool ret_commit = this->db.commit();
        if (!ret_commit)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    else
    {
        this->db.rollback();
        return false;
    }
    return true;
}

void DB_PostgreSQL::backUp_register_chargingLog()
{
    QSqlQuery query(this->db_lite);
    QString qs_state = "pending";
    qDebug() << "SQLITE 백업 큐 가져옴 ::::::::::::::::::::";
    bool ok_prepare = query.prepare("SELECT * FROM charging_log WHERE state = :state");

    // 디버깅
    if (!this->check_query_prepare(ok_prepare, query))
    {
        return;
    }

    query.bindValue(":state", qs_state);

    bool b_ok_exec = query.exec();

    if (!this->check_query_exec(b_ok_exec, query))
    {
        return;
    }

    while (query.next())
    {
        int row_id = 0;
        struct db_data st_db_data = {0};
        row_id = query.value(0).toInt();
        st_db_data.store_id = query.value(1).toInt();
        st_db_data.hmi_id = query.value(2).toString();
        st_db_data.ocpp_tx_id = query.value(3).toInt();
        st_db_data.card_uid = query.value(4).toString();
        st_db_data.start_time = query.value(5).toString();
        st_db_data.end_time = query.value(6).toString();
        st_db_data.duration_time = query.value(7).toString();
        st_db_data.average_kWh = query.value(8).toReal();
        st_db_data.soc_start = query.value(9).toReal();
        st_db_data.soc_end = query.value(10).toReal();
        st_db_data.advance_payment = query.value(11).toInt();
        st_db_data.cancel_payment = query.value(12).toInt();
        st_db_data.actual_payment = query.value(13).toInt();
        st_db_data.unit_price = query.value(14).toInt();
        st_db_data.tariff_type = query.value(15).toString();
        st_db_data.session_status = query.value(16).toString();
        st_db_data.stop_reason = query.value(17).toString();
        st_db_data.local_tx_id = query.value(18).toString();
        st_db_data.back_state = query.value(19).toString();

        int row_id_2 = this->chargingLog_backUp_upDate_QPSQL(st_db_data);

        // -1 이면 실패한거임 그냥 pending으로 남겨둠
        // 서버 끊겨있는대 저게 어떻게 성공으로 처리댐?
        if (row_id_2 != -1)
        {
            QSqlQuery query_upDate(this->db_lite);
            bool ok_prepare_2 = query_upDate.prepare("UPDATE charging_log "
                                                     "SET "
                                                     "state = :state "
                                                     "WHERE row_id = :row_id");
            // 디버깅
            if (!this->check_query_prepare(ok_prepare_2, query_upDate))
            {
                return;
            }

            query_upDate.bindValue(":state", "done");
            query_upDate.bindValue(":row_id", row_id);

            bool b_ok_exec_2 = query_upDate.exec();

            if (!this->check_query_exec(b_ok_exec_2, query_upDate))
            {
                return;
            }
        }
    }

    return;
}

void DB_PostgreSQL::backUp_register_membershipCard_finished()
{
    QSqlQuery query(this->db_lite);
    QString qs_state = "pending";
    qDebug() << "SQLITE 백업 큐 멤버쉽 카드 가져옴 ::::::::::::::::::::";
    bool ok_prepare = query.prepare("SELECT * FROM membership_card WHERE state = :state");

    // 디버깅
    if (!this->check_query_prepare(ok_prepare, query))
    {
        return;
    }

    query.bindValue(":state", qs_state);

    bool b_ok_exec = query.exec();

    if (!this->check_query_exec(b_ok_exec, query))
    {
        return;
    }

    while (query.next())
    {
        QString card_uid;
        int adv_pay;
        int act_pay;
        int can_pay;
        int t_id;
        QString request_id;
        QString state;

        card_uid = query.value(0).toString();
        adv_pay = query.value(1).toInt();
        act_pay = query.value(2).toInt();
        can_pay = query.value(3).toInt();
        t_id = query.value(4).toInt();
        request_id = query.value(5).toString();
        state = query.value(6).toString();

        bool b = this->membershipCard_finished_backup_upDate_QPSQL(adv_pay,
                                                                   act_pay,
                                                                   can_pay,
                                                                   card_uid,
                                                                   t_id,
                                                                   request_id);
        // -1 이면 실패한거임 그냥 pending으로 남겨둠
        if (b)
        {
            qDebug() << "?_______________________";
            QSqlQuery query_upDate(this->db_lite);
            bool ok_prepare_2 = query_upDate.prepare("UPDATE membership_card "
                                                     "SET "
                                                     "state = :state "
                                                     "WHERE request_id = :request_id");
            // 디버깅
            if (!this->check_query_prepare(ok_prepare_2, query_upDate))
            {
                return;
            }

            query_upDate.bindValue(":state", "done");
            query_upDate.bindValue(":request_id", request_id);

            bool b_ok_exec_2 = query_upDate.exec();

            if (!this->check_query_exec(b_ok_exec_2, query_upDate))
            {
                return;
            }
        }
        else
        {
            qDebug() << "+_______________________";
        }
    }

    return;
}

void DB_PostgreSQL::slot_select_From_soc(const mp_wk_key key,
                                         QString table,
                                         int total,
                                         QString col1,
                                         QString val1,
                                         QString col2,
                                         QString val2,
                                         QString col3,
                                         QString val3)
{
    if (!this->db_openCheck())
    {
        return;
    }

    QSqlQuery query(this->db);
    QString qs_pre;

    if (total == 0)
    {
        qs_pre = QString("SELECT * FROM %1").arg(table);
        bool ok_prepare = query.prepare(qs_pre);

        if (!this->check_query_prepare(ok_prepare, query))
        {
            return;
        }

        bool ok_exec = query.exec();

        if (!this->check_query_exec(ok_exec, query))
        {
            return;
        }
    }
    else if (total == 1)
    {
        qs_pre = QString("SELECT * FROM %1 "
                         "WHERE "
                         "%2 = :val1")
                     .arg(table)
                     .arg(col1);
        bool ok_prepare = query.prepare(qs_pre);

        if (!this->check_query_prepare(ok_prepare, query))
        {
            return;
        }

        query.bindValue(":val1", val1);

        bool ok_exec = query.exec();

        if (!this->check_query_exec(ok_exec, query))
        {
            return;
        }
    }
    else if (total == 2)
    {
        qs_pre = QString("SELECT * FROM %1 "
                         "WHERE "
                         "%2 = :val1 AND "
                         "%3 = :val2")
                     .arg(table)
                     .arg(col1)
                     .arg(col2);
        bool ok_prepare = query.prepare(qs_pre);

        if (!this->check_query_prepare(ok_prepare, query))
        {
            return;
        }

        query.bindValue(":val1", val1);
        query.bindValue(":val2", val2);

        bool ok_exec = query.exec();

        if (!this->check_query_exec(ok_exec, query))
        {
            return;
        }
    }
    else if (total == 3)
    {
        qs_pre = QString("SELECT * FROM %1 "
                         "WHERE "
                         "%2 = :val1 AND "
                         "%3 = :val2 AND "
                         "%4 = :val3")
                     .arg(table)
                     .arg(col1)
                     .arg(col2)
                     .arg(col3);
        bool ok_prepare = query.prepare(qs_pre);

        if (!this->check_query_prepare(ok_prepare, query))
        {
            return;
        }

        query.bindValue(":val1", val1);
        query.bindValue(":val2", val2);
        query.bindValue(":val3", val3);

        bool ok_exec = query.exec();

        if (!this->check_query_exec(ok_exec, query))
        {
            return;
        }
    }

    if (table == "charging_log")
    {
        QVector<charging_log_admin> vec;
        while (query.next())
        {
            struct charging_log_admin st_log = {0};

            st_log.created_at = query.value(0).toString();
            st_log.updated_at = query.value(1).toString();
            st_log.row_id = query.value(2).toInt();
            st_log.store_id = query.value(3).toInt();
            st_log.hmi_id = query.value(4).toString();
            st_log.ocpp_tx_id = query.value(5).toInt();
            st_log.card_uid = query.value(6).toString();
            st_log.start_time = query.value(7).toString();
            st_log.end_time = query.value(8).toString();
            st_log.duration_time = query.value(9).toString();
            st_log.average_kwh = query.value(10).toDouble();
            st_log.soc_start = query.value(11).toDouble();
            st_log.soc_end = query.value(12).toDouble();
            st_log.advance_payment = query.value(13).toInt();
            st_log.cancel_payment = query.value(14).toInt();
            st_log.actual_payment = query.value(15).toInt();
            st_log.unit_price = query.value(16).toInt();
            st_log.tariff_type = query.value(17).toString();
            st_log.session_status = query.value(18).toString();
            st_log.stop_reason = query.value(19).toString();
            st_log.local_tx_id = query.value(20).toString();

            vec.push_back(st_log);
        }

        emit this->sig_charging_log_select_ret(key, vec);
        return;
    }
    else if (table == "hmi_current_stat")
    {
        QVector<hmi_current_stat_admin> vec;
        while (query.next())
        {
            struct hmi_current_stat_admin st_log = {0};

            st_log.hmi_id = query.value(0).toString();
            st_log.store_id = query.value(1).toInt();
            st_log.ws_connected = query.value(2).toBool();
            st_log.last_heartbeat_at = query.value(3).toString();
            st_log.screen_name = query.value(4).toString();
            st_log.updated_at = query.value(5).toString();

            vec.push_back(st_log);
        }

        emit this->sig_hmi_current_stat_select_ret(key, vec);
        return;
    }
    else if (table == "hmi_device")
    {
        QVector<hmi_device_admin> vec;
        while (query.next())
        {
            struct hmi_device_admin st_log = {0};

            st_log.hmi_id = query.value(0).toString();
            st_log.store_id = query.value(1).toInt();

            vec.push_back(st_log);
        }

        emit this->sig_hmi_device_select_ret(key, vec);
        return;
    }
    else if (table == "membership_card")
    {
        QVector<membership_card_admin> vec;
        while (query.next())
        {
            struct membership_card_admin st_log = {0};

            st_log.card_uid = query.value(0).toString();
            st_log.balance_total = query.value(1).toInt();
            st_log.balance_available = query.value(2).toInt();
            st_log.hold_amount = query.value(3).toInt();
            st_log.transaction_state = query.value(4).toString();

            vec.push_back(st_log);
        }

        emit this->sig_membership_card_select_ret(key, vec);
        return;
    }
    else if (table == "membership_log")
    {
        QVector<membership_log_admin> vec;
        while (query.next())
        {
            struct membership_log_admin st_log = {0};

            st_log.card_uid = query.value(0).toString();
            st_log.transaction_id = query.value(1).toInt();
            st_log.event_type = query.value(2).toString();
            st_log.amount = query.value(3).toInt();
            st_log.balance_available_before = query.value(4).toInt();
            st_log.balance_available_after = query.value(5).toInt();
            st_log.hold_amount_before = query.value(6).toInt();
            st_log.hold_amount_after = query.value(7).toInt();
            st_log.transaction_state_before = query.value(8).toString();
            st_log.transaction_state_after = query.value(9).toString();
            st_log.created_at = query.value(10).toString();
            st_log.request_id = query.value(11).toString();

            vec.push_back(st_log);
        }

        emit this->sig_membership_log_select_ret(key, vec);
        return;
    }
    else if (table == "store_user")
    {
        QVector<store_user_admin> vec;
        while (query.next())
        {
            struct store_user_admin st_log = {0};

            st_log.id = query.value(0).toInt();
            st_log.name = query.value(1).toString();
            st_log.location = query.value(2).toString();
            vec.push_back(st_log);
        }

        emit this->sig_store_user_select_ret(key, vec);
        return;
    }

    return;
}

void DB_PostgreSQL::slot_select_mCard_status_From_soc(const mp_wk_key key,
                                                      QString table,
                                                      QString card_uid)
{
    if (!this->db_openCheck())
    {
        return;
    }

    QSqlQuery query(this->db);
    QString qs_pre;

    qs_pre = QString("SELECT * FROM %1 "
                     "WHERE "
                     "card_uid = :val1")
                 .arg(table);
    bool ok_prepare = query.prepare(qs_pre);

    if (!this->check_query_prepare(ok_prepare, query))
    {
        return;
    }

    query.bindValue(":val1", card_uid);

    bool ok_exec = query.exec();

    if (!this->check_query_exec(ok_exec, query))
    {
        return;
    }

    QVector<membership_card_admin> vec;
    while (query.next())
    {
        struct membership_card_admin st_log = {0};

        st_log.card_uid = query.value(0).toString();
        st_log.balance_total = query.value(1).toInt();
        st_log.balance_available = query.value(2).toInt();
        st_log.hold_amount = query.value(3).toInt();
        st_log.transaction_state = query.value(4).toString();

        vec.push_back(st_log);
    }

    QMetaObject::invokeMethod(this->p_soc,
                              "slot_mCard_status_ret_From_DB__To_admin",
                              Qt::QueuedConnection,
                              Q_ARG(mp_wk_key, key),
                              Q_ARG(QVector<membership_card_admin>, vec));

    return;
}

void DB_PostgreSQL::slot_revision_mCard_status_From_soc(
    QString card_uid, int total, int remain, int hold, QString stat)
{
    qDebug() << Q_FUNC_INFO;
    qDebug() << card_uid;
    if (!this->db_openCheck())
    {
        return;
    }

    QSqlQuery query(this->db);

    bool ok_prepare = query.prepare("UPDATE membership_card "
                                    "SET "
                                    "balance_total = :balance_total, "
                                    "balance_available = :balance_available, "
                                    "hold_amount = :hold_amount, "
                                    "transaction_state = :transaction_state "
                                    "WHERE card_uid = :card_uid");

    if (!this->check_query_prepare(ok_prepare, query))
    {
        return;
    }

    query.bindValue(":balance_total", total);
    query.bindValue(":balance_available", remain);
    query.bindValue(":hold_amount", hold);
    query.bindValue(":transaction_state", stat);
    query.bindValue(":card_uid", card_uid);

    bool b_ok_exec = query.exec();

    if (!this->check_query_exec(b_ok_exec, query))
    {
        return;
    }

    return;
}
