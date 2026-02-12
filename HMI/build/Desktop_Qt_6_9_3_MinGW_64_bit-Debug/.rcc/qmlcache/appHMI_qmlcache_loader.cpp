#include <QtQml/qqmlprivate.h>
#include <QtCore/qdir.h>
#include <QtCore/qurl.h>
#include <QtCore/qhash.h>
#include <QtCore/qstring.h>

namespace QmlCacheGeneratedCode {
namespace _qt_qml_HMI_Main_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_HMI_Start_page_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_HMI_HMI_main_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_HMI_Select_charge_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_HMI_Select_card_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_HMI_Select_amount_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_HMI__0x2e__Qml_Module_Popup_Text_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_HMI__0x2e__Qml_Module_Keypad_Number_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_HMI__0x2e__Qml_Module_BackGround_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_HMI__0x2e__Qml_Module_RecBtn_qml { 
    extern const unsigned char qmlData[];
    extern const QQmlPrivate::AOTCompiledFunction aotBuiltFunctions[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), &aotBuiltFunctions[0], nullptr
    };
}
namespace _qt_qml_HMI_Qml_Module_Circle_Number_qml { 
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
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/HMI/Main.qml"), &QmlCacheGeneratedCode::_qt_qml_HMI_Main_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/HMI/Start_page.qml"), &QmlCacheGeneratedCode::_qt_qml_HMI_Start_page_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/HMI/HMI_main.qml"), &QmlCacheGeneratedCode::_qt_qml_HMI_HMI_main_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/HMI/Select_charge.qml"), &QmlCacheGeneratedCode::_qt_qml_HMI_Select_charge_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/HMI/Select_card.qml"), &QmlCacheGeneratedCode::_qt_qml_HMI_Select_card_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/HMI/Select_amount.qml"), &QmlCacheGeneratedCode::_qt_qml_HMI_Select_amount_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/HMI/./Qml_Module/Popup_Text.qml"), &QmlCacheGeneratedCode::_qt_qml_HMI__0x2e__Qml_Module_Popup_Text_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/HMI/./Qml_Module/Keypad_Number.qml"), &QmlCacheGeneratedCode::_qt_qml_HMI__0x2e__Qml_Module_Keypad_Number_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/HMI/./Qml_Module/BackGround.qml"), &QmlCacheGeneratedCode::_qt_qml_HMI__0x2e__Qml_Module_BackGround_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/HMI/./Qml_Module/RecBtn.qml"), &QmlCacheGeneratedCode::_qt_qml_HMI__0x2e__Qml_Module_RecBtn_qml::unit);
    resourcePathToCachedUnit.insert(QStringLiteral("/qt/qml/HMI/Qml_Module/Circle_Number.qml"), &QmlCacheGeneratedCode::_qt_qml_HMI_Qml_Module_Circle_Number_qml::unit);
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
int QT_MANGLE_NAMESPACE(qInitResources_qmlcache_appHMI)() {
    ::unitRegistry();
    return 1;
}
Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_qmlcache_appHMI))
int QT_MANGLE_NAMESPACE(qCleanupResources_qmlcache_appHMI)() {
    return 1;
}
