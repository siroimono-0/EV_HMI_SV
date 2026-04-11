#ifndef WK_SERIAL_H
#define WK_SERIAL_H

#include <QDebug>
#include <QElapsedTimer>
#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QtSystemDetection>
#include "../Common/StatData.h"

class WK_WebSocket;
class Cpp_Module;
class StatStore;

struct test_st
{
    char slave_id;
    char func_code;
    char data_startAdd;
    char quntity;
};

enum RESPONSE_TYPE { START = 0, STOP = 1, READ = 2 };
enum DEV_ROLE { MCU = 0, MODULE = 1, EMS = 2, CARD = 3 };

class WK_Serial : public QObject
{
    Q_OBJECT
public:
    explicit WK_Serial(QObject *parent = nullptr);

    void serial_init();
    void serial_compare();
    void serial_open(const QString path);

    void rs485_modbus_open(const QString path);
    void rs485_crc_compare();
    static uint8_t cnv_uint8_t(char c);

    void rs485_coil_all_off();
    void rs485_coil_on_off(char coil_num, bool onoff);

    void rs232_modbus_open(const QString path);
    bool rs232_crc_compare();
    void rs232_modbus_req();
    void rs232_modbus_response_parsing();
    //====================================================
    uint16_t read16_BE(const QByteArray &qba, int pos);
    uint32_t read32_BE(const QByteArray &qba, int pos);

    void uart_ems_open(const QString path);

    void set_p_module(Cpp_Module *module);
    void set_p_stat(StatStore *stat);

public slots:
    void slot_stop();

    void slot_serial_read();
    void slot_modbus_write();
    void slot_set_p_soc(WK_WebSocket *soc);

    void slot_set_card_stat(bool stat);
    void slot_set_card_type(QString set);

    void slot_rs485_coil1_on_off(bool onoff);
    void slot_rs485_coil234_on_off(bool onoff);
    void slot_rs485_read();
    void slot_rs485_modbus_end();

    void slot_rs232_cmd(uint16_t addr, uint16_t val);
    void slot_rs232_read();
    void slot_rs232_modbus_end();
    void slot_rs232_reqTimer_timeout();

    void slot_uart_ems_read();
    void slot_uart_ems_end();
signals:
    void sig_end();

private:
    QSerialPort *p_serial = nullptr;
    QByteArray readData;
    QString card_type;

    QSerialPort *p_rs485_modbus = nullptr;
    QTimer *p_rs485_tm_silent;
    QByteArray rs485_req;
    QByteArray rs485_readData;
    bool rs485_modbus_wait = false;
    bool coil_all_off_stat = true;

    QSerialPort *p_rs232_modbus = nullptr;
    QTimer *p_rs232_tm_silent;
    QTimer *p_rs232_tm_readReq = nullptr;
    QElapsedTimer *p_rs232_el_tm = nullptr;
    QByteArray rs232_req;
    QByteArray rs232_readData;
    bool rs232_modbus_wait = false;

    QSerialPort *p_ems = nullptr;
    QByteArray ems_readData;
    QTimer *p_ems_tm_silent = nullptr;

    Cpp_Module *p_module = nullptr;
    WK_WebSocket *p_soc = nullptr;
    StatStore *p_stat = nullptr;
    bool card_stat = false;

    QVector<QPair<char, bool>> connecter234_stat;

    QVector<serial_info> vec_init_serial_info;
};

Q_DECLARE_METATYPE(WK_Serial *)

/*
MCU(RS232)
description    = "USB-Serial Controller D"
manufacturer   = "Prolific Technology Inc."
serialNumber   = ""
vendorId       = "0x067b"
productId      = "0x2303"

=====================================================

Module(RS485)
description    = "USB Serial"
manufacturer   = "1a86"
serialNumber   = ""
vendorId       = "0x1a86"
productId      = "0x7523"

=====================================================

EMS(Uart)
description    = "FT232R USB UART"
manufacturer   = "FTDI"
serialNumber   = "A5069RR4"
vendorId       = "0x0403"
productId      = "0x6001"

=====================================================

Card
description    = "CP2102 USB to UART Bridge Controller"
manufacturer   = "Silicon Labs"
serialNumber   = "0001"
vendorId       = "0x10c4"
productId      = "0xea60"
*/

/*
EMS(Uart)
portName       = "COM5"
systemLocation = "\\\\.\\COM5"
description    = "USB Serial Port"
manufacturer   = "FTDI"
serialNumber   = "A5069RR4A"
vendorId       = "0x0403"
productId      = "0x6001"

=====================================================

MCU(RS232)
portName       = "COM12"
systemLocation = "\\\\.\\COM12"
description    = "Prolific USB-to-Serial Comm Port"
manufacturer   = "Prolific"
serialNumber   = ""
vendorId       = "0x067b"
productId      = "0x2303"

=====================================================

Module(RS485)
portName       = "COM11"
systemLocation = "\\\\.\\COM11"
description    = "USB-SERIAL CH340"
manufacturer   = "wch.cn"
serialNumber   = ""
vendorId       = "0x1a86"
productId      = "0x7523"

=====================================================

Card
portName       = "COM7"
systemLocation = "\\\\.\\COM7"
description    = "Silicon Labs CP210x USB to UART Bridge"
manufacturer   = "Silicon Laboratories"
serialNumber   = "0001"
vendorId       = "0x10c4"
productId      = "0xea60"
 */
#endif // WK_SERIAL_H
