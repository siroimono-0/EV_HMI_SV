#include "MD_hmi_device.h"

MD_hmi_device::MD_hmi_device(QObject *parent)
    : QAbstractListModel{parent}
{}

int MD_hmi_device::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }

    return this->qvec.size();
}

QVariant MD_hmi_device::data(const QModelIndex &index, int role) const
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
    return QVariant();
}

QHash<int, QByteArray> MD_hmi_device::roleNames() const
{
    QHash<int, QByteArray> qh;
    qh[hmi_id_Role] = "hmi_id";
    qh[store_id_Role] = "store_id";

    return qh;
}

Q_INVOKABLE void MD_hmi_device::reset_md()
{
    beginResetModel();
    endResetModel();
}

void MD_hmi_device::slot_qvec_update(QVector<hmi_device_admin> new_qvec)
{
    qDebug() << Q_FUNC_INFO;
    beginResetModel();
    this->qvec = new_qvec;
    endResetModel();
    qDebug() << this->qvec.size();
    return;
}
