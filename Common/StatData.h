#ifndef STATDATA_H
#define STATDATA_H
#include <QMetaType>
#include <QObject>

typedef enum CHARGER_STATE {
    STATE_CHARGING = 0, // 충전중
    STATE_IDLE = 1,     // 대기중
    STATE_FAULT         // 에러 상태
} CHARGER_STATE;

typedef enum ERR_CODE {
    ERR_NONE = 0,    // 정상
    ERR_OVERVOLT,    // 과전압
    ERR_OVERCURRENT, // 과전류
    ERR_OVERTEMP,    // 과온
    ERR_RELAY,       // 릴레이 이상
    ERR_COMM,        // 통신 이상
    ERR_EMERGENCY    // 비상정지
} ERR_CODE;

struct charging_stat
{
    uint16_t charger_stat;
    uint16_t err_code;
    uint16_t voltage;
    uint16_t current;
    uint32_t battery_current;
    uint32_t battery_full;
    uint32_t elapsed_time;
};
Q_DECLARE_METATYPE(charging_stat)

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
Q_DECLARE_METATYPE(stat_data)

struct details
{};

struct store_info
{
    int id;
    QString name;
    QString location;
};

Q_DECLARE_METATYPE(store_info)
#endif // STATDATA_H
