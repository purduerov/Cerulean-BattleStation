TEMPLATE = app

QT += qml quick serialport core widgets

SOURCES += main.cpp \
    mainticker.cpp \
    battlestation.cpp \
    threadcontroller.cpp \
    joystick.cpp \
    serial.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    tickclock.h \
    mainticker.h \
    battlestation.h \
    threadcontroller.h \
    joystick.h \
    serial.h

unix:!macx|win32: LIBS += -L$$PWD/../SDL/lib/x86/ -lSDL2

INCLUDEPATH += $$PWD/../SDL/include
DEPENDPATH += $$PWD/../SDL/include