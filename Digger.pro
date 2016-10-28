QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Digger
TEMPLATE = app

# Input
SOURCES += \
    main.cpp \
    bigtheater.cpp \
    actor.cpp

HEADERS += \
    bigtheater.h \
    actor.h

RESOURCES += \
    clothing.qrc
