#include "MD_store_user.h"

MD_store_user::MD_store_user(QObject *parent)
    : QAbstractListModel{parent}
{}

int MD_store_user::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }

    return this->qvec.size();
}

QVariant MD_store_user::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= qvec.size())
    {
        return QVariant();
    }

    if (role == id_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).id);
        return qva;
    }
    else if (role == name_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).name);
        return qva;
    }
    else if (role == location_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).location);
        return qva;
    }

    return QVariant();
}

QHash<int, QByteArray> MD_store_user::roleNames() const
{
    QHash<int, QByteArray> qh;
    qh[id_Role] = "id";
    qh[name_Role] = "name";
    qh[location_Role] = "location";

    return qh;
}

Q_INVOKABLE void MD_store_user::reset_md()
{
    beginResetModel();
    endResetModel();
}

void MD_store_user::slot_qvec_update(QVector<store_user_admin> new_qvec)
{
    qDebug() << Q_FUNC_INFO;
    beginResetModel();
    this->qvec = new_qvec;
    endResetModel();
    qDebug() << this->qvec.size();
    return;
}
