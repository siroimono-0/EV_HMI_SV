#include "MD_hmi_current_stat.h"

MD_hmi_current_stat::MD_hmi_current_stat(QObject *parent)
    : QAbstractListModel{parent}
{}

int MD_hmi_current_stat::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }

    return this->qvec.size();
}

QVariant MD_hmi_current_stat::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= qvec.size())
    {
        return QVariant();
    }

    if (role == hmi_id_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).hmi_id);
        return qva;
    }
    else if (role == store_id_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).store_id);
        return qva;
    }
    else if (role == ws_connected_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).ws_connected);
        return qva;
    }
    else if (role == last_heartbeat_at_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).last_heartbeat_at);
        return qva;
    }
    else if (role == screen_name_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).screen_name);
        return qva;
    }
    else if (role == updated_at_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).updated_at);
        return qva;
    }

    return QVariant();
}

QHash<int, QByteArray> MD_hmi_current_stat::roleNames() const
{
    QHash<int, QByteArray> qh;
    qh[hmi_id_Role] = "hmi_id";
    qh[store_id_Role] = "store_id";
    qh[ws_connected_Role] = "ws_connected";
    qh[last_heartbeat_at_Role] = "last_heartbeat_at";
    qh[screen_name_Role] = "screen_name";
    qh[updated_at_Role] = "updated_at";

    return qh;
}

Q_INVOKABLE void MD_hmi_current_stat::reset_md()
{
    beginResetModel();
    endResetModel();
}

void MD_hmi_current_stat::slot_qvec_update(QVector<hmi_current_stat_admin> new_qvec)
{
    qDebug() << Q_FUNC_INFO;
    beginResetModel();
    this->qvec = new_qvec;
    endResetModel();
    qDebug() << this->qvec.size();
    return;
}
