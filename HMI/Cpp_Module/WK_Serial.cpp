#include "WK_Serial.h"
#include "Cpp_Module.h"
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

    // 초기 코일값 세팅
    this->connecter234_stat.push_back({0x01, false});
    this->connecter234_stat.push_back({0x02, false});
    this->connecter234_stat.push_back({0x03, false});

    // this->connecter234_stat.push_back({0x01, true});
    // this->connecter234_stat.push_back({0x02, true});
    // this->connecter234_stat.push_back({0x03, true});

    // 처음에 코일 전부다 off 상태로 만들어야댐
    this->slot_rs485_coil234_on_off(true);
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

void WK_Serial::rs232_modbus_open()
{
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
    this->rs485_modbus_wait = false;
    this->rs485_crc_compare();
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
        // 전 요청값 저장대있는 것으로 재요청
        this->p_rs485_modbus->write(this->rs485_req);
        if (!this->p_rs485_modbus->waitForBytesWritten(200))
        {
            qDebug() << "write timeout";
            return;
        }
    }
    else
    {
        qDebug() << this->rs485_req << " :: ok";

        if (cnv_uint8_t(this->rs485_req.at(4)) == 0xFF)
        {
            if (cnv_uint8_t(this->rs485_readData.at(3)) == 0x01
                && this->connecter234_stat.at(1).second == false)
            {
                this->connecter234_stat[0].second = true;
                this->slot_rs485_coil234_on_off(true);
                qDebug() << this->rs485_req << " :: ??";
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
            }
        }
        else if (cnv_uint8_t(this->rs485_req.at(4)) == 0x00)
        {
            if (cnv_uint8_t(this->rs485_readData.at(3)) == 0x01
                && this->connecter234_stat.at(1).second == false)
            {
                this->connecter234_stat[0].second = false;
                this->slot_rs485_coil234_on_off(false);
                qDebug() << this->rs485_req << " :: ??";
            }
            else if (cnv_uint8_t(this->rs485_readData.at(3)) == 0x02
                     && this->connecter234_stat.at(2).second == false)
            {
                this->connecter234_stat[1].second = false;
                this->slot_rs485_coil234_on_off(false);
            }
            else if (cnv_uint8_t(this->rs485_readData.at(3)) == 0x03)
            {
                this->connecter234_stat[2].second = false;
            }
        }

        // 요청 정상처리됨
        // 이전 요청 저장 + 응답 버퍼 클리어
        this->rs485_req.clear();
        this->rs485_readData.clear();
    }
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
                    QMetaObject::invokeMethod(this->p_soc,
                                              "slot_netAccess_post",
                                              Qt::QueuedConnection,
                                              Q_ARG(QByteArray, this->readData));
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
