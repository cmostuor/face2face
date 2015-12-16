/****************************************************************************
** Meta object code from reading C++ file 'ModelViewer5.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ModelViewer5.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ModelViewer5.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ModelViewer_t {
    QByteArrayData data[11];
    char stringdata0[127];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ModelViewer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ModelViewer_t qt_meta_stringdata_ModelViewer = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ModelViewer"
QT_MOC_LITERAL(1, 12, 12), // "mousePressed"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 13), // "mousePosition"
QT_MOC_LITERAL(4, 40, 10), // "mouseMoved"
QT_MOC_LITERAL(5, 51, 13), // "mouseReleased"
QT_MOC_LITERAL(6, 65, 14), // "renderRotation"
QT_MOC_LITERAL(7, 80, 14), // "updateGeometry"
QT_MOC_LITERAL(8, 95, 12), // "changeCamImg"
QT_MOC_LITERAL(9, 108, 7), // "cv::Mat"
QT_MOC_LITERAL(10, 116, 10) // "_imgBuffer"

    },
    "ModelViewer\0mousePressed\0\0mousePosition\0"
    "mouseMoved\0mouseReleased\0renderRotation\0"
    "updateGeometry\0changeCamImg\0cv::Mat\0"
    "_imgBuffer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ModelViewer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,
       5,    0,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   51,    2, 0x0a /* Public */,
       7,    0,   52,    2, 0x0a /* Public */,
       8,    1,   53,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QVector2D,    3,
    QMetaType::Void, QMetaType::QVector2D,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,

       0        // eod
};

void ModelViewer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ModelViewer *_t = static_cast<ModelViewer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mousePressed((*reinterpret_cast< QVector2D(*)>(_a[1]))); break;
        case 1: _t->mouseMoved((*reinterpret_cast< QVector2D(*)>(_a[1]))); break;
        case 2: _t->mouseReleased(); break;
        case 3: _t->renderRotation(); break;
        case 4: _t->updateGeometry(); break;
        case 5: _t->changeCamImg((*reinterpret_cast< cv::Mat(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ModelViewer::*_t)(QVector2D );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ModelViewer::mousePressed)) {
                *result = 0;
            }
        }
        {
            typedef void (ModelViewer::*_t)(QVector2D );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ModelViewer::mouseMoved)) {
                *result = 1;
            }
        }
        {
            typedef void (ModelViewer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ModelViewer::mouseReleased)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject ModelViewer::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_ModelViewer.data,
      qt_meta_data_ModelViewer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ModelViewer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModelViewer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ModelViewer.stringdata0))
        return static_cast<void*>(const_cast< ModelViewer*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int ModelViewer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ModelViewer::mousePressed(QVector2D _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ModelViewer::mouseMoved(QVector2D _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ModelViewer::mouseReleased()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
