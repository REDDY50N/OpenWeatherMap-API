QT          -= gui
QT          += core network

CONFIG      += c++11 console

TEMPLATE    = app
TARGET      = owm_test
DESTDIR     =  $$PWD/bin


SOURCES += \
        main.cpp \
        weatherapi.cpp

HEADERS += \
        weatherapi.h

DISTFILES += \
        README.md \
        NOTES.md \
        LICENSE

