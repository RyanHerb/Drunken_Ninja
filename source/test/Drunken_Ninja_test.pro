TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
unix : QMAKE_CXXFLAGS += -std=c++11

release:DESTDIR = release
debug:DESTDIR = debug

include(../model/model.pri)
INCLUDEPATH += src
SOURCES += src/main.cpp
HEADERS += src/main.hpp
