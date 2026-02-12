#ifndef WK_WEBSOCKET_H
#define WK_WEBSOCKET_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QUrl>
#include <QWebSocket>
#include "../Common/StatData.h"

class StatStore;
class Cpp_Module;

class WK_WebSocket : public QObject
{
    Q_OBJECT
public:
    explicit WK_WebSocket(QObject *parent = nullptr);
    void set_p_stat(StatStore *set_p_stat);
    void set_p_Module(Cpp_Module *set_p_Module);

public slots:
    void slot_stop();
    void slot_Connect_Sv();
    void slot_SocErr(QAbstractSocket::SocketError error);

    void slot_sendData(stat_data st_stat);

signals:
    void sig_end();

private:
    QWebSocket *p_webSoc;
    StatStore *p_stat;
    Cpp_Module *p_Module;
};

#endif // WK_WEBSOCKET_H
