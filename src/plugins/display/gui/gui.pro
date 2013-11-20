
UI_DIR = ../../../../tmp/ui

MOC_DIR = ../../../../tmp/moc

OBJECTS_DIR = ../../../../tmp/obj

TEMPLATE = lib

CONFIG += dll \
 uitools \
 debug


TARGET = ../../../../dist/lib/kesq/plugins/display/gui

HEADERS += Gui.h

SOURCES += Gui.cpp

QT += xml

CONFIG -= release

