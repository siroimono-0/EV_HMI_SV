#ifndef HTTPSV_H
#define HTTPSV_H

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QHttpServer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <QObject>
#include <QStandardPaths>
#include <QTcpServer>

enum COMPARE_ROLE { SUCCESS = 0, NOT_FIND = 1, NOT_MONEY = 2 };

class HttpSv : public QObject
{
    Q_OBJECT
public:
    explicit HttpSv(QObject *parent = nullptr);

    void mkdir();
    void upload_mp4();

public slots:
    QHttpServerResponse slot_compare(const QHttpServerRequest &req);
    QHttpServerResponse slot_pay_ack(int compare_role, const QJsonObject &jsObj);
    QHttpServerResponse slot_cancle_ack(int compare_role, const QJsonObject &jsObj);

    QHttpServerResponse slot_compare_get(const QHttpServerRequest &req);
signals:

private:
    QHttpServer *p_httpSv = nullptr;
    QTcpServer *p_tcpSv = nullptr;
    QMap<QString, bool> qmp;
    QString path_mp4;
};

#endif // HTTPSV_H
