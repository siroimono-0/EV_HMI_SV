#include "WK_Serial.h"
#include "Cpp_Module.h"
#include "StatStore.h"
#include "WK_WebSocket.h"
extern "C" {
#include "./External_Library/checksum.h"
}

WK_Serial::WK_Serial(QObject *parent)
    : QObject{parent}
{
    this->serial_open();

    // timer 같이 초기화
    this->rs485_modbus_open();

    this->rs232_modbus_open();

    // 처음에 코일 전부다 off 상태로 만들어야댐
    this->rs485_coil_all_off();

    // 초기 코일값 세팅
    // this->connecter234_stat.push_back({0x01, true});
    // this->connecter234_stat.push_back({0x02, true});
    // this->connecter234_stat.push_back({0x03, true});

    this->connecter234_stat.push_back({0x01, false});
    this->connecter234_stat.push_back({0x02, false});
    this->connecter234_stat.push_back({0x03, false});

    // this->connecter234_stat.push_back({0x01, true});
    // this->connecter234_stat.push_back({0x02, true});
    // this->connecter234_stat.push_back({0x03, true});

    // 처음에 코일 전부다 off 상태로 만들어야댐
    // this->slot_rs485_coil234_on_off(true);
    // this->rs485_coil_on_off(0x00, false);
    // this->rs485_coil_on_off(0x01, false);
    // this->rs485_coil_on_off(0x02, false);
    // this->rs485_coil_on_off(0x03, false);
}

void WK_Serial::rs485_coil_all_off()
{
    this->coil_all_off_stat = true;
    this->slot_rs485_coil1_on_off(false);
    return;
}

void WK_Serial::slot_set_p_soc(WK_WebSocket *soc)
{
    this->p_soc = soc;
    return;
}

uint8_t WK_Serial::cnv_uint8_t(char c)
{
    return (uint8_t) (unsigned char) c;
}

void WK_Serial::rs485_modbus_open()
{
    this->p_rs485_modbus = new QSerialPort(this);
    this->p_rs485_modbus->setPortName("COM8"); // 장치관리자에서 본 COM 번호
    this->p_rs485_modbus->setBaudRate(QSerialPort::Baud9600);
    this->p_rs485_modbus->setDataBits(QSerialPort::Data8);
    this->p_rs485_modbus->setParity(QSerialPort::NoParity);
    this->p_rs485_modbus->setStopBits(QSerialPort::OneStop);
    this->p_rs485_modbus->setFlowControl(QSerialPort::NoFlowControl);

    connect(this->p_rs485_modbus, &QSerialPort::readyRead, this, &WK_Serial::slot_rs485_read);

    if (this->p_rs485_modbus->open(QIODevice::ReadWrite))
    {
        qDebug() << "rs485 open OK";
    }
    else
    {
        qDebug() << "rs485 open FAIL:" << this->p_rs485_modbus->errorString();
    }

    this->p_rs485_tm_silent = new QTimer(this);
    // 타이머 싱글샷으로 설정하고 read시 재설정 반복
    this->p_rs485_tm_silent->setSingleShot(true);
    connect(this->p_rs485_tm_silent, &QTimer::timeout, this, &WK_Serial::slot_rs485_modbus_end);

    // this->slot_modbus_write();
    // this->slot_rs485_coil1_on_off(false);
    return;
}

void WK_Serial::rs485_coil_on_off(char coil_num, bool onoff)
{
    if (this->rs485_modbus_wait == true)
    {
        qDebug() << "모드버스 응답 전 명령 요청됨";
        return;
    }

    // JD1 ON: 01 05 00 00 FF 00 8C 3A
    QByteArray qba;
    qba.append(char(0x01));
    qba.append(char(0x05));
    qba.append(char(0x00));
    qba.append(coil_num);

    if (onoff == true)
    {
        qba.append(char(0xFF));
        qba.append(char(0x00));
    }
    else
    {
        qba.append(char(0x00));
        qba.append(char(0x00));
    }

    // crc계산 라이브러리
    uint16_t crc = crc_modbus((const unsigned char *) qba.data(), qba.size());

    uint8_t crc_H = ((crc >> 8) & 0xFF);
    uint8_t crc_L = (crc & 0xFF);

    qba.append(char(crc_L));
    qba.append(char(crc_H));

    this->p_rs485_modbus->write(qba);
    if (!this->p_rs485_modbus->waitForBytesWritten(200))
    {
        qDebug() << "write timeout";
        return;
    }

    // 슬레이브에게 보내는 요청 값 저장
    this->rs485_req = qba;

    // 모드버스 wait 상태로 전환
    this->rs485_modbus_wait = true;

    return;
}

void WK_Serial::slot_rs485_coil1_on_off(bool onoff)
{
    this->rs485_coil_on_off(0x00, onoff);
    return;
}

void WK_Serial::slot_rs485_coil234_on_off(bool onoff)
{
    if (onoff == true)
    {
        for (auto &v : this->connecter234_stat)
        {
            if (v.second == false)
            {
                this->rs485_coil_on_off(v.first, onoff);
                return;
            }
        }
    }
    else
    {
        for (auto &v : this->connecter234_stat)
        {
            if (v.second == true)
            {
                this->rs485_coil_on_off(v.first, onoff);
                return;
            }
        }
    }

    return;
}

void WK_Serial::slot_rs485_read()
{
    QByteArray qba = this->p_rs485_modbus->readAll();
    this->rs485_readData.append(qba);
    this->p_rs485_tm_silent->start(30);
    return;
}

void WK_Serial::slot_rs485_modbus_end()
{
    this->rs485_crc_compare();
    // this->rs485_modbus_wait = ret_wait;
    return;
}

void WK_Serial::rs485_crc_compare()
{
    QByteArray crc = this->rs485_readData.right(2);

    QByteArray data_notCrc = this->rs485_readData.left(this->rs485_readData.size() - 2);

    uint16_t crc_tmp = crc_modbus((const unsigned char *) data_notCrc.data(), data_notCrc.size());
    uint8_t crc_H = ((crc_tmp >> 8) & 0xFF);
    uint8_t crc_L = (crc_tmp & 0xFF);

    QByteArray crc_compare;
    crc_compare.append(char(crc_L));
    crc_compare.append(char(crc_H));

    if (crc != crc_compare)
    {
        this->rs485_readData.clear();
        // 전 요청값 저장대있는 것으로 재요청
        this->p_rs485_modbus->write(this->rs485_req);
        this->p_rs485_modbus->waitForBytesWritten(200);
    }
    else
    {
        qDebug().noquote() << this->rs485_req.toHex(' ') << " :: req Data";
        qDebug().noquote() << this->rs485_readData.toHex(' ') << " :: read Data";

        // 재용청 보내기전 응답 완료 처리
        this->rs485_modbus_wait = false;

        // 코일 초기값 전부 off로 세팅 분기
        if (this->coil_all_off_stat == true)
        {
            if (this->rs485_readData.at(3) == 0x00)
            {
                this->rs485_coil_on_off(0x01, false);
            }
            else if (this->rs485_readData.at(3) == 0x01)
            {
                this->rs485_coil_on_off(0x02, false);
            }
            else if (this->rs485_readData.at(3) == 0x02)
            {
                this->rs485_coil_on_off(0x03, false);
            }
            else if (this->rs485_readData.at(3) == 0x03)
            {
                this->coil_all_off_stat = false;
            }
        }

        // coil 234 연속 동작 하기위한 분기문
        if (cnv_uint8_t(this->rs485_req.at(4)) == 0xFF)
        {
            if (cnv_uint8_t(this->rs485_readData.at(3)) == 0x01
                && this->connecter234_stat.at(1).second == false)
            {
                this->connecter234_stat[0].second = true;
                this->slot_rs485_coil234_on_off(true);
            }
            else if (cnv_uint8_t(this->rs485_readData.at(3)) == 0x02
                     && this->connecter234_stat.at(2).second == false)
            {
                this->connecter234_stat[1].second = true;
                this->slot_rs485_coil234_on_off(true);
            }
            else if (cnv_uint8_t(this->rs485_readData.at(3)) == 0x03)
            {
                this->connecter234_stat[2].second = true;
                // 다 완료됨 응답까지 받았으니 Qml에 완료했음 응답
                QMetaObject::invokeMethod(this->p_module,
                                          &Cpp_Module::sig_coil_ready_ok_ToQml,
                                          Qt::QueuedConnection);
            }
        }
        else if (cnv_uint8_t(this->rs485_req.at(4)) == 0x00)
        {
            if (cnv_uint8_t(this->rs485_readData.at(3)) == 0x01
                && this->connecter234_stat.at(1).second == true)
            {
                this->connecter234_stat[0].second = false;
                this->slot_rs485_coil234_on_off(false);
            }
            else if (cnv_uint8_t(this->rs485_readData.at(3)) == 0x02
                     && this->connecter234_stat.at(2).second == true)
            {
                this->connecter234_stat[1].second = false;
                this->slot_rs485_coil234_on_off(false);
            }
            else if (cnv_uint8_t(this->rs485_readData.at(3)) == 0x03)
            {
                this->connecter234_stat[2].second = false;
                // 코일234 꺼진서 확인댓으면 qml에 다음페이지 요청
                QMetaObject::invokeMethod(this->p_module,
                                          &Cpp_Module::sig_coil234_off_check_ToQml,
                                          Qt::QueuedConnection);
            }
        }

        // 요청 정상처리됨
        // 이전 요청 저장 + 응답 버퍼 클리어
        // this->rs485_req.clear();
        this->rs485_readData.clear();
    }
    return;
}

void WK_Serial::rs232_modbus_open()
{
    this->p_rs232_modbus = new QSerialPort(this);
    this->p_rs232_modbus->setPortName("COM9"); // 장치관리자에서 본 COM 번호
    this->p_rs232_modbus->setBaudRate(QSerialPort::Baud9600);
    this->p_rs232_modbus->setDataBits(QSerialPort::Data8);
    this->p_rs232_modbus->setParity(QSerialPort::NoParity);
    this->p_rs232_modbus->setStopBits(QSerialPort::OneStop);
    this->p_rs232_modbus->setFlowControl(QSerialPort::NoFlowControl);

    connect(this->p_rs232_modbus, &QSerialPort::readyRead, this, &WK_Serial::slot_rs232_read);

    if (this->p_rs232_modbus->open(QIODevice::ReadWrite))
    {
        qDebug() << "rs232 open OK";
    }
    else
    {
        qDebug() << "rs232 open FAIL:" << this->p_rs232_modbus->errorString();
    }

    this->p_rs232_tm_silent = new QTimer(this);
    // 타이머 싱글샷으로 설정하고 read시 재설정 반복
    this->p_rs232_tm_silent->setSingleShot(true);
    connect(this->p_rs232_tm_silent, &QTimer::timeout, this, &WK_Serial::slot_rs232_modbus_end);

    // this->slot_rs232_cmd(0, 1);
    return;
}

void WK_Serial::slot_rs232_cmd(uint16_t addr, uint16_t val)
{
    if (this->rs232_modbus_wait == true)
    {
        qDebug() << "모드버스 응답 전 명령 요청됨";
        return;
    }

    // JD1 ON: 01 05 00 00 FF 00 8C 3A
    QByteArray qba;
    qba.append(char(0x01));
    qba.append(char(0x06));

    uint8_t addr_H = ((addr >> 8) & 0xFF);
    uint8_t addr_L = (addr & 0xFF);

    qba.append(addr_H);
    qba.append(addr_L);

    uint8_t val_L = (val & 0xFF);
    uint8_t val_H = ((val >> 8) & 0xFF);

    qba.append(val_H);
    qba.append(val_L);

    // crc계산 라이브러리
    uint16_t crc = crc_modbus((const unsigned char *) qba.data(), qba.size());

    uint8_t crc_H = ((crc >> 8) & 0xFF);
    uint8_t crc_L = (crc & 0xFF);

    qba.append(char(crc_L));
    qba.append(char(crc_H));

    this->p_rs232_modbus->write(qba);
    if (!this->p_rs232_modbus->waitForBytesWritten(200))
    {
        qDebug() << "write timeout";
        return;
    }

    // 슬레이브에게 보내는 요청 값 저장
    this->rs232_req = qba;

    // 모드버스 wait 상태로 전환
    this->rs232_modbus_wait = true;

    return;
}

void WK_Serial::slot_rs232_read()
{
    QByteArray qba = this->p_rs232_modbus->readAll();
    this->rs232_readData.append(qba);
    this->p_rs232_tm_silent->start(30);
    return;
}

void WK_Serial::rs232_modbus_req()
{
    if (this->rs232_modbus_wait == true)
    {
        qDebug() << "모드버스 응답 전 명령 요청됨";
        return;
    }

    // JD1 ON: 01 05 00 00 FF 00 8C 3A
    QByteArray qba;
    qba.append(char(0x01));
    qba.append(char(0x03));

    uint16_t addr = 0x00;
    uint8_t addr_H = ((addr >> 8) & 0xFF);
    uint8_t addr_L = (addr & 0xFF);

    qba.append(addr_H);
    qba.append(addr_L);

    uint16_t val = 0x08;
    uint8_t val_H = ((val >> 8) & 0xFF);
    uint8_t val_L = (val & 0xFF);

    qba.append(val_H);
    qba.append(val_L);

    // crc계산 라이브러리
    uint16_t crc = crc_modbus((const unsigned char *) qba.data(), qba.size());

    uint8_t crc_H = ((crc >> 8) & 0xFF);
    uint8_t crc_L = (crc & 0xFF);

    qba.append(char(crc_L));
    qba.append(char(crc_H));

    this->p_rs232_modbus->write(qba);
    if (!this->p_rs232_modbus->waitForBytesWritten(200))
    {
        qDebug() << "write timeout";
        return;
    }

    // 슬레이브에게 보내는 요청 값 저장
    this->rs232_req = qba;

    // 모드버스 wait 상태로 전환
    this->rs232_modbus_wait = true;
    return;
}

void WK_Serial::slot_rs232_modbus_end()
{
    this->rs232_crc_compare();
    this->rs232_modbus_wait = false;
    return;
}

bool WK_Serial::rs232_crc_compare()
{
    QByteArray crc = this->rs232_readData.right(2);

    QByteArray data_notCrc = this->rs232_readData.left(this->rs232_readData.size() - 2);

    uint16_t crc_tmp = crc_modbus((const unsigned char *) data_notCrc.data(), data_notCrc.size());
    uint8_t crc_H = ((crc_tmp >> 8) & 0xFF);
    uint8_t crc_L = (crc_tmp & 0xFF);

    QByteArray crc_compare;
    crc_compare.append(char(crc_L));
    crc_compare.append(char(crc_H));

    if (crc != crc_compare)
    {
        // 전 요청값 저장대있는 것으로 재요청
        this->rs232_readData.clear();
        this->p_rs232_modbus->write(this->rs232_req);
        this->p_rs232_modbus->waitForBytesWritten(200);
        return true;
    }
    else
    {
        qDebug().noquote() << this->rs232_req.toHex(' ') << " :: req Data";
        qDebug().noquote() << this->rs232_readData.toHex(' ') << " :: read Data";
        this->rs232_modbus_response_parsing();
        // 이전 요청 저장 + 응답 버퍼 클리어
        // this->rs232_req.clear();
        this->rs232_readData.clear();
    }
    return false;
}

void WK_Serial::rs232_modbus_response_parsing()
{
    // 스타트 요청 잘 완료된거 확인했으면
    // 타이머로 1초마다 값 읽어오게함
    uint8_t func_code = this->rs232_readData.at(1);

    if (func_code == 0x06)
    {
        // &&  && val_H == 0x00 && val_L == 0x01

        uint8_t addr_H = this->rs232_readData.at(2);
        uint8_t addr_L = this->rs232_readData.at(3);
        uint8_t val_H = this->rs232_readData.at(4);
        uint8_t val_L = this->rs232_readData.at(5);

        if (addr_H == 0x00 && addr_L == 0x00 && val_H == 0x00 && val_L == 0x01)
        {
            // 시작
            if (this->p_rs232_tm_readReq == nullptr)
            {
                this->p_rs232_tm_readReq = new QTimer(this);
                connect(this->p_rs232_tm_readReq,
                        &QTimer::timeout,
                        this,
                        &WK_Serial::slot_rs232_reqTimer_timeout);

                // 경과시간 측정용
                this->p_rs232_el_tm = new QElapsedTimer();
                this->p_rs232_el_tm->start();
            }
            this->p_rs232_tm_readReq->start(1000);
            this->p_rs232_el_tm->restart();
        }
        else if (addr_H == 0x00 && addr_L == 0x01 && val_H == 0x00 && val_L == 0x01)
        {
            // 종료
            this->p_rs232_tm_readReq->stop();

            // 충전 로그 서버에 보내야댐

            // Qml에 정상 종료 메시지
            QMetaObject::invokeMethod(this->p_module,
                                      &Cpp_Module::sig_charging_stop_ToQml,
                                      Qt::QueuedConnection);
        }
    }
    else if (func_code == 0x03)
    {
        /*
        0x0000	Charger State // 3
        0x0001	Fault Code// 5

        0x0002	voltage// 7
        0x0003	current// 9

        0x0004	Battery_current (H)// 11
        0x0005	Battery_current (L)// 13

        0x0006	Battery_full (H)// 15
        0x0007	Battery_full (L)// 17
        */

        int data_start_pos = 3;

        uint16_t charger_stat = this->read16_BE(this->rs232_readData, data_start_pos);

        uint16_t err_code = this->read16_BE(this->rs232_readData, data_start_pos + 2);

        uint16_t voltage = this->read16_BE(this->rs232_readData, data_start_pos + 4);
        qDebug() << voltage << " :: voltage";

        uint16_t current = this->read16_BE(this->rs232_readData, data_start_pos + 6);
        qDebug() << current << " :: current ";

        uint32_t battery_current_total = this->read32_BE(this->rs232_readData, data_start_pos + 8);
        qDebug() << battery_current_total << " :: battery current";

        uint32_t battery_full_total = this->read32_BE(this->rs232_readData, data_start_pos + 12);
        qDebug() << battery_full_total << " :: battery full";

        uint32_t elapsed_time = this->p_rs232_el_tm->elapsed() / 1000;

        struct charging_stat c_stat;
        c_stat.charger_stat = charger_stat;
        c_stat.err_code = err_code;
        c_stat.voltage = voltage;
        c_stat.current = current;
        c_stat.battery_current = battery_current_total;
        c_stat.battery_full = battery_full_total;
        c_stat.elapsed_time = elapsed_time;

        QMetaObject::invokeMethod(this->p_stat,
                                  "slot_update_chargingStat",
                                  Qt::QueuedConnection,
                                  Q_ARG(charging_stat, c_stat));
        // if(this->)
    }

    return;
}

uint16_t WK_Serial::read16_BE(const QByteArray &qba, int pos)
{
    uint8_t u8_H = (uint8_t) qba.at(pos);
    uint8_t u8_L = (uint8_t) qba.at(pos + 1);

    return ((uint16_t) u8_H) << 8 | (uint16_t) u8_L;
}

uint32_t WK_Serial::read32_BE(const QByteArray &qba, int pos)
{
    uint16_t u16_H = this->read16_BE(qba, pos);
    uint16_t u16_L = this->read16_BE(qba, pos + 2);
    return ((uint32_t) u16_H << 16) | (uint32_t) u16_L;
}

void WK_Serial::slot_rs232_reqTimer_timeout()
{
    this->rs232_modbus_req();
    return;
}

void WK_Serial::serial_open()
{
    this->p_serial = new QSerialPort(this);
    this->p_serial->setPortName("COM7"); // 장치관리자에서 본 COM 번호
    this->p_serial->setBaudRate(QSerialPort::Baud9600);
    this->p_serial->setDataBits(QSerialPort::Data8);
    this->p_serial->setParity(QSerialPort::NoParity);
    this->p_serial->setStopBits(QSerialPort::OneStop);
    this->p_serial->setFlowControl(QSerialPort::NoFlowControl);

    connect(this->p_serial, &QSerialPort::readyRead, this, &WK_Serial::slot_serial_read);

    if (this->p_serial->open(QIODevice::ReadWrite))
    {
        qDebug() << "this->p_serial open OK";
    }
    else
    {
        qDebug() << "this->p_serial open FAIL:" << this->p_serial->errorString();
    }
    // this->slot_modbus_write();
    return;
}

void WK_Serial::set_p_module(Cpp_Module *module)
{
    this->p_module = module;
    return;
}

void WK_Serial::set_p_stat(StatStore *stat)
{
    this->p_stat = stat;
    return;
}

void WK_Serial::slot_serial_read()
{
    QByteArray qba = this->p_serial->readAll();

    if (this->card_stat == true)
    {
        // 카드 확인 중 Qml 취소버튼 눌리면 안댐
        // 취소버튼 안보이게 하고 비지터 돌려야댐
        // qml 신호 필요
        QMetaObject::invokeMethod(this->p_module,
                                  &Cpp_Module::sig_card_compare_ToQml,
                                  Qt::QueuedConnection);

        for (auto &v : qba)
        {
            if (v == 0x02)
            {
                // 카드 리더기 시작 이전 쌓인거 있으면 클리어
                this->readData.clear();
            }
            else if (v == 0x03)
            {
                this->readData.replace("\r", "");
                this->readData.replace("\n", "");
                qDebug() << this->readData;
                // 카드 리더기 종료
                if (this->p_soc != nullptr)
                {
                    if (this->card_type == "creditCard")
                    {
                        // http server 카드 정보 확인 요청
                        QMetaObject::invokeMethod(this->p_soc,
                                                  "slot_netAccess_post",
                                                  Qt::QueuedConnection,
                                                  Q_ARG(QByteArray, this->readData));
                    }
                    else if (this->card_type == "membershipCard")
                    {
                        QPair<int, QString> qp;
                        QMetaObject::invokeMethod(this->p_stat,
                                                  &StatStore::slot_get_advPay_hmiId,
                                                  Qt::BlockingQueuedConnection,
                                                  qReturnArg(qp));

                        int adv_pay = qp.first;
                        QString hmi_id = qp.second;
                        QString request_id;
                        QDateTime dt_utc = QDateTime::currentDateTimeUtc();
                        request_id = hmi_id + dt_utc.toString();

                        QMetaObject::invokeMethod(this->p_stat,
                                                  "slot_set_card_uid",
                                                  Qt::QueuedConnection,
                                                  Q_ARG(QString, QString::fromUtf8(this->readData)));

                        QMetaObject::invokeMethod(this->p_soc,
                                                  "slot_send_membership_authorized_textData",
                                                  Qt::QueuedConnection,
                                                  Q_ARG(int, adv_pay),
                                                  Q_ARG(QByteArray, this->readData),
                                                  Q_ARG(QString, request_id));
                    }
                }
            }
            else
            {
                this->readData += v;
            }
        }
    }

    // qDebug() << "hello?";
    return;
}

void WK_Serial::slot_set_card_stat(bool stat)
{
    this->card_stat = stat;
    return;
}

void WK_Serial::slot_modbus_write()
{
    QByteArray modbus;
    modbus.append(char(0x01)); // Slave ID
    modbus.append(char(0x03)); // Function code
    modbus.append(char(0x00)); // Address
    modbus.append(char(0x01)); // quantity

    this->p_serial->write(modbus);
    return;
}

void WK_Serial::slot_set_card_type(QString set)
{
    this->card_type = set;
    return;
}
