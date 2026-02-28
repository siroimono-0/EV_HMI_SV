#ifndef STATMODEL_H
#define STATMODEL_H

#include <QAbstractListModel>
#include <QDate>
#include <QObject>
#include "../../Common/StatData.h"

// 등록 시간
// 충전기 도로명
// 충전기명
// 현재 상태

class StatModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit StatModel(QObject *parent = nullptr);

    // QML에서 접근할 "역할(role)" 이름 정의
    enum Role {
        NumberRole = Qt::UserRole + 1,
        DateRole = Qt::UserRole + 2,
        LocationRole = Qt::UserRole + 3,
        IDRole = Qt::UserRole + 4,
        StatRole = Qt::UserRole + 5
    };
    Q_ENUM(Role) // QML에서도 enum을 인식할 수 있게 함

    // 모델의 총 행 개수 반환 (QML의 model.count 등에서 사용)
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // 특정 인덱스의 데이터 반환 (QML에서 model.text 요청 시 호출됨)
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // QML에서 model.text로 접근할 수 있도록 role과 이름 매핑
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void reset_md();
public slots:
    void slot_qvec_update(stat_data st_stat);
    void slot_qvec_del(int id_common);

signals:

private:
    QVector<stat_data> qvec;
};

#endif // STATMODEL_H
