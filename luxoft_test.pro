TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    config_parser.cpp \
    threads.cpp

HEADERS += \
    config_parser.h \
    thread_base.h \
    threads.h \
    typedefs.h

DISTFILES += \
    README.md
