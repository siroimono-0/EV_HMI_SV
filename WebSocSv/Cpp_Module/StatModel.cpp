#include "StatModel.h"

StatModel::StatModel(QObject *parent)
    : QAbstractListModel{parent}
{
    struct stat_data test_data;
    test_data.number = 0;
    QString qs_date = QDate::currentDate().toString("yyyy-MM-dd");

    test_data.date = qs_date;
    test_data.location = "seoul";
    test_data.id = 999;
    test_data.stat = 0;

    this->slot_qvec_update(test_data);
}

int StatModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
    {
        return 0;
    }

    return this->qvec.size();
}

QVariant StatModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= qvec.size())
    {
        return QVariant();
    }

    if (role == NumberRole)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).number);
        return qva;
    }
    else if (role == DateRole)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).date);
        return qva;
    }
    else if (role == LocationRole)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).location);
        return qva;
    }
    else if (role == IDRole)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).id);
        return qva;
    }
    else if (role == StatRole)
    {
        QVariant qva = QVariant(this->qvec.at(index.row()).stat);
        return qva;
    }

    return QVariant();
}

QHash<int, QByteArray> StatModel::roleNames() const
{
    QHash<int, QByteArray> qh;
    qh[NumberRole] = "number";
    qh[DateRole] = "date";
    qh[LocationRole] = "location";
    qh[IDRole] = "id";
    qh[StatRole] = "stat";

    return qh;
}

Q_INVOKABLE void StatModel::reset_md()
{
    beginResetModel();
    endResetModel();
}

void StatModel::slot_qvec_update(stat_data st_stat)
{
    qDebug() << Q_FUNC_INFO;
    // 먼져 이미 있는지 아이디로 찾아야댐
    qDebug() << st_stat.location;
    qDebug() << st_stat.date;
    qDebug() << st_stat.id;
    qDebug() << st_stat.stat;
    bool flag = false;
    int find_idx = 0;

    for (int i = 0; i < this->qvec.size(); i++)
    {
        if (qvec[i].id == st_stat.id)
        {
            flag = true;
            find_idx = i;
            break;
        }
    }

    if (flag == false)
    {
        int row = this->qvec.size();
        st_stat.number = row;

        beginInsertRows(QModelIndex(), row, row);
        this->qvec.push_back(st_stat);
        endInsertRows();
    }
    else
    {
        // 컨테이너 값 변경
        this->qvec[find_idx] = st_stat;

        // 변경된 값 Qml에게 수정하라고 알림
        QVector<int> change_Role{NumberRole, DateRole, LocationRole, IDRole, StatRole};
        QModelIndex idx = index(find_idx);
        emit dataChanged(idx, idx, change_Role);
    }
    return;
}

void StatModel::slot_qvec_del(int id_common)
{
    int find_idx = 0;
    bool flag = false;

    for (int i = 0; i < this->qvec.size(); i++)
    {
        if (qvec[i].id == id_common)
        {
            find_idx = i;
            flag = true;
            break;
        }
    }

    if (flag == true)
    {
        beginRemoveRows(QModelIndex(), find_idx, find_idx);
        this->qvec.removeAt(find_idx);
        endRemoveRows();
        return;
    }
    qDebug() << Q_FUNC_INFO;
}
