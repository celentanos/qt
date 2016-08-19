#-------------------------------------------------
#
# Project created by QtCreator 2016-08-17T14:13:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = weatherDataParser
TEMPLATE = app

DESTDIR = $$PWD/bin

SOURCES += main.cpp\
        mainwindow.cpp \
    helpers.cpp \
    measure.cpp \
    measure_list.cpp \
    eca_parser.cpp \
    log.cpp

HEADERS  += mainwindow.h \
    result.h \
    error_result.h \
    success_result.h \
    helpers.h \
    measure.h \
    measure_list.h \
    eca_parser.h \
    log.h

FORMS    += mainwindow.ui
