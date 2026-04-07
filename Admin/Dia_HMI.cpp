#include "Dia_HMI.h"
#include "./CppModule/WK_soc.h"
#include "ui_Dia_HMI.h"

Dia_HMI::Dia_HMI(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dia_HMI)
{
    ui->setupUi(this);

    connect(this->ui->pushButton_8, &QPushButton::clicked, this, &Dia_HMI::slot_Btn_search);

    connect(this->ui->pushButton_2,
            &QPushButton::clicked,
            this,
            &Dia_HMI::slot_Btn_move_maintenance);

    connect(this->ui->pushButton, &QPushButton::clicked, this, &Dia_HMI::slot_Btn_move_home);

    connect(this->ui->pushButton_3, &QPushButton::clicked, this, &Dia_HMI::slot_Btn_revision_price);

    connect(this->ui->pushButton_4, &QPushButton::clicked, this, &Dia_HMI::slot_Btn_revision_method);

    connect(this->ui->pushButton_5,
            &QPushButton::clicked,
            this,
            &Dia_HMI::slot_Btn_connector_case_unlock);

    connect(this->ui->pushButton_6,
            &QPushButton::clicked,
            this,
            &Dia_HMI::slot_Btn_connector_unlock);

    connect(this->ui->pushButton_9, &QPushButton::clicked, this, &Dia_HMI::slot_Btn_ad_add);

    connect(this->ui->pushButton_10, &QPushButton::clicked, this, &Dia_HMI::slot_Btn_ad_remove);

    connect(this->ui->pushButton_11, &QPushButton::clicked, this, &Dia_HMI::slot_Btn_shutdown_nomal);

    connect(this->ui->pushButton_7,
            &QPushButton::clicked,
            this,
            &Dia_HMI::slot_Btn_shutdown_restart);
}

Dia_HMI::~Dia_HMI()
{
    delete ui;
}

void Dia_HMI::set_p_soc(WK_soc *set)
{
    this->p_soc = set;
    connect(this, &Dia_HMI::sig_revision_hmi_To_Soc, this->p_soc, &WK_soc::slot_revision_hmi_To_SV);

    QMetaObject::invokeMethod(this->p_soc,
                              "slot_set_p_dia_hmi",
                              Qt::QueuedConnection,
                              Q_ARG(Dia_HMI *, this));

    return;
}

void Dia_HMI::slot_Btn_search()
{
    QString col_1 = "hmi_id";
    QString val_1 = this->ui->lineEdit_3->text();

    QString col_2 = "store_id";
    QString val_2 = this->ui->lineEdit_2->text();

    if (val_1.isEmpty() || val_2.isEmpty())
    {
        return;
    }

    QMetaObject::invokeMethod(this->p_soc,
                              "slot_set_dia_hmi_reqStat",
                              Qt::BlockingQueuedConnection,
                              Q_ARG(bool, true));

    QMetaObject::invokeMethod(this->p_soc,
                              "slot_req_select_db",
                              Qt::QueuedConnection,
                              Q_ARG(QString, "hmi_current_stat"),
                              Q_ARG(int, 2),
                              Q_ARG(QString, col_1),
                              Q_ARG(QString, val_1),
                              Q_ARG(QString, col_2),
                              Q_ARG(QString, val_2));

    return;
}

void Dia_HMI::slot_update_hmi_current_stat_From_Soc(const QVector<hmi_current_stat_admin> ret)
{
    auto it = ret.front();
    this->ui->label_2->setText(QString::number(it.store_id));
    this->ui->label_4->setText(it.hmi_id);
    this->ui->label_6->setText(it.last_heartbeat_at.left(19));
    this->ui->label_8->setText(it.screen_name);

    this->ui->lineEdit_2->clear();
    this->ui->lineEdit_3->clear();

    return;
}

void Dia_HMI::slot_Btn_move_maintenance()
{
    if (this->ui->label_4->text().isEmpty())
    {
        return;
    }
    struct revision_hmi_admin st_data = {0};
    st_data.store_id = this->ui->label_2->text().toInt();
    st_data.hmi_id = this->ui->label_4->text();
    st_data.cmd = "screen_move";
    st_data.val = "maintenance";

    emit this->sig_revision_hmi_To_Soc(st_data);
    return;
}

void Dia_HMI::slot_Btn_move_home()
{
    if (this->ui->label_4->text().isEmpty())
    {
        return;
    }
    struct revision_hmi_admin st_data = {0};
    st_data.store_id = this->ui->label_2->text().toInt();
    st_data.hmi_id = this->ui->label_4->text();
    st_data.cmd = "screen_move";
    st_data.val = "home";

    emit this->sig_revision_hmi_To_Soc(st_data);
    return;
}

void Dia_HMI::slot_Btn_revision_price()
{
    if (this->ui->label_4->text().isEmpty())
    {
        return;
    }
    struct revision_hmi_admin st_data = {0};
    st_data.store_id = this->ui->label_2->text().toInt();
    st_data.hmi_id = this->ui->label_4->text();
    st_data.cmd = "price";
    st_data.val = this->ui->lineEdit->text();

    this->ui->lineEdit->clear();

    emit this->sig_revision_hmi_To_Soc(st_data);
    return;
}

void Dia_HMI::slot_Btn_revision_method()
{
    if (this->ui->label_4->text().isEmpty())
    {
        return;
    }
    struct revision_hmi_admin st_data = {0};
    st_data.store_id = this->ui->label_2->text().toInt();
    st_data.hmi_id = this->ui->label_4->text();
    st_data.cmd = "method";
    st_data.val = this->ui->comboBox->currentText();

    emit this->sig_revision_hmi_To_Soc(st_data);
    return;
}

void Dia_HMI::slot_Btn_connector_case_unlock()
{
    if (this->ui->label_4->text().isEmpty())
    {
        return;
    }
    struct revision_hmi_admin st_data = {0};
    st_data.store_id = this->ui->label_2->text().toInt();
    st_data.hmi_id = this->ui->label_4->text();
    st_data.cmd = "connector_case";
    st_data.val = "unlock";

    emit this->sig_revision_hmi_To_Soc(st_data);
    return;
}

void Dia_HMI::slot_Btn_connector_unlock()
{
    if (this->ui->label_4->text().isEmpty())
    {
        return;
    }

    struct revision_hmi_admin st_data = {0};
    st_data.store_id = this->ui->label_2->text().toInt();
    st_data.hmi_id = this->ui->label_4->text();
    st_data.cmd = "connector";
    st_data.val = "unlock";

    emit this->sig_revision_hmi_To_Soc(st_data);
    return;
}

void Dia_HMI::slot_Btn_ad_add()
{
    if (this->ui->label_4->text().isEmpty())
    {
        return;
    }
    struct revision_hmi_admin st_data = {0};
    st_data.store_id = this->ui->label_2->text().toInt();
    st_data.hmi_id = this->ui->label_4->text();
    st_data.cmd = "ad_add";
    st_data.val = this->ui->lineEdit_4->text();

    this->ui->lineEdit_4->clear();
    emit this->sig_revision_hmi_To_Soc(st_data);

    return;
}

void Dia_HMI::slot_Btn_ad_remove()
{
    if (this->ui->label_4->text().isEmpty())
    {
        return;
    }
    struct revision_hmi_admin st_data = {0};
    st_data.store_id = this->ui->label_2->text().toInt();
    st_data.hmi_id = this->ui->label_4->text();
    st_data.cmd = "ad_remove";
    st_data.val = this->ui->lineEdit_5->text();

    this->ui->lineEdit_5->clear();
    emit this->sig_revision_hmi_To_Soc(st_data);

    return;
}

void Dia_HMI::slot_Btn_shutdown_nomal()
{
    if (this->ui->label_4->text().isEmpty())
    {
        return;
    }
    struct revision_hmi_admin st_data = {0};
    st_data.store_id = this->ui->label_2->text().toInt();
    st_data.hmi_id = this->ui->label_4->text();
    st_data.cmd = "shutdown";
    st_data.val = "nomal";
    emit this->sig_revision_hmi_To_Soc(st_data);

    return;
}

void Dia_HMI::slot_Btn_shutdown_restart()
{
    if (this->ui->label_4->text().isEmpty())
    {
        return;
    }
    struct revision_hmi_admin st_data = {0};
    st_data.store_id = this->ui->label_2->text().toInt();
    st_data.hmi_id = this->ui->label_4->text();
    st_data.cmd = "shutdown";
    st_data.val = "restart";
    emit this->sig_revision_hmi_To_Soc(st_data);

    return;
}

/*
    주소 지정해줘야댐
    Dialog에서 버튼 클릭하는거 함수는 따로뺌
    각 함수에서 매개변수 받아서 signal에 넣어서 분기시킴
    소켓에서 받은 후 SV 전달
    타입은 리비전
    그 뒤 cmd / val로 분기
    SV -> hmi 전달
    map에 넣어서 관리하던거 수정해서 각 소켓이랑 매칭 -> hmi특정할 수 있도록 수정
*/
