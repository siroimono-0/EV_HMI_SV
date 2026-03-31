#include "Dia_membership_card.h"
#include "./CppModule/WK_soc.h"
#include "ui_Dia_membership_card.h"

Dia_membership_card::Dia_membership_card(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dia_membership_card)
{
    ui->setupUi(this);
    connect(this->ui->pushButton,
            &QPushButton::clicked,
            this,
            &Dia_membership_card::slot_search_btn_Clicked);

    connect(this->ui->pushButton_2,
            &QPushButton::clicked,
            this,
            &Dia_membership_card::slot_revision_btn_Clicked);
}

Dia_membership_card::~Dia_membership_card()
{
    delete ui;
}

void Dia_membership_card::slot_search_btn_Clicked()
{
    QString card_uid = this->ui->lineEdit->text();

    QMetaObject::invokeMethod(this->p_soc,
                              "slot_req_mCard_status_db",
                              Qt::QueuedConnection,
                              Q_ARG(QString, card_uid));

    // this->close();
    return;
}

void Dia_membership_card::set_p_soc(WK_soc *set)
{
    this->p_soc = set;
    QMetaObject::invokeMethod(this->p_soc,
                              "slot_set_p_dia_mCard",
                              Q_ARG(Dia_membership_card *, this));
    return;
}

void Dia_membership_card::slot_display_select_ret(QVector<membership_card_admin> ret)
{
    membership_card_admin st_data = {0};
    st_data = ret.front();
    this->ui->label->setText(st_data.card_uid);
    this->ui->label_2->setText(QString::number(st_data.balance_total));
    this->ui->label_3->setText(QString::number(st_data.balance_available));
    this->ui->label_5->setText(QString::number(st_data.hold_amount));
    this->ui->label_4->setText(st_data.transaction_state);

    this->ui->label_12->setText(st_data.card_uid);

    return;
}

void Dia_membership_card::slot_revision_btn_Clicked()
{
    membership_card_admin st_data = {0};
    st_data.card_uid = this->ui->label_12->text();
    st_data.balance_total = this->ui->lineEdit_2->text().toInt();
    st_data.balance_available = this->ui->lineEdit_3->text().toInt();
    st_data.hold_amount = this->ui->lineEdit_4->text().toInt();
    st_data.transaction_state = this->ui->comboBox->currentText();

    this->ui->lineEdit_2->clear();
    this->ui->lineEdit_3->clear();
    this->ui->lineEdit_4->clear();

    QMetaObject::invokeMethod(this->p_soc,
                              "slot_req_mCard_revision_db",
                              Q_ARG(membership_card_admin, st_data));
    return;
}
