#-------------------------------------------------
#
# Project created by QtCreator 2017-12-13T20:24:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Sculptura
TEMPLATE = app

#PCL
INCLUDEPATH += "C:\Program Files\PCL 1.8.0\include\pcl-1.8"
INCLUDEPATH += "C:\Program Files\PCL 1.8.0\3rdParty\VTK\include\vtk-7.0"
INCLUDEPATH += "C:\Program Files\PCL 1.8.0\3rdParty\Boost\include\boost-1_61"
INCLUDEPATH += "C:\Program Files\PCL 1.8.0\3rdParty\Qhull\include"
INCLUDEPATH += "C:\Program Files\PCL 1.8.0\3rdParty\FLANN\include"
INCLUDEPATH += "C:\Program Files\PCL 1.8.0\3rdParty\Eigen\eigen3"
INCLUDEPATH += "C:\Program Files\Microsoft SDKs\Kinect\v2.0_1409\inc"
INCLUDEPATH += "C:\Program Files\OpenNI2\Include"
INCLUDEPATH += "C:\Program Files (x86)\Windows Kits\10\Include\10.0.10240.0\um"
INCLUDEPATH += "C:\Program Files (x86)\Windows Kits\10\Include\10.0.10240.0\shared"
INCLUDEPATH += "C:/Program Files (x86)/Windows Kits/10/Include/10.0.10240.0/ucrt"

LIBS += "-LC:\Program Files\PCL 1.8.0\lib"
LIBS += "-LC:\Program Files\PCL 1.8.0\3rdParty\VTK\lib"
LIBS += "-LC:\Program Files\PCL 1.8.0\3rdParty\Qhull\lib"
LIBS += "-LC:\Program Files\PCL 1.8.0\3rdParty\FLANN\lib"
LIBS += "-LC:\Program Files\PCL 1.8.0\3rdParty\Boost\lib"

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
