#include "WK_Soc.h"
#include "Hub.h"
#include "StatModel.h"

WK_Soc::WK_Soc(QObject *parent)
    : QObject{parent}
{
}

void WK_Soc::set_p_webSoc(QWebSocket *set_webSoc, int id_mp)
{
    this->p_webSoc = set_webSoc;
    this->id_mp = id_mp;
    // nextpending 으로 받은 소켓 객체 부모설정
    // WK객체 죽을 때 소켓 같이 삭제 유도
    this->p_webSoc->setParent(this);

    connect(this->p_webSoc, &QWebSocket::textMessageReceived, this, &WK_Soc::slot_textRecved);

    // 소켓 연결 끊어지면 소켓 삭제 + 워커 객체 삭제
    // 소켓 연결 끊어지면 Hub qvec에서 wk* 삭제
    // 소켓 연결 끊어지면 Model 에서 st_stat 삭제
    connect(this->p_webSoc, &QWebSocket::disconnected, this, &WK_Soc::slot_disconnect_Soc);

    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_Soc::slot_disconnect_Soc()
{
    // 중복 호출 방지
    if (this->stat_disconnect == true)
    {
        return;
    }
    this->stat_disconnect = true;

    // 소켓 연결 끊어지면 Hub qvec에서 wk* 삭제
    this->p_Hub->slot_del_mpWk(this->id_mp);

    // 소켓 연결 끊어지면 Model 에서 st_stat 삭제
    QMetaObject::invokeMethod(this->p_md,
                              &StatModel::slot_qvec_del,
                              Qt::QueuedConnection,
                              this->id_common);

    // 소켓 연결 끊어지면 워커객체 삭제 (소유 중 Soc 자동 삭제)
    // 부모 WK객체이므로
    this->deleteLater();

    return;
}

void WK_Soc::slot_textRecved(QString msg)
{
    qDebug() << Q_FUNC_INFO;

    QByteArray qba = msg.toUtf8();
    QJsonParseError json_err;
    QJsonDocument json_doc = QJsonDocument::fromJson(qba, &json_err);

    if (json_err.error != QJsonParseError::NoError)
    {
        qDebug() << "Json Err";
    }

    QJsonObject json_obj = json_doc.object();
    struct stat_data st_stat;
    st_stat.number = json_obj["number"].toInt();
    st_stat.id = json_obj["id"].toInt();
    st_stat.location = json_obj["location"].toString();
    st_stat.date = json_obj["date"].toString();
    st_stat.stat = json_obj["stat"].toInt();

    qDebug() << st_stat.id;
    qDebug() << st_stat.location;
    qDebug() << st_stat.date;

    // 구별자 id 설정
    this->id_common = st_stat.id;
    emit sig_update_md(st_stat);

    qDebug() << Q_FUNC_INFO;
    return;
}

void WK_Soc::set_p_md(StatModel *set_md)
{
    this->p_md = set_md;

    // p_md 설정 후 모델 업데이트 시그널 연결
    if (this->p_md)
    {
        connect(this, &WK_Soc::sig_update_md, this->p_md, &StatModel::slot_qvec_update);
    }

    return;
}

void WK_Soc::set_p_Hub(Hub *set_Hub)
{
    this->p_Hub = set_Hub;
    return;
}
