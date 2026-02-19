#ifndef DB_POSTGRESQL_H
#define DB_POSTGRESQL_H

#include <QDebug>
#include <QObject>
#include <QtSql>
#include "../Common/StatData.h"

class Cpp_Module;

class DB_PostgreSQL : public QObject
{
    Q_OBJECT
public:
    explicit DB_PostgreSQL(QObject *parent = nullptr);
    ~DB_PostgreSQL();

    void set_p_Module(Cpp_Module *module);

    void createDB();

public slots:
    void slot_end();

    bool slot_createStore(int id, QString name, QString location);
    store_info slot_query_find_id(QString find_id);

    bool slot_query_register(const QString id, const QString name, const QString location);

    bool slot_query_register_hmi(const QString storeId, const QString hmiId);

    bool slot_query_find_hello_hmi(const QString storeId, const QString hmiId);

signals:
    void sig_end();

private:
    QSqlDatabase db;
    Cpp_Module *p_Module;
};

#endif // DB_POSTGRESQL_H
