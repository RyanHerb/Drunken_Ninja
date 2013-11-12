TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += src

SOURCES += \
            src/main.cpp \
    src/node.cpp \
    src/graph.cpp \
    src/tree.cpp \
    src/bipartiteGraph.cpp \
    src/smallcovergraph.cpp

HEADERS += \
    src/node.hpp \
    src/graph.hpp \
    src/tree.hpp \
    src/bipartiteGraph.hpp \
    src/smallcovergraph.hpp
