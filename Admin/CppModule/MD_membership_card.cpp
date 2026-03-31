#include "MD_membership_card.h"

MD_membership_card::MD_membership_card(QObject *parent)
    : QAbstractListModel{parent}
{}

int MD_membership_card::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }

    return this->qvec.size();
}

QVariant MD_membership_card::data(const QModelIndex &index, int role) const
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
    else if (role == balance_total_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).balance_total);
        return qva;
    }
    else if (role == balance_available_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).balance_available);
        return qva;
    }
    else if (role == hold_amount_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).hold_amount);
        return qva;
    }
    else if (role == transaction_state_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).transaction_state);
        return qva;
    }

    return QVariant();
}

QHash<int, QByteArray> MD_membership_card::roleNames() const
{
    QHash<int, QByteArray> qh;
    qh[card_uid_Role] = "card_uid";
    qh[balance_total_Role] = "balance_total";
    qh[balance_available_Role] = "balance_available";
    qh[hold_amount_Role] = "hold_amount";
    qh[transaction_state_Role] = "transaction_state";

    return qh;
}

Q_INVOKABLE void MD_membership_card::reset_md()
{
    beginResetModel();
    endResetModel();
}

void MD_membership_card::slot_qvec_update(QVector<membership_card_admin> new_qvec)
{
    qDebug() << Q_FUNC_INFO;
    beginResetModel();
    this->qvec = new_qvec;
    endResetModel();
    qDebug() << this->qvec.size();
    return;
}
