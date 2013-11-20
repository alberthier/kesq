
UI_DIR = ../../../../tmp/ui

MOC_DIR = ../../../../tmp/moc

OBJECTS_DIR = ../../../../tmp/obj

TEMPLATE = lib

CONFIG += dll \
 debug


SOURCES += Keyboard.cpp

HEADERS += Keyboard.h

TARGET = ../../../../dist/lib/kesq/plugins/input/keyboard

CONFIG -= release

