TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += src

SOURCES += \
            src/main.cpp \
    src/node.cpp \
    src/graphgen.cpp \
    src/graph.cpp

HEADERS += \
    src/node.hpp \
    src/graphgen.hpp \
    src/graph.hpp
