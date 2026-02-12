#ifndef CPP_MODULE_H
#define CPP_MODULE_H

#include <QDebug>
#include <QObject>
#include <QThread>
#include <QVariant>
#include "../Common/StatData.h"
#include "StatModel.h"

class Hub;

class Cpp_Module : public QObject
{
    Q_OBJECT
    Q_PROPERTY(StatModel *hmi_md READ get_hmi_md NOTIFY sig_hmi_md_changed)

public:
    explicit Cpp_Module(QObject *parent = nullptr);

    Q_INVOKABLE bool set_webSoc_Sv(QVariant s);

    StatModel *get_hmi_md();

public slots:

signals:
    void sig_hmi_md_changed();

private:
    Hub *p_WebSoc_Hub;
    QThread *p_th_HUB;
    StatModel *hmi_md;
};

#endif // CPP_MODULE_H
