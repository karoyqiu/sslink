#-------------------------------------------------
#
# Project created by QtCreator 2015-04-15T19:29:18
#
#-------------------------------------------------

QT       += core gui concurrent webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ss-link
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    sslink.cpp \
    shadowsocksserverlistmodel.cpp \
    ping.cpp \
    ssproxy.cpp \
    optionsdialog.cpp

HEADERS  += mainwidget.h \
    sslink.h \
    shadowsocksserver.h \
    shadowsocksserverlistmodel.h \
    ping.h \
    ssproxy.h \
    optionsdialog.h

FORMS    += mainwidget.ui \
    optionsdialog.ui

RESOURCES += \
    shadowsocks.qrc

RC_ICONS = res/shadowsocks.ico
VERSION = 0.1
