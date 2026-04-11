#ifndef DIA_AD_H
#define DIA_AD_H

#include <QDialog>
#include <QDir>
#include <QFileDialog>
// #include "./CppModule/WK_soc.h"
class WK_soc;

namespace Ui {
class Dia_ad;
}

class Dia_ad : public QDialog
{
    Q_OBJECT

public:
    explicit Dia_ad(QWidget *parent = nullptr);
    ~Dia_ad();
    void set_p_soc(WK_soc *set);

public slots:
    void slot_btn_search();
    void slot_btn_register();

private:
    Ui::Dia_ad *ui;
    WK_soc *p_soc = nullptr;
};
Q_DECLARE_METATYPE(Dia_ad *)

#endif // DIA_AD_H
