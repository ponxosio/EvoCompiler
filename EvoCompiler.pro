#-------------------------------------------------
#
# Project created by QtCreator 2016-10-03T12:31:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EvoCompiler
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc

INCLUDEPATH += X:/boost_1_61_0
INCLUDEPATH += X:/EvoCoreLibrary/include
INCLUDEPATH += X:/EvoCoreLibrary/external
INCLUDEPATH += C:/Python27/include

LIBS += -L$$quote(X:\boost_1_61_0\stage\lib) -lboost_python-vc140-mt-1_61
LIBS += -L$$quote(C:\Python27\libs)
LIBS += -L$$quote(X:\EvoCoreLibrary\lib) -lEvoCoderCore
