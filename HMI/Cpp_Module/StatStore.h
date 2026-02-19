#ifndef STATSTORE_H
#define STATSTORE_H

#include <QDebug>
#include <QObject>
#include "../Common/StatData.h"

class StatStore : public QObject
{
    Q_OBJECT
public:
    explicit StatStore(QObject *parent = nullptr);
    void set_First_stat(stat_data st_stat);

public slots:
    void slot_update_FromSoc(stat_data st_stat);
    void slot_update_FromSerial(stat_data st_stat);
    void slot_update_FromModule(stat_data st_stat);
    void slot_update_current();

    stat_data slot_get_stat();

signals:
    // 상태 값 변경시 발생
    void sig_Stat_changed(stat_data st_stat);

private:
    struct stat_data st_stat;
};

#endif // STATSTORE_H
