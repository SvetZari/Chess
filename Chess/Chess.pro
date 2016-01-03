TEMPLATE = app

CONFIG += c++11

QT += qml quick widgets

SOURCES += main.cpp \
    model/abstractfigure.cpp \
    model/chessmove.cpp \
    logiccontroller.cpp

HEADERS += \
    model/abstractfigure.h \
    model/chessmove.h \
    logiccontroller.h \
    defines.h

RESOURCES += qml.qrc

QMAKE_MAC_SDK = macosx10.11

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)
