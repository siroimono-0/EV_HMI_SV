#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "./Cpp_Module/Cpp_Module.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    Cpp_Module cpp_Module;

    // qmlRegisterType<Cpp_WebSocSv>("Cpp_WebSocSv", 1, 0, "Cpp_WebSocSv");

    engine.rootContext()->setContextProperty("cppSv", &cpp_Module);
    qRegisterMetaType<stat_data>("stat_data");

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("WebSocSv", "Main");

    return app.exec();
}
