TEMPLATE = app

CONFIG += c++11

QT += qml quick widgets

SOURCES += main.cpp \
    model/abstractfigure.cpp \
    logiccontroller.cpp \
    chessmove.cpp

HEADERS += \
    model/abstractfigure.h \
    logiccontroller.h \
    chessmove.h \
    model/defines.h

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)
