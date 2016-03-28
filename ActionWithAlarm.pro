#-------------------------------------------------
#
# Project created by QtCreator 2016-03-20T20:15:46
#
#-------------------------------------------------

QT       += core gui
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#添加预编译头文件
CONFIG += precompile_header
CONFIG += qaxcontainer

PRECOMPILED_HEADER = stable.h

#生成程序名称
TARGET = AlarmLink



TARGET = ActionWithAlarm
TEMPLATE = app


SOURCES += main.cpp \
    mainwindow.cpp \
    alarm_hc.cpp \
    textspeech.cpp


HEADERS  += mainwindow.h \
    alarm_hc.h \
    HCSDK/HCNetSDK.h \
    stable.h \
    AlarmClass.h \
    textspeech.h

FORMS    += mainwindow.ui
