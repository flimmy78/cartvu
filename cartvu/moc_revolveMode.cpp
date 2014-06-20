/****************************************************************************
** Meta object code from reading C++ file 'revolveMode.h'
**
** Created: Thu Jun 19 10:14:53 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "revolveMode.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'revolveMode.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_revolveMode[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      44,   12,   12,   12, 0x08,
      71,   12,   12,   12, 0x08,
      91,   12,   12,   12, 0x08,
     103,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_revolveMode[] = {
    "revolveMode\0\0on_log_in_out_button_clicked()\0"
    "on_return_button_clicked()\0"
    "revolve_pic_start()\0init_mode()\0"
    "return_serial_mode()\0"
};

const QMetaObject revolveMode::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_revolveMode,
      qt_meta_data_revolveMode, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &revolveMode::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *revolveMode::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *revolveMode::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_revolveMode))
        return static_cast<void*>(const_cast< revolveMode*>(this));
    return QDialog::qt_metacast(_clname);
}

int revolveMode::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_log_in_out_button_clicked(); break;
        case 1: on_return_button_clicked(); break;
        case 2: revolve_pic_start(); break;
        case 3: init_mode(); break;
        case 4: return_serial_mode(); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
