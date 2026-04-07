#ifndef DIA_HMI_H
#define DIA_HMI_H

#include <QDialog>
#include "../Common/StatData.h"

namespace Ui {
class Dia_HMI;
}

class WK_soc;
class Dia_HMI : public QDialog
{
    Q_OBJECT

public:
    explicit Dia_HMI(QWidget *parent = nullptr);
    ~Dia_HMI();

    void set_p_soc(WK_soc *set);

public slots:
    void slot_Btn_search();
    void slot_Btn_move_maintenance();
    void slot_Btn_move_home();
    void slot_Btn_revision_price();
    void slot_Btn_revision_method();
    void slot_Btn_connector_case_unlock();
    void slot_Btn_connector_unlock();

    void slot_update_hmi_current_stat_From_Soc(const QVector<hmi_current_stat_admin> ret);

    void slot_Btn_ad_add();
    void slot_Btn_ad_remove();

    void slot_Btn_shutdown_nomal();
    void slot_Btn_shutdown_restart();
signals:
    // set_p_soc에서 커넥트
    void sig_revision_hmi_To_Soc(revision_hmi_admin);

private:
    Ui::Dia_HMI *ui;
    WK_soc *p_soc = nullptr;
};

Q_DECLARE_METATYPE(Dia_HMI *)
/*
    type: revision_HMI
    cmd: screen_move //
    val: home // maintenance

    cmd: price //
    val: string //

    cmd: method
    val: string

    cmd: connector_case
    val: unlock

    cmd: connector
    val: unlock

    cmd: ad_add
    val: string

    cmd: ad_remove
    val: string

    cmd: shutdown
    val: nomal // restart
*/

#endif // DIA_HMI_H
