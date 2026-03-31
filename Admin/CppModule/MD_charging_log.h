#ifndef MD_CHARGING_LOG_H
#define MD_CHARGING_LOG_H

#include <QAbstractListModel>
#include <QDate>
#include <QObject>
#include "../../Common/StatData.h"

class MD_charging_log : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MD_charging_log(QObject *parent = nullptr);

    // QML에서 접근할 "역할(role)" 이름 정의
    enum Role {
        created_at_Role = Qt::UserRole + 1,
        updated_at_Role = Qt::UserRole + 2,
        row_id_Role = Qt::UserRole + 3,
        store_id_Role = Qt::UserRole + 4,
        hmi_id_Role = Qt::UserRole + 5,
        ocpp_tx_id_Role = Qt::UserRole + 6,
        card_uid_Role = Qt::UserRole + 7,
        start_time_Role = Qt::UserRole + 8,
        end_time_Role = Qt::UserRole + 9,
        duration_time_Role = Qt::UserRole + 10,
        average_kwh_Role = Qt::UserRole + 11,
        soc_start_Role = Qt::UserRole + 12,
        soc_end_Role = Qt::UserRole + 13,
        advance_payment_Role = Qt::UserRole + 14,
        cancel_payment_Role = Qt::UserRole + 15,
        actual_payment_Role = Qt::UserRole + 16,
        unit_price_Role = Qt::UserRole + 17,
        tariff_type_Role = Qt::UserRole + 18,
        session_status_Role = Qt::UserRole + 19,
        stop_reason_Role = Qt::UserRole + 20,
        local_tx_id_Role = Qt::UserRole + 21
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
    void slot_qvec_update(QVector<charging_log_admin> new_qvec);
    // void slot_qvec_update(QVector<charging_log_admin_cnv> new_qvec);

signals:

private:
    QVector<charging_log_admin> qvec;
    // QVector<charging_log_admin_cnv> qvec;
};

Q_DECLARE_METATYPE(MD_charging_log *)
#endif // MD_CHARGING_LOG_H
