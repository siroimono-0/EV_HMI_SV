#ifndef WK_SERIAL_H
#define WK_SERIAL_H

#include <QDebug>
#include <QObject>
#include <QSerialPort>
#include <QTimer>
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

class WK_Serial : public QObject
{
    Q_OBJECT
public:
    explicit WK_Serial(QObject *parent = nullptr);

    void serial_open();

    void rs485_modbus_open();
    void rs485_crc_compare();
    static uint8_t cnv_uint8_t(char c);

    void rs485_coil_all_off();
    void rs485_coil_on_off(char coil_num, bool onoff);

    void rs232_modbus_open();
    bool rs232_crc_compare();
    void rs232_modbus_req();
    void rs232_modbus_response_parsing();
    //====================================================
    uint16_t read16_BE(const QByteArray &qba, int pos);
    uint32_t read32_BE(const QByteArray &qba, int pos);

    void set_p_module(Cpp_Module *module);
    void set_p_stat(StatStore *stat);

public slots:
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

signals:

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

    Cpp_Module *p_module = nullptr;
    WK_WebSocket *p_soc = nullptr;
    StatStore *p_stat = nullptr;
    bool card_stat = false;

    QVector<QPair<char, bool>> connecter234_stat;
};

Q_DECLARE_METATYPE(WK_Serial *)
#endif // WK_SERIAL_H
