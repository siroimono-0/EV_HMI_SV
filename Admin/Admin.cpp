#include "Admin.h"
#include "./CppModule/WK_soc.h"
#include "ui_Admin.h"

Admin::Admin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Admin)
{
    ui->setupUi(this);

    // qDebug() << this->screen()->size();
    connect(ui->btn_Register, &QPushButton::clicked, this, &Admin::slot_btn_register_clicked);

    connect(ui->btn_hmiRegister, &QPushButton::clicked, this, &Admin::slot_btn_hmiRegister_clicked);

    connect(ui->pushButton_2, &QPushButton::clicked, this, &Admin::slot_btn_mCard_clicked);

    connect(ui->pushButton_3, &QPushButton::clicked, this, &Admin::slot_btn_HMI_revision_clicked);

    this->create_wk();

    this->create_qml_charging_log();
    this->create_qml_hmi_current_stat();
    this->create_qml_hmi_device();
    this->create_qml_membership_card();
    this->create_qml_membership_log();
    this->create_qml_store_user();

    connect(this->ui->comboBox, &QComboBox::textActivated, this, &Admin::slot_set_comboBox);
    connect(this->ui->comboBox_2, &QComboBox::textActivated, this, &Admin::slot_set_comboBox_2);
    connect(this->ui->comboBox_3, &QComboBox::textActivated, this, &Admin::slot_set_comboBox_3);

    connect(this->ui->pushButton, &QPushButton::clicked, this, &Admin::search_btn_clicked);

    this->ui->lineEdit->clear();
    this->ui->lineEdit->setReadOnly(true);

    this->ui->lineEdit_2->clear();
    this->ui->lineEdit_2->setReadOnly(true);

    this->ui->lineEdit_3->clear();
    this->ui->lineEdit_3->setReadOnly(true);
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
    Dia_Register_HMI dia(this);
    dia.set_p_soc(this->p_wk);
    dia.exec();
    qDebug() << Q_FUNC_INFO;

    return;
}

void Admin::slot_btn_mCard_clicked()
{
    Dia_membership_card dia(this);
    dia.set_p_soc(this->p_wk);
    dia.exec();
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

void Admin::create_qml_charging_log()
{
    this->p_md_charging_log = new MD_charging_log();
    QMetaObject::invokeMethod(this->p_wk,
                              "slot_set_p_md_charging_log",
                              Qt::QueuedConnection,
                              Q_ARG(MD_charging_log *, this->p_md_charging_log));

    this->p_qquick_charging_log = new QQuickWidget();

    this->p_qquick_charging_log->rootContext()->setContextProperty("cppModel",
                                                                   this->p_md_charging_log);

    QString s_path = "C:/Users/siroi/siroimono/w_qt/EV/Admin/Qml_Module/View_ChargingLog.qml";
    qDebug() << s_path;
    this->p_qquick_charging_log->setSource(QUrl::fromLocalFile(s_path));

    this->idx_charging_log = this->ui->stackedWidget->addWidget(this->p_qquick_charging_log);

    // this->ui->stackedWidget->setCurrentIndex(this->idx_charging_log);
    // qDebug() << this->ui->stackedWidget->size();
    qDebug() << Q_FUNC_INFO;
    return;
}

void Admin::create_qml_hmi_current_stat()
{
    this->p_md_hmi_current_stat = new MD_hmi_current_stat();
    QMetaObject::invokeMethod(this->p_wk,
                              "slot_set_p_md_hmi_current_stat",
                              Qt::QueuedConnection,
                              Q_ARG(MD_hmi_current_stat *, this->p_md_hmi_current_stat));

    this->p_qquick_hmi_current_stat = new QQuickWidget();

    this->p_qquick_hmi_current_stat->rootContext()->setContextProperty("cppModel",
                                                                       this->p_md_hmi_current_stat);

    QString s_path = "C:/Users/siroi/siroimono/w_qt/EV/Admin/Qml_Module/View_hmi_current_stat.qml";
    qDebug() << s_path;
    this->p_qquick_hmi_current_stat->setSource(QUrl::fromLocalFile(s_path));

    this->idx_hmi_current_stat = this->ui->stackedWidget->addWidget(this->p_qquick_hmi_current_stat);

    // this->ui->stackedWidget->setCurrentIndex(this->idx_charging_log);
    // qDebug() << this->ui->stackedWidget->size();
    qDebug() << Q_FUNC_INFO;
    return;
}

void Admin::create_qml_hmi_device()
{
    this->p_md_hmi_device = new MD_hmi_device();
    QMetaObject::invokeMethod(this->p_wk,
                              "slot_set_p_md_hmi_device",
                              Qt::QueuedConnection,
                              Q_ARG(MD_hmi_device *, this->p_md_hmi_device));

    this->p_qquick_hmi_device = new QQuickWidget();

    this->p_qquick_hmi_device->rootContext()->setContextProperty("cppModel", this->p_md_hmi_device);

    QString s_path = "C:/Users/siroi/siroimono/w_qt/EV/Admin/Qml_Module/View_hmi_device.qml";
    qDebug() << s_path;
    this->p_qquick_hmi_device->setSource(QUrl::fromLocalFile(s_path));

    this->idx_hmi_device = this->ui->stackedWidget->addWidget(this->p_qquick_hmi_device);

    qDebug() << Q_FUNC_INFO;
    return;
}

void Admin::create_qml_membership_card()
{
    this->p_md_membership_card = new MD_membership_card();
    QMetaObject::invokeMethod(this->p_wk,
                              "slot_set_p_md_membership_card",
                              Qt::QueuedConnection,
                              Q_ARG(MD_membership_card *, this->p_md_membership_card));

    this->p_qquick_membership_card = new QQuickWidget();

    this->p_qquick_membership_card->rootContext()->setContextProperty("cppModel",
                                                                      this->p_md_membership_card);

    QString s_path = "C:/Users/siroi/siroimono/w_qt/EV/Admin/Qml_Module/View_membership_card.qml";
    qDebug() << s_path;
    this->p_qquick_membership_card->setSource(QUrl::fromLocalFile(s_path));

    this->idx_membership_card = this->ui->stackedWidget->addWidget(this->p_qquick_membership_card);

    qDebug() << Q_FUNC_INFO;
    return;
}

void Admin::create_qml_membership_log()
{
    this->p_md_membership_log = new MD_membership_log();
    QMetaObject::invokeMethod(this->p_wk,
                              "slot_set_p_md_membership_log",
                              Qt::QueuedConnection,
                              Q_ARG(MD_membership_log *, this->p_md_membership_log));

    this->p_qquick_membership_log = new QQuickWidget();

    this->p_qquick_membership_log->rootContext()->setContextProperty("cppModel",
                                                                     this->p_md_membership_log);

    QString s_path = "C:/Users/siroi/siroimono/w_qt/EV/Admin/Qml_Module/View_membership_log.qml";
    qDebug() << s_path;
    this->p_qquick_membership_log->setSource(QUrl::fromLocalFile(s_path));

    this->idx_membership_log = this->ui->stackedWidget->addWidget(this->p_qquick_membership_log);

    qDebug() << Q_FUNC_INFO;
    return;
}

void Admin::create_qml_store_user()
{
    this->p_md_store_user = new MD_store_user();
    QMetaObject::invokeMethod(this->p_wk,
                              "slot_set_p_md_store_user",
                              Qt::QueuedConnection,
                              Q_ARG(MD_store_user *, this->p_md_store_user));

    this->p_qquick_store_user = new QQuickWidget();

    this->p_qquick_store_user->rootContext()->setContextProperty("cppModel", this->p_md_store_user);

    QString s_path = "C:/Users/siroi/siroimono/w_qt/EV/Admin/Qml_Module/View_store_user.qml";
    qDebug() << s_path;
    this->p_qquick_store_user->setSource(QUrl::fromLocalFile(s_path));

    this->idx_store_user = this->ui->stackedWidget->addWidget(this->p_qquick_store_user);

    qDebug() << Q_FUNC_INFO;
    return;
}

void Admin::slot_set_comboBox(QString select_text)
{
    this->ui->comboBox_2->clear();
    this->ui->lineEdit->clear();
    this->ui->lineEdit->setReadOnly(false);

    this->ui->comboBox_3->clear();
    this->ui->lineEdit_2->clear();
    this->ui->lineEdit_2->setReadOnly(true);

    this->ui->comboBox_4->clear();
    this->ui->lineEdit_3->clear();
    this->ui->lineEdit_3->setReadOnly(true);

    QStringList qs_list;
    if (select_text == "charging_log")
    {
        qs_list = {"store_id",
                   "hmi_id",
                   "ocpp_tx_id",
                   "card_uid",
                   "start_time",
                   "end_time",
                   "soc_start",
                   "soc_end",
                   "advance_payment",
                   "cancel_payment",
                   "actual_payment",
                   "session_status",
                   "stop_reason"};
        this->ui->comboBox_2->addItems(qs_list);
        return;
    }
    else if (select_text == "hmi_current_stat")
    {
        qs_list = {"hmi_id", "store_id"};
        this->ui->comboBox_2->addItems(qs_list);
        return;
    }
    else if (select_text == "hmi_device")
    {
        qs_list = {"store_id"};
        this->ui->comboBox_2->addItems(qs_list);
        return;
    }
    else if (select_text == "membership_card")
    {
        qs_list = {"card_uid",
                   "balance_total",
                   "balance_available",
                   "hold_amount",
                   "transaction_state"};
        this->ui->comboBox_2->addItems(qs_list);
        return;
    }
    else if (select_text == "membership_log")
    {
        return;
    }
    else if (select_text == "store_user")
    {
        return;
    }
    return;
}

void Admin::slot_set_comboBox_2(QString select_text)
{
    this->ui->comboBox_3->clear();
    this->ui->lineEdit_2->clear();
    this->ui->lineEdit_2->setReadOnly(false);

    this->ui->comboBox_4->clear();
    this->ui->lineEdit_3->clear();
    this->ui->lineEdit_3->setReadOnly(true);

    QStringList qs_list;

    if (this->ui->comboBox->currentText() == "charging_log")
    {
        qs_list = {"store_id",
                   "hmi_id",
                   "ocpp_tx_id",
                   "card_uid",
                   "start_time",
                   "end_time",
                   "soc_start",
                   "soc_end",
                   "advance_payment",
                   "cancel_payment",
                   "actual_payment",
                   "session_status",
                   "stop_reason"};

        qs_list.removeOne(select_text);
        this->ui->comboBox_3->addItems(qs_list);
        return;
    }
    else if (select_text == "hmi_current_stat")
    {
        qs_list = {"hmi_id", "store_id"};
        qs_list.removeOne(select_text);
        this->ui->comboBox_3->addItems(qs_list);
        return;
    }
    else if (select_text == "hmi_device")
    {
        return;
    }
    else if (select_text == "membership_card")
    {
        qs_list = {"card_uid",
                   "balance_total",
                   "balance_available",
                   "hold_amount",
                   "transaction_state"};
        qs_list.removeOne(select_text);
        this->ui->comboBox_3->addItems(qs_list);
        return;
    }
    else if (select_text == "membership_log")
    {
        return;
    }
    else if (select_text == "store_user")
    {
        return;
    }
    return;
}

void Admin::slot_set_comboBox_3(QString select_text)
{
    this->ui->comboBox_4->clear();
    this->ui->lineEdit_3->clear();
    this->ui->lineEdit_3->setReadOnly(false);

    QStringList qs_list;

    if (this->ui->comboBox->currentText() == "charging_log")
    {
        qs_list = {"store_id",
                   "hmi_id",
                   "ocpp_tx_id",
                   "card_uid",
                   "start_time",
                   "end_time",
                   "soc_start",
                   "soc_end",
                   "advance_payment",
                   "cancel_payment",
                   "actual_payment",
                   "session_status",
                   "stop_reason"};

        qs_list.removeOne(this->ui->comboBox_2->currentText());
        qs_list.removeOne(select_text);
        this->ui->comboBox_4->addItems(qs_list);
        return;
    }
    else if (select_text == "hmi_current_stat")
    {
        return;
    }
    else if (select_text == "hmi_device")
    {
        return;
    }
    else if (select_text == "membership_card")
    {
        qs_list = {"card_uid",
                   "balance_total",
                   "balance_available",
                   "hold_amount",
                   "transaction_state"};
        qs_list.removeOne(this->ui->comboBox_2->currentText());
        qs_list.removeOne(select_text);
        this->ui->comboBox_4->addItems(qs_list);
        return;
    }
    else if (select_text == "membership_log")
    {
        return;
    }
    else if (select_text == "store_user")
    {
        return;
    }
    return;
}

void Admin::search_btn_clicked()
{
    QString qs_table = this->ui->comboBox->currentText();
    QVector<QPair<QString, QString>> vp;
    if (this->ui->lineEdit->text() != "")
    {
        QString tmp1 = this->ui->comboBox_2->currentText();
        QString tmp1_2 = this->ui->lineEdit->text();
        vp.push_back({tmp1, tmp1_2});
    }
    if (this->ui->lineEdit_2->text() != "")
    {
        QString tmp2 = this->ui->comboBox_3->currentText();
        QString tmp2_2 = this->ui->lineEdit_2->text();
        vp.push_back({tmp2, tmp2_2});
    }
    if (this->ui->lineEdit_3->text() != "")
    {
        QString tmp3 = this->ui->comboBox_4->currentText();
        QString tmp3_2 = this->ui->lineEdit_3->text();
        vp.push_back({tmp3, tmp3_2});
    }

    if (vp.size() == 0)
    {
        QMetaObject::invokeMethod(this->p_wk,
                                  "slot_req_select_db",
                                  Qt::QueuedConnection,
                                  Q_ARG(QString, qs_table),
                                  Q_ARG(int, 0));
    }
    else if (vp.size() == 1)
    {
        QString col_1 = vp[0].first;
        QString val_1 = vp[0].second;

        QMetaObject::invokeMethod(this->p_wk,
                                  "slot_req_select_db",
                                  Qt::QueuedConnection,
                                  Q_ARG(QString, qs_table),
                                  Q_ARG(int, 1),
                                  Q_ARG(QString, col_1),
                                  Q_ARG(QString, val_1));
    }
    else if (vp.size() == 2)
    {
        QString col_1 = vp[0].first;
        QString val_1 = vp[0].second;

        QString col_2 = vp[1].first;
        QString val_2 = vp[1].second;

        QMetaObject::invokeMethod(this->p_wk,
                                  "slot_req_select_db",
                                  Qt::QueuedConnection,
                                  Q_ARG(QString, qs_table),
                                  Q_ARG(int, 2),
                                  Q_ARG(QString, col_1),
                                  Q_ARG(QString, val_1),
                                  Q_ARG(QString, col_2),
                                  Q_ARG(QString, val_2));
    }
    else if (vp.size() == 3)
    {
        QString col_1 = vp[0].first;
        QString val_1 = vp[0].second;

        QString col_2 = vp[1].first;
        QString val_2 = vp[1].second;

        QString col_3 = vp[2].first;
        QString val_3 = vp[2].second;

        QMetaObject::invokeMethod(this->p_wk,
                                  "slot_req_select_db",
                                  Qt::QueuedConnection,
                                  Q_ARG(QString, qs_table),
                                  Q_ARG(int, 3),
                                  Q_ARG(QString, col_1),
                                  Q_ARG(QString, val_1),
                                  Q_ARG(QString, col_2),
                                  Q_ARG(QString, val_2),
                                  Q_ARG(QString, col_3),
                                  Q_ARG(QString, val_3));
    }

    this->ui->comboBox_2->clear();
    this->ui->comboBox_3->clear();
    this->ui->comboBox_4->clear();
    this->ui->lineEdit->clear();
    this->ui->lineEdit_2->clear();
    this->ui->lineEdit_3->clear();

    QString cur_table = this->ui->comboBox->currentText();
    if (cur_table == "charging_log")
    {
        this->ui->stackedWidget->setCurrentIndex(this->idx_charging_log);
    }
    else if (cur_table == "hmi_current_stat")
    {
        this->ui->stackedWidget->setCurrentIndex(this->idx_hmi_current_stat);
    }
    else if (cur_table == "hmi_device")
    {
        this->ui->stackedWidget->setCurrentIndex(this->idx_hmi_device);
    }
    else if (cur_table == "membership_card")
    {
        this->ui->stackedWidget->setCurrentIndex(this->idx_membership_card);
    }
    else if (cur_table == "membership_log")
    {
        this->ui->stackedWidget->setCurrentIndex(this->idx_membership_log);
    }
    else if (cur_table == "store_user")
    {
        this->ui->stackedWidget->setCurrentIndex(this->idx_store_user);
    }

    return;
}

void Admin::slot_btn_HMI_revision_clicked()
{
    Dia_HMI dia(this);
    dia.set_p_soc(this->p_wk);
    dia.exec();
    qDebug() << Q_FUNC_INFO;

    return;
}
