#include "HttpSv.h"

HttpSv::HttpSv(QObject *parent)
    : QObject{parent}
{
    this->mkdir();

    this->p_httpSv = new QHttpServer(this);
    this->p_httpSv->route("/compare", QHttpServerRequest::Method::Post, this, &HttpSv::slot_compare);

    this->p_httpSv->route("/compare",
                          QHttpServerRequest::Method::Get,
                          this,
                          &HttpSv::slot_compare_get);

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

void HttpSv::mkdir()
{
    QString tmp_dir_path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    tmp_dir_path += "/mp4";

    QDir dir_path;
    dir_path.mkpath(tmp_dir_path);
    qDebug() << tmp_dir_path;

    this->path_mp4 = tmp_dir_path;
    return;
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
    else if (req.value("Content-Type") == "application/mp4/upload")
    {
        QByteArray qba = req.body();
        int find_idx = qba.indexOf("\r\n");
        if (find_idx == -1)
        {
            qDebug() << "ERR";
        }

        QString name = QString::fromUtf8(qba.left(find_idx));
        qDebug() << name;
        // QString path = "C:/Users/siroi/siroimono/w_qt/EV/HttpSv/mp4/" + name;
        QString path = this->path_mp4 + "/" + name;
        QFile up_file(path);
        up_file.open(QIODevice::ReadWrite);
        up_file.write(qba.right(qba.size() - (find_idx + 2)));
        up_file.close();

        QJsonObject jsObj;

        jsObj.insert("type", "file_upload_ack");

        QJsonDocument jsDoc(jsObj);
        QString send_qs = jsDoc.toJson(QJsonDocument::Compact);

        QHttpServerResponse rep("application/json", send_qs.toUtf8());
        return rep;
    }
}

QHttpServerResponse HttpSv::slot_compare_get(const QHttpServerRequest &req)
{
    if (req.value("Content-Type") == "application/mp4/download")
    {
        QString name = QString::fromUtf8(req.body());

        // QString path = "C:/Users/siroi/siroimono/w_qt/EV/HttpSv/mp4/" + name;
        QString path = this->path_mp4 + "/" + name;
        QFile down_file(path);
        down_file.open(QIODevice::ReadWrite);
        QByteArray qba;
        qba += name.toUtf8();
        qba += "\r\n";
        qba += down_file.readAll();

        QHttpServerResponse rep("application/mp4/download", qba);
        down_file.close();
        return rep;
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
