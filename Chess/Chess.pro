TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    model/abstractfigure.cpp \
    logiccontroller.cpp

HEADERS += \
    model/abstractfigure.h \
    logiccontroller.h

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)
