TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    node.cpp \
    temporal_ds.cpp

HEADERS += \
    node.h \
    temporal_ds.h
