TEMPLATE = lib

CONFIG += dll \
 debug

QT += xml

TARGET = ../../../../dist/lib/kesq/plugins/mediaproviders/staticlist

UI_DIR = ../../../../tmp/ui

MOC_DIR = ../../../../tmp/moc

OBJECTS_DIR = ../../../../tmp/obj

HEADERS += StaticList.h

SOURCES += StaticList.cpp

CONFIG -= release

