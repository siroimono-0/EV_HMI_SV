#include "HttpSv.h"

HttpSv::HttpSv(QObject *parent)
    : QObject{parent}
{
    this->p_httpSv = new QHttpServer(this);
    this->p_httpSv->route("/compare", QHttpServerRequest::Method::Post, this, &HttpSv::slot_compare);

    this->p_tcpSv = new QTcpServer(this->p_httpSv);
    if (!this->p_tcpSv->listen(QHostAddress::Any, 8080))
    {
        qDebug() << "tcp listen Err";
        return;
    }

    if (!this->p_httpSv->bind(this->p_tcpSv))
    {
        qDebug() << "httpSv bind Err";
        return;
    }

    // 태스트 카드 값 저장
    this->qmp.insert("45005A91B8", true);
}

QHttpServerResponse HttpSv::slot_compare(const QHttpServerRequest &req)
{
    if (req.value("Content-Type") == "application/json")
    {
        QByteArray qba = req.body();

        QJsonParseError jsErr;
        QJsonDocument jsDoc = QJsonDocument::fromJson(qba, &jsErr);

        QJsonObject jsObj = jsDoc.object();
        QString type = jsObj["type"].toString();

        if (type == "pay")
        {
            if (jsObj["role"].toString() == "creditCard")
            {
                QString uid = jsObj["uid"].toString();
                // uid가 결제 가능 카드인지 확인
                // + 잔액이 남았는지 확인
                if (qmp.find(uid) != qmp.end())
                {
                    if (qmp[uid] == true)
                    {
                        return this->slot_pay_ack(SUCCESS, jsObj);
                    }
                    else
                    {
                        return this->slot_pay_ack(NOT_MONEY, jsObj);
                    }
                }
                else
                {
                    return this->slot_pay_ack(NOT_FIND, jsObj);
                }
            }
        }
        else if (type == "cancle")
        {
            return this->slot_cancle_ack(SUCCESS, jsObj);
        }
    }
}

QHttpServerResponse HttpSv::slot_pay_ack(int compare_role, const QJsonObject &jsObj)
{
    QJsonObject send_jsObj;

    send_jsObj.insert("type", "pay_ack");
    send_jsObj.insert("role", jsObj["role"].toString());
    send_jsObj.insert("uid", jsObj["uid"].toString());

    if (compare_role == SUCCESS)
    {
        send_jsObj.insert("ok", true);
    }
    else if (compare_role == NOT_FIND)
    {
        send_jsObj.insert("ok", false);
        send_jsObj.insert("err", "미등록 카드");
    }
    else if (compare_role == NOT_MONEY)
    {
        send_jsObj.insert("ok", false);
        send_jsObj.insert("err", "금액 부족");
    }

    QJsonDocument jsDoc(send_jsObj);
    QString send_qs = jsDoc.toJson(QJsonDocument::Compact);

    // 생성자에서 자동으로 Content-Type 으로 헤더 생성
    QHttpServerResponse rep("application/json", send_qs.toUtf8());
    return rep;

    /* ack 미전송 테스트
    QHttpServerResponse test("application/json", "test");
    return test;
    */
}

QHttpServerResponse HttpSv::slot_cancle_ack(int compare_role, const QJsonObject &jsObj)
{
    QJsonObject send_jsObj;

    send_jsObj.insert("type", "cancle_ack");
    send_jsObj.insert("role", jsObj["role"].toString());
    send_jsObj.insert("uid", jsObj["uid"].toString());

    if (compare_role == SUCCESS)
    {
        send_jsObj.insert("ok", true);
    }
    else if (compare_role == NOT_FIND)
    {
        send_jsObj.insert("ok", false);
        send_jsObj.insert("err", "미등록 카드");
    }
    else if (compare_role == NOT_MONEY)
    {
        send_jsObj.insert("ok", false);
        send_jsObj.insert("err", "금액 부족");
    }

    QJsonDocument jsDoc(send_jsObj);
    QString send_qs = jsDoc.toJson(QJsonDocument::Compact);

    // 생성자에서 자동으로 Content-Type 으로 헤더 생성
    QHttpServerResponse rep("application/json", send_qs.toUtf8());
    return rep;

    /*ack 미전송 테스트
    QHttpServerResponse test("application/json", "tesy");
    return test;
*/
}
