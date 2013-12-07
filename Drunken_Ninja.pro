TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

release:DESTDIR = release
debug:DESTDIR = debug

INCLUDEPATH += src

SOURCES += \
            src/main.cpp \
    src/node.cpp \
    src/graph.cpp \
    src/tree.cpp \
    src/bipartiteGraph.cpp \
    src/smallcovergraph.cpp \
    src/graphutils.cpp

HEADERS += \
    src/node.hpp \
    src/graph.hpp \
    src/tree.hpp \
    src/bipartiteGraph.hpp \
    src/smallcovergraph.hpp \
    src/graphutils.hpp
