/****************************************************************************
** Meta object code from reading C++ file 'ModelController.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ModelController.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ModelController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ModelController_t {
    QByteArrayData data[26];
    char stringdata0[373];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ModelController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ModelController_t qt_meta_stringdata_ModelController = {
    {
QT_MOC_LITERAL(0, 0, 15), // "ModelController"
QT_MOC_LITERAL(1, 16, 10), // "updateView"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 8), // "sendPing"
QT_MOC_LITERAL(4, 37, 11), // "sendMessage"
QT_MOC_LITERAL(5, 49, 13), // "ModellMessage"
QT_MOC_LITERAL(6, 63, 13), // "_modelMessage"
QT_MOC_LITERAL(7, 77, 22), // "computeArcBallRotation"
QT_MOC_LITERAL(8, 100, 20), // "startArcBallRotation"
QT_MOC_LITERAL(9, 121, 13), // "mousePosition"
QT_MOC_LITERAL(10, 135, 21), // "updateArcBallRotation"
QT_MOC_LITERAL(11, 157, 19), // "stopArcBallRotation"
QT_MOC_LITERAL(12, 177, 19), // "processTuioAddEvent"
QT_MOC_LITERAL(13, 197, 9), // "newFinger"
QT_MOC_LITERAL(14, 207, 20), // "processTuioMoveEvent"
QT_MOC_LITERAL(15, 228, 13), // "updatedFinger"
QT_MOC_LITERAL(16, 242, 22), // "processTuioDeleteEvent"
QT_MOC_LITERAL(17, 265, 2), // "id"
QT_MOC_LITERAL(18, 268, 20), // "processTuioTransform"
QT_MOC_LITERAL(19, 289, 10), // "keyPressed"
QT_MOC_LITERAL(20, 300, 10), // "QKeyEvent*"
QT_MOC_LITERAL(21, 311, 5), // "event"
QT_MOC_LITERAL(22, 317, 14), // "receiveMessage"
QT_MOC_LITERAL(23, 332, 16), // "_incomingMessage"
QT_MOC_LITERAL(24, 349, 11), // "changeModel"
QT_MOC_LITERAL(25, 361, 11) // "modelNumber"

    },
    "ModelController\0updateView\0\0sendPing\0"
    "sendMessage\0ModellMessage\0_modelMessage\0"
    "computeArcBallRotation\0startArcBallRotation\0"
    "mousePosition\0updateArcBallRotation\0"
    "stopArcBallRotation\0processTuioAddEvent\0"
    "newFinger\0processTuioMoveEvent\0"
    "updatedFinger\0processTuioDeleteEvent\0"
    "id\0processTuioTransform\0keyPressed\0"
    "QKeyEvent*\0event\0receiveMessage\0"
    "_incomingMessage\0changeModel\0modelNumber"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ModelController[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06 /* Public */,
       3,    0,   85,    2, 0x06 /* Public */,
       4,    1,   86,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   89,    2, 0x0a /* Public */,
       8,    1,   90,    2, 0x0a /* Public */,
      10,    1,   93,    2, 0x0a /* Public */,
      11,    0,   96,    2, 0x0a /* Public */,
      12,    1,   97,    2, 0x0a /* Public */,
      14,    1,  100,    2, 0x0a /* Public */,
      16,    1,  103,    2, 0x0a /* Public */,
      18,    0,  106,    2, 0x0a /* Public */,
      19,    1,  107,    2, 0x0a /* Public */,
      22,    1,  110,    2, 0x0a /* Public */,
      24,    1,  113,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QVector2D,    9,
    QMetaType::Void, QMetaType::QVector2D,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QVector3D,   13,
    QMetaType::Void, QMetaType::QVector3D,   15,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void, 0x80000000 | 5,   23,
    QMetaType::Void, QMetaType::Int,   25,

       0        // eod
};

void ModelController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ModelController *_t = static_cast<ModelController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateView(); break;
        case 1: _t->sendPing(); break;
        case 2: _t->sendMessage((*reinterpret_cast< ModellMessage(*)>(_a[1]))); break;
        case 3: _t->computeArcBallRotation(); break;
        case 4: _t->startArcBallRotation((*reinterpret_cast< QVector2D(*)>(_a[1]))); break;
        case 5: _t->updateArcBallRotation((*reinterpret_cast< QVector2D(*)>(_a[1]))); break;
        case 6: _t->stopArcBallRotation(); break;
        case 7: _t->processTuioAddEvent((*reinterpret_cast< QVector3D(*)>(_a[1]))); break;
        case 8: _t->processTuioMoveEvent((*reinterpret_cast< QVector3D(*)>(_a[1]))); break;
        case 9: _t->processTuioDeleteEvent((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->processTuioTransform(); break;
        case 11: _t->keyPressed((*reinterpret_cast< QKeyEvent*(*)>(_a[1]))); break;
        case 12: _t->receiveMessage((*reinterpret_cast< ModellMessage(*)>(_a[1]))); break;
        case 13: _t->changeModel((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ModelController::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ModelController::updateView)) {
                *result = 0;
            }
        }
        {
            typedef void (ModelController::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ModelController::sendPing)) {
                *result = 1;
            }
        }
        {
            typedef void (ModelController::*_t)(ModellMessage );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ModelController::sendMessage)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject ModelController::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ModelController.data,
      qt_meta_data_ModelController,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ModelController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModelController::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ModelController.stringdata0))
        return static_cast<void*>(const_cast< ModelController*>(this));
    return QObject::qt_metacast(_clname);
}

int ModelController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void ModelController::updateView()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void ModelController::sendPing()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void ModelController::sendMessage(ModellMessage _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
