/****************************************************************************
** Meta object code from reading C++ file 'affichagenote.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PluriNotes/affichagenote.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'affichagenote.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AffichageNote_t {
    QByteArrayData data[7];
    char stringdata0[67];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AffichageNote_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AffichageNote_t qt_meta_stringdata_AffichageNote = {
    {
QT_MOC_LITERAL(0, 0, 13), // "AffichageNote"
QT_MOC_LITERAL(1, 14, 13), // "fermetureNote"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 2), // "id"
QT_MOC_LITERAL(4, 32, 15), // "nouvelleVersion"
QT_MOC_LITERAL(5, 48, 16), // "selectionVersion"
QT_MOC_LITERAL(6, 65, 1) // "i"

    },
    "AffichageNote\0fermetureNote\0\0id\0"
    "nouvelleVersion\0selectionVersion\0i"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AffichageNote[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   32,    2, 0x0a /* Public */,
       5,    1,   33,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,

       0        // eod
};

void AffichageNote::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AffichageNote *_t = static_cast<AffichageNote *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->fermetureNote((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->nouvelleVersion(); break;
        case 2: _t->selectionVersion((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AffichageNote::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AffichageNote::fermetureNote)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject AffichageNote::staticMetaObject = {
    { &QMdiSubWindow::staticMetaObject, qt_meta_stringdata_AffichageNote.data,
      qt_meta_data_AffichageNote,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AffichageNote::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AffichageNote::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AffichageNote.stringdata0))
        return static_cast<void*>(const_cast< AffichageNote*>(this));
    return QMdiSubWindow::qt_metacast(_clname);
}

int AffichageNote::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMdiSubWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void AffichageNote::fermetureNote(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_AffichageArticle_t {
    QByteArrayData data[3];
    char stringdata0[34];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AffichageArticle_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AffichageArticle_t qt_meta_stringdata_AffichageArticle = {
    {
QT_MOC_LITERAL(0, 0, 16), // "AffichageArticle"
QT_MOC_LITERAL(1, 17, 15), // "nouvelleVersion"
QT_MOC_LITERAL(2, 33, 0) // ""

    },
    "AffichageArticle\0nouvelleVersion\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AffichageArticle[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void AffichageArticle::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AffichageArticle *_t = static_cast<AffichageArticle *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->nouvelleVersion(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject AffichageArticle::staticMetaObject = {
    { &AffichageNote::staticMetaObject, qt_meta_stringdata_AffichageArticle.data,
      qt_meta_data_AffichageArticle,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AffichageArticle::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AffichageArticle::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AffichageArticle.stringdata0))
        return static_cast<void*>(const_cast< AffichageArticle*>(this));
    return AffichageNote::qt_metacast(_clname);
}

int AffichageArticle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AffichageNote::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_AffichageTache_t {
    QByteArrayData data[3];
    char stringdata0[32];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AffichageTache_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AffichageTache_t qt_meta_stringdata_AffichageTache = {
    {
QT_MOC_LITERAL(0, 0, 14), // "AffichageTache"
QT_MOC_LITERAL(1, 15, 15), // "nouvelleVersion"
QT_MOC_LITERAL(2, 31, 0) // ""

    },
    "AffichageTache\0nouvelleVersion\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AffichageTache[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void AffichageTache::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AffichageTache *_t = static_cast<AffichageTache *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->nouvelleVersion(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject AffichageTache::staticMetaObject = {
    { &AffichageNote::staticMetaObject, qt_meta_stringdata_AffichageTache.data,
      qt_meta_data_AffichageTache,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AffichageTache::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AffichageTache::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AffichageTache.stringdata0))
        return static_cast<void*>(const_cast< AffichageTache*>(this));
    return AffichageNote::qt_metacast(_clname);
}

int AffichageTache::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AffichageNote::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
