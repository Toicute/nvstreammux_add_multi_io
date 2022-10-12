/****************************************************************************
** Meta object code from reading C++ file 'mqqt.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mqqt.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mqqt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_mqqt_t {
    QByteArrayData data[9];
    char stringdata0[87];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mqqt_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mqqt_t qt_meta_stringdata_mqqt = {
    {
QT_MOC_LITERAL(0, 0, 4), // "mqqt"
QT_MOC_LITERAL(1, 5, 9), // "AddStream"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 6), // "source"
QT_MOC_LITERAL(4, 23, 12), // "RemoveStream"
QT_MOC_LITERAL(5, 36, 15), // "OnConnectBroker"
QT_MOC_LITERAL(6, 52, 17), // "OnMessageReceived"
QT_MOC_LITERAL(7, 70, 12), // "QMqttMessage"
QT_MOC_LITERAL(8, 83, 3) // "msg"

    },
    "mqqt\0AddStream\0\0source\0RemoveStream\0"
    "OnConnectBroker\0OnMessageReceived\0"
    "QMqttMessage\0msg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mqqt[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   40,    2, 0x0a /* Public */,
       6,    1,   41,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void mqqt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<mqqt *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->AddStream((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->RemoveStream((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->OnConnectBroker(); break;
        case 3: _t->OnMessageReceived((*reinterpret_cast< QMqttMessage(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QMqttMessage >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (mqqt::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&mqqt::AddStream)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (mqqt::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&mqqt::RemoveStream)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject mqqt::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_mqqt.data,
    qt_meta_data_mqqt,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *mqqt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mqqt::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_mqqt.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int mqqt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void mqqt::AddStream(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void mqqt::RemoveStream(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
