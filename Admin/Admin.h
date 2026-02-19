#ifndef ADMIN_H
#define ADMIN_H

#include <QMainWindow>
#include <QThread>
#include "Dia_Register.h"

class WK_soc;

QT_BEGIN_NAMESPACE
namespace Ui {
class Admin;
}
QT_END_NAMESPACE

class Admin : public QMainWindow
{
    Q_OBJECT

public:
    Admin(QWidget *parent = nullptr);
    ~Admin();

    void create_wk();

public slots:
    void slot_btn_register_clicked();

    void slot_btn_hmiRegister_clicked();

signals:

private:
    Ui::Admin *ui;

    WK_soc *p_wk;
    QThread *p_th;
};
#endif // ADMIN_H
