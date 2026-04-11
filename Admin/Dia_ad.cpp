#include "Dia_ad.h"
#include "./CppModule/WK_soc.h"
#include "ui_Dia_ad.h"

Dia_ad::Dia_ad(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dia_ad)
{
    ui->setupUi(this);

    connect(this->ui->pushButton, &QPushButton::clicked, this, &Dia_ad::slot_btn_search);

    connect(this->ui->pushButton_2, &QPushButton::clicked, this, &Dia_ad::slot_btn_register);
}

Dia_ad::~Dia_ad()
{
    delete ui;
}

void Dia_ad::slot_btn_search()
{
    QString cur_path = QDir::currentPath();
    QString path = QFileDialog::getOpenFileName(this, "select file", cur_path, "MP4 Files (*.mp4)");
    this->ui->label->setText(path);

    return;
}

void Dia_ad::set_p_soc(WK_soc *set)
{
    this->p_soc = set;
    QMetaObject::invokeMethod(this->p_soc,
                              "slot_set_p_dia_ad",
                              Qt::QueuedConnection,
                              Q_ARG(Dia_ad *, this));
    return;
}

void Dia_ad::slot_btn_register()
{
    QMetaObject::invokeMethod(this->p_soc,
                              "slot_netAccess_post",
                              Qt::QueuedConnection,
                              Q_ARG(QString, this->ui->label->text()));
    return;
}
