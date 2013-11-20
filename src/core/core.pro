
TEMPLATE = app


OBJECTS_DIR = ../../tmp/obj

UI_DIR = ../../tmp/ui

MOC_DIR = ../../tmp/moc


SOURCES += main.cpp \
Input.cpp \
PluginPool.cpp \
 Display.cpp \
 Plugin.cpp \
 MediaHandler.cpp \
 MediaProvider.cpp \
 Dispatcher.cpp
TARGET = ../../dist/bin/kesq

HEADERS += Input.h \
PluginPool.h \
 Display.h \
 Plugin.h \
 MediaHandler.h \
 MediaProvider.h \
 Dispatcher.h \
 Definitions.h
QT += xml

CONFIG -= release

CONFIG += debug

