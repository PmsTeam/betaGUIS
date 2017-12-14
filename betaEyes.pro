#-------------------------------------------------
#
# Project created by QtCreator 2017-11-28T10:43:03
#
#-------------------------------------------------

QT       += core gui\
            multimedia\
            multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = betaEyes
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    home.cpp \
    home_analysis.cpp \
    home.cpp \
    home_analysis.cpp \
    main.cpp \
    mainwindow.cpp \
    mytitlebar.cpp

HEADERS += \
        mainwindow.h \
    home.h \
    home_analysis.h \
    home.h \
    home_analysis.h \
    mainwindow.h \
    mytitlebar.h

FORMS += \
        mainwindow.ui \
    home.ui \
    home_analysis.ui

DISTFILES += \
    style.qss \
    res/icon.ico \
    res/qtdemo.rc

RC_FILE = res/qtdemo.rc
