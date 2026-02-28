/****************************************************************************
** Meta object code from reading C++ file 'WK_Soc.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Cpp_Module/WK_Soc.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WK_Soc.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN6WK_SocE_t {};
} // unnamed namespace

template <> constexpr inline auto WK_Soc::qt_create_metaobjectdata<qt_meta_tag_ZN6WK_SocE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "WK_Soc",
        "sig_update_md",
        "",
        "stat_data",
        "st_stat",
        "sig_chargingLog_To_DB",
        "db_data",
        "st_db_data",
        "sig_heartbitData_To_DB",
        "heartbit_data",
        "slot_Recv_TextData",
        "recvData",
        "slot_Disconnect_Soc",
        "slot_helloAck",
        "ret",
        "slot_registerReq",
        "jsObj",
        "slot_registerAck",
        "slot_registerReq_hmi",
        "slot_registerAck_hmi",
        "slot_chargingLog_authorized_ack_To_hmi",
        "uint64_t",
        "session_id",
        "slot_chargingLog_charging_start_ack_To_hmi",
        "uint32_t",
        "ocpp_tx_id",
        "slot_chargingLog_charging_finished_ack_To_hmi",
        "slot_membershipCard_authorized_ack_To_hmi",
        "ok",
        "msg",
        "slot_membershipCard_finished_ack_To_hmi"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'sig_update_md'
        QtMocHelpers::SignalData<void(stat_data)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Signal 'sig_chargingLog_To_DB'
        QtMocHelpers::SignalData<void(db_data)>(5, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 6, 7 },
        }}),
        // Signal 'sig_heartbitData_To_DB'
        QtMocHelpers::SignalData<void(heartbit_data)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 9, 7 },
        }}),
        // Slot 'slot_Recv_TextData'
        QtMocHelpers::SlotData<void(QString)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 11 },
        }}),
        // Slot 'slot_Disconnect_Soc'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'slot_helloAck'
        QtMocHelpers::SlotData<void(bool)>(13, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 14 },
        }}),
        // Slot 'slot_registerReq'
        QtMocHelpers::SlotData<bool(const QJsonObject &)>(15, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QJsonObject, 16 },
        }}),
        // Slot 'slot_registerAck'
        QtMocHelpers::SlotData<void(bool)>(17, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 14 },
        }}),
        // Slot 'slot_registerReq_hmi'
        QtMocHelpers::SlotData<bool(const QJsonObject &)>(18, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QJsonObject, 16 },
        }}),
        // Slot 'slot_registerAck_hmi'
        QtMocHelpers::SlotData<void(bool)>(19, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 14 },
        }}),
        // Slot 'slot_chargingLog_authorized_ack_To_hmi'
        QtMocHelpers::SlotData<void(uint64_t)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 21, 22 },
        }}),
        // Slot 'slot_chargingLog_charging_start_ack_To_hmi'
        QtMocHelpers::SlotData<void(uint32_t)>(23, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 24, 25 },
        }}),
        // Slot 'slot_chargingLog_charging_finished_ack_To_hmi'
        QtMocHelpers::SlotData<void()>(26, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'slot_membershipCard_authorized_ack_To_hmi'
        QtMocHelpers::SlotData<void(bool, QString)>(27, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 28 }, { QMetaType::QString, 29 },
        }}),
        // Slot 'slot_membershipCard_authorized_ack_To_hmi'
        QtMocHelpers::SlotData<void(bool)>(27, 2, QMC::AccessPublic | QMC::MethodCloned, QMetaType::Void, {{
            { QMetaType::Bool, 28 },
        }}),
        // Slot 'slot_membershipCard_finished_ack_To_hmi'
        QtMocHelpers::SlotData<void(bool)>(30, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 28 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<WK_Soc, qt_meta_tag_ZN6WK_SocE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject WK_Soc::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6WK_SocE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6WK_SocE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN6WK_SocE_t>.metaTypes,
    nullptr
} };

void WK_Soc::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<WK_Soc *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->sig_update_md((*reinterpret_cast< std::add_pointer_t<stat_data>>(_a[1]))); break;
        case 1: _t->sig_chargingLog_To_DB((*reinterpret_cast< std::add_pointer_t<db_data>>(_a[1]))); break;
        case 2: _t->sig_heartbitData_To_DB((*reinterpret_cast< std::add_pointer_t<heartbit_data>>(_a[1]))); break;
        case 3: _t->slot_Recv_TextData((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->slot_Disconnect_Soc(); break;
        case 5: _t->slot_helloAck((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 6: { bool _r = _t->slot_registerReq((*reinterpret_cast< std::add_pointer_t<QJsonObject>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->slot_registerAck((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 8: { bool _r = _t->slot_registerReq_hmi((*reinterpret_cast< std::add_pointer_t<QJsonObject>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->slot_registerAck_hmi((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 10: _t->slot_chargingLog_authorized_ack_To_hmi((*reinterpret_cast< std::add_pointer_t<uint64_t>>(_a[1]))); break;
        case 11: _t->slot_chargingLog_charging_start_ack_To_hmi((*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[1]))); break;
        case 12: _t->slot_chargingLog_charging_finished_ack_To_hmi(); break;
        case 13: _t->slot_membershipCard_authorized_ack_To_hmi((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 14: _t->slot_membershipCard_authorized_ack_To_hmi((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 15: _t->slot_membershipCard_finished_ack_To_hmi((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
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
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< heartbit_data >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (WK_Soc::*)(stat_data )>(_a, &WK_Soc::sig_update_md, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (WK_Soc::*)(db_data )>(_a, &WK_Soc::sig_chargingLog_To_DB, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (WK_Soc::*)(heartbit_data )>(_a, &WK_Soc::sig_heartbitData_To_DB, 2))
            return;
    }
}

const QMetaObject *WK_Soc::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WK_Soc::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6WK_SocE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WK_Soc::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void WK_Soc::sig_update_md(stat_data _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}

// SIGNAL 1
void WK_Soc::sig_chargingLog_To_DB(db_data _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 1, nullptr, _t1);
}

// SIGNAL 2
void WK_Soc::sig_heartbitData_To_DB(heartbit_data _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 2, nullptr, _t1);
}
QT_WARNING_POP
