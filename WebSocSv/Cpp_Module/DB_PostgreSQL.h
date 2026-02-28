#ifndef DB_POSTGRESQL_H
#define DB_POSTGRESQL_H

#include <QDebug>
#include <QObject>
#include <QtSql>
#include "../../Common/StatData.h"

enum RECURSIVE_ERR { MB_AUTHORIZED = 0, MB_FINISHED = 1 };

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
    bool query_exec_recursive(bool ok_exec, QSqlQuery &query);
    void query_exec_recursive_err(RECURSIVE_ERR err);

    QPair<bool, QString> membershipCard_log_insert_authorized(const membership_log &m_log);
    bool membershipCard_log_insert_finished(const membership_log &m_log);

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

    // soc -> set_p_db에서 커넥트
    void slot_heartbitData_From_soc(heartbit_data st_hb_data);
    void slot_membershipCard_authorized_From_soc(int adv_pay, QString card_uid, QString request_id);
    void slot_membershipCard_finished_From_soc(
        int adv_pay, int act_pay, int can_pay, QString card_uid, uint32_t t_id, QString request_id);

signals:
    void sig_end();

private:
    QSqlDatabase db;
    Cpp_Module *p_Module;
    WK_Soc *p_soc;
};

#endif // DB_POSTGRESQL_H
