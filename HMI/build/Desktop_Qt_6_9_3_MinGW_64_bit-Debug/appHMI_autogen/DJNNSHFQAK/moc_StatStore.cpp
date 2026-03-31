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
        "sig_stat_db_update",
        "",
        "db_data",
        "st_db_data",
        "sig_elapsed_time_change",
        "sig_remaining_time_change",
        "sig_charging_speed_change",
        "sig_charging_capacity_change",
        "sig_charging_amount_change",
        "sig_battery_start_persent_change",
        "sig_battery_current_change",
        "sig_advance_payment_change",
        "sig_actual_payment_change",
        "sig_cancle_payment_change",
        "sig_charge_price_kWh",
        "sig_heartbit_pong",
        "heartbit_data",
        "st_hb_data",
        "slot_get_store_id",
        "slot_get_mac_addr",
        "slot_get_advPay_hmiId",
        "std::pair<int,QString>",
        "slot_set_p_serial",
        "WK_Serial*",
        "serial",
        "slot_get_i_adv_pay",
        "slot_update_chargingStat",
        "charging_stat",
        "c_stat",
        "slot_set_charging_type",
        "CHARGING_TYPE",
        "charging_type",
        "val",
        "slot_clear_charging_type",
        "slot_set_payment",
        "slot_set_card_uid",
        "set",
        "slot_set_charging_start_time",
        "slot_charging_end_stat_clear",
        "slot_card_ok_db_update",
        "slot_set_session_id",
        "uint64_t",
        "slot_set_ocpp_tx_id",
        "uint32_t",
        "slot_heartbit_ping",
        "slot_set_membership_t_id",
        "elapsed_time",
        "remaining_time",
        "charging_speed",
        "charging_capacity",
        "charging_amount",
        "battery_start_persent",
        "battery_current",
        "advance_payment",
        "actual_payment",
        "cancle_payment",
        "charge_price_kWh"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'sig_stat_db_update'
        QtMocHelpers::SignalData<void(db_data)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
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
        // Signal 'sig_advance_payment_change'
        QtMocHelpers::SignalData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sig_actual_payment_change'
        QtMocHelpers::SignalData<void()>(13, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sig_cancle_payment_change'
        QtMocHelpers::SignalData<void()>(14, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sig_charge_price_kWh'
        QtMocHelpers::SignalData<void()>(15, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sig_heartbit_pong'
        QtMocHelpers::SignalData<void(heartbit_data)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 17, 18 },
        }}),
        // Slot 'slot_get_store_id'
        QtMocHelpers::SlotData<int()>(19, 2, QMC::AccessPublic, QMetaType::Int),
        // Slot 'slot_get_mac_addr'
        QtMocHelpers::SlotData<QString()>(20, 2, QMC::AccessPublic, QMetaType::QString),
        // Slot 'slot_get_advPay_hmiId'
        QtMocHelpers::SlotData<QPair<int,QString>()>(21, 2, QMC::AccessPublic, 0x80000000 | 22),
        // Slot 'slot_set_p_serial'
        QtMocHelpers::SlotData<void(WK_Serial *)>(23, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 24, 25 },
        }}),
        // Slot 'slot_get_i_adv_pay'
        QtMocHelpers::SlotData<int()>(26, 2, QMC::AccessPublic, QMetaType::Int),
        // Slot 'slot_update_chargingStat'
        QtMocHelpers::SlotData<void(charging_stat)>(27, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 28, 29 },
        }}),
        // Slot 'slot_set_charging_type'
        QtMocHelpers::SlotData<void(CHARGING_TYPE, int)>(30, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 31, 32 }, { QMetaType::Int, 33 },
        }}),
        // Slot 'slot_clear_charging_type'
        QtMocHelpers::SlotData<void()>(34, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'slot_set_payment'
        QtMocHelpers::SlotData<void()>(35, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'slot_set_card_uid'
        QtMocHelpers::SlotData<void(QString)>(36, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 37 },
        }}),
        // Slot 'slot_set_charging_start_time'
        QtMocHelpers::SlotData<void()>(38, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'slot_charging_end_stat_clear'
        QtMocHelpers::SlotData<void()>(39, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'slot_card_ok_db_update'
        QtMocHelpers::SlotData<void()>(40, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'slot_set_session_id'
        QtMocHelpers::SlotData<void(uint64_t)>(41, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 42, 37 },
        }}),
        // Slot 'slot_set_ocpp_tx_id'
        QtMocHelpers::SlotData<void(uint32_t)>(43, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 44, 37 },
        }}),
        // Slot 'slot_heartbit_ping'
        QtMocHelpers::SlotData<void()>(45, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'slot_set_membership_t_id'
        QtMocHelpers::SlotData<void(uint32_t)>(46, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 44, 37 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'elapsed_time'
        QtMocHelpers::PropertyData<QString>(47, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable, 1),
        // property 'remaining_time'
        QtMocHelpers::PropertyData<QString>(48, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable, 2),
        // property 'charging_speed'
        QtMocHelpers::PropertyData<QString>(49, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable, 3),
        // property 'charging_capacity'
        QtMocHelpers::PropertyData<QString>(50, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable, 4),
        // property 'charging_amount'
        QtMocHelpers::PropertyData<QString>(51, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable, 5),
        // property 'battery_start_persent'
        QtMocHelpers::PropertyData<QString>(52, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable, 6),
        // property 'battery_current'
        QtMocHelpers::PropertyData<QString>(53, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::Final, 7),
        // property 'advance_payment'
        QtMocHelpers::PropertyData<QString>(54, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::Final, 8),
        // property 'actual_payment'
        QtMocHelpers::PropertyData<QString>(55, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::Final, 9),
        // property 'cancle_payment'
        QtMocHelpers::PropertyData<QString>(56, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable | QMC::Final, 10),
        // property 'charge_price_kWh'
        QtMocHelpers::PropertyData<int>(57, QMetaType::Int, QMC::DefaultPropertyFlags | QMC::Writable | QMC::Final, 11),
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
        case 0: _t->sig_stat_db_update((*reinterpret_cast< std::add_pointer_t<db_data>>(_a[1]))); break;
        case 1: _t->sig_elapsed_time_change(); break;
        case 2: _t->sig_remaining_time_change(); break;
        case 3: _t->sig_charging_speed_change(); break;
        case 4: _t->sig_charging_capacity_change(); break;
        case 5: _t->sig_charging_amount_change(); break;
        case 6: _t->sig_battery_start_persent_change(); break;
        case 7: _t->sig_battery_current_change(); break;
        case 8: _t->sig_advance_payment_change(); break;
        case 9: _t->sig_actual_payment_change(); break;
        case 10: _t->sig_cancle_payment_change(); break;
        case 11: _t->sig_charge_price_kWh(); break;
        case 12: _t->sig_heartbit_pong((*reinterpret_cast< std::add_pointer_t<heartbit_data>>(_a[1]))); break;
        case 13: { int _r = _t->slot_get_store_id();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 14: { QString _r = _t->slot_get_mac_addr();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 15: { std::pair<int,QString> _r = _t->slot_get_advPay_hmiId();
            if (_a[0]) *reinterpret_cast< std::pair<int,QString>*>(_a[0]) = std::move(_r); }  break;
        case 16: _t->slot_set_p_serial((*reinterpret_cast< std::add_pointer_t<WK_Serial*>>(_a[1]))); break;
        case 17: { int _r = _t->slot_get_i_adv_pay();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 18: _t->slot_update_chargingStat((*reinterpret_cast< std::add_pointer_t<charging_stat>>(_a[1]))); break;
        case 19: _t->slot_set_charging_type((*reinterpret_cast< std::add_pointer_t<CHARGING_TYPE>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 20: _t->slot_clear_charging_type(); break;
        case 21: _t->slot_set_payment(); break;
        case 22: _t->slot_set_card_uid((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 23: _t->slot_set_charging_start_time(); break;
        case 24: _t->slot_charging_end_stat_clear(); break;
        case 25: _t->slot_card_ok_db_update(); break;
        case 26: _t->slot_set_session_id((*reinterpret_cast< std::add_pointer_t<uint64_t>>(_a[1]))); break;
        case 27: _t->slot_set_ocpp_tx_id((*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[1]))); break;
        case 28: _t->slot_heartbit_ping(); break;
        case 29: _t->slot_set_membership_t_id((*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< heartbit_data >(); break;
            }
            break;
        case 18:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< charging_stat >(); break;
            }
            break;
        case 19:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< CHARGING_TYPE >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (StatStore::*)(db_data )>(_a, &StatStore::sig_stat_db_update, 0))
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
        if (QtMocHelpers::indexOfMethod<void (StatStore::*)()>(_a, &StatStore::sig_advance_payment_change, 8))
            return;
        if (QtMocHelpers::indexOfMethod<void (StatStore::*)()>(_a, &StatStore::sig_actual_payment_change, 9))
            return;
        if (QtMocHelpers::indexOfMethod<void (StatStore::*)()>(_a, &StatStore::sig_cancle_payment_change, 10))
            return;
        if (QtMocHelpers::indexOfMethod<void (StatStore::*)()>(_a, &StatStore::sig_charge_price_kWh, 11))
            return;
        if (QtMocHelpers::indexOfMethod<void (StatStore::*)(heartbit_data )>(_a, &StatStore::sig_heartbit_pong, 12))
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
        case 7: *reinterpret_cast<QString*>(_v) = _t->get_advance_payment(); break;
        case 8: *reinterpret_cast<QString*>(_v) = _t->get_actual_payment(); break;
        case 9: *reinterpret_cast<QString*>(_v) = _t->get_cancle_payment(); break;
        case 10: *reinterpret_cast<int*>(_v) = _t->get_charge_price_kWh(); break;
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
        case 7: _t->set_advance_payment(*reinterpret_cast<QString*>(_v)); break;
        case 8: _t->set_actual_payment(*reinterpret_cast<QString*>(_v)); break;
        case 9: _t->set_cancle_payment(*reinterpret_cast<QString*>(_v)); break;
        case 10: _t->set_charge_price_kWh(*reinterpret_cast<int*>(_v)); break;
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
        if (_id < 30)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 30;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 30)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 30;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void StatStore::sig_stat_db_update(db_data _t1)
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

// SIGNAL 8
void StatStore::sig_advance_payment_change()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void StatStore::sig_actual_payment_change()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void StatStore::sig_cancle_payment_change()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}

// SIGNAL 11
void StatStore::sig_charge_price_kWh()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void StatStore::sig_heartbit_pong(heartbit_data _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 12, nullptr, _t1);
}
QT_WARNING_POP
