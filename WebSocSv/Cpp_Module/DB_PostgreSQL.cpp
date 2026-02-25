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
