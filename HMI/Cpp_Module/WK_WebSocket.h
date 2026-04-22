#ifndef WK_WEBSOCKET_H
#define WK_WEBSOCKET_H

#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QTimer>
#include <QUrl>
#include <QWebSocket>
#include <QtSystemDetection>
#include "../Common/StatData.h"
#include "StatStore.h"

class StatStore;
class Cpp_Module;
class WK_Serial;

enum class EN_CloseReason { AppQuit, Manual, None };

class WK_WebSocket : public QObject
{
    Q_OBJECT
public:
    explicit WK_WebSocket(QObject *parent = nullptr);
    void set_p_stat(StatStore *set_p_stat);
    void set_p_Module(Cpp_Module *set_p_Module);
    void set_httpSv_url(const QString set);

    void create_netAccess();

    void parsing_revision_HMI(const QJsonObject jo);

    void update_ad(const QString name);
    void remove_ad(const QString name);

    void netAccess_get_download(const QString name);

    void shutdown_nomal();
    void shutdown_restart();


public slots:
    void slot_stop();
    void slot_Connect_Sv();
    void slot_disconnected();
    void slot_set_p_serial(WK_Serial *set);

    void slot_ID_Check();
    void slot_ID_Resert(bool resert);

    void slot_SocErr(QAbstractSocket::SocketError error);

    // 수정부분 안씀
    // void slot_Send_TextData(stat_data st_stat);
    void slot_send_db_update_textData(db_data st_db_data);
    void slot_Recv_TextData(QString recvData);

    ////////////////////////////////////////////////
    void slot_netAccess_reply(QNetworkReply *reply);
    // 카드 결제 요청
    void slot_netAccess_post(QByteArray qba);
    void slot_timeOut_pay_ack();
    void slot_netAccess_post_cancle(QString card_uid);
    void slot_timeOut_cancle_ack();
    //===================================================

    // serial Class 에서 invok
    void slot_send_membership_authorized_textData(int adv_pay, QByteArray card_uid, QString hmi_id);
    void slot_timeOut_membership_authorized_ack();

    void slot_send_membership_finished_textData(
        int adv_pay, int act_pay, int can_pay, QString card_uid, uint32_t t_id, QString request_id);
    void slot_timeOut_membership_finished_ack();

    //===================================================
    // set_p_stat 에서 커넥트
    // connect(this->p_stat, &StatStore::sig_hartbit_pong, this, &WK_WebSocket::slot_send_hartbit_pong);
    void slot_send_heartbit_pong(heartbit_data st_hb_data);

    void slot_update_ad(const QString name);

signals:
    void sig_end();
    // set_p_stat 에서 커넥트
    // statStore slot -> sig -> soc slot -> sv
    void sig_heartbit_ping_To_statStore();

private:
    QWebSocket *p_webSoc = nullptr;
    StatStore *p_stat = nullptr;
    Cpp_Module *p_Module = nullptr;
    WK_Serial *p_serial = nullptr;
    QNetworkAccessManager *p_netAccess = nullptr;
    bool connect_stat = false;
    EN_CloseReason close_reason = EN_CloseReason::None;

    // ack 안올 때 재전송 위한 데이터
    bool pay_ack = false;
    int pay_ack_cnt = 0;
    QByteArray slot_netAccess_post_Data;

    bool cancle_ack = false;
    int cancle_ack_cnt = 0;
    QString slot_netAccess_post_cancle_Data;

    // ack 안올 때 재전송 위한 데이터
    bool member_ack = false;
    int member_ack_cnt = 0;
    QPair<int, QByteArray> membership_authorized_Data;
    QString membership_authorized_requestId_Data;
    // ack 안올 때 재전송 위한 데이터

    // ack 안올 때 재전송 위한 데이터
    bool member_finished_ack = false;
    int member_finished_ack_cnt = 0;
    int adv_pay;
    int act_pay;
    int can_pay;
    QString card_uid;
    uint32_t t_id;
    QString membership_finished_requestId_Data;
    // ack 안올 때 재전송 위한 데이터

    QUrl httpSv_url;
};

Q_DECLARE_METATYPE(WK_WebSocket *)

#endif // WK_WEBSOCKET_H
