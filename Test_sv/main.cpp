#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Cpp_Sv.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    Cpp_Sv sv;
    engine.rootContext()->setContextProperty("Cpp_sv", &sv);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Test_sv", "Main");

    return app.exec();
}
