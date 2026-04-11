#ifndef DIA_REGISTER_H
#define DIA_REGISTER_H

#include <QDialog>

class WK_soc;

namespace Ui {
class Dia_Register;
}

class Dia_Register : public QDialog
{
    Q_OBJECT

public:
    explicit Dia_Register(QWidget *parent = nullptr);
    ~Dia_Register();

    void set_soc(WK_soc *soc);

public slots:
    void slot_btnClicked();

signals:

private:
    Ui::Dia_Register *ui;

    WK_soc *p_soc = nullptr;
};

#endif // DIA_REGISTER_H
