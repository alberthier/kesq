TEMPLATE = lib

CONFIG += dll \
debug
TARGET = ../../../../dist/lib/kesq/plugins/mediahandlers/mpd

CONFIG -= release

QT -= gui

QT += xml

OBJECTS_DIR = ../../../../tmp/obj

MOC_DIR = ../../../../tmp/moc

UI_DIR = ../../../../tmp/ui

HEADERS += Mpd.h

SOURCES += Mpd.cpp

LIBS += -lmpd

