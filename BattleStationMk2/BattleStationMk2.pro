TEMPLATE = app

QT += qml quick serialport core widgets

SOURCES += main.cpp \
    serial.cpp \
    qmlbattlestationcontext.cpp \
    genericjoystick.cpp \
    xboxjoystick.cpp \
    inputhandler.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    serial.h \
    godheader.h \
    qmlbattlestationcontext.h \
    genericjoystick.h \
    xboxjoystick.h \
    inputhandler.h

win32 {

    INCLUDEPATH += $$PWD/../SDL/include
    DEPENDPATH += $$PWD/../SDL/include

    !contains(QMAKE_TARGET.arch, x86_64) {
        #x86 / 32-bit Windows define
        LIBS += -L$$PWD/../SDL/lib/x86/ -lSDL2
    } else {
        #x86_64 / 64-bit Window define
        LIBS += -L$$PWD/../SDL/lib/x64/ -lSDL2
    }
}

macx {
    INCLUDEPATH += $$PWD/../SDL/include
    INCLUDEPATH += -F/Library/Frameworks
    QMAKE_LFLAGS += -F/Library/Frameworks/ -framework SDL2

    CCFLAG += -std=c++11
}

#linux-g++ {
#    LIBS += -L$$PWD/../SDL/lib/x64/ -lSDL2
#    INCLUDEPATH += $$PWD/../SDL/include
#    DEPENDPATH += $$PWD/../SDL/include
#}
