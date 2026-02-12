#ifndef WK_SERIAL_H
#define WK_SERIAL_H

#include <QDebug>
#include <QObject>
#include <QSerialPort>
#include "../Common/StatData.h"

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

    void test_open();

public slots:
    void test_read();
    void slot_modbus_write();

signals:

private:
    QSerialPort *p_serial;
};

#endif // WK_SERIAL_H
