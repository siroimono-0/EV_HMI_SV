#include "DB_PostgreSQL.h"

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

store_info DB_PostgreSQL::slot_query_find_id(QString find_id)
{
    QSqlQuery query(this->db);
    // SELECT id FROM 테이블명 WHERE id = 값;
    query.prepare("SELECT * FROM HMI연결 WHERE id = :id");
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
}

bool DB_PostgreSQL::slot_query_register(const QString id, const QString name, const QString location)
{
    QString new_id = id;
    qDebug() << id << " :: id";
    qDebug() << name << " :: name";
    qDebug() << location << " :: location";

    QSqlQuery query(this->db);
    // SELECT id FROM 테이블명 WHERE id = 값;
    bool b_ok = query.prepare(
        "INSERT INTO store_user (id, name, location) VALUES (:id, :name, :location)");

    if (!b_ok)
    {
        QSqlError e = query.lastError();
        qDebug() << "DB prepare failed";
        qDebug() << "driverText =" << e.driverText();
        qDebug() << "databaseText =" << e.databaseText();
        qDebug() << "lastQuery =" << query.lastQuery();
        return false;
    }

    query.bindValue(":id", new_id.toInt());
    query.bindValue(":name", name);
    query.bindValue(":location", location);

    bool ret = query.exec();
    if (ret)
    {
        return true;
    }
    else
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

    return false;
}

bool DB_PostgreSQL::slot_query_register_hmi(const QString storeId, const QString hmiId)
{
    QString new_id = storeId;
    qDebug() << storeId << " :: sotreId";
    qDebug() << hmiId << " :: hmiId";

    QSqlQuery query(this->db);
    // SELECT id FROM 테이블명 WHERE id = 값;
    bool b_ok = query.prepare(
        "INSERT INTO hmi_device (hmi_id, store_id) VALUES (:hmi_id, :store_id)");

    if (!b_ok)
    {
        QSqlError e = query.lastError();
        qDebug() << "DB prepare failed";
        qDebug() << "driverText =" << e.driverText();
        qDebug() << "databaseText =" << e.databaseText();
        qDebug() << "lastQuery =" << query.lastQuery();
        return false;
    }

    query.bindValue(":hmi_id", hmiId);
    query.bindValue(":store_id", new_id.toInt());

    bool ret = query.exec();
    if (ret)
    {
        return true;
    }
    else
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

    return false;
}

bool DB_PostgreSQL::slot_query_find_hello_hmi(const QString storeId, const QString hmiId)
{
    QSqlQuery query(this->db);
    // SELECT id FROM 테이블명 WHERE id = 값;
    bool b_ok = query.prepare("SELECT * FROM hmi_device WHERE hmi_id = :hmi_id");
    query.bindValue(":hmi_id", hmiId);

    if (!b_ok)
    {
        QSqlError e = query.lastError();
        qDebug() << "DB prepare failed";
        qDebug() << "driverText =" << e.driverText();
        qDebug() << "databaseText =" << e.databaseText();
        qDebug() << "lastQuery =" << query.lastQuery();
        return false;
    }

    QString compare_hmiId;
    QString compare_storeId;

    // 만약 값이 있다면
    if (query.exec())
    {
        query.next();
        compare_hmiId = query.value(0).toString();
        compare_storeId = query.value(1).toString();
    }
    else
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
