#-------------------------------------------------
#
# Project created by QtCreator 2017-12-13T20:24:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sculptura
TEMPLATE = app
#OPENCV AND OPENNI INCLUDE PATH
INCLUDEPATH  += "C:\opencv\build\include"
INCLUDEPATH += "C:\Program Files\OpenNI2\Include"
INCLUDEPATH += "C:\Program Files\OpenNI2\Tools"



DLLDESTDIR += "C:\Program Files\OpenNI2\Tools\OpenNI2\Drivers"


LIBS += "C:\Program Files\OpenNI2\Lib\*.lib"
LIBS += "C:\opencv\build\x64\vc14\lib\*.lib"


SOURCES += main.cpp\
        mainwindow.cpp \
    advanced_scanning.cpp \
    camerapreview.cpp

HEADERS  += mainwindow.h \
    advanced_scanning.h \
    camerapreview.h


FORMS    += mainwindow.ui \
    advanced_scanning.ui

RESOURCES += \
    icons.qrc
