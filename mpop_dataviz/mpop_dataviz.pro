

QT += core
QT += network
CONFIG += c++11
CONFIG -= qtquickcompiler
CONFIG += sdk_no_version_check # disable warning on macOS


# Main files:
INCLUDEPATH += $$PWD

SOURCES += \
    openglwindow.cpp \
    main.cpp \
    datavizwindow.cpp \
    sceneobject.cpp \
    layout.cpp \
    barchartlayout.cpp \
    prisonerline.cpp \
    controller.cpp

HEADERS += openglwindow.h \
    datavizwindow.h \
    sceneobject.h \
    layout.h \
    barchartlayout.h \
    prisonerline.h \
    controller.h


# OSC support:
INCLUDEPATH += $$PWD/../qosc
INCLUDEPATH += $$PWD/../qosc/contrib/packosc

SOURCES += \
    ../qosc/contrib/oscpack/OscOutboundPacketStream.cpp \
    ../qosc/contrib/oscpack/OscPrintReceivedElements.cpp \
    ../qosc/contrib/oscpack/OscReceivedElements.cpp \
    ../qosc/contrib/oscpack/OscTypes.cpp \
    ../qosc/oscreceiver.cpp \
    ../qosc/oscsender.cpp

HEADERS += \
    ../qosc/contrib/oscpack/MessageMappingOscPacketListener.h \
    ../qosc/contrib/oscpack/OscException.h \
    ../qosc/contrib/oscpack/OscHostEndianness.h \
    ../qosc/contrib/oscpack/OscOutboundPacketStream.h \
    ../qosc/contrib/oscpack/OscPacketListener.h \
    ../qosc/contrib/oscpack/OscPrintReceivedElements.h \
    ../qosc/contrib/oscpack/OscReceivedElements.h \
    ../qosc/contrib/oscpack/OscTypes.h \
    ../qosc/oscreceiver.h \
    ../qosc/oscsender.h

