#-------------------------------------------------
#
# Project created by QtCreator 2015-04-24T20:20:36
#
#-------------------------------------------------

QT       += core gui webkitwidgets

TARGET = ssspider
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ssspider.cpp

HEADERS += \
    ssspider.h

RC_ICONS = ../ss-link/res/shadowsocks.ico
VERSION = 0.3.1

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../shadowsocksserver/release/ -lshadowsocksserver
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../shadowsocksserver/debug/ -lshadowsocksserver
else:unix: LIBS += -L$$OUT_PWD/../shadowsocksserver/ -lshadowsocksserver

INCLUDEPATH += $$PWD/../shadowsocksserver
DEPENDPATH += $$PWD/../shadowsocksserver

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../shadowsocksserver/release/libshadowsocksserver.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../shadowsocksserver/debug/libshadowsocksserver.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../shadowsocksserver/release/shadowsocksserver.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../shadowsocksserver/debug/shadowsocksserver.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../shadowsocksserver/libshadowsocksserver.a
