/****************************************************************************
** Meta object code from reading C++ file 'mybucks.h'
**
** Created: Fri Sep 6 08:02:40 2013
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mybucks.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mybucks.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_myBucks[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x0a,
      24,    8,    8,    8, 0x0a,
      32,    8,    8,    8, 0x0a,
      39,    8,    8,    8, 0x0a,
      48,    8,    8,    8, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_myBucks[] = {
    "myBucks\0\0myBucksTrack()\0about()\0info()\0"
    "gtotal()\0handleSelectionChanged(int)\0"
};

const QMetaObject myBucks::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_myBucks,
      qt_meta_data_myBucks, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &myBucks::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *myBucks::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *myBucks::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_myBucks))
        return static_cast<void*>(const_cast< myBucks*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int myBucks::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: myBucksTrack(); break;
        case 1: about(); break;
        case 2: info(); break;
        case 3: gtotal(); break;
        case 4: handleSelectionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
