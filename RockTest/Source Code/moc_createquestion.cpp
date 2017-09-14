/****************************************************************************
** Meta object code from reading C++ file 'createquestion.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QT/untitled/createquestion.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'createquestion.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CreateQuestion_t {
    QByteArrayData data[17];
    char stringdata0[510];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CreateQuestion_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CreateQuestion_t qt_meta_stringdata_CreateQuestion = {
    {
QT_MOC_LITERAL(0, 0, 14), // "CreateQuestion"
QT_MOC_LITERAL(1, 15, 12), // "ResetAnswers"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 35), // "on_pushButton_CreateSubject_c..."
QT_MOC_LITERAL(4, 65, 38), // "on_comboBox_Subject_currentTe..."
QT_MOC_LITERAL(5, 104, 4), // "arg1"
QT_MOC_LITERAL(6, 109, 34), // "on_pushButton_EditQuestion_cl..."
QT_MOC_LITERAL(7, 144, 45), // "on_comboBox_TypeofExercise_cu..."
QT_MOC_LITERAL(8, 190, 28), // "on_pushButton_Finish_clicked"
QT_MOC_LITERAL(9, 219, 30), // "on_pushButton_Continue_clicked"
QT_MOC_LITERAL(10, 250, 42), // "on_pushButton_CreateTypeofExe..."
QT_MOC_LITERAL(11, 293, 41), // "on_comboBox_Difficulty_curren..."
QT_MOC_LITERAL(12, 335, 38), // "on_pushButton_CreateDifficult..."
QT_MOC_LITERAL(13, 374, 33), // "on_pushButton_EditAnswerA_cli..."
QT_MOC_LITERAL(14, 408, 33), // "on_pushButton_EditAnswerB_cli..."
QT_MOC_LITERAL(15, 442, 33), // "on_pushButton_EditAnswerC_cli..."
QT_MOC_LITERAL(16, 476, 33) // "on_pushButton_EditAnswerD_cli..."

    },
    "CreateQuestion\0ResetAnswers\0\0"
    "on_pushButton_CreateSubject_clicked\0"
    "on_comboBox_Subject_currentTextChanged\0"
    "arg1\0on_pushButton_EditQuestion_clicked\0"
    "on_comboBox_TypeofExercise_currentTextChanged\0"
    "on_pushButton_Finish_clicked\0"
    "on_pushButton_Continue_clicked\0"
    "on_pushButton_CreateTypeofExercise_clicked\0"
    "on_comboBox_Difficulty_currentTextChanged\0"
    "on_pushButton_CreateDifficulty_clicked\0"
    "on_pushButton_EditAnswerA_clicked\0"
    "on_pushButton_EditAnswerB_clicked\0"
    "on_pushButton_EditAnswerC_clicked\0"
    "on_pushButton_EditAnswerD_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CreateQuestion[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    1,   86,    2, 0x08 /* Private */,
       6,    0,   89,    2, 0x08 /* Private */,
       7,    1,   90,    2, 0x08 /* Private */,
       8,    0,   93,    2, 0x08 /* Private */,
       9,    0,   94,    2, 0x08 /* Private */,
      10,    0,   95,    2, 0x08 /* Private */,
      11,    1,   96,    2, 0x08 /* Private */,
      12,    0,   99,    2, 0x08 /* Private */,
      13,    0,  100,    2, 0x08 /* Private */,
      14,    0,  101,    2, 0x08 /* Private */,
      15,    0,  102,    2, 0x08 /* Private */,
      16,    0,  103,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CreateQuestion::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CreateQuestion *_t = static_cast<CreateQuestion *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ResetAnswers(); break;
        case 1: _t->on_pushButton_CreateSubject_clicked(); break;
        case 2: _t->on_comboBox_Subject_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->on_pushButton_EditQuestion_clicked(); break;
        case 4: _t->on_comboBox_TypeofExercise_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->on_pushButton_Finish_clicked(); break;
        case 6: _t->on_pushButton_Continue_clicked(); break;
        case 7: _t->on_pushButton_CreateTypeofExercise_clicked(); break;
        case 8: _t->on_comboBox_Difficulty_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->on_pushButton_CreateDifficulty_clicked(); break;
        case 10: _t->on_pushButton_EditAnswerA_clicked(); break;
        case 11: _t->on_pushButton_EditAnswerB_clicked(); break;
        case 12: _t->on_pushButton_EditAnswerC_clicked(); break;
        case 13: _t->on_pushButton_EditAnswerD_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject CreateQuestion::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CreateQuestion.data,
      qt_meta_data_CreateQuestion,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CreateQuestion::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CreateQuestion::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CreateQuestion.stringdata0))
        return static_cast<void*>(const_cast< CreateQuestion*>(this));
    return QDialog::qt_metacast(_clname);
}

int CreateQuestion::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
