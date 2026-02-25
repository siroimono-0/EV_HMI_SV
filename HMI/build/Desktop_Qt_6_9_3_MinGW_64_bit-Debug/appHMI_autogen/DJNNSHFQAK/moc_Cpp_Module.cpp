/****************************************************************************
** Meta object code from reading C++ file 'Cpp_Module.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Cpp_Module/Cpp_Module.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Cpp_Module.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10Cpp_ModuleE_t {};
} // unnamed namespace

template <> constexpr inline auto Cpp_Module::qt_create_metaobjectdata<qt_meta_tag_ZN10Cpp_ModuleE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "Cpp_Module",
        "sig_SocErr_ToQml",
        "",
        "msg",
        "sig_SocSuccess_ToQml",
        "sig_SocFailed_ToQml",
        "sig_card_success_ToQml",
        "sig_card_failed_ToQml",
        "sig_card_compare_ToQml",
        "sig_coil_ready_ok_ToQml",
        "sig_coil234_off_check_ToQml",
        "sig_charging_stop_ToQml",
        "join_WebSv",
        "id",
        "set_card_stat_To_serial",
        "stat",
        "chargingConnecter_open_To_serial",
        "chargingConnecter_ready_To_serial",
        "charging_start_To_serial",
        "charging_stop_To_serial",
        "chargingConnecter_close_To_serial",
        "chargingConnecter_off_To_serial",
        "charging_start_To_statStore",
        "charging_type_To_statStore",
        "type",
        "val",
        "charging_type_clear_To_statStore",
        "charging_end_stat_clear_To_statStore",
        "set_payment_To_statStore",
        "chard_ok_To_statStore",
        "charging_finished_To_statStore",
        "statStore",
        "StatStore*"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'sig_SocErr_ToQml'
        QtMocHelpers::SignalData<void(QString)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Signal 'sig_SocSuccess_ToQml'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sig_SocFailed_ToQml'
        QtMocHelpers::SignalData<void(QString)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Signal 'sig_card_success_ToQml'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sig_card_failed_ToQml'
        QtMocHelpers::SignalData<void(QString)>(7, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 3 },
        }}),
        // Signal 'sig_card_compare_ToQml'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sig_coil_ready_ok_ToQml'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sig_coil234_off_check_ToQml'
        QtMocHelpers::SignalData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sig_charging_stop_ToQml'
        QtMocHelpers::SignalData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'join_WebSv'
        QtMocHelpers::MethodData<void(QString)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 13 },
        }}),
        // Method 'set_card_stat_To_serial'
        QtMocHelpers::MethodData<void(bool)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 15 },
        }}),
        // Method 'chargingConnecter_open_To_serial'
        QtMocHelpers::MethodData<void()>(16, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'chargingConnecter_ready_To_serial'
        QtMocHelpers::MethodData<void()>(17, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'charging_start_To_serial'
        QtMocHelpers::MethodData<void()>(18, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'charging_stop_To_serial'
        QtMocHelpers::MethodData<void()>(19, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'chargingConnecter_close_To_serial'
        QtMocHelpers::MethodData<void()>(20, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'chargingConnecter_off_To_serial'
        QtMocHelpers::MethodData<void()>(21, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'charging_start_To_statStore'
        QtMocHelpers::MethodData<void()>(22, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'charging_type_To_statStore'
        QtMocHelpers::MethodData<void(QString, qint32)>(23, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 24 }, { QMetaType::Int, 25 },
        }}),
        // Method 'charging_type_clear_To_statStore'
        QtMocHelpers::MethodData<void()>(26, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'charging_end_stat_clear_To_statStore'
        QtMocHelpers::MethodData<void()>(27, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'set_payment_To_statStore'
        QtMocHelpers::MethodData<void()>(28, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'chard_ok_To_statStore'
        QtMocHelpers::MethodData<void()>(29, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'charging_finished_To_statStore'
        QtMocHelpers::MethodData<void()>(30, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'statStore'
        QtMocHelpers::PropertyData<StatStore*>(31, 0x80000000 | 32, QMC::DefaultPropertyFlags | QMC::EnumOrFlag | QMC::Constant),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<Cpp_Module, qt_meta_tag_ZN10Cpp_ModuleE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject Cpp_Module::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10Cpp_ModuleE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10Cpp_ModuleE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10Cpp_ModuleE_t>.metaTypes,
    nullptr
} };

void Cpp_Module::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<Cpp_Module *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->sig_SocErr_ToQml((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->sig_SocSuccess_ToQml(); break;
        case 2: _t->sig_SocFailed_ToQml((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->sig_card_success_ToQml(); break;
        case 4: _t->sig_card_failed_ToQml((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->sig_card_compare_ToQml(); break;
        case 6: _t->sig_coil_ready_ok_ToQml(); break;
        case 7: _t->sig_coil234_off_check_ToQml(); break;
        case 8: _t->sig_charging_stop_ToQml(); break;
        case 9: _t->join_WebSv((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 10: _t->set_card_stat_To_serial((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 11: _t->chargingConnecter_open_To_serial(); break;
        case 12: _t->chargingConnecter_ready_To_serial(); break;
        case 13: _t->charging_start_To_serial(); break;
        case 14: _t->charging_stop_To_serial(); break;
        case 15: _t->chargingConnecter_close_To_serial(); break;
        case 16: _t->chargingConnecter_off_To_serial(); break;
        case 17: _t->charging_start_To_statStore(); break;
        case 18: _t->charging_type_To_statStore((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<qint32>>(_a[2]))); break;
        case 19: _t->charging_type_clear_To_statStore(); break;
        case 20: _t->charging_end_stat_clear_To_statStore(); break;
        case 21: _t->set_payment_To_statStore(); break;
        case 22: _t->chard_ok_To_statStore(); break;
        case 23: _t->charging_finished_To_statStore(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (Cpp_Module::*)(QString )>(_a, &Cpp_Module::sig_SocErr_ToQml, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (Cpp_Module::*)()>(_a, &Cpp_Module::sig_SocSuccess_ToQml, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (Cpp_Module::*)(QString )>(_a, &Cpp_Module::sig_SocFailed_ToQml, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (Cpp_Module::*)()>(_a, &Cpp_Module::sig_card_success_ToQml, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (Cpp_Module::*)(QString )>(_a, &Cpp_Module::sig_card_failed_ToQml, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (Cpp_Module::*)()>(_a, &Cpp_Module::sig_card_compare_ToQml, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (Cpp_Module::*)()>(_a, &Cpp_Module::sig_coil_ready_ok_ToQml, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (Cpp_Module::*)()>(_a, &Cpp_Module::sig_coil234_off_check_ToQml, 7))
            return;
        if (QtMocHelpers::indexOfMethod<void (Cpp_Module::*)()>(_a, &Cpp_Module::sig_charging_stop_ToQml, 8))
            return;
    }
    if (_c == QMetaObject::RegisterPropertyMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< StatStore* >(); break;
        }
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<StatStore**>(_v) = _t->statStore(); break;
        default: break;
        }
    }
}

const QMetaObject *Cpp_Module::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Cpp_Module::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10Cpp_ModuleE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Cpp_Module::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 24)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 24;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void Cpp_Module::sig_SocErr_ToQml(QString _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void Cpp_Module::sig_SocSuccess_ToQml()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Cpp_Module::sig_SocFailed_ToQml(QString _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}

// SIGNAL 3
void Cpp_Module::sig_card_success_ToQml()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void Cpp_Module::sig_card_failed_ToQml(QString _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 4, nullptr, _t1);
}

// SIGNAL 5
void Cpp_Module::sig_card_compare_ToQml()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void Cpp_Module::sig_coil_ready_ok_ToQml()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void Cpp_Module::sig_coil234_off_check_ToQml()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void Cpp_Module::sig_charging_stop_ToQml()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}
QT_WARNING_POP
