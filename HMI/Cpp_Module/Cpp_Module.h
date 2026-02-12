#ifndef CPP_MODULE_H
#define CPP_MODULE_H

#include <QDebug>
#include <QObject>
#include <QThread>
#include "../Common/StatData.h"

class WK_Serial;
class WK_WebSocket;
class StatStore;

class Cpp_Module : public QObject
{
    Q_OBJECT
public:
    explicit Cpp_Module(QObject* parent = nullptr);
    ~Cpp_Module();

    Q_INVOKABLE void join_WebSv(QString id, QString location);

    void create_WebSoc();
    void create_Serial();

    void end_p_wk_websoc();
    void end_p_wk_serial();

public slots:

signals:
    void sig_SocErr_ToQml(QString msg);
    void sig_SocSuccess_ToQml();

private:
    StatStore* p_stat = nullptr;

    WK_WebSocket* p_wk_websoc = nullptr;
    QThread* p_th_websoc = nullptr;

    WK_Serial* p_wk_serial = nullptr;
    QThread* p_th_serial = nullptr;
};

#endif // CPP_MODULE_H
