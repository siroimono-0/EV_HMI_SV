#include "Dia_Register_HMI.h"
#include "ui_Dia_Register_HMI.h"

Dia_Register_HMI::Dia_Register_HMI(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dia_Register_HMI)
{
    ui->setupUi(this);

    connect(ui->btn_register, &QPushButton::clicked, this, &Dia_Register_HMI::slot_btnClicked);
}

Dia_Register_HMI::~Dia_Register_HMI()
{
    delete ui;
}

void Dia_Register_HMI::set_p_soc(WK_soc *set)
{
    this->p_soc = set;
    return;
}

void Dia_Register_HMI::slot_btnClicked()
{
    QString store_id = ui->le_id->text();
    QString hmi_id = ui->le_name->text();

    QMetaObject::invokeMethod(this->p_soc,
                              "slot_register_hmi",
                              Qt::QueuedConnection,
                              Q_ARG(QString, store_id),
                              Q_ARG(QString, hmi_id));
    qDebug() << Q_FUNC_INFO;

    this->close();
    return;
}
