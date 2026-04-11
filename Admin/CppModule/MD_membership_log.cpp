#include "MD_membership_log.h"

MD_membership_log::MD_membership_log(QObject *parent)
    : QAbstractListModel{parent}
{}

int MD_membership_log::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }

    return this->qvec.size();
}

QVariant MD_membership_log::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= qvec.size())
    {
        return QVariant();
    }

    if (role == card_uid_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).card_uid);
        return qva;
    }
    else if (role == transaction_id_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).transaction_id);
        return qva;
    }
    else if (role == event_type_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).event_type);
        return qva;
    }
    else if (role == amount_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).amount);
        return qva;
    }
    else if (role == balance_available_before_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).balance_available_before);
        return qva;
    }
    else if (role == balance_available_after_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).balance_available_after);
        return qva;
    }
    else if (role == hold_amount_before_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).hold_amount_before);
        return qva;
    }
    else if (role == hold_amount_after_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).hold_amount_after);
        return qva;
    }
    else if (role == transaction_state_before_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).transaction_state_before);
        return qva;
    }
    else if (role == transaction_state_after_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).transaction_state_after);
        return qva;
    }
    else if (role == created_at_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).created_at);
        return qva;
    }
    else if (role == request_id_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).request_id);
        return qva;
    }

    return QVariant();
}

QHash<int, QByteArray> MD_membership_log::roleNames() const
{
    QHash<int, QByteArray> qh;

    qh[card_uid_Role] = "card_uid";
    qh[transaction_id_Role] = "transaction_id";
    qh[event_type_Role] = "event_type";
    qh[amount_Role] = "amount";
    qh[balance_available_before_Role] = "balance_available_before";
    qh[balance_available_after_Role] = "balance_available_after";
    qh[hold_amount_before_Role] = "hold_amount_before";
    qh[hold_amount_after_Role] = "hold_amount_after";
    qh[transaction_state_before_Role] = "transaction_state_before";
    qh[transaction_state_after_Role] = "transaction_state_after";
    qh[created_at_Role] = "created_at";
    qh[request_id_Role] = "request_id";

    return qh;
}

Q_INVOKABLE void MD_membership_log::reset_md()
{
    beginResetModel();
    endResetModel();
}

void MD_membership_log::slot_qvec_update(QVector<membership_log_admin> new_qvec)
{
    qDebug() << Q_FUNC_INFO;
    beginResetModel();
    this->qvec = new_qvec;
    endResetModel();
    qDebug() << this->qvec.size();
    return;
}
