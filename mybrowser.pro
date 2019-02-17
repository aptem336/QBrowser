QT += core gui webkitwidgets
CONFIG += c++11 strict_c++
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mybrowser
TEMPLATE = app

SOURCES += main.cpp\
    mysettings.cpp \
    mymainwindow.cpp

HEADERS  += \
    mysettings.h \
    mymainwindow.h

TRANSLATIONS += lang_ru.ts

RESOURCES += \
    myresources.qrc
