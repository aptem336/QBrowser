#-------------------------------------------------
#
# Project created by QtCreator 2017-09-15T15:52:13
#
#-------------------------------------------------

QT += core gui webkitwidgets
CONFIG += c++11 strict_c++
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mybrowser
TEMPLATE = app

SOURCES += main.cpp\
    urllineedit.cpp \
    htmlhighlighter.cpp \
    popupmenu.cpp \
    mysettings.cpp \
    mymainwindow.cpp \
    tabpanel.cpp \
    mybutton.cpp

HEADERS  += \
    urllineedit.h \
    htmlhighlighter.h \
    popupmenu.h \
    mysettings.h \
    mymainwindow.h \
    tabpanel.h \
    mybutton.h

TRANSLATIONS += lang_ru.ts

RESOURCES += \
    myresources.qrc
