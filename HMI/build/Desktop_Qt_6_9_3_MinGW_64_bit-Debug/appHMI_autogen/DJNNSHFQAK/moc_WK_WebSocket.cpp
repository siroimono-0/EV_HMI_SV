/****************************************************************************
** Meta object code from reading C++ file 'WK_WebSocket.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Cpp_Module/WK_WebSocket.h"
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WK_WebSocket.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN12WK_WebSocketE_t {};
} // unnamed namespace

template <> constexpr inline auto WK_WebSocket::qt_create_metaobjectdata<qt_meta_tag_ZN12WK_WebSocketE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "WK_WebSocket",
        "sig_end",
        "",
        "sig_heartbit_ping_To_statStore",
        "slot_stop",
        "slot_Connect_Sv",
        "slot_set_p_serial",
        "WK_Serial*",
        "set",
        "slot_ID_Check",
        "slot_ID_Resert",
        "resert",
        "slot_SocErr",
        "QAbstractSocket::SocketError",
        "error",
        "slot_send_db_update_textData",
        "db_data",
        "st_db_data",
        "slot_Recv_TextData",
        "recvData",
        "slot_netAccess_reply",
        "QNetworkReply*",
        "reply",
        "slot_netAccess_post",
        "qba",
        "slot_timeOut_pay_ack",
        "slot_netAccess_post_cancle",
        "card_uid",
        "slot_timeOut_cancle_ack",
        "slot_send_membership_authorized_textData",
        "adv_pay",
        "hmi_id",
        "slot_timeOut_membership_authorized_ack",
        "slot_send_membership_finished_textData",
        "act_pay",
        "can_pay",
        "uint32_t",
        "t_id",
        "request_id",
        "slot_timeOut_membership_finished_ack",
        "slot_send_heartbit_pong",
        "heartbit_data",
        "st_hb_data",
        "slot_update_ad",
        "name"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'sig_end'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'sig_heartbit_ping_To_statStore'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'slot_stop'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'slot_Connect_Sv'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'slot_set_p_serial'
        QtMocHelpers::SlotData<void(WK_Serial *)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 7, 8 },
        }}),
        // Slot 'slot_ID_Check'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'slot_ID_Resert'
        QtMocHelpers::SlotData<void(bool)>(10, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 11 },
        }}),
        // Slot 'slot_SocErr'
        QtMocHelpers::SlotData<void(QAbstractSocket::SocketError)>(12, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 13, 14 },
        }}),
        // Slot 'slot_send_db_update_textData'
        QtMocHelpers::SlotData<void(db_data)>(15, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 16, 17 },
        }}),
        // Slot 'slot_Recv_TextData'
        QtMocHelpers::SlotData<void(QString)>(18, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 19 },
        }}),
        // Slot 'slot_netAccess_reply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(20, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 21, 22 },
        }}),
        // Slot 'slot_netAccess_post'
        QtMocHelpers::SlotData<void(QByteArray)>(23, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QByteArray, 24 },
        }}),
        // Slot 'slot_timeOut_pay_ack'
        QtMocHelpers::SlotData<void()>(25, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'slot_netAccess_post_cancle'
        QtMocHelpers::SlotData<void(QString)>(26, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 27 },
        }}),
        // Slot 'slot_timeOut_cancle_ack'
        QtMocHelpers::SlotData<void()>(28, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'slot_send_membership_authorized_textData'
        QtMocHelpers::SlotData<void(int, QByteArray, QString)>(29, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 30 }, { QMetaType::QByteArray, 27 }, { QMetaType::QString, 31 },
        }}),
        // Slot 'slot_timeOut_membership_authorized_ack'
        QtMocHelpers::SlotData<void()>(32, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'slot_send_membership_finished_textData'
        QtMocHelpers::SlotData<void(int, int, int, QString, uint32_t, QString)>(33, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 30 }, { QMetaType::Int, 34 }, { QMetaType::Int, 35 }, { QMetaType::QString, 27 },
            { 0x80000000 | 36, 37 }, { QMetaType::QString, 38 },
        }}),
        // Slot 'slot_timeOut_membership_finished_ack'
        QtMocHelpers::SlotData<void()>(39, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'slot_send_heartbit_pong'
        QtMocHelpers::SlotData<void(heartbit_data)>(40, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 41, 42 },
        }}),
        // Slot 'slot_update_ad'
        QtMocHelpers::SlotData<void(const QString)>(43, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 44 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<WK_WebSocket, qt_meta_tag_ZN12WK_WebSocketE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject WK_WebSocket::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12WK_WebSocketE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12WK_WebSocketE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN12WK_WebSocketE_t>.metaTypes,
    nullptr
} };

void WK_WebSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<WK_WebSocket *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->sig_end(); break;
        case 1: _t->sig_heartbit_ping_To_statStore(); break;
        case 2: _t->slot_stop(); break;
        case 3: _t->slot_Connect_Sv(); break;
        case 4: _t->slot_set_p_serial((*reinterpret_cast< std::add_pointer_t<WK_Serial*>>(_a[1]))); break;
        case 5: _t->slot_ID_Check(); break;
        case 6: _t->slot_ID_Resert((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 7: _t->slot_SocErr((*reinterpret_cast< std::add_pointer_t<QAbstractSocket::SocketError>>(_a[1]))); break;
        case 8: _t->slot_send_db_update_textData((*reinterpret_cast< std::add_pointer_t<db_data>>(_a[1]))); break;
        case 9: _t->slot_Recv_TextData((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 10: _t->slot_netAccess_reply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 11: _t->slot_netAccess_post((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        case 12: _t->slot_timeOut_pay_ack(); break;
        case 13: _t->slot_netAccess_post_cancle((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 14: _t->slot_timeOut_cancle_ack(); break;
        case 15: _t->slot_send_membership_authorized_textData((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[3]))); break;
        case 16: _t->slot_timeOut_membership_authorized_ack(); break;
        case 17: _t->slot_send_membership_finished_textData((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<uint32_t>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[6]))); break;
        case 18: _t->slot_timeOut_membership_finished_ack(); break;
        case 19: _t->slot_send_heartbit_pong((*reinterpret_cast< std::add_pointer_t<heartbit_data>>(_a[1]))); break;
        case 20: _t->slot_update_ad((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketError >(); break;
            }
            break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QNetworkReply* >(); break;
            }
            break;
        case 19:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< heartbit_data >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (WK_WebSocket::*)()>(_a, &WK_WebSocket::sig_end, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (WK_WebSocket::*)()>(_a, &WK_WebSocket::sig_heartbit_ping_To_statStore, 1))
            return;
    }
}

const QMetaObject *WK_WebSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WK_WebSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN12WK_WebSocketE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WK_WebSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 21)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 21;
    }
    return _id;
}

// SIGNAL 0
void WK_WebSocket::sig_end()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void WK_WebSocket::sig_heartbit_ping_To_statStore()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
