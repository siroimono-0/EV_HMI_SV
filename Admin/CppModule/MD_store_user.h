#ifndef MD_STORE_USER_H
#define MD_STORE_USER_H

#include <QAbstractListModel>
#include <QDate>
#include <QObject>
#include "../../Common/StatData.h"

class MD_store_user : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MD_store_user(QObject *parent = nullptr);

    // QML에서 접근할 "역할(role)" 이름 정의
    enum Role {
        id_Role = Qt::UserRole + 1,
        name_Role = Qt::UserRole + 2,
        location_Role = Qt::UserRole + 3
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
    void slot_qvec_update(QVector<store_user_admin> new_qvec);

signals:

private:
    QVector<store_user_admin> qvec;
};
Q_DECLARE_METATYPE(MD_store_user *)

#endif // MD_STORE_USER_H
