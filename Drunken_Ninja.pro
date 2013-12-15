TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
unix : QMAKE_CXXFLAGS += -std=c++11

release:DESTDIR = release
debug:DESTDIR = debug

INCLUDEPATH += src

SOURCES += \
    src/main.cpp \
    src/node.cpp \
    src/graph.cpp \
    src/tree.cpp \
    src/smallcovergraph.cpp \
    src/graphutils.cpp \
    src/edge.cpp \
    src/bipartitegraph.cpp \
    src/minisatconverter.cpp

HEADERS += \
    src/node.hpp \
    src/graph.hpp \
    src/tree.hpp \
    src/smallcovergraph.hpp \
    src/graphutils.hpp \
    src/edge.hpp \
    src/bipartitegraph.hpp \
    src/minisatconverter.hpp \
    src/config.h
