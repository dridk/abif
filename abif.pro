TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
#CONFIG -= qt
CONFIG   += c++11
QT += core
SOURCES += main.cpp \
    abif.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    abif.h

