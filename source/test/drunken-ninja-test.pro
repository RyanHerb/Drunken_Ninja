TEMPLATE = app
TARGET = drunken-ninja-test

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
unix : QMAKE_CXXFLAGS += -std=c++11

DESTDIR = bin

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui

include(../model/model.pri)
INCLUDEPATH += src
SOURCES += src/main.cpp
HEADERS += src/main.hpp src/rlutil.h
