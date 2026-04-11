#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Cpp_cli.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Cpp_cli *p_cli = new Cpp_cli(&engine);

    engine.rootContext()->setContextProperty("Cpp_cli", p_cli);
    QObject::connect(&app, &QCoreApplication::aboutToQuit, p_cli, &Cpp_cli::shutdown);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("Test_cli", "Main");

    return app.exec();
}
