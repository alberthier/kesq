SOURCES += main.cpp \
 plugins/input/Keyboard.cpp \
 plugins/input/Mouse.cpp
TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt
TARGET = ../bin/kesq


HEADERS += plugins/input/Keyboard.h \
 plugins/input/Mouse.h

