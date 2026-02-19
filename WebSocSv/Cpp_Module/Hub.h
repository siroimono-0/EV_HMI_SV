#ifndef HUB_H
#define HUB_H

#include <QMap>
#include <QObject>
#include <QWebSocket>
#include <QWebSocketServer>
#include "../Common/StatData.h"

class WK_Soc;
class StatModel;
class DB_PostgreSQL;

class Hub : public QObject
{
    Q_OBJECT
public:
    explicit Hub(QObject *parent = nullptr);

    void set_p_md(StatModel *set_md);
    void set_p_db(DB_PostgreSQL *set_db);

public slots:
    void slot_start_sv();
    void slot_end();
    void slot_new_connection();
    void slot_del_mpWk(int idx);

signals:
    void sig_end();

private:
    QWebSocketServer *p_webSoc_Sv;
    QMap<int, WK_Soc *> qmp_wk;
    StatModel *p_md;
    DB_PostgreSQL *p_obj_db;
    int id_mp = 0;
};

#endif // HUB_H
