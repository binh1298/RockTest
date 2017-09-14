#-------------------------------------------------
#
# Project created by QtCreator 2016-12-08T23:08:00
#
#-------------------------------------------------

QT       += core gui
QT  +=  axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RockTest
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    createquestion.cpp \
    maketest.cpp \

HEADERS  += mainwindow.h \
    createquestion.h \
    maketest.h \

FORMS    += mainwindow.ui \
    createquestion.ui \
    maketest.ui

RC_FILE += myapp.rc
