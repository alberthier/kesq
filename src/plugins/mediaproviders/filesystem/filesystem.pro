
UI_DIR = ../../../../tmp/ui

MOC_DIR = ../../../../tmp/moc

OBJECTS_DIR = ../../../../tmp/obj

TEMPLATE = lib

CONFIG += dll \
 debug



TARGET = ../../../../dist/lib/kesq/plugins/mediaproviders/filesystem

SOURCES += FileSystem.cpp \
 FileSystemModel.cpp \
 MediaIconProvider.cpp

HEADERS += FileSystem.h \
 FileSystemModel.h \
 MediaIconProvider.h

QT += xml


CONFIG -= release

