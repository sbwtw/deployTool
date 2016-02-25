QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../common/common.pri)

TARGET = Generate
TEMPLATE = app
CONFIG += c++11


SOURCES += \
    main.cpp \
    generate.cpp \
    itemdialog.cpp

HEADERS  += \
    generate.h \
    itemdialog.h

FORMS    +=
