/****************************************************************************
** Meta object code from reading C++ file 'cplayerthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../cplayerthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cplayerthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CPlayerThread_t {
    QByteArrayData data[14];
    char stringdata0[172];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CPlayerThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CPlayerThread_t qt_meta_stringdata_CPlayerThread = {
    {
QT_MOC_LITERAL(0, 0, 13), // "CPlayerThread"
QT_MOC_LITERAL(1, 14, 17), // "ShowStatusMessage"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 3), // "str"
QT_MOC_LITERAL(4, 37, 22), // "UpdateCurrentTimeStamp"
QT_MOC_LITERAL(5, 60, 13), // "long long int"
QT_MOC_LITERAL(6, 74, 9), // "timestamp"
QT_MOC_LITERAL(7, 84, 14), // "UpdateTableRow"
QT_MOC_LITERAL(8, 99, 5), // "index"
QT_MOC_LITERAL(9, 105, 12), // "CHANNEL_INFO"
QT_MOC_LITERAL(10, 118, 7), // "channel"
QT_MOC_LITERAL(11, 126, 10), // "OnUpdateUI"
QT_MOC_LITERAL(12, 137, 24), // "OnUpdateChannelBroadCast"
QT_MOC_LITERAL(13, 162, 9) // "broadcast"

    },
    "CPlayerThread\0ShowStatusMessage\0\0str\0"
    "UpdateCurrentTimeStamp\0long long int\0"
    "timestamp\0UpdateTableRow\0index\0"
    "CHANNEL_INFO\0channel\0OnUpdateUI\0"
    "OnUpdateChannelBroadCast\0broadcast"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CPlayerThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,
       7,    2,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   50,    2, 0x0a /* Public */,
      12,    2,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 9,    8,   10,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool,    8,   13,

       0        // eod
};

void CPlayerThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CPlayerThread *_t = static_cast<CPlayerThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ShowStatusMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->UpdateCurrentTimeStamp((*reinterpret_cast< long long int(*)>(_a[1]))); break;
        case 2: _t->UpdateTableRow((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< CHANNEL_INFO(*)>(_a[2]))); break;
        case 3: _t->OnUpdateUI(); break;
        case 4: _t->OnUpdateChannelBroadCast((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< CHANNEL_INFO >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CPlayerThread::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CPlayerThread::ShowStatusMessage)) {
                *result = 0;
            }
        }
        {
            typedef void (CPlayerThread::*_t)(long long int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CPlayerThread::UpdateCurrentTimeStamp)) {
                *result = 1;
            }
        }
        {
            typedef void (CPlayerThread::*_t)(int , CHANNEL_INFO );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CPlayerThread::UpdateTableRow)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject CPlayerThread::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CPlayerThread.data,
      qt_meta_data_CPlayerThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CPlayerThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CPlayerThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CPlayerThread.stringdata0))
        return static_cast<void*>(const_cast< CPlayerThread*>(this));
    return QObject::qt_metacast(_clname);
}

int CPlayerThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void CPlayerThread::ShowStatusMessage(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CPlayerThread::UpdateCurrentTimeStamp(long long int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CPlayerThread::UpdateTableRow(int _t1, CHANNEL_INFO _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
