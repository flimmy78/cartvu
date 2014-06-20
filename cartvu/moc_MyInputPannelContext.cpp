/****************************************************************************
** Meta object code from reading C++ file 'MyInputPannelContext.h'
**
** Created: Fri Jun 13 18:11:07 2014
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MyInputPannelContext.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MyInputPannelContext.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MyInputPannelContext[] = {

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
      27,   22,   21,   21, 0x05,

 // slots: signature, parameters, type, tag, flags
      62,   52,   21,   21, 0x0a,
      82,   78,   21,   21, 0x0a,
      95,   22,   21,   21, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_MyInputPannelContext[] = {
    "MyInputPannelContext\0\0info\0"
    "now_line_string(QString)\0character\0"
    "charSlot(QChar)\0key\0intSlot(int)\0"
    "update_line(QString)\0"
};

const QMetaObject MyInputPannelContext::staticMetaObject = {
    { &QInputContext::staticMetaObject, qt_meta_stringdata_MyInputPannelContext,
      qt_meta_data_MyInputPannelContext, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MyInputPannelContext::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MyInputPannelContext::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MyInputPannelContext::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MyInputPannelContext))
        return static_cast<void*>(const_cast< MyInputPannelContext*>(this));
    return QInputContext::qt_metacast(_clname);
}

int MyInputPannelContext::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QInputContext::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: now_line_string((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: charSlot((*reinterpret_cast< QChar(*)>(_a[1]))); break;
        case 2: intSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: update_line((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void MyInputPannelContext::now_line_string(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
