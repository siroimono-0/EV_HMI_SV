#ifndef DIA_MEMBERSHIP_CARD_H
#define DIA_MEMBERSHIP_CARD_H

#include <QDialog>
#include "../Common/StatData.h"

namespace Ui {
class Dia_membership_card;
}
class WK_soc;

class Dia_membership_card : public QDialog
{
    Q_OBJECT

public:
    explicit Dia_membership_card(QWidget *parent = nullptr);
    ~Dia_membership_card();

    void set_p_soc(WK_soc *set);

public slots:
    void slot_search_btn_Clicked();

    void slot_display_select_ret(QVector<membership_card_admin> ret);

    void slot_revision_btn_Clicked();

    // void slot_

private:
    Ui::Dia_membership_card *ui;
    WK_soc *p_soc = nullptr;
};
Q_DECLARE_METATYPE(Dia_membership_card *)
#endif // DIA_MEMBERSHIP_CARD_H
