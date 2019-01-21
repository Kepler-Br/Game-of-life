TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        *.cpp

HEADERS += \
        *.h

LIBS += -lSDL2 -lGL -lGLEW
