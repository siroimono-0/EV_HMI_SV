#include "Admin.h"
#include "./CppModule/WK_soc.h"
#include "ui_Admin.h"

Admin::Admin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Admin)
{
    ui->setupUi(this);
    connect(ui->btn_Register, &QPushButton::clicked, this, &Admin::slot_btn_register_clicked);

    connect(ui->btn_hmiRegister, &QPushButton::clicked, this, &Admin::slot_btn_hmiRegister_clicked);

    this->create_wk();
}

Admin::~Admin()
{
    if (p_th && p_th->isRunning())
    {
        //문제점 해당 invoke는 실행댐 그런대 slot에서
        //sig_end 발생시켜도 th가 quit안대서 프로세스 안끝남
        QMetaObject::invokeMethod(this->p_wk, &WK_soc::slot_end, Qt::BlockingQueuedConnection);

        this->p_th->quit();
        this->p_th->wait(2000);
    }

    delete ui;
    qDebug() << Q_FUNC_INFO;
}

void Admin::slot_btn_register_clicked()
{
    Dia_Register dia(this);
    dia.set_soc(this->p_wk);
    dia.exec();
    return;
}

void Admin::slot_btn_hmiRegister_clicked()
{
    QString qs_sotreId = ui->le_store_id->text();
    QString qs_hmiId = ui->le_hmi_id->text();

    QMetaObject::invokeMethod(this->p_wk,
                              "slot_register_hmi",
                              Qt::QueuedConnection,
                              Q_ARG(QString, qs_sotreId),
                              Q_ARG(QString, qs_hmiId));
    qDebug() << Q_FUNC_INFO;

    return;
}

void Admin::create_wk()
{
    this->p_wk = new WK_soc();
    this->p_th = new QThread();
    this->p_wk->moveToThread(this->p_th);

    connect(this->p_th, &QThread::started, this->p_wk, &WK_soc::slot_start);

    //소멸자에서 quit 중복으로 재호출
    connect(this->p_wk, &WK_soc::sig_end, this->p_th, &QThread::quit);
    connect(this->p_th, &QThread::finished, this->p_wk, &WK_soc::deleteLater);
    connect(this->p_th, &QThread::finished, this->p_th, &QThread::deleteLater);

    this->p_th->start();
    qDebug() << Q_FUNC_INFO;

    return;
}
