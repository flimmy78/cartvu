/****************************************************************************
** Meta object code from reading C++ file 'serialMode.h'
**
** Created: Thu Jun 19 10:14:58 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "serialMode.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serialMode.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_serialMode[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      27,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,
      27,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      39,   11,   11,   11, 0x0a,
      66,   11,   11,   11, 0x08,
      91,   11,   11,   11, 0x08,
     116,   11,   11,   11, 0x08,
     142,   11,   11,   11, 0x08,
     170,   11,   11,   11, 0x08,
     199,   11,   11,   11, 0x08,
     228,   11,   11,   11, 0x08,
     255,   11,   11,   11, 0x08,
     281,   11,   11,   11, 0x08,
     309,   11,   11,   11, 0x08,
     336,   11,   11,   11, 0x08,
     362,   11,   11,   11, 0x08,
     387,   11,   11,   11, 0x08,
     413,   11,   11,   11, 0x08,
     438,   11,   11,   11, 0x08,
     456,   11,   11,   11, 0x08,
     474,   11,   11,   11, 0x08,
     486,   11,   11,   11, 0x08,
     521,   11,   11,   11, 0x08,
     548,  546,   11,   11, 0x08,
     591,   11,   11,   11, 0x08,
     608,   11,   11,   11, 0x08,
     633,  628,   11,   11, 0x08,
     659,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_serialMode[] = {
    "serialMode\0\0sig_take_pic()\0record_ok()\0"
    "on_logout_button_clicked()\0"
    "on_lane_button_clicked()\0"
    "on_time_button_clicked()\0"
    "on_title_button_clicked()\0"
    "on_recover_button_clicked()\0"
    "on_pushButton_hide_pressed()\0"
    "on_pushButton_hide_clicked()\0"
    "on_check_button_released()\0"
    "on_check_button_pressed()\0"
    "on_logout_button_released()\0"
    "on_logout_button_pressed()\0"
    "on_list_button_released()\0"
    "on_list_button_pressed()\0"
    "on_check_button_clicked()\0"
    "on_list_button_clicked()\0date_time_flash()\0"
    "tick_time_flash()\0cam_flash()\0"
    "show_sensor_state(sensor_all_att*)\0"
    "show_alarm_and_twinkle()\0,\0"
    "finished_playing(int,QProcess::ExitStatus)\0"
    "cashier_update()\0return_cam_status()\0"
    "flag\0show_recover_button(bool)\0"
    "revolve_pic()\0"
};

const QMetaObject serialMode::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_serialMode,
      qt_meta_data_serialMode, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &serialMode::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *serialMode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *serialMode::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_serialMode))
        return static_cast<void*>(const_cast< serialMode*>(this));
    return QDialog::qt_metacast(_clname);
}

int serialMode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: sig_take_pic(); break;
        case 1: record_ok(); break;
        case 2: on_logout_button_clicked(); break;
        case 3: on_lane_button_clicked(); break;
        case 4: on_time_button_clicked(); break;
        case 5: on_title_button_clicked(); break;
        case 6: on_recover_button_clicked(); break;
        case 7: on_pushButton_hide_pressed(); break;
        case 8: on_pushButton_hide_clicked(); break;
        case 9: on_check_button_released(); break;
        case 10: on_check_button_pressed(); break;
        case 11: on_logout_button_released(); break;
        case 12: on_logout_button_pressed(); break;
        case 13: on_list_button_released(); break;
        case 14: on_list_button_pressed(); break;
        case 15: on_check_button_clicked(); break;
        case 16: on_list_button_clicked(); break;
        case 17: date_time_flash(); break;
        case 18: tick_time_flash(); break;
        case 19: cam_flash(); break;
        case 20: show_sensor_state((*reinterpret_cast< sensor_all_att*(*)>(_a[1]))); break;
        case 21: show_alarm_and_twinkle(); break;
        case 22: finished_playing((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 23: cashier_update(); break;
        case 24: return_cam_status(); break;
        case 25: show_recover_button((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 26: revolve_pic(); break;
        default: ;
        }
        _id -= 27;
    }
    return _id;
}

// SIGNAL 0
void serialMode::sig_take_pic()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void serialMode::record_ok()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
