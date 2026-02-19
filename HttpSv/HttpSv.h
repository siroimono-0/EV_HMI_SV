#ifndef HTTPSV_H
#define HTTPSV_H

#include <QDebug>
#include <QHttpServer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <QObject>
#include <QTcpServer>

enum COMPARE_ROLE { SUCCESS = 0, NOT_FIND = 1, NOT_MONEY = 2 };

class HttpSv : public QObject
{
    Q_OBJECT
public:
    explicit HttpSv(QObject *parent = nullptr);

public slots:
    QHttpServerResponse slot_compare(const QHttpServerRequest &req);
    QHttpServerResponse slot_pay_ack(int compare_role, const QJsonObject &jsObj);

signals:

private:
    QHttpServer *p_httpSv = nullptr;
    QTcpServer *p_tcpSv = nullptr;
    QMap<QString, bool> qmp;
};

#endif // HTTPSV_H
