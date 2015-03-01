#-------------------------------------------------
#
# Project created by QtCreator 2015-01-25T15:04:06
#
#-------------------------------------------------

QT       += core gui xml multimedia printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ElapsedTime
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    pastwindow.cpp \
    setttings.cpp

HEADERS  += mainwindow.h \
    pastwindow.h \
    setttings.h

FORMS    += mainwindow.ui \
    pastwindow.ui \
    setttings.ui

RESOURCES += \
    Res.qrc

RC_ICONS=res/icon.ico
