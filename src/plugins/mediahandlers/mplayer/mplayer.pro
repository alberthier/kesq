TEMPLATE = lib

CONFIG += dll \
 debug

TARGET = ../../../../dist/lib/kesq/plugins/mediahandlers/mplayer

OBJECTS_DIR = ../../../../tmp/obj

UI_DIR = ../../../../tmp/ui

MOC_DIR = ../../../../tmp/moc

HEADERS += MPlayer.h

SOURCES += MPlayer.cpp


QT += xml

CONFIG -= release

