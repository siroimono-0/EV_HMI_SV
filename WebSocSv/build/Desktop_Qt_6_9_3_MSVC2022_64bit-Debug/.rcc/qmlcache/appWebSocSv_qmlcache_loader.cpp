#include <QtQml/qqmlprivate.h>
#include <QtCore/qdir.h>
#include <QtCore/qurl.h>
#include <QtCore/qhash.h>
#include <QtCore/qstring.h>

namespace QmlCacheGeneratedCode {
namespace _qt_qml_WebSocSv_Main_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_WebSocSv_Start_page_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_WebSocSv_SV_info_page_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_WebSocSv_BackBtn_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_WebSocSv_StoreManagement_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_WebSocSv__0x2e__Qml_Module_BackGround_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_WebSocSv__0x2e__Qml_Module_Popup_Text_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_WebSocSv__0x2e__Qml_Module_RecBtn_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_WebSocSv__0x2e__Qml_Module_PopUp_CreateStore_DB_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}

}
namespace {
struct Registry {
    Registry();
    ~Registry();
    QHash<QString, const QQmlPrivate::CachedQmlUnit*> resourcePathToCachedUnit;
    static const QQmlPrivate::CachedQmlUnit *lookupCachedUnit(const QUrl &url);
};

Q_GLOBAL_STATIC(Registry, unitRegistry)


Registry::Registry() {
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/WebSocSv/Main.qml"), &QmlCacheGeneratedCode::_qt_qml_WebSocSv_Main_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/WebSocSv/Start_page.qml"), &QmlCacheGeneratedCode::_qt_qml_WebSocSv_Start_page_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/WebSocSv/SV_info_page.qml"), &QmlCacheGeneratedCode::_qt_qml_WebSocSv_SV_info_page_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/WebSocSv/BackBtn.qml"), &QmlCacheGeneratedCode::_qt_qml_WebSocSv_BackBtn_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/WebSocSv/StoreManagement.qml"), &QmlCacheGeneratedCode::_qt_qml_WebSocSv_StoreManagement_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/WebSocSv/./Qml_Module/BackGround.qml"), &QmlCacheGeneratedCode::_qt_qml_WebSocSv__0x2e__Qml_Module_BackGround_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/WebSocSv/./Qml_Module/Popup_Text.qml"), &QmlCacheGeneratedCode::_qt_qml_WebSocSv__0x2e__Qml_Module_Popup_Text_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/WebSocSv/./Qml_Module/RecBtn.qml"), &QmlCacheGeneratedCode::_qt_qml_WebSocSv__0x2e__Qml_Module_RecBtn_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/WebSocSv/./Qml_Module/PopUp_CreateStore_DB.qml"), &QmlCacheGeneratedCode::_qt_qml_WebSocSv__0x2e__Qml_Module_PopUp_CreateStore_DB_qml::unit);
    QQmlPrivate::RegisterQmlUnitCacheHook registration;
    registration.structVersion = 0;
    registration.lookupCachedQmlUnit = &lookupCachedUnit;
    QQmlPrivate::qmlregister(QQmlPrivate::QmlUnitCacheHookRegistration, &registration);
}

Registry::~Registry() {
    QQmlPrivate::qmlunregister(QQmlPrivate::QmlUnitCacheHookRegistration, quintptr(&lookupCachedUnit));
}

const QQmlPrivate::CachedQmlUnit *Registry::lookupCachedUnit(const QUrl &url) {
    if (url.scheme() != QLatin1String("qrc"))
        return nullptr;
    QString resourcePath = QDir::cleanPath(url.path());
    if (resourcePath.isEmpty())
        return nullptr;
    if (!resourcePath.startsWith(QLatin1Char('/')))
        resourcePath.prepend(QLatin1Char('/'));
    return unitRegistry()->resourcePathToCachedUnit.value(resourcePath, nullptr);
}
}
int QT_MANGLE_NAMESPACE(qInitResources_qmlcache_appWebSocSv)() {
    ::unitRegistry();
    return 1;
}
Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_qmlcache_appWebSocSv))
int QT_MANGLE_NAMESPACE(qCleanupResources_qmlcache_appWebSocSv)() {
    return 1;
}
