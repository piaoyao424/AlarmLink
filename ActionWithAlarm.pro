#-------------------------------------------------
#
# Project created by QtCreator 2016-03-20T20:15:46
#
#-------------------------------------------------
#添加预编译头文件
CONFIG+=precompile_header
PRECOMPILED_HEADER = stable.h

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ActionWithAlarm
TEMPLATE = app


SOURCES += main.cpp \
        mainwindow.cpp \
    alarm_hc.cpp


HEADERS  += mainwindow.h \
    alarm_hc.h \
    HCSDK/HCNetSDK.h \
    stable.h

FORMS    += mainwindow.ui
