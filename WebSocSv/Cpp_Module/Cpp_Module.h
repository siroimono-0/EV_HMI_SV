#ifndef CPP_MODULE_H
#define CPP_MODULE_H

#include <QDebug>
#include <QObject>
#include <QThread>
#include <QTimer>
#include <QVariant>
#include "../../Common/StatData.h"
// #include "../Common/StatData.h"
#include "DB_PostgreSQL.h"
#include "StatModel.h"

class Hub;

class Cpp_Module : public QObject
{
    Q_OBJECT
    Q_PROPERTY(StatModel *hmi_md READ get_hmi_md NOTIFY sig_hmi_md_changed)

public:
    explicit Cpp_Module(QObject *parent = nullptr);
    ~Cpp_Module();

    Q_INVOKABLE bool set_webSoc_Sv();

    StatModel *get_hmi_md();

    void create_obj_DB();

public slots:
    // Q_INVOKABLE bool createStore_sql(QString id, const QString name, const QString location); 수정

signals:
    void sig_hmi_md_changed();

private:
    Hub *p_WebSoc_Hub;
    QThread *p_th_HUB;
    StatModel *hmi_md;

    // 생성자에서 생성
    DB_PostgreSQL *p_obj_db;
    QThread *p_th_db;
};

#endif // CPP_MODULE_H
