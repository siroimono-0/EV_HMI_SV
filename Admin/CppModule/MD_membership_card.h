#ifndef MD_MEMBERSHIP_CARD_H
#define MD_MEMBERSHIP_CARD_H
#include <QAbstractListModel>
#include <QDate>
#include <QObject>
#include "../../Common/StatData.h"

class MD_membership_card : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MD_membership_card(QObject *parent = nullptr);

    // QML에서 접근할 "역할(role)" 이름 정의
    enum Role {
        card_uid_Role = Qt::UserRole + 1,
        balance_total_Role = Qt::UserRole + 2,
        balance_available_Role = Qt::UserRole + 3,
        hold_amount_Role = Qt::UserRole + 4,
        transaction_state_Role = Qt::UserRole + 5
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
    void slot_qvec_update(QVector<membership_card_admin> new_qvec);

signals:

private:
    QVector<membership_card_admin> qvec;
};
Q_DECLARE_METATYPE(MD_membership_card *)

#endif // MD_MEMBERSHIP_CARD_H
