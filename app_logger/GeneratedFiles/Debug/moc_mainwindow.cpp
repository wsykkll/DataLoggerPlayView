/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[22];
    char stringdata0[265];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 16), // "UpdateRecordList"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 3), // "str"
QT_MOC_LITERAL(4, 33, 6), // "record"
QT_MOC_LITERAL(5, 40, 12), // "SwitchRecord"
QT_MOC_LITERAL(6, 53, 18), // "OnTimerUpdateTable"
QT_MOC_LITERAL(7, 72, 13), // "OnStartRecord"
QT_MOC_LITERAL(8, 86, 12), // "OnStopRecord"
QT_MOC_LITERAL(9, 99, 13), // "OnLogFinished"
QT_MOC_LITERAL(10, 113, 11), // "OnSelectAll"
QT_MOC_LITERAL(11, 125, 14), // "OnInvertSelect"
QT_MOC_LITERAL(12, 140, 19), // "OnShowStatusMessage"
QT_MOC_LITERAL(13, 160, 3), // "msg"
QT_MOC_LITERAL(14, 164, 18), // "OnTableItemClicked"
QT_MOC_LITERAL(15, 183, 1), // "x"
QT_MOC_LITERAL(16, 185, 1), // "y"
QT_MOC_LITERAL(17, 187, 17), // "OnShowLogFileName"
QT_MOC_LITERAL(18, 205, 11), // "strFileName"
QT_MOC_LITERAL(19, 217, 20), // "OnUpdateRecordStatus"
QT_MOC_LITERAL(20, 238, 13), // "RECORD_STATUS"
QT_MOC_LITERAL(21, 252, 12) // "recordStatus"

    },
    "MainWindow\0UpdateRecordList\0\0str\0"
    "record\0SwitchRecord\0OnTimerUpdateTable\0"
    "OnStartRecord\0OnStopRecord\0OnLogFinished\0"
    "OnSelectAll\0OnInvertSelect\0"
    "OnShowStatusMessage\0msg\0OnTableItemClicked\0"
    "x\0y\0OnShowLogFileName\0strFileName\0"
    "OnUpdateRecordStatus\0RECORD_STATUS\0"
    "recordStatus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   74,    2, 0x06 /* Public */,
       5,    1,   79,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   82,    2, 0x0a /* Public */,
       7,    0,   83,    2, 0x0a /* Public */,
       8,    0,   84,    2, 0x0a /* Public */,
       9,    0,   85,    2, 0x0a /* Public */,
      10,    0,   86,    2, 0x0a /* Public */,
      11,    0,   87,    2, 0x0a /* Public */,
      12,    1,   88,    2, 0x0a /* Public */,
      14,    2,   91,    2, 0x0a /* Public */,
      17,    1,   96,    2, 0x0a /* Public */,
      19,    1,   99,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    3,    4,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   15,   16,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void, 0x80000000 | 20,   21,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->UpdateRecordList((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->SwitchRecord((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->OnTimerUpdateTable(); break;
        case 3: _t->OnStartRecord(); break;
        case 4: _t->OnStopRecord(); break;
        case 5: _t->OnLogFinished(); break;
        case 6: _t->OnSelectAll(); break;
        case 7: _t->OnInvertSelect(); break;
        case 8: _t->OnShowStatusMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->OnTableItemClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->OnShowLogFileName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->OnUpdateRecordStatus((*reinterpret_cast< RECORD_STATUS(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< RECORD_STATUS >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(QString , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::UpdateRecordList)) {
                *result = 0;
            }
        }
        {
            typedef void (MainWindow::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::SwitchRecord)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::UpdateRecordList(QString _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::SwitchRecord(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
