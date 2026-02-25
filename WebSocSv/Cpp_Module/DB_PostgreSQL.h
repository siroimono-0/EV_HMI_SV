#ifndef DB_POSTGRESQL_H
#define DB_POSTGRESQL_H

#include <QDebug>
#include <QObject>
#include <QtSql>
#include "../Common/StatData.h"

class Cpp_Module;
class WK_Soc;

class DB_PostgreSQL : public QObject
{
    Q_OBJECT
public:
    explicit DB_PostgreSQL(QObject *parent = nullptr);
    ~DB_PostgreSQL();

    void set_p_Module(Cpp_Module *module);

    void createDB();

    bool check_query_prepare(bool ok, QSqlQuery &query);
    bool check_query_exec(bool ok, QSqlQuery &query);

public slots:
    void slot_end();
    void slot_set_p_soc(WK_Soc *soc);

    bool slot_createStore(int id, QString name, QString location);
    // 수정
    // store_info slot_query_find_id(QString find_id);

    bool slot_query_register(const QString id, const QString name, const QString location);

    bool slot_query_register_hmi(const QString storeId, const QString hmiId);

    bool slot_query_find_hello_hmi(const QString storeId, const QString hmiId);

    // soc -> set_p_db에서 커넥트
    void slot_chargingLog_From_soc(db_data st_db_data);

signals:
    void sig_end();

private:
    QSqlDatabase db;
    Cpp_Module *p_Module;
    WK_Soc *p_soc;
};

#endif // DB_POSTGRESQL_H
