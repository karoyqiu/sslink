#-------------------------------------------------
#
# Project created by QtCreator 2015-04-15T19:29:18
#
#-------------------------------------------------

QT       += core gui concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ss-link
TEMPLATE = app


SOURCES += main.cpp\
    mainwidget.cpp \
    shadowsocksserverlistmodel.cpp \
    ping.cpp \
    ssproxy.cpp \
    optionsdialog.cpp \
    abstracthttpproxy.cpp \
    polipo.cpp \
    cow.cpp \
    meow.cpp \
    qrcodedialog.cpp

HEADERS  += mainwidget.h \
    shadowsocksserverlistmodel.h \
    ping.h \
    ssproxy.h \
    optionsdialog.h \
    abstracthttpproxy.h \
    polipo.h \
    cow.h \
    meow.h \
    qrcodedialog.h

FORMS    += mainwidget.ui \
    optionsdialog.ui \
    qrcodedialog.ui

RESOURCES += \
    shadowsocks.qrc

RC_ICONS = res/shadowsocks.ico
VERSION = 0.5

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../qrcode/release/ -lqrcode
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../qrcode/debug/ -lqrcode
else:unix: LIBS += -L$$OUT_PWD/../qrcode/ -lqrcode

INCLUDEPATH += $$PWD/../qrcode
DEPENDPATH += $$PWD/../qrcode
