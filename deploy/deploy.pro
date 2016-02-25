QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Deploy
TEMPLATE = app
CONFIG += c++11

include(../common/common.pri)


SOURCES += main.cpp\
        deploy.cpp

HEADERS  += deploy.h

FORMS    +=
