/****************************************************************************
** Meta object code from reading C++ file 'code_view.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../src/frontends/qmps/code_view.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'code_view.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CodeView_t {
    QByteArrayData data[8];
    char stringdata0[63];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CodeView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CodeView_t qt_meta_stringdata_CodeView = {
    {
QT_MOC_LITERAL(0, 0, 8), // "CodeView"
QT_MOC_LITERAL(1, 9, 8), // "loadCode"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 16), // "onMachineStopped"
QT_MOC_LITERAL(4, 36, 12), // "updateMargin"
QT_MOC_LITERAL(5, 49, 4), // "rect"
QT_MOC_LITERAL(6, 54, 2), // "dy"
QT_MOC_LITERAL(7, 57, 5) // "reset"

    },
    "CodeView\0loadCode\0\0onMachineStopped\0"
    "updateMargin\0rect\0dy\0reset"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CodeView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x08 /* Private */,
       3,    0,   35,    2, 0x08 /* Private */,
       4,    2,   36,    2, 0x08 /* Private */,
       7,    0,   41,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QRect, QMetaType::Int,    5,    6,
    QMetaType::Void,

       0        // eod
};

void CodeView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CodeView *_t = static_cast<CodeView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loadCode(); break;
        case 1: _t->onMachineStopped(); break;
        case 2: _t->updateMargin((*reinterpret_cast< const QRect(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->reset(); break;
        default: ;
        }
    }
}

const QMetaObject CodeView::staticMetaObject = {
    { &QPlainTextEdit::staticMetaObject, qt_meta_stringdata_CodeView.data,
      qt_meta_data_CodeView,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CodeView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CodeView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CodeView.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "sigc::trackable"))
        return static_cast< sigc::trackable*>(this);
    return QPlainTextEdit::qt_metacast(_clname);
}

int CodeView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPlainTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
