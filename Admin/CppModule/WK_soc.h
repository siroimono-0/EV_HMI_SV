#ifndef WK_SOC_H
#define WK_SOC_H

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QObject>
#include <QThread>
#include <QTimer>
#include <QWebSocket>
#include <Qurl>

class Admin;

class WK_soc : public QObject
{
    Q_OBJECT
public:
    explicit WK_soc(QObject *parent = nullptr);

public slots:
    void slot_end();
    void slot_start();
    void slot_disconnected();

    void slot_connect_hello();
    void slot_register_store(const QString id, const QString name, const QString location);
    void slot_register_hmi(const QString storeId, const QString hmiId);

    void slot_recvText(QString recvMsg);

signals:
    void sig_end();

private:
    Admin *p_admin = nullptr;
    QWebSocket *p_soc = nullptr;
};

#endif // WK_SOC_H
