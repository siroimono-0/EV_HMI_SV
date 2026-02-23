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
        "slot_stop",
        "slot_Connect_Sv",
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
        "qba"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'sig_end'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'slot_stop'
        QtMocHelpers::SlotData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'slot_Connect_Sv'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'slot_ID_Check'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'slot_ID_Resert'
        QtMocHelpers::SlotData<void(bool)>(6, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Bool, 7 },
        }}),
        // Slot 'slot_SocErr'
        QtMocHelpers::SlotData<void(QAbstractSocket::SocketError)>(8, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 9, 10 },
        }}),
        // Slot 'slot_send_db_update_textData'
        QtMocHelpers::SlotData<void(db_data)>(11, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 12, 13 },
        }}),
        // Slot 'slot_Recv_TextData'
        QtMocHelpers::SlotData<void(QString)>(14, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QString, 15 },
        }}),
        // Slot 'slot_netAccess_reply'
        QtMocHelpers::SlotData<void(QNetworkReply *)>(16, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 17, 18 },
        }}),
        // Slot 'slot_netAccess_post'
        QtMocHelpers::SlotData<void(QByteArray)>(19, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::QByteArray, 20 },
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
        case 1: _t->slot_stop(); break;
        case 2: _t->slot_Connect_Sv(); break;
        case 3: _t->slot_ID_Check(); break;
        case 4: _t->slot_ID_Resert((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 5: _t->slot_SocErr((*reinterpret_cast< std::add_pointer_t<QAbstractSocket::SocketError>>(_a[1]))); break;
        case 6: _t->slot_send_db_update_textData((*reinterpret_cast< std::add_pointer_t<db_data>>(_a[1]))); break;
        case 7: _t->slot_Recv_TextData((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 8: _t->slot_netAccess_reply((*reinterpret_cast< std::add_pointer_t<QNetworkReply*>>(_a[1]))); break;
        case 9: _t->slot_netAccess_post((*reinterpret_cast< std::add_pointer_t<QByteArray>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QAbstractSocket::SocketError >(); break;
            }
            break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QNetworkReply* >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (WK_WebSocket::*)()>(_a, &WK_WebSocket::sig_end, 0))
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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void WK_WebSocket::sig_end()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
