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

struct db_data
{
    // 카드 인증시 insert
    // 충전 시작시 update
    // 충전 데이터 받아오면 update 1회
    // 충전 종료시 update

    uint64_t session_id; // db에서 자동생성
    uint32_t store_id;   // store클래스 멤버변수 // 카드 인증시 생성
    QString hmi_id;      // store클래스 멤버변수 // 카드 인증시 생성

    uint32_t ocpp_tx_id; // (transactionId) // sv ack 오면 생성
    QString card_uid;    // store클래스 멤버변수 // 카드 인증시 생성

    // 시간/결과
    // created_at / updated_at는 DB가 자동 관리(DEFAULT + 트리거)
    QString start_time;     // store클래스 멤버변수 // 충전 시작시 생성
    uint32_t end_time;      // 추가 필요 // 충전 완료시 생성
    uint32_t duration_time; // 경과 시간 // 충전 완료시 생성
    uint32_t average_kWh;   // 추가 필요 // 충전 완료시 생성

    uint32_t soc_start; // 충전 시작시 생성
    uint32_t soc_end;   // 충전 완료시 생성

    // 금액(정산용)
    uint32_t advance_payment; // (선결제 “가정” 금액) // 카드 인증시 생성
    uint32_t cancel_payment;  // (부분취소된 금액) // 충전 완료시 생성
    uint32_t actual_payment;  //(실제청구 = advance - cancel)  // 충전 완료시 생성
    uint32_t unit_price;      //(원/kWh)
    QString tariff_type;      //(단가 방식) // 카드 인증시 생성

    // 상태
    QString session_status; // db 업데이트마다 지속 갱신
    /*
    Authorize Accepted → AUTHORIZED
    StartTransaction OK → CHARGING
    StopTransaction OK → FINISHED
    FAILED
    TIMEOUT
    */
    QString stop_reason; // db 업데이트마다 지속 갱신
    /*
    LOCAL  //  사용자 종료
    REMOTE  //  어드민 종료
    FAULT
    TIMEOUT
     */
};
#endif // STATDATA_H
