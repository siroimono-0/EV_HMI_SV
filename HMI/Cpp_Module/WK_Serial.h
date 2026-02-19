#ifndef WK_SERIAL_H
#define WK_SERIAL_H

#include <QDebug>
#include <QObject>
#include <QSerialPort>
#include <QTimer>
#include "../Common/StatData.h"

class WK_WebSocket;
class Cpp_Module;

struct test_st
{
    char slave_id;
    char func_code;
    char data_startAdd;
    char quntity;
};

class WK_Serial : public QObject
{
    Q_OBJECT
public:
    explicit WK_Serial(QObject *parent = nullptr);

    void serial_open();

    void rs485_modbus_open();
    void rs485_crc_compare();
    static uint8_t cnv_uint8_t(char c);

    void rs232_modbus_open();

    void rs485_coil_on_off(char coil_num, bool onoff);

    void set_p_module(Cpp_Module *module);

public slots:
    void slot_serial_read();
    void slot_modbus_write();
    void slot_set_p_soc(WK_WebSocket *soc);

    void slot_set_card_stat(bool stat);

    void slot_rs485_coil1_on_off(bool onoff);
    void slot_rs485_coil234_on_off(bool onoff);

    void slot_rs485_read();
    void slot_rs485_modbus_end();

signals:

private:
    QSerialPort *p_serial = nullptr;
    QByteArray readData;

    QSerialPort *p_rs485_modbus = nullptr;
    QTimer *p_rs485_tm_silent;
    QByteArray rs485_req;
    QByteArray rs485_readData;
    bool rs485_modbus_wait = false;

    QSerialPort *p_rs232_modbus = nullptr;

    Cpp_Module *p_module = nullptr;
    WK_WebSocket *p_soc = nullptr;
    bool card_stat = false;

    QVector<QPair<char, bool>> connecter234_stat;
};

#endif // WK_SERIAL_H
