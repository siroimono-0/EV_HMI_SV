// #include <QGuiApplication>
// #include <QQmlApplicationEngine>
// #include <QQmlContext>
// #include <QQuickStyle>
#include "./Cpp_Module/Cpp_Module.h"
#include "./Cpp_Module/Hub.h"
#include "./Cpp_Module/WK_Soc.h"

int main(int argc, char *argv[])
{
    // QGuiApplication app(argc, argv);
    QCoreApplication app(argc, argv);

    // QQmlApplicationEngine engine;
    Cpp_Module cpp_Module;

    // qmlRegisterType<Cpp_WebSocSv>("Cpp_WebSocSv", 1, 0, "Cpp_WebSocSv");

    qRegisterMetaType<stat_data>("stat_data");
    qRegisterMetaType<store_info>("store_info");
    qRegisterMetaType<WK_Soc *>("WK_Socc*");
    qRegisterMetaType<charging_log_admin>("charging_log_admin");
    qRegisterMetaType<QVector<charging_log_admin>>("QVector<charging_log_admin>");
    qRegisterMetaType<QVector<membership_card_admin>>("QVector<membership_card_admin>");
    qRegisterMetaType<Hub *>("Hub*");
    qRegisterMetaType<mp_wk_key>("mp_wk_key");
    /*
    engine.rootContext()->setContextProperty("cppSv", &cpp_Module);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("WebSocSv", "Main");
    */
    return app.exec();
}
