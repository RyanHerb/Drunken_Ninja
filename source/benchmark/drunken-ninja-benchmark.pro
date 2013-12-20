TEMPLATE = app
TARGET = drunken-ninja-benchmark
CONFIG += debug

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

SOURCES += \
    hayai/hayai_posix_main.cpp \
    src/tree/tree_getcover_200.cpp \
    src/tree/tree_getcover_400.cpp \
    src/tree/tree_getcover_800.cpp \
    src/smallcovergraph/smallcovergraph_getcoverfpt_200.cpp

HEADERS += \
    hayai/hayai.hpp \
    hayai/hayai_benchmarker.hpp \
    hayai/hayai_console.hpp \
    hayai/hayai_console_outputter.hpp \
    hayai/hayai_default_test_factory.hpp \
    hayai/hayai_fixture.hpp \
    hayai/hayai_outputter.hpp \
    hayai/hayai_test.hpp \
    hayai/hayai_test_descriptor.hpp \
    hayai/hayai_test_factory.hpp
    hayai/hayai_test_result.hpp

unix {
    QMAKE_CXXFLAGS += -std=c++11
}
