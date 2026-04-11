#ifndef DIA_REGISTER_HMI_H
#define DIA_REGISTER_HMI_H

#include <QDialog>
#include "./CppModule/WK_soc.h"

namespace Ui {
class Dia_Register_HMI;
}

class Dia_Register_HMI : public QDialog
{
    Q_OBJECT

public:
    explicit Dia_Register_HMI(QWidget *parent = nullptr);
    ~Dia_Register_HMI();

    void set_p_soc(WK_soc *set);

public slots:
    void slot_btnClicked();

private:
    Ui::Dia_Register_HMI *ui;
    WK_soc *p_soc;
};

#endif // DIA_REGISTER_HMI_H
