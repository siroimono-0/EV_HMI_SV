#ifndef WK_SOC_H
#define WK_SOC_H

#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QThread>
#include <QTimer>
#include <QUrl>
#include <QWebSocket>
#include "../Common/StatData.h"
#include <algorithm>

class Admin;
class MD_charging_log;
class MD_hmi_current_stat;
class MD_hmi_device;
class MD_membership_card;
class MD_membership_log;
class MD_store_user;
class Dia_membership_card;
class Dia_HMI;
class Dia_ad;

class WK_soc : public QObject
{
    Q_OBJECT
public:
    explicit WK_soc(QObject *parent = nullptr);

    void parsing_select(const QJsonObject jo);

    void parsing_mCard(const QJsonObject jo);

public slots:
    void slot_end();
    void slot_start();
    void slot_disconnected();

    void slot_connect_hello();
    void slot_register_store(const QString id, const QString name, const QString location);
    void slot_register_hmi(const QString storeId, const QString hmiId);

    void slot_recvText(QString recvMsg);

    void slot_req_select_db(QString table,
                            int total,
                            QString col_1 = "",
                            QString val_1 = "",
                            QString col_2 = "",
                            QString val_2 = "",
                            QString col_3 = "",
                            QString val_3 = "");

    void slot_set_p_md_charging_log(MD_charging_log *set);
    void slot_set_p_md_hmi_current_stat(MD_hmi_current_stat *set);
    void slot_set_p_md_hmi_device(MD_hmi_device *set);
    void slot_set_p_md_membership_card(MD_membership_card *set);
    void slot_set_p_md_membership_log(MD_membership_log *set);
    void slot_set_p_md_store_user(MD_store_user *set);
    void slot_set_p_dia_mCard(Dia_membership_card *set);
    void slot_set_p_dia_hmi(Dia_HMI *set);
    void slot_set_p_dia_ad(Dia_ad *set);

    void slot_req_mCard_status_db(QString card_uid);
    void slot_req_mCard_revision_db(membership_card_admin st_mCard);

    // Dia_HMI -> sep_p_soc에서 커넥트
    void slot_revision_hmi_To_SV(const revision_hmi_admin st_revision);
    void slot_set_dia_hmi_reqStat(bool set);

    // void slot_netAccess_reply(QNetworkReply *reply);
    void slot_netAccess_post(QString file_path);

signals:
    void sig_end();

    // slot_set_p_md_charging_log에서 connect
    void sig_update_charging_log(QVector<charging_log_admin> vec);

    // slot_set_p_md_hmi_current_stat에서 connect
    void sig_update_hmi_current_stat(QVector<hmi_current_stat_admin> vec);
    //  slot_set_p_dia_hmi에서 connect
    void sig_update_hmi_current_stat_To_Dia_HMI(QVector<hmi_current_stat_admin> vec);

    //  slot_set_p_md_hmi_device에서 connect
    void sig_update_hmi_device(QVector<hmi_device_admin> vec);

    //  slot_set_p_md_membership_card에서 connect
    void sig_update_membership_card(QVector<membership_card_admin> vec);

    //  slot_set_p_md_membership_log에서 connect
    void sig_update_membership_log(QVector<membership_log_admin> vec);

    //  slot_set_p_md_store_user에서 connect
    void sig_update_store_user(QVector<store_user_admin> vec);

private:
    Admin *p_admin = nullptr;
    QWebSocket *p_soc = nullptr;
    QNetworkAccessManager *p_netAccess = nullptr;

    // md 생성될 때 WK_soc slot으로 초기화
    MD_charging_log *p_md_charging_log = nullptr;

    // md 생성될 때 WK_soc slot으로 초기화
    MD_hmi_current_stat *p_md_hmi_current_stat = nullptr;

    // md 생성될 때 WK_soc slot으로 초기화
    MD_hmi_device *p_md_hmi_device = nullptr;

    // md 생성될 때 WK_soc slot으로 초기화
    MD_membership_card *p_md_membership_card = nullptr;

    // md 생성될 때 WK_soc slot으로 초기화
    MD_membership_log *p_md_membership_log = nullptr;

    // md 생성될 때 WK_soc slot으로 초기화
    MD_store_user *p_md_store_user = nullptr;

    Dia_membership_card *p_dia_mCard = nullptr;

    // Dia_HMI -> set_p_soc 에서 slot_으로 초기화
    Dia_HMI *p_dia_hmi = nullptr;
    bool dia_hmi_reqStat = false;

    // Dia_ad -> set_p_soc 에서 slot_으로 초기화
    Dia_ad *p_dia_ad = nullptr;
};

#endif // WK_SOC_H
