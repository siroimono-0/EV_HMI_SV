#include "Cpp_Module.h"
#include "Hub.h"
#include "StatModel.h"

Cpp_Module::Cpp_Module(QObject *parent)
    : QObject{parent}
{
    this->hmi_md = new StatModel(this);
}

Q_INVOKABLE bool Cpp_Module::set_webSoc_Sv(QVariant s)
{
    this->p_WebSoc_Hub = new Hub;
    this->p_th_HUB = new QThread;
    this->p_WebSoc_Hub->set_p_md(this->hmi_md);

    this->p_WebSoc_Hub->moveToThread(this->p_th_HUB);

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
