INCLUDEPATH += $$PWD/libqrencode $$PWD
DEFINES *= HAVE_CONFIG_H

HEADERS += \
    $$PWD/libqrencode/bitstream.h \
    $$PWD/libqrencode/mask.h \
    $$PWD/libqrencode/mmask.h \
    $$PWD/libqrencode/mqrspec.h \
    $$PWD/libqrencode/qrencode.h \
    $$PWD/libqrencode/qrencode_inner.h \
    $$PWD/libqrencode/qrinput.h \
    $$PWD/libqrencode/qrspec.h \
    $$PWD/libqrencode/rsecc.h \
    $$PWD/libqrencode/split.h

SOURCES += \
    $$PWD/libqrencode/bitstream.c \
    $$PWD/libqrencode/mask.c \
    $$PWD/libqrencode/mmask.c \
    $$PWD/libqrencode/mqrspec.c \
    $$PWD/libqrencode/qrencode.c \
    $$PWD/libqrencode/qrinput.c \
    $$PWD/libqrencode/qrspec.c \
    $$PWD/libqrencode/rsecc.c \
    $$PWD/libqrencode/split.c
