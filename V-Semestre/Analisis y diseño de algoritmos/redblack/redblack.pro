#-------------------------------------------------
#
# Project created by QtCreator 2014-10-14T13:31:22
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = redblack
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp

HEADERS += \
    Node.h \
    RB_Tree.h
