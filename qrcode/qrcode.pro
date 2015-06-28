#-------------------------------------------------
#
# Project created by QtCreator 2015-06-24T22:46:17
#
#-------------------------------------------------

TARGET = qrcode
TEMPLATE = lib

DEFINES += QRCODE_LIBRARY

include(../3rdparty/libqrencode.pri)

SOURCES += qrcode.cpp

HEADERS += qrcode.h\
        qrcode_global.h

#VERSION = 0.1

unix {
    target.path = /usr/lib
    INSTALLS += target
}
