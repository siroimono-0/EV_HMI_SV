#include "Cpp_Module.h"
#include "./Cpp_Module/StatStore.h"
#include "./Cpp_Module/WK_Serial.h"
#include "./Cpp_Module/WK_WebSocket.h"

Cpp_Module::Cpp_Module(QObject *parent)
    : QObject{parent}
{
    // this->set_p_wk_websoc();
    this->create_Serial();
    this->p_stat = new StatStore(this);
}

Cpp_Module::~Cpp_Module()
{
    this->end_p_wk_websoc();
    this->end_p_wk_serial();
    return;
}

void Cpp_Module::end_p_wk_websoc()
{
    if (this->p_wk_websoc && this->p_th_websoc->isRunning())
    {
        QMetaObject::invokeMethod(this->p_wk_websoc, &WK_WebSocket::slot_stop, Qt::QueuedConnection);
    }

    this->p_th_websoc->quit();

    this->p_th_websoc->wait(3000);

    return;
}

void Cpp_Module::end_p_wk_serial()
{
    return;
}

Q_INVOKABLE void Cpp_Module::join_WebSv(QString id, QString location)
{
    this->create_WebSoc();

    struct stat_data st_stat = {0};

    QString qs_date = QDate::currentDate().toString("yyyy-MM-dd");

    st_stat.id = id.toInt();
    st_stat.location = location;
    st_stat.date = qs_date;
    st_stat.stat = 0;

    this->p_stat->set_First_stat(st_stat);

    qDebug() << Q_FUNC_INFO;
    return;
}

void Cpp_Module::create_WebSoc()
{
    this->p_th_websoc = new QThread(this);
    this->p_wk_websoc = new WK_WebSocket();
    this->p_wk_websoc->set_p_stat(this->p_stat);
    this->p_wk_websoc->set_p_Module(this);

    this->p_wk_websoc->moveToThread(this->p_th_websoc);
    connect(this->p_th_websoc, &QThread::started, this->p_wk_websoc, &WK_WebSocket::slot_Connect_Sv);
    connect(this->p_wk_websoc, &WK_WebSocket::sig_end, this->p_th_websoc, &QThread::quit);
    connect(this->p_th_websoc, &QThread::finished, this->p_wk_websoc, &WK_WebSocket::deleteLater);
    connect(this->p_th_websoc, &QThread::finished, this->p_th_websoc, &QThread::deleteLater);

    this->p_th_websoc->start();
    qDebug() << Q_FUNC_INFO;
    return;
}

void Cpp_Module::create_Serial()
{
    this->p_th_serial = new QThread();
    this->p_wk_serial = new WK_Serial();
    this->p_wk_serial->moveToThread(this->p_th_serial);

    this->p_th_serial->start();
    return;
}
