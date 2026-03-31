#include "MD_charging_log.h"

MD_charging_log::MD_charging_log(QObject *parent)
    : QAbstractListModel{parent}
{
    // QVector<charging_log_admin_cnv> tmp;
    // struct charging_log_admin_cnv test_data;

    // test_data.actual_payment = "123";
    // tmp.push_back(test_data);

    // this->slot_qvec_update(tmp);
}

int MD_charging_log::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }

    return this->qvec.size();
}

QVariant MD_charging_log::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= qvec.size())
    {
        return QVariant();
    }

    if (role == created_at_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).created_at);
        return qva;
    }
    else if (role == updated_at_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).updated_at);
        return qva;
    }
    else if (role == row_id_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).row_id);
        return qva;
    }
    else if (role == store_id_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).store_id);
        return qva;
    }
    else if (role == hmi_id_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).hmi_id);
        return qva;
    }
    else if (role == ocpp_tx_id_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).ocpp_tx_id);
        return qva;
    }
    else if (role == card_uid_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).card_uid);
        return qva;
    }
    else if (role == start_time_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).start_time);
        return qva;
    }
    else if (role == end_time_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).end_time);
        return qva;
    }
    else if (role == duration_time_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).duration_time);
        return qva;
    }
    else if (role == average_kwh_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).average_kwh);
        return qva;
    }
    else if (role == soc_start_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).soc_start);
        return qva;
    }
    else if (role == soc_end_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).soc_end);
        return qva;
    }
    else if (role == advance_payment_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).advance_payment);
        return qva;
    }
    else if (role == cancel_payment_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).cancel_payment);
        return qva;
    }
    else if (role == actual_payment_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).actual_payment);
        return qva;
    }
    else if (role == unit_price_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).unit_price);
        return qva;
    }
    else if (role == tariff_type_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).tariff_type);
        return qva;
    }
    else if (role == session_status_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).session_status);
        return qva;
    }
    else if (role == stop_reason_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).stop_reason);
        return qva;
    }
    else if (role == local_tx_id_Role)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).local_tx_id);
        return qva;
    }

    return QVariant();
}

QHash<int, QByteArray> MD_charging_log::roleNames() const
{
    QHash<int, QByteArray> qh;

    qh[created_at_Role] = "created_at";
    qh[updated_at_Role] = "updated_at";
    qh[row_id_Role] = "row_id";
    qh[store_id_Role] = "store_id";
    qh[hmi_id_Role] = "hmi_id";
    qh[ocpp_tx_id_Role] = "ocpp_tx_id";
    qh[card_uid_Role] = "card_uid";
    qh[start_time_Role] = "start_time";
    qh[end_time_Role] = "end_time";
    qh[duration_time_Role] = "duration_time";
    qh[average_kwh_Role] = "average_kwh";
    qh[soc_start_Role] = "soc_start";
    qh[soc_end_Role] = "soc_end";
    qh[advance_payment_Role] = "advance_payment";
    qh[cancel_payment_Role] = "cancel_payment";
    qh[actual_payment_Role] = "actual_payment";
    qh[unit_price_Role] = "unit_price";
    qh[tariff_type_Role] = "tariff_type";
    qh[session_status_Role] = "session_status";
    qh[stop_reason_Role] = "stop_reason";
    qh[local_tx_id_Role] = "local_tx_id";

    return qh;
}

Q_INVOKABLE void MD_charging_log::reset_md()
{
    beginResetModel();
    endResetModel();
}

void MD_charging_log::slot_qvec_update(QVector<charging_log_admin> new_qvec)
{
    qDebug() << Q_FUNC_INFO;
    beginResetModel();
    this->qvec = new_qvec;
    endResetModel();
    qDebug() << this->qvec.size();
    return;
}
