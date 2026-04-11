#include "Dia_Register.h"
#include "./CppModule/WK_soc.h"
#include "ui_Dia_Register.h"

Dia_Register::Dia_Register(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dia_Register)
{
    ui->setupUi(this);

    connect(ui->btn_register, &QPushButton::clicked, this, &Dia_Register::slot_btnClicked);
}

Dia_Register::~Dia_Register()
{
    delete ui;
}

void Dia_Register::set_soc(WK_soc *soc)
{
    this->p_soc = soc;
    return;
}

void Dia_Register::slot_btnClicked()
{
    QString qs_id = ui->le_id->text();
    QString qs_name = ui->le_name->text();
    QString qs_location = ui->le_location->text();

    QMetaObject::invokeMethod(this->p_soc,
                              "slot_register_store",
                              Qt::QueuedConnection,
                              Q_ARG(QString, qs_id),
                              Q_ARG(QString, qs_name),
                              Q_ARG(QString, qs_location));
    qDebug() << Q_FUNC_INFO;

    this->close();
    return;
}
