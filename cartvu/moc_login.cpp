/****************************************************************************
** Meta object code from reading C++ file 'login.h'
**
** Created: Thu Jun 19 10:14:47 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "login.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'login.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_login[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      48,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       7,    6,    6,    6, 0x08,
      35,    6,    6,    6, 0x08,
      62,    6,    6,    6, 0x08,
      86,    6,    6,    6, 0x08,
     113,    6,    6,    6, 0x08,
     139,    6,    6,    6, 0x08,
     168,    6,    6,    6, 0x08,
     196,    6,    6,    6, 0x08,
     223,    6,    6,    6, 0x08,
     249,    6,    6,    6, 0x08,
     276,    6,    6,    6, 0x08,
     302,    6,    6,    6, 0x08,
     329,    6,    6,    6, 0x08,
     355,    6,    6,    6, 0x08,
     382,    6,    6,    6, 0x08,
     408,    6,    6,    6, 0x08,
     435,    6,    6,    6, 0x08,
     461,    6,    6,    6, 0x08,
     488,    6,    6,    6, 0x08,
     514,    6,    6,    6, 0x08,
     541,    6,    6,    6, 0x08,
     567,    6,    6,    6, 0x08,
     594,    6,    6,    6, 0x08,
     620,    6,    6,    6, 0x08,
     647,    6,    6,    6, 0x08,
     673,    6,    6,    6, 0x08,
     700,    6,    6,    6, 0x08,
     726,    6,    6,    6, 0x08,
     752,    6,    6,    6, 0x08,
     780,    6,    6,    6, 0x08,
     807,    6,    6,    6, 0x08,
     833,    6,    6,    6, 0x08,
     859,    6,    6,    6, 0x08,
     885,    6,    6,    6, 0x08,
     911,    6,    6,    6, 0x08,
     937,    6,    6,    6, 0x08,
     963,    6,    6,    6, 0x08,
     989,    6,    6,    6, 0x08,
    1015,    6,    6,    6, 0x08,
    1041,    6,    6,    6, 0x08,
    1067,    6,    6,    6, 0x08,
    1086,    6,    6,    6, 0x08,
    1102, 1097,    6,    6, 0x08,
    1124,    6,    6,    6, 0x08,
    1144,    6,    6,    6, 0x08,
    1161,    6,    6,    6, 0x08,
    1179,    6,    6,    6, 0x08,
    1199,    6,    6,    6, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_login[] = {
    "login\0\0on_pushButton_ac_released()\0"
    "on_pushButton_ac_clicked()\0"
    "on_big_button_clicked()\0"
    "on_login_button_released()\0"
    "on_login_button_pressed()\0"
    "on_pushButton_del_released()\0"
    "on_pushButton_del_pressed()\0"
    "on_pushButton_0_released()\0"
    "on_pushButton_0_pressed()\0"
    "on_pushButton_9_released()\0"
    "on_pushButton_9_pressed()\0"
    "on_pushButton_8_released()\0"
    "on_pushButton_8_pressed()\0"
    "on_pushButton_7_released()\0"
    "on_pushButton_7_pressed()\0"
    "on_pushButton_6_released()\0"
    "on_pushButton_6_pressed()\0"
    "on_pushButton_5_released()\0"
    "on_pushButton_5_pressed()\0"
    "on_pushButton_4_released()\0"
    "on_pushButton_4_pressed()\0"
    "on_pushButton_3_released()\0"
    "on_pushButton_3_pressed()\0"
    "on_pushButton_2_released()\0"
    "on_pushButton_2_pressed()\0"
    "on_pushButton_1_released()\0"
    "on_pushButton_1_pressed()\0"
    "on_login_button_clicked()\0"
    "on_pushButton_del_clicked()\0"
    "on_pushButton_ac_pressed()\0"
    "on_pushButton_0_clicked()\0"
    "on_pushButton_9_clicked()\0"
    "on_pushButton_8_clicked()\0"
    "on_pushButton_7_clicked()\0"
    "on_pushButton_6_clicked()\0"
    "on_pushButton_5_clicked()\0"
    "on_pushButton_4_clicked()\0"
    "on_pushButton_3_clicked()\0"
    "on_pushButton_2_clicked()\0"
    "on_pushButton_1_clicked()\0send_status_to_s()\0"
    "judge_ok()\0flag\0show_big_button(bool)\0"
    "select_mode_start()\0close_box_slot()\0"
    "receive_message()\0confirmed_message()\0"
    "confirmed2_message()\0"
};

const QMetaObject login::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_login,
      qt_meta_data_login, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &login::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *login::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *login::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_login))
        return static_cast<void*>(const_cast< login*>(this));
    return QDialog::qt_metacast(_clname);
}

int login::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_pushButton_ac_released(); break;
        case 1: on_pushButton_ac_clicked(); break;
        case 2: on_big_button_clicked(); break;
        case 3: on_login_button_released(); break;
        case 4: on_login_button_pressed(); break;
        case 5: on_pushButton_del_released(); break;
        case 6: on_pushButton_del_pressed(); break;
        case 7: on_pushButton_0_released(); break;
        case 8: on_pushButton_0_pressed(); break;
        case 9: on_pushButton_9_released(); break;
        case 10: on_pushButton_9_pressed(); break;
        case 11: on_pushButton_8_released(); break;
        case 12: on_pushButton_8_pressed(); break;
        case 13: on_pushButton_7_released(); break;
        case 14: on_pushButton_7_pressed(); break;
        case 15: on_pushButton_6_released(); break;
        case 16: on_pushButton_6_pressed(); break;
        case 17: on_pushButton_5_released(); break;
        case 18: on_pushButton_5_pressed(); break;
        case 19: on_pushButton_4_released(); break;
        case 20: on_pushButton_4_pressed(); break;
        case 21: on_pushButton_3_released(); break;
        case 22: on_pushButton_3_pressed(); break;
        case 23: on_pushButton_2_released(); break;
        case 24: on_pushButton_2_pressed(); break;
        case 25: on_pushButton_1_released(); break;
        case 26: on_pushButton_1_pressed(); break;
        case 27: on_login_button_clicked(); break;
        case 28: on_pushButton_del_clicked(); break;
        case 29: on_pushButton_ac_pressed(); break;
        case 30: on_pushButton_0_clicked(); break;
        case 31: on_pushButton_9_clicked(); break;
        case 32: on_pushButton_8_clicked(); break;
        case 33: on_pushButton_7_clicked(); break;
        case 34: on_pushButton_6_clicked(); break;
        case 35: on_pushButton_5_clicked(); break;
        case 36: on_pushButton_4_clicked(); break;
        case 37: on_pushButton_3_clicked(); break;
        case 38: on_pushButton_2_clicked(); break;
        case 39: on_pushButton_1_clicked(); break;
        case 40: send_status_to_s(); break;
        case 41: judge_ok(); break;
        case 42: show_big_button((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 43: select_mode_start(); break;
        case 44: close_box_slot(); break;
        case 45: receive_message(); break;
        case 46: confirmed_message(); break;
        case 47: confirmed2_message(); break;
        default: ;
        }
        _id -= 48;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
