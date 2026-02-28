/****************************************************************************
** Meta object code from reading C++ file 'DB_PostgreSQL.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Cpp_Module/DB_PostgreSQL.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DB_PostgreSQL.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN13DB_PostgreSQLE_t {};
} // unnamed namespace

template <> constexpr inline auto DB_PostgreSQL::qt_create_metaobjectdata<qt_meta_tag_ZN13DB_PostgreSQLE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "DB_PostgreSQL",
        "sig_end",
        "",
        "slot_end",
        "slot_set_p_soc",
        "WK_Soc*",
        "soc",
        "slot_createStore",
        "id",
        "name",
        "location",
        "slot_query_register",
        "slot_query_register_hmi",
        "storeId",
        "hmiId",
        "slot_query_find_hello_hmi",
        "slot_chargingLog_From_soc",
        "db_data",
        "st_db_data",
        "slot_heartbitData_From_soc",
        "heartbit_data",
        "st_hb_data",
        "slot_membershipCard_authorized_From_soc",
        "adv_pay",
        "card_uid",
        "request_id",
        "slot_membershipCard_finished_From_soc",
        "act_pay",
        "can_pay",
        "uint32_t",
        "t_id"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'sig_end'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'slot_end'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'slot_set_p_soc'
        QtMocHelpers::SlotData<void(WK_Soc *)>(4, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 5, 6 },
        }}),
        // Slot 'slot_createStore'
        QtMocHelpers::SlotData<bool(int, QString, QString)>(7, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::Int, 8 }, { QMetaType::QString, 9 }, { QMetaType::QString, 10 },
        }}),
        // Slot 'slot_query_register'
        QtMocHelpers::SlotData<bool(const QString, const QString, const QString)>(11, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 8 }, { QMetaType::QString, 9 }, { QMetaType::QString, 10 },
        }}),
        // Slot 'slot_query_register_hmi'
        QtMocHelpers::SlotData<bool(const QString, const QString)>(12, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 13 }, { QMetaType::QString, 14 },
        }}),
        // Slot 'slot_query_find_hello_hmi'
        QtMocHelpers::SlotData<bool(const QString, const QString)>(15, 2, QMC::AccessPublic, QMetaType::Bool, {{
            { QMetaType::QString, 13 }, { QMetaType::QString, 14 },
        }}),
        // Slot 'slot_chargingLog_From_soc'
        QtMocHelpers::SlotData<void(db_data)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 17, 18 },
        }}),
        // Slot 'slot_heartbitData_From_soc'
        QtMocHelpers::SlotData<void(heartbit_data)>(19, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 20, 21 },
        }}),
        // Slot 'slot_membershipCard_authorized_From_soc'
        QtMocHelpers::SlotData<void(int, QString, QString)>(22, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 23 }, { QMetaType::QString, 24 }, { QMetaType::QString, 25 },
        }}),
        // Slot 'slot_membershipCard_finished_From_soc'
        QtMocHelpers::SlotData<void(int, int, int, QString, uint32_t)>(26, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 23 }, { QMetaType::Int, 27 }, { QMetaType::Int, 28 }, { QMetaType::QString, 24 },
            { 0x80000000 | 29, 30 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<DB_PostgreSQL, qt_meta_tag_ZN13DB_PostgreSQLE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject DB_PostgreSQL::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13DB_PostgreSQLE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13DB_PostgreSQLE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN13DB_PostgreSQLE_t>.metaTypes,
    nullptr
} };

void DB_PostgreSQL::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<DB_PostgreSQL *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->sig_end(); break;
        case 1: _t->slot_end(); break;
        case 2: _t->slot_set_p_soc((*reinterpret_cast< std::add_pointer_t<WK_Soc*>>(_a[1]))); break;
        case 3: { bool _r = _t->slot_createStore((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 4: { bool _r = _t->slot_query_register((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: { bool _r = _t->slot_query_register_hmi((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: { bool _r = _t->slot_query_find_hello_hmi((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->slot_chargingLog_From_soc((*reinterpret_cast< std::add_pointer_t<db_data>>(_a[1]))); break;
        case 8: _t->slot_heartbitData_From_soc((*reinterpret_cast< std::add_pointer_t<heartbit_data>>(_a[1]))); break;
        case 9: _t->slot_membershipCard_authorized_From_soc((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 10: _t->slot_membershipCard_finished_From_soc((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[5]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< heartbit_data >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (DB_PostgreSQL::*)()>(_a, &DB_PostgreSQL::sig_end, 0))
            return;
    }
}

const QMetaObject *DB_PostgreSQL::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DB_PostgreSQL::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN13DB_PostgreSQLE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DB_PostgreSQL::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void DB_PostgreSQL::sig_end()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
