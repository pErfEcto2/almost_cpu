QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++23

INCLUDEPATH += headers
DEPENDPATH += headers

SOURCES += \
    src/alu.cpp \
    src/command.cpp \
    src/core.cpp \
    src/cpu.cpp \
    src/lib.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/memory.cpp

HEADERS += \
    headers/alu.h \
    headers/command.h \
    headers/core.h \
    headers/cpu.h \
    headers/lib.h \
    headers/mainwindow.h \
    headers/memory.h \
    headers/vector.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    lab3_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += \
                                target
