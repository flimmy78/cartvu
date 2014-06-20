/****************************************************************************
** Meta object code from reading C++ file 'camThread.h'
**
** Created: Fri Jun 13 18:10:49 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "camThread.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'camThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_camThread[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      11,   10,   10,   10, 0x05,

 // slots: signature, parameters, type, tag, flags
      18,   10,   10,   10, 0x08,
      29,   10,   10,   10, 0x08,
      40,   10,   10,   10, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_camThread[] = {
    "camThread\0\0play()\0take_pic()\0emit_pic()\0"
    "show_last_pic()\0"
};

const QMetaObject camThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_camThread,
      qt_meta_data_camThread, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &camThread::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *camThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *camThread::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_camThread))
        return static_cast<void*>(const_cast< camThread*>(this));
    return QThread::qt_metacast(_clname);
}

int camThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: play(); break;
        case 1: take_pic(); break;
        case 2: emit_pic(); break;
        case 3: show_last_pic(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void camThread::play()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
