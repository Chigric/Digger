QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Digger
TEMPLATE = app

# Input
SOURCES += \
    main.cpp \
    bigtheater.cpp \
    actor.cpp \
    scenery.cpp \
    digger.cpp \
    imerald.cpp

HEADERS += \
    bigtheater.h \
    actor.h \
    scenery.h \
    digger.h \
    define.h \
    imerald.h

RESOURCES += \
    clothing.qrc
