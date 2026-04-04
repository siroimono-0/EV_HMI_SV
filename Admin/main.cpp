#include <QApplication>
#include "Admin.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<MD_charging_log *>("MD_charging_log*");
    qRegisterMetaType<MD_hmi_current_stat *>("MD_hmi_current_stat*");
    qRegisterMetaType<MD_hmi_device *>("MD_hmi_device*");
    qRegisterMetaType<MD_membership_card *>("MD_membership_card*");
    qRegisterMetaType<MD_membership_log *>("MD_membership_log*");
    qRegisterMetaType<MD_store_user *>("MD_store_user*");
    qRegisterMetaType<Dia_membership_card *>("Dia_membership_card*");
    qRegisterMetaType<Dia_HMI *>("Dia_HMI*");
    qRegisterMetaType<Dia_ad *>("Dia_ad*");

    Admin w;
    w.show();

    QObject::connect(qApp, &QCoreApplication::aboutToQuit, []() {
        qDebug() << "aboutToQuit fired";
    });

    qDebug() << "quitOnLastWindowClosed =" << qApp->quitOnLastWindowClosed();

    return a.exec();
}
