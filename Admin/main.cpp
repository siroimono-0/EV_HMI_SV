#include "Admin.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Admin w;
    w.show();
    QObject::connect(qApp, &QCoreApplication::aboutToQuit, []() {
        qDebug() << "aboutToQuit fired";
    });

    qDebug() << "quitOnLastWindowClosed =" << qApp->quitOnLastWindowClosed();

    return a.exec();
}
