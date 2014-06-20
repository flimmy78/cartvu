/****************************************************************************
** Meta object code from reading C++ file 'client.h'
**
** Created: Fri Jun 13 18:10:52 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "client.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_client[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x05,
      23,    7,    7,    7, 0x05,

 // slots: signature, parameters, type, tag, flags
      34,    7,    7,    7, 0x08,
      46,    7,    7,    7, 0x08,
      57,    7,    7,    7, 0x08,
     101,    7,    7,    7, 0x08,
     150,    7,    7,    7, 0x08,
     176,    7,    7,    7, 0x08,
     207,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_client[] = {
    "client\0\0emit_receive()\0now_sate()\0"
    "cmd_write()\0rec_data()\0"
    "display_error(QAbstractSocket::SocketError)\0"
    "test_display_error(QAbstractSocket::SocketError)\0"
    "connect_to_host_timeout()\0"
    "test_connect_to_host_timeout()\0"
    "emit_connect_state()\0"
};

const QMetaObject client::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_client,
      qt_meta_data_client, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &client::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *client::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_client))
        return static_cast<void*>(const_cast< client*>(this));
    return QObject::qt_metacast(_clname);
}

int client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: emit_receive(); break;
        case 1: now_sate(); break;
        case 2: cmd_write(); break;
        case 3: rec_data(); break;
        case 4: display_error((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 5: test_display_error((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 6: connect_to_host_timeout(); break;
        case 7: test_connect_to_host_timeout(); break;
        case 8: emit_connect_state(); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void client::emit_receive()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void client::now_sate()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
