
UI_DIR = ../../../../tmp/ui

MOC_DIR = ../../../../tmp/moc

OBJECTS_DIR = ../../../../tmp/obj

TEMPLATE = lib

CONFIG += dll \
 debug


SOURCES += Mouse.cpp

HEADERS += Mouse.h

TARGET = ../../../../dist/lib/kesq/plugins/input/mouse

CONFIG -= release

