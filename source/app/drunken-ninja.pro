TEMPLATE = app
TARGET = drunken-ninja

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += debug
unix : QMAKE_CXXFLAGS += -std=c++11

debug:DESTDIR = bin/debug
release:DESTDIR = bin/release

CONFIG(debug, debug|release) {
    DESTDIR = bin/debug
}
CONFIG(release, debug|release) {
    DESTDIR = bin/release
}

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui

include(../model/model.pri)
SOURCES += main.cpp
HEADERS += config.h
