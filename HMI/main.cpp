#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include "./Cpp_Module/Cpp_Module.h"
#include "./Cpp_Module/WK_Serial.h"
#include "./Cpp_Module/WK_WebSocket.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Fusion");

    QQmlApplicationEngine engine;
    Cpp_Module cpp_module;

    qRegisterMetaType<WK_WebSocket *>("WK_WebSocket*");
    qRegisterMetaType<WK_Serial *>("WK_Serial*");
    qRegisterMetaType<CHARGING_TYPE>("CHARGING_TYPE");
    qRegisterMetaType<charging_stat>("charging_stat");
    qRegisterMetaType<heartbit_data>("heartbit_data");

    engine.rootContext()->setContextProperty("cpp_module", &cpp_module);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("HMI", "Main");

    return app.exec();
}
