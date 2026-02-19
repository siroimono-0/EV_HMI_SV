#include "WK_soc.h"

WK_soc::WK_soc(QObject *parent)
    : QObject{parent}
{}

void WK_soc::slot_end()
{
    if (this->p_soc)
    {
        // 정상 close (필요하면 closeCode/Reason도)
        this->p_soc->close();

        this->p_soc = nullptr;
    }

    emit this->sig_end();
    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_soc::slot_start()
{
    this->p_soc = new QWebSocket();
    this->p_soc->setParent(this);

    connect(this->p_soc, &QWebSocket::connected, this, &WK_soc::slot_connect_hello);
    connect(this->p_soc, &QWebSocket::disconnected, this, &WK_soc::slot_disconnected);

    connect(this->p_soc, &QWebSocket::textMessageReceived, this, &WK_soc::slot_recvText);

    this->p_soc->open(QUrl("ws://192.168.123.100:12345/ws/admin"));
    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_soc::slot_disconnected()
{
    // QTimer::singleShot(0, this, &QObject::deleteLater);
    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_soc::slot_connect_hello()
{
    QJsonObject jsObj;
    jsObj.insert("type", "hello");
    jsObj.insert("role", "admin");
    jsObj.insert("token", "");
    jsObj.insert("adminId", "001");

    QJsonDocument jsDoc(jsObj);
    this->p_soc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));
    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_soc::slot_register_store(const QString id, const QString name, const QString location)
{
    QJsonObject jsObj;
    qDebug() << id << " :: id";
    qDebug() << name << " :: name";
    qDebug() << location << " :: location";

    jsObj.insert("type", "register");
    jsObj.insert("registerId", id);
    jsObj.insert("registerName", name);
    jsObj.insert("registerLocation", location);

    QJsonDocument jsDoc(jsObj);
    this->p_soc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));
    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_soc::slot_register_hmi(const QString storeId, const QString hmiId)
{
    QJsonObject jsObj;
    qDebug() << storeId << " :: id";
    qDebug() << hmiId << " :: name";

    jsObj.insert("type", "register_hmi");
    jsObj.insert("registerId_store", storeId);
    jsObj.insert("registerId_hmi", hmiId);

    QJsonDocument jsDoc(jsObj);
    this->p_soc->sendTextMessage(jsDoc.toJson(QJsonDocument::Compact));
    qDebug() << Q_FUNC_INFO;

    return;
}

void WK_soc::slot_recvText(QString recvMsg)
{
    QByteArray qba = recvMsg.toUtf8();
    QJsonParseError jsErr;
    QJsonDocument jsDoc = QJsonDocument::fromJson(qba, &jsErr);

    if (jsErr.error != QJsonParseError::NoError)
    {
        qDebug() << "Json Err";
    }

    QJsonObject jsObj = jsDoc.object();

    if (jsObj.contains("type"))
    {
        if (jsObj["type"].toString() == "hello_ack")
        {
            if (jsObj["ok"].toBool() == true)
            {
                qDebug() << "hello ok";
            }
            else if (jsObj["ok"].toBool() == false)
            {
                qDebug() << "hello X";
            }
        }
        else if (jsObj["type"].toString() == "register_ack")
        {
            if (jsObj["ok"].toBool() == true)
            {
                qDebug() << "register ok";
            }
            else if (jsObj["ok"].toBool() == false)
            {
                qDebug() << "register X";
            }
        }
        else if (jsObj["type"].toString() == "register_hmi_ack")
        {
            if (jsObj["ok"].toBool() == true)
            {
                qDebug() << "register ok";
            }
            else if (jsObj["ok"].toBool() == false)
            {
                qDebug() << "register X";
            }
        }
    }
    qDebug() << Q_FUNC_INFO;
    return;
}
/*
 {
  "type": "hello",
  "role": "admin|hmi",
  "token": "...",
  "clientId": "..."
}
 */
