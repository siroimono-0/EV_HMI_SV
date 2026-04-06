#ifndef DB_POSTGRESQL_H
#define DB_POSTGRESQL_H

#include <QDebug>
#include <QObject>
#include <QtSql>
#include "../../Common/StatData.h"

enum RECURSIVE_ERR {
    MB_AUTHORIZED = 0,
    MB_FINISHED = 1,
    CHARGING_AUTHORIZED = 2,
    CHARGING_START = 3,
    CHARGING_FINISHED = 4
};

class Cpp_Module;
class WK_Soc;
class Hub;

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

    QPair<bool, QString> membershipCard_log_insert_authorized(const membership_log &m_log);
    bool membershipCard_log_insert_finished(const membership_log &m_log);

    void membershipCard_finished_sqlite_backUp(const membership_backUp_sqlite back_data);
    void chargingLog_sqlite_backUp(const db_data back_data);

    // 걍 닫힘? -> 열음
    // 닫혀있는대 착시임? -> 트랜잭션때 실패함
    // 다시 닫힘? -> 열음 반복시킴 어자피 실제 제품도 아니고 걍 단순하게
    bool db_openCheck();

    void membershipCard_authorized_false_msg(const mp_wk_key key);
    void membershipCard_finished_stat(const mp_wk_key key, bool stat);
    void chargingLog_authorized_invok(const mp_wk_key key);
    void chargingLog_start_invok(const mp_wk_key key, uint32_t ocpp_tx);
    void chargingLog_finished_invok(const mp_wk_key key);

    // SQLITE 백업큐 꺼내서 PQ등록하는거 만들어야댐
    void backUp_register_chargingLog();
    void backUp_register_membershipCard_finished();

    int chargingLog_backUp_upDate_QPSQL(db_data st_db_data);
    bool membershipCard_finished_backup_upDate_QPSQL(
        int adv_pay, int act_pay, int can_pay, QString card_uid, uint32_t t_id, QString request_id);

public slots:
    void slot_end();
    void slot_set_p_soc(Hub *soc);

    bool slot_createStore(int id, QString name, QString location);
    // 수정
    // store_info slot_query_find_id(QString find_id);

    bool slot_query_register(const QString id, const QString name, const QString location);

    bool slot_query_register_hmi(const QString storeId, const QString hmiId);

    bool slot_query_find_hello_hmi(const QString storeId, const QString hmiId);

    // soc -> set_p_db에서 커넥트
    void slot_chargingLog_From_soc(const mp_wk_key key, db_data st_db_data);

    // soc -> set_p_db에서 커넥트
    void slot_heartbitData_From_soc(heartbit_data st_hb_data);
    void slot_membershipCard_authorized_From_soc(const mp_wk_key key,
                                                 int adv_pay,
                                                 QString card_uid,
                                                 QString request_id);
    void slot_membershipCard_finished_From_soc(const mp_wk_key key,
                                               int adv_pay,
                                               int act_pay,
                                               int can_pay,
                                               QString card_uid,
                                               uint32_t t_id,
                                               QString request_id);

    // soc -> set_p_db에서 커넥트
    void slot_select_From_soc(const mp_wk_key key,
                              QString table,
                              int total,
                              QString col1 = "",
                              QString val1 = "",
                              QString col2 = "",
                              QString val2 = "",
                              QString col3 = "",
                              QString val3 = "");

    void slot_select_mCard_status_From_soc(const mp_wk_key key, QString table, QString card_uid);
    void slot_revision_mCard_status_From_soc(
        QString card_uid, int total, int remain, int hold, QString stat);

signals:
    void sig_end();

    // slot_set_p_soc에서 커넥트
    void sig_charging_log_select_ret(const mp_wk_key key, QVector<charging_log_admin> ret);

    // slot_set_p_soc에서 커넥트
    void sig_hmi_current_stat_select_ret(const mp_wk_key key, QVector<hmi_current_stat_admin> ret);

    // slot_set_p_soc에서 커넥트
    void sig_hmi_device_select_ret(const mp_wk_key key, QVector<hmi_device_admin> ret);

    // slot_set_p_soc에서 커넥트
    void sig_membership_card_select_ret(const mp_wk_key key, QVector<membership_card_admin> ret);

    // slot_set_p_soc에서 커넥트
    void sig_membership_log_select_ret(const mp_wk_key key, QVector<membership_log_admin> ret);

    // slot_set_p_soc에서 커넥트
    void sig_store_user_select_ret(const mp_wk_key key, QVector<store_user_admin> ret);

private:
    QSqlDatabase db;
    QSqlDatabase db_lite;
    QTimer *p_timer_lite;
    QString path;

    Cpp_Module *p_Module;
    // WK_Soc *p_soc; Hub로 변경...
    Hub *p_soc;
};

#endif // DB_POSTGRESQL_H
