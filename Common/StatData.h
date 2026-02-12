#ifndef STATDATA_H
#define STATDATA_H
#include <QMetaType>
#include <QObject>

enum STAT {

};

// id 값으로 이미 있는지 확인하고 있으면 해당 요소 없데이트
// 없으면 추가
struct stat_data
{
    int id;
    int number;
    QString date;
    QString location;
    int stat;
};

struct details
{};

Q_DECLARE_METATYPE(stat_data)
#endif // STATDATA_H
