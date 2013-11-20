TEMPLATE = lib

CONFIG += dll \
 debug

QT -= gui

QT += xml

OBJECTS_DIR = ../../../../tmp/obj

UI_DIR = ../../../../tmp/ui

MOC_DIR = ../../../../tmp/moc

SOURCES += System.cpp

HEADERS += System.h

TARGET = ../../../../dist/lib/kesq/plugins/mediahandlers/system

CONFIG -= release

