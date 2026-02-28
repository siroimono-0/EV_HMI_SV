#include "Hub.h"
#include "StatModel.h"
#include "WK_Soc.h"

Hub::Hub(QObject *parent)
    : QObject{parent}
{
    this->p_timer = new QTimer(this);
    connect(this->p_timer, &QTimer::timeout, this, &Hub::slot_timeOut_heartbit);
    this->p_timer->start(10000);
}

void Hub::set_p_md(StatModel *set_md)
{
    this->p_md = set_md;
    return;
}

void Hub::set_p_db(DB_PostgreSQL *set_db)
{
    this->p_obj_db = set_db;
    return;
}

void Hub::slot_start_sv()
{
    QFile cert_file("../../../ssl/server.crt");
    QFile key_file("../../../ssl/server.key");
    QString sv_name = "WebSocSv";

    if (!cert_file.open(QIODevice::ReadOnly))
    {
        qDebug() << "cert open fail";
        return;
    }

    if (!key_file.open(QIODevice::ReadOnly))
    {
        qDebug() << "key open fail";
        return;
    }

    QSslCertificate cert(&cert_file, QSsl::Pem);
    QSslKey key(&key_file, QSsl::Rsa, QSsl::Pem);

    QSslConfiguration ssl_cfg = QSslConfiguration::defaultConfiguration();
    ssl_cfg.setLocalCertificate(cert);
    ssl_cfg.setPrivateKey(key);
    ssl_cfg.setProtocol(QSsl::TlsV1_2OrLater);

    this->p_webSoc_Sv = new QWebSocketServer(sv_name, QWebSocketServer::SecureMode, this);

    this->p_webSoc_Sv->setSslConfiguration(ssl_cfg);

    QObject::connect(this->p_webSoc_Sv,
                     &QWebSocketServer::sslErrors,
                     [](const QList<QSslError> &vl_err) {
                         qDebug() << "ssl error";
                         for (const QSslError &err : vl_err)
                         {
                             qDebug() << err.errorString();
                         }
                     });

    bool ret_listen = this->p_webSoc_Sv->listen(QHostAddress::Any, 12345);

    if (ret_listen == false)
    {
        qDebug() << Q_FUNC_INFO << " listen Err";
        return;
    }

    connect(this->p_webSoc_Sv, &QWebSocketServer::newConnection, this, &Hub::slot_new_connection);

    if (this->p_webSoc_Sv->isListening())
    {
        qDebug() << Q_FUNC_INFO << " listen OK";
    }
}

void Hub::slot_end()
{
    if (this->p_webSoc_Sv && this->p_webSoc_Sv->isListening())
    {
        this->p_webSoc_Sv->close();
    }

    for (auto wk : qmp_wk)
    {
        wk->deleteLater();
    }

    qmp_wk.clear();
    emit this->sig_end();
    return;
}

void Hub::slot_new_connection()
{
    qDebug() << Q_FUNC_INFO << "새 연결 시작";

    QWebSocket *new_cli = this->p_webSoc_Sv->nextPendingConnection();

    if (!new_cli)
    {
        qDebug() << Q_FUNC_INFO << "nextPendingConnection이 null 반환!";
        return;
    }

    qDebug() << Q_FUNC_INFO << "새 클라이언트 소켓:" << new_cli;
    qDebug() << Q_FUNC_INFO << "소켓 상태:" << new_cli->state();

    WK_Soc *wk = new WK_Soc(this);
    int new_id = this->id_mp++;

    // p_md를 먼저 설정해야 set_p_webSoc 내부의 connect가 정상 작동함
    wk->set_p_md(this->p_md);
    wk->set_p_webSoc(new_cli, new_id);
    wk->set_p_Hub(this);
    wk->set_p_db(this->p_obj_db);

    this->qmp_wk.insert(new_id, wk);
    qDebug() << Q_FUNC_INFO << "워커 추가 완료";

    return;
}

void Hub::slot_del_mpWk(int id_mp)
{
    this->qmp_wk.remove(id_mp);
    return;
}

void Hub::slot_timeOut_heartbit()
{
    for (auto it = qmp_wk.begin(); it != qmp_wk.end(); it++)
    {
        it.value()->occur_heartbit();
    }

    return;
}
