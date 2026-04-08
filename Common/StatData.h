#ifndef STATDATA_H
#define STATDATA_H
#include <QDateTime>
#include <QMetaType>
#include <QObject>

typedef enum EXIT_CODE { EXIT_NOMAL = 0, EXIT_RESTART = 85 } EXIT_CODE;

typedef enum AD_NEED {
    NEED_DOWNLOAD = 0, // 다운
    NEED_PLAY = 1,     // 다운이미 대있음 재생 마킹
    NEED_NOT           // 마킹도 대있음 그냥 업뎃한번
} AD_NEED;

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

struct membership_backUp_sqlite
{
    // 인증시 hold 상태
    // 인증 1회 시도 -> db 미응답 -> lite 저장
    // 인증 2회 시도시 성공 -> captured 상태
    // lite 재시도 -> 상태 hold일 때만 진행댐으로 무시댐
    QString card_uid;
    uint32_t adv_pay;
    uint32_t act_pay;
    uint32_t can_pay;
    uint32_t t_id;
    QString request_id;
};

struct membership_log
{
    QString card_uid;
    uint32_t transaction_id; // db생성
    QString event_type;
    uint32_t amount;
    uint32_t balance_available_before;
    uint32_t balance_available_after;
    uint32_t hold_amount_before;
    uint32_t hold_amount_after;
    QString transaction_state_before;
    QString transaction_state_after;
    QString request_id;
};

struct heartbit_data
{
    QString hmi_id;              // hmi 생성
    uint32_t store_id;           // hmi 생성
    bool ws_connected;           // sv가 수신 후 생성
    QDateTime last_heartbeat_at; // sv가 수신한 후 생성
    QString screen_name;         // hmi 갱신
    // updated_at // db 자동생성
};
Q_DECLARE_METATYPE(heartbit_data)

// sqlite backUp 데이터 호환
struct db_data
{
    // 카드 인증시 insert
    // 충전 시작시 update
    // 충전 종료시 update

    // type == chargingLog
    // role == hmi

    uint64_t session_id; // db에서 자동생성
    uint32_t store_id;   // store클래스 멤버변수 // 카드 인증시 생성
    QString hmi_id;      // store클래스 멤버변수 // 카드 인증시 생성

    uint32_t ocpp_tx_id; // (transactionId) // sv ack 오면 생성
    QString card_uid;    // store클래스 멤버변수 // 카드 인증시 생성

    // 시간/결과
    // created_at / updated_at는 DB가 자동 관리(DEFAULT + 트리거)
    QString start_time;     // store클래스 멤버변수 // 충전 시작시 생성
    QString end_time;       // 추가 필요 // 충전 완료시 생성
    QString duration_time;  // 경과 시간 // 충전 완료시 생성
    double average_kWh;     // 추가 필요 // 충전 완료시 생성

    double soc_start; // 충전 시작시 생성
    double soc_end;   // 충전 완료시 생성

    // 금액(정산용) DB upDate X
    QString card_type;
    uint32_t advance_payment; // (선결제 “가정” 금액) // 카드 인증시 생성
    uint32_t cancel_payment;  // (부분취소된 금액) // 충전 완료시 생성
    uint32_t actual_payment;  //(실제청구 = advance - cancel)  // 충전 완료시 생성
    uint32_t unit_price;      //(원/kWh)
    QString tariff_type;      //(단가 방식) // 카드 인증시 생성

    // 상태
    QString session_status; // db 업데이트마다 지속 갱신
    /*
    Authorize Accepted → AUTHORIZED
    StartTransaction OK → CHARGING_START
    StopTransaction OK → CHARGING_FINISHED
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

    QString local_tx_id; // 거래 묶음용 hmi 생성

    // 백업 데이터 구분 용
    QString back_state;
};

struct charging_log_admin
{
    QString created_at;
    QString updated_at;
    int row_id;
    int store_id;
    QString hmi_id;
    int ocpp_tx_id;
    QString card_uid;
    QString start_time;
    QString end_time;
    QString duration_time;
    double average_kwh;
    double soc_start;
    double soc_end;
    int advance_payment;
    int cancel_payment;
    int actual_payment;
    int unit_price;
    QString tariff_type;
    QString session_status;
    QString stop_reason;
    QString local_tx_id;
};
Q_DECLARE_METATYPE(charging_log_admin)

struct hmi_current_stat_admin
{
    QString hmi_id;
    int store_id;
    bool ws_connected;
    QString last_heartbeat_at;
    QString screen_name;
    QString updated_at;
};
Q_DECLARE_METATYPE(hmi_current_stat_admin)

struct hmi_device_admin
{
    QString hmi_id;
    int store_id;
};
Q_DECLARE_METATYPE(hmi_device_admin)

struct membership_card_admin
{
    QString card_uid;
    int balance_total;
    int balance_available;
    int hold_amount;
    QString transaction_state;
};

struct membership_log_admin
{
    QString card_uid;
    int transaction_id;
    QString event_type;
    int amount;
    int balance_available_before;
    int balance_available_after;
    int hold_amount_before;
    int hold_amount_after;
    QString transaction_state_before;
    QString transaction_state_after;
    QString created_at;
    QString request_id;
};

struct store_user_admin
{
    int id;
    QString name;
    QString location;
};

struct revision_hmi_admin
{
    int store_id;
    QString hmi_id;
    QString cmd;
    QString val;
};

struct mp_wk_key
{
    int id;
    QString s_id;
};
Q_DECLARE_METATYPE(mp_wk_key)

struct serial_info
{
    int role;
    QString path;
    QString description;
    QString manufacturer;
    QString vendorId;
    QString productId;
};
#endif // STATDATA_H
