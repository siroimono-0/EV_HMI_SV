#include "Cpp_Module.h"
#include "Hub.h"
#include "StatModel.h"

Cpp_Module::Cpp_Module(QObject *parent)
    : QObject{parent}
{
    this->hmi_md = new StatModel(this);
    this->create_obj_DB();
    this->set_webSoc_Sv();
}

Cpp_Module::~Cpp_Module()
{
    QMetaObject::invokeMethod(this->p_obj_db, &DB_PostgreSQL::slot_end, Qt::QueuedConnection);

    this->p_th_db->quit();
    this->p_th_db->wait();

    QMetaObject::invokeMethod(this->p_WebSoc_Hub, &Hub::slot_end, Qt::QueuedConnection);

    this->p_th_HUB->quit();
    this->p_th_HUB->wait();

    return;
}

void Cpp_Module::create_obj_DB()
{
    // 멀티 쓰레드 이기 때문에 부모 설정 X
    this->p_obj_db = new DB_PostgreSQL();
    this->p_obj_db->set_p_Module(this);

    this->p_th_db = new QThread();
    this->p_obj_db->moveToThread(this->p_th_db);

    connect(this->p_th_db, &QThread::started, this->p_obj_db, &DB_PostgreSQL::createDB);

    // 서버 프로세스 죽을때까지 살아있는 객체이므로
    // Module 소멸자에서 삭제하도록 설정
    connect(this->p_obj_db, &DB_PostgreSQL::sig_end, this->p_th_db, &QThread::quit);
    connect(this->p_th_db, &QThread::finished, this->p_obj_db, &DB_PostgreSQL::deleteLater);
    connect(this->p_th_db, &QThread::finished, this->p_th_db, &QThread::deleteLater);

    this->p_th_db->start();
    qDebug() << Q_FUNC_INFO;
    return;
}

Q_INVOKABLE bool Cpp_Module::set_webSoc_Sv()
{
    this->p_WebSoc_Hub = new Hub;
    this->p_th_HUB = new QThread;
    this->p_WebSoc_Hub->set_p_md(this->hmi_md);
    this->p_WebSoc_Hub->set_p_db(this->p_obj_db);

    this->p_WebSoc_Hub->moveToThread(this->p_th_HUB);

    // 서버 프로세스 죽을때까지 살아있는 객체이므로
    // Module 소멸자에서 삭제하도록 설정
    connect(this->p_th_HUB, &QThread::started, this->p_WebSoc_Hub, &Hub::slot_start_sv);
    connect(this->p_WebSoc_Hub, &Hub::sig_end, this->p_th_HUB, &QThread::quit);
    connect(this->p_th_HUB, &QThread::finished, this->p_WebSoc_Hub, &Hub::deleteLater);
    connect(this->p_th_HUB, &QThread::finished, this->p_th_HUB, &QThread::deleteLater);

    this->p_th_HUB->start();

    qDebug() << Q_FUNC_INFO;

    return true;
}

StatModel *Cpp_Module::get_hmi_md()
{
    return this->hmi_md;
}

/* 수정
Q_INVOKABLE bool Cpp_Module::createStore_sql(QString id, const QString name, const QString location)
{
    int cnv_id = id.toInt();
    bool ret_slot_createStore = false;
    QMetaObject::invokeMethod(this->p_obj_db,
                              "slot_createStore",
                              Qt::BlockingQueuedConnection,
                              Q_ARG(int, cnv_id),
                              Q_ARG(QString, name),
                              Q_ARG(QString, location),
                              Q_RETURN_ARG(bool, ret_slot_createStore));

    return ret_slot_createStore;
} */
