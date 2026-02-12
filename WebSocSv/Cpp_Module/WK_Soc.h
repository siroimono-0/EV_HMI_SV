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

class WK_Soc : public QObject
{
    Q_OBJECT
public:
    explicit WK_Soc(QObject *parent = nullptr);
    void set_p_webSoc(QWebSocket *set_webSoc, int id_mp);
    void set_p_md(StatModel *set_md);
    void set_p_Hub(Hub *set_Hub);

public slots:
    void slot_textRecved(QString msg);
    void slot_disconnect_Soc();

signals:
    void sig_update_md(stat_data st_stat);

private:
    QWebSocket *p_webSoc;
    StatModel *p_md;
    Hub *p_Hub;
    int id_common = 0;
    int id_mp = 0;
    bool stat_disconnect = false;
};

#endif // WK_SOC_H
