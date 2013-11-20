TEMPLATE = lib

CONFIG += dll \
 debug

QT -= gui

TARGET = ../../../../dist/lib/kesq/plugins/input/lirc

OBJECTS_DIR = ../../../../tmp/obj

UI_DIR = ../../../../tmp/ui

MOC_DIR = ../../../../tmp/moc

SOURCES += QlircInput.cpp \
Lirc.cpp
HEADERS += QlircInput.h \
Lirc.h
LIBS += -llirc_client

CONFIG -= release

