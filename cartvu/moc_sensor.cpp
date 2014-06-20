/****************************************************************************
** Meta object code from reading C++ file 'sensor.h'
**
** Created: Thu Jun 19 10:14:56 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "sensor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sensor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_sensor_c[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   10,    9,    9, 0x05,
      43,    9,    9,    9, 0x05,
      60,    9,    9,    9, 0x05,
      77,    9,    9,    9, 0x05,
      91,    9,    9,    9, 0x05,
     115,    9,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
     131,    9,    9,    9, 0x08,
     146,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_sensor_c[] = {
    "sensor_c\0\0sensor\0show_led(sensor_all_att*)\0"
    "take_alarm_pic()\0last_alarm_pic()\0"
    "start_alarm()\0return_to_serial_mode()\0"
    "image_time_ok()\0switch_to_E2()\0"
    "set_alarm_interval_ture()\0"
};

const QMetaObject sensor_c::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_sensor_c,
      qt_meta_data_sensor_c, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &sensor_c::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *sensor_c::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *sensor_c::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_sensor_c))
        return static_cast<void*>(const_cast< sensor_c*>(this));
    return QThread::qt_metacast(_clname);
}

int sensor_c::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: show_led((*reinterpret_cast< sensor_all_att*(*)>(_a[1]))); break;
        case 1: take_alarm_pic(); break;
        case 2: last_alarm_pic(); break;
        case 3: start_alarm(); break;
        case 4: return_to_serial_mode(); break;
        case 5: image_time_ok(); break;
        case 6: switch_to_E2(); break;
        case 7: set_alarm_interval_ture(); break;
        default: ;
        }
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void sensor_c::show_led(sensor_all_att * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void sensor_c::take_alarm_pic()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void sensor_c::last_alarm_pic()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void sensor_c::start_alarm()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void sensor_c::return_to_serial_mode()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}

// SIGNAL 5
void sensor_c::image_time_ok()
{
    QMetaObject::activate(this, &staticMetaObject, 5, 0);
}
QT_END_MOC_NAMESPACE
