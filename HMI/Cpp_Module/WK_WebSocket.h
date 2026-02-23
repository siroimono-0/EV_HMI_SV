#ifndef WK_WEBSOCKET_H
#define WK_WEBSOCKET_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QUrl>
#include <QWebSocket>
#include "../Common/StatData.h"
#include "StatStore.h"

class StatStore;
class Cpp_Module;

class WK_WebSocket : public QObject
{
    Q_OBJECT
public:
    explicit WK_WebSocket(QObject *parent = nullptr);
    void set_p_stat(StatStore *set_p_stat);
    void set_p_Module(Cpp_Module *set_p_Module);

    void create_netAccess();

public slots:
    void slot_stop();
    void slot_Connect_Sv();

    void slot_ID_Check();
    void slot_ID_Resert(bool resert);

    void slot_SocErr(QAbstractSocket::SocketError error);

    // 수정부분 안씀
    // void slot_Send_TextData(stat_data st_stat);
    void slot_send_db_update_textData(db_data st_db_data);
    void slot_Recv_TextData(QString recvData);

    ////////////////////////////////////////////////
    void slot_netAccess_reply(QNetworkReply *reply);
    void slot_netAccess_post(QByteArray qba);

signals:
    void sig_end();

private:
    QWebSocket *p_webSoc = nullptr;
    StatStore *p_stat = nullptr;
    Cpp_Module *p_Module = nullptr;
    QNetworkAccessManager *p_netAccess = nullptr;
    bool connect_stat = false;
};

Q_DECLARE_METATYPE(WK_WebSocket *)

#endif // WK_WEBSOCKET_H
