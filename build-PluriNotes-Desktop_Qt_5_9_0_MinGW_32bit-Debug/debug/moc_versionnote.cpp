/****************************************************************************
** Meta object code from reading C++ file 'versionnote.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PluriNotes/versionnote.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'versionnote.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VersionNote_t {
    QByteArrayData data[1];
    char stringdata0[12];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VersionNote_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VersionNote_t qt_meta_stringdata_VersionNote = {
    {
QT_MOC_LITERAL(0, 0, 11) // "VersionNote"

    },
    "VersionNote"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VersionNote[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void VersionNote::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject VersionNote::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_VersionNote.data,
      qt_meta_data_VersionNote,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *VersionNote::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VersionNote::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VersionNote.stringdata0))
        return static_cast<void*>(const_cast< VersionNote*>(this));
    return QObject::qt_metacast(_clname);
}

int VersionNote::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_Article_t {
    QByteArrayData data[1];
    char stringdata0[8];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Article_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Article_t qt_meta_stringdata_Article = {
    {
QT_MOC_LITERAL(0, 0, 7) // "Article"

    },
    "Article"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Article[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void Article::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject Article::staticMetaObject = {
    { &VersionNote::staticMetaObject, qt_meta_stringdata_Article.data,
      qt_meta_data_Article,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Article::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Article::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Article.stringdata0))
        return static_cast<void*>(const_cast< Article*>(this));
    return VersionNote::qt_metacast(_clname);
}

int Article::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = VersionNote::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_Tache_t {
    QByteArrayData data[6];
    char stringdata0[69];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Tache_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Tache_t qt_meta_stringdata_Tache = {
    {
QT_MOC_LITERAL(0, 0, 5), // "Tache"
QT_MOC_LITERAL(1, 6, 18), // "setStatusEnAttente"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 7), // "checked"
QT_MOC_LITERAL(4, 34, 16), // "setStatusEnCours"
QT_MOC_LITERAL(5, 51, 17) // "setStatusTerminee"

    },
    "Tache\0setStatusEnAttente\0\0checked\0"
    "setStatusEnCours\0setStatusTerminee"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Tache[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       4,    1,   32,    2, 0x0a /* Public */,
       5,    1,   35,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Bool,    3,

       0        // eod
};

void Tache::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Tache *_t = static_cast<Tache *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setStatusEnAttente((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->setStatusEnCours((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->setStatusTerminee((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Tache::staticMetaObject = {
    { &VersionNote::staticMetaObject, qt_meta_stringdata_Tache.data,
      qt_meta_data_Tache,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Tache::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Tache::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Tache.stringdata0))
        return static_cast<void*>(const_cast< Tache*>(this));
    return VersionNote::qt_metacast(_clname);
}

int Tache::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = VersionNote::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
