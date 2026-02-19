#ifndef WK_SOC_H
#define WK_SOC_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QObject>
#include <QWebSocket>
#include "../Common/StatData.h"

struct details;
class StatModel;
class Hub;
class DB_PostgreSQL;

class WK_Soc : public QObject
{
    Q_OBJECT
public:
    explicit WK_Soc(QObject *parent = nullptr);
    void set_p_webSoc(QWebSocket *set_webSoc, int id_mp);
    void set_p_md(StatModel *set_md);
    void set_p_Hub(Hub *set_Hub);
    void set_p_db(DB_PostgreSQL *set_db);

public slots:
    void slot_Recv_TextData(QString recvData);
    void slot_Disconnect_Soc();

    void slot_helloAck(bool ret);

    bool slot_registerReq(const QJsonObject &jsObj);
    void slot_registerAck(bool ret);

    bool slot_registerReq_hmi(const QJsonObject &jsObj);
    void slot_registerAck_hmi(bool ret);

signals:
    void sig_update_md(stat_data st_stat);

private:
    QWebSocket *p_WebSoc;
    StatModel *p_Md;
    Hub *p_Hub;
    DB_PostgreSQL *p_obj_db;

    QString connectRole = "";
    QString token = "";
    QString roleId = "";

    int id_Common = 0;
    int id_Mp = 0;
    bool stat_Disconnect = false;
};

#endif // WK_SOC_H
