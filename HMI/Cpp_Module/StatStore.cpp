#include "StatStore.h"

StatStore::StatStore(QObject *parent)
    : QObject{parent}
{}

void StatStore::set_First_stat(stat_data st_stat)
{
    this->st_stat = st_stat;
    return;
}

void StatStore::slot_update_FromSoc(stat_data st_stat)
{
    this->st_stat = st_stat;
    emit this->sig_Stat_changed(this->st_stat);

    qDebug() << Q_FUNC_INFO;
    return;
}

void StatStore::slot_update_FromSerial(stat_data st_stat)
{
    this->st_stat = st_stat;
    emit this->sig_Stat_changed(this->st_stat);

    qDebug() << Q_FUNC_INFO;
    return;
}

void StatStore::slot_update_FromModule(stat_data st_stat)
{
    this->st_stat = st_stat;
    emit this->sig_Stat_changed(this->st_stat);

    qDebug() << Q_FUNC_INFO;
    return;
}

void StatStore::slot_update_current()
{
    emit this->sig_Stat_changed(this->st_stat);

    qDebug() << Q_FUNC_INFO;
    return;
}
