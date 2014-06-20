/****************************************************************************
** Meta object code from reading C++ file 'read_sys.h'
**
** Created: Thu Jun 19 10:14:50 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "read_sys.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'read_sys.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_read_sys[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      22,    9,    9,    9, 0x05,
      41,   36,    9,    9, 0x05,
      64,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
      81,    9,    9,    9, 0x08,
      96,    9,    9,    9, 0x08,
     106,    9,    9,    9, 0x08,
     124,    9,    9,    9, 0x08,
     143,    9,    9,    9, 0x08,
     158,    9,    9,    9, 0x08,
     175,    9,    9,    9, 0x08,
     188,    9,    9,    9, 0x08,
     206,    9,    9,    9, 0x08,
     225,    9,    9,    9, 0x08,
     241,    9,    9,    9, 0x08,
     270,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_read_sys[] = {
    "read_sys\0\0config_ok()\0log_out_sig()\0"
    "flag\0show_hide_button(bool)\0"
    "read_config_ok()\0is_logout_ok()\0"
    "log_out()\0deal_update_app()\0"
    "check_update_app()\0random_delay()\0"
    "down_load_file()\0info_flash()\0"
    "closing_machine()\0openning_machine()\0"
    "reset_machine()\0initial_part_global_config()\0"
    "initial_all_par()\0"
};

const QMetaObject read_sys::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_read_sys,
      qt_meta_data_read_sys, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &read_sys::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *read_sys::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *read_sys::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_read_sys))
        return static_cast<void*>(const_cast< read_sys*>(this));
    return QObject::qt_metacast(_clname);
}

int read_sys::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: config_ok(); break;
        case 1: log_out_sig(); break;
        case 2: show_hide_button((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: read_config_ok(); break;
        case 4: is_logout_ok(); break;
        case 5: log_out(); break;
        case 6: deal_update_app(); break;
        case 7: check_update_app(); break;
        case 8: random_delay(); break;
        case 9: down_load_file(); break;
        case 10: info_flash(); break;
        case 11: closing_machine(); break;
        case 12: openning_machine(); break;
        case 13: reset_machine(); break;
        case 14: initial_part_global_config(); break;
        case 15: initial_all_par(); break;
        default: ;
        }
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void read_sys::config_ok()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void read_sys::log_out_sig()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void read_sys::show_hide_button(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void read_sys::read_config_ok()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}
QT_END_MOC_NAMESPACE
