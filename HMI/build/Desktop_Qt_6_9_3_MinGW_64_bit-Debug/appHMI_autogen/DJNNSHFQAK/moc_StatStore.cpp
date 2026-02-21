/****************************************************************************
** Meta object code from reading C++ file 'StatStore.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Cpp_Module/StatStore.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'StatStore.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN9StatStoreE_t {};
} // unnamed namespace

template <> constexpr inline auto StatStore::qt_create_metaobjectdata<qt_meta_tag_ZN9StatStoreE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "StatStore",
        "sig_Stat_changed",
        "",
        "stat_data",
        "st_stat",
        "sig_elapsed_time_change",
        "sig_remaining_time_change",
        "sig_charging_speed_change",
        "sig_charging_capacity_change",
        "sig_charging_amount_change",
        "sig_battery_start_persent_change",
        "sig_battery_current_change",
        "slot_update_FromSoc",
        "slot_update_FromSerial",
        "slot_update_FromModule",
        "slot_update_current",
        "slot_get_stat",
        "slot_set_p_serial",
        "WK_Serial*",
        "serial",
        "slot_update_chargingStat",
        "charging_stat",
        "c_stat",
        "slot_set_charging_type",
        "CHARGING_TYPE",
        "charging_type",
        "val",
        "slot_clear_charging_type",
        "elapsed_time",
        "remaining_time",
        "charging_speed",
        "charging_capacity",
        "charging_amount",
        "battery_start_persent",
        "battery_current"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'sig_Stat_changed'
        QtMocHelpers::SignalData<void(stat_data)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'sig_elapsed_time_change'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sig_remaining_time_change'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sig_charging_speed_change'
        QtMocHelpers::SignalData<void()>(7, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sig_charging_capacity_change'
        QtMocHelpers::SignalData<void()>(8, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sig_charging_amount_change'
        QtMocHelpers::SignalData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sig_battery_start_persent_change'
        QtMocHelpers::SignalData<void()>(10, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sig_battery_current_change'
        QtMocHelpers::SignalData<void()>(11, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'slot_update_FromSoc'
        QtMocHelpers::SlotData<void(stat_data)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Slot 'slot_update_FromSerial'
        QtMocHelpers::SlotData<void(stat_data)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Slot 'slot_update_FromModule'
        QtMocHelpers::SlotData<void(stat_data)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Slot 'slot_update_current'
        QtMocHelpers::SlotData<void()>(15, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'slot_get_stat'
        QtMocHelpers::SlotData<stat_data()>(16, 2, QMC::AccessPublic, 0x80000000 | 3),
        // Slot 'slot_set_p_serial'
        QtMocHelpers::SlotData<void(WK_Serial *)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 18, 19 },
        }}),
        // Slot 'slot_update_chargingStat'
        QtMocHelpers::SlotData<void(charging_stat)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 21, 22 },
        }}),
        // Slot 'slot_set_charging_type'
        QtMocHelpers::SlotData<void(CHARGING_TYPE, int)>(23, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 24, 25 }, { QMetaType::Int, 26 },
        }}),
        // Slot 'slot_clear_charging_type'
        QtMocHelpers::SlotData<void()>(27, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'elapsed_time'
        QtMocHelpers::PropertyData<QString>(28, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable, 1),
        // property 'remaining_time'
        QtMocHelpers::PropertyData<QString>(29, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable, 2),
        // property 'charging_speed'
        QtMocHelpers::PropertyData<QString>(30, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable, 3),
        // property 'charging_capacity'
        QtMocHelpers::PropertyData<QString>(31, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable, 4),
        // property 'charging_amount'
        QtMocHelpers::PropertyData<QString>(32, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable, 5),
        // property 'battery_start_persent'
        QtMocHelpers::PropertyData<QString>(33, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable, 6),
        // property 'battery_current'
        QtMocHelpers::PropertyData<QString>(34, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::Final, 7),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<StatStore, qt_meta_tag_ZN9StatStoreE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject StatStore::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9StatStoreE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9StatStoreE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN9StatStoreE_t>.metaTypes,
    nullptr
} };

void StatStore::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<StatStore *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->sig_Stat_changed((*reinterpret_cast< std::add_pointer_t<stat_data>>(_a[1]))); break;
        case 1: _t->sig_elapsed_time_change(); break;
        case 2: _t->sig_remaining_time_change(); break;
        case 3: _t->sig_charging_speed_change(); break;
        case 4: _t->sig_charging_capacity_change(); break;
        case 5: _t->sig_charging_amount_change(); break;
        case 6: _t->sig_battery_start_persent_change(); break;
        case 7: _t->sig_battery_current_change(); break;
        case 8: _t->slot_update_FromSoc((*reinterpret_cast< std::add_pointer_t<stat_data>>(_a[1]))); break;
        case 9: _t->slot_update_FromSerial((*reinterpret_cast< std::add_pointer_t<stat_data>>(_a[1]))); break;
        case 10: _t->slot_update_FromModule((*reinterpret_cast< std::add_pointer_t<stat_data>>(_a[1]))); break;
        case 11: _t->slot_update_current(); break;
        case 12: { stat_data _r = _t->slot_get_stat();
            if (_a[0]) *reinterpret_cast< stat_data*>(_a[0]) = std::move(_r); }  break;
        case 13: _t->slot_set_p_serial((*reinterpret_cast< std::add_pointer_t<WK_Serial*>>(_a[1]))); break;
        case 14: _t->slot_update_chargingStat((*reinterpret_cast< std::add_pointer_t<charging_stat>>(_a[1]))); break;
        case 15: _t->slot_set_charging_type((*reinterpret_cast< std::add_pointer_t<CHARGING_TYPE>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 16: _t->slot_clear_charging_type(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< stat_data >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< stat_data >(); break;
            }
            break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< stat_data >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< stat_data >(); break;
            }
            break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< charging_stat >(); break;
            }
            break;
        case 15:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< CHARGING_TYPE >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (StatStore::*)(stat_data )>(_a, &StatStore::sig_Stat_changed, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (StatStore::*)()>(_a, &StatStore::sig_elapsed_time_change, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (StatStore::*)()>(_a, &StatStore::sig_remaining_time_change, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (StatStore::*)()>(_a, &StatStore::sig_charging_speed_change, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (StatStore::*)()>(_a, &StatStore::sig_charging_capacity_change, 4))
            return;
        if (QtMocHelpers::indexOfMethod<void (StatStore::*)()>(_a, &StatStore::sig_charging_amount_change, 5))
            return;
        if (QtMocHelpers::indexOfMethod<void (StatStore::*)()>(_a, &StatStore::sig_battery_start_persent_change, 6))
            return;
        if (QtMocHelpers::indexOfMethod<void (StatStore::*)()>(_a, &StatStore::sig_battery_current_change, 7))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<QString*>(_v) = _t->get_elapsed_time(); break;
        case 1: *reinterpret_cast<QString*>(_v) = _t->get_remaining_time(); break;
        case 2: *reinterpret_cast<QString*>(_v) = _t->get_charging_speed(); break;
        case 3: *reinterpret_cast<QString*>(_v) = _t->get_charging_capacity(); break;
        case 4: *reinterpret_cast<QString*>(_v) = _t->get_charging_amount(); break;
        case 5: *reinterpret_cast<QString*>(_v) = _t->get_battery_start_persent(); break;
        case 6: *reinterpret_cast<QString*>(_v) = _t->get_battery_current(); break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->set_elapsed_time(*reinterpret_cast<QString*>(_v)); break;
        case 1: _t->set_remaining_time(*reinterpret_cast<QString*>(_v)); break;
        case 2: _t->set_charging_speed(*reinterpret_cast<QString*>(_v)); break;
        case 3: _t->set_charging_capacity(*reinterpret_cast<QString*>(_v)); break;
        case 4: _t->set_charging_amount(*reinterpret_cast<QString*>(_v)); break;
        case 5: _t->set_battery_start_persent(*reinterpret_cast<QString*>(_v)); break;
        case 6: _t->set_battery_current(*reinterpret_cast<QString*>(_v)); break;
        default: break;
        }
    }
}

const QMetaObject *StatStore::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StatStore::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9StatStoreE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int StatStore::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void StatStore::sig_Stat_changed(stat_data _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void StatStore::sig_elapsed_time_change()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void StatStore::sig_remaining_time_change()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void StatStore::sig_charging_speed_change()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void StatStore::sig_charging_capacity_change()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void StatStore::sig_charging_amount_change()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void StatStore::sig_battery_start_persent_change()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void StatStore::sig_battery_current_change()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
