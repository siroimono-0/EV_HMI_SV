#ifndef ADMIN_H
#define ADMIN_H

#include <QDir>
#include <QGuiApplication>
#include <QLabel>
#include <QMainWindow>
#include <QQmlContext>
#include <QQmlEngine>
#include <QQuickWidget>
#include <QThread>

#include "CppModule/MD_charging_log.h"
#include "CppModule/MD_hmi_current_stat.h"
#include "CppModule/MD_hmi_device.h"
#include "CppModule/MD_membership_card.h"
#include "CppModule/MD_membership_log.h"
#include "CppModule/MD_store_user.h"
#include "Dia_HMI.h"
#include "Dia_Register.h"
#include "Dia_Register_HMI.h"
#include "Dia_ad.h"
#include "Dia_membership_card.h"

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

    void create_qml_charging_log();
    void create_qml_hmi_current_stat();
    void create_qml_hmi_device();
    void create_qml_membership_card();
    void create_qml_membership_log();
    void create_qml_store_user();

public slots:
    void slot_btn_register_clicked();

    void slot_btn_hmiRegister_clicked();

    void slot_btn_mCard_clicked();

    void slot_btn_HMI_revision_clicked();

    void slot_set_comboBox(QString select_text);
    void slot_set_comboBox_2(QString select_text);
    void slot_set_comboBox_3(QString select_text);

    void search_btn_clicked();

    void slot_btn_ad_upload();

signals:

private:
    Ui::Admin *ui;

    WK_soc *p_wk;
    QThread *p_th;

    int idx_charging_log;
    QQuickWidget *p_qquick_charging_log = nullptr;
    MD_charging_log *p_md_charging_log = nullptr;

    int idx_hmi_current_stat;
    QQuickWidget *p_qquick_hmi_current_stat = nullptr;
    MD_hmi_current_stat *p_md_hmi_current_stat = nullptr;

    int idx_hmi_device;
    QQuickWidget *p_qquick_hmi_device = nullptr;
    MD_hmi_device *p_md_hmi_device = nullptr;

    int idx_membership_card;
    QQuickWidget *p_qquick_membership_card = nullptr;
    MD_membership_card *p_md_membership_card = nullptr;

    int idx_membership_log;
    QQuickWidget *p_qquick_membership_log = nullptr;
    MD_membership_log *p_md_membership_log = nullptr;

    int idx_store_user;
    QQuickWidget *p_qquick_store_user = nullptr;
    MD_store_user *p_md_store_user = nullptr;
};

#endif // ADMIN_H
