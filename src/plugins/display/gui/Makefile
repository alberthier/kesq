#############################################################################
# Makefile for building: libgui.so.1.0.0
# Generated by qmake (2.01a) (Qt 4.4.0) on: Fri May 23 00:09:09 2008
# Project:  gui.pro
# Template: lib
# Command: /usr/bin/qmake-qt4 -unix -o Makefile gui.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_XML_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -D_REENTRANT -Wall -W -fPIC $(DEFINES)
CXXFLAGS      = -pipe -g -D_REENTRANT -Wall -W -fPIC $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtUiTools -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtXml -I/usr/include/qt4/QtXml -I/usr/include/qt4 -I../../../../tmp/moc -I../../../../tmp/ui
LINK          = g++
LFLAGS        = -Wl,--no-undefined -shared -Wl,-soname,libgui.so.1
LIBS          = $(SUBLIBS)  -L/usr/lib -lQtXml -lQtGui -lQtCore -lQtUiTools -lpthread
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -sf
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ../../../../tmp/obj/

####### Files

SOURCES       = Gui.cpp ../../../../tmp/moc/moc_Gui.cpp
OBJECTS       = ../../../../tmp/obj/Gui.o \
		../../../../tmp/obj/moc_Gui.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/uitools.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/dll.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		gui.pro
QMAKE_TARGET  = gui
DESTDIR       = ../../../../dist/lib/kesq/plugins/display/
TARGET        = libgui.so.1.0.0
TARGETA       = ../../../../dist/lib/kesq/plugins/display/libgui.a
TARGETD       = libgui.so.1.0.0
TARGET0       = libgui.so
TARGET1       = libgui.so.1
TARGET2       = libgui.so.1.0

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile  ../../../../dist/lib/kesq/plugins/display/$(TARGET)

../../../../dist/lib/kesq/plugins/display/$(TARGET):  $(OBJECTS) $(SUBLIBS) $(OBJCOMP)  
	@$(CHK_DIR_EXISTS) ../../../../dist/lib/kesq/plugins/display/ || $(MKDIR) ../../../../dist/lib/kesq/plugins/display/ 
	-$(DEL_FILE) $(TARGET) $(TARGET0) $(TARGET1) $(TARGET2)
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS) $(OBJCOMP)
	-ln -s $(TARGET) $(TARGET0)
	-ln -s $(TARGET) $(TARGET1)
	-ln -s $(TARGET) $(TARGET2)
	-$(DEL_FILE) ../../../../dist/lib/kesq/plugins/display/$(TARGET)
	-$(DEL_FILE) ../../../../dist/lib/kesq/plugins/display/$(TARGET0)
	-$(DEL_FILE) ../../../../dist/lib/kesq/plugins/display/$(TARGET1)
	-$(DEL_FILE) ../../../../dist/lib/kesq/plugins/display/$(TARGET2)
	-$(MOVE) $(TARGET) $(TARGET0) $(TARGET1) $(TARGET2) ../../../../dist/lib/kesq/plugins/display/



staticlib: $(TARGETA)

$(TARGETA):  $(OBJECTS) $(OBJCOMP) 
	-$(DEL_FILE) $(TARGETA) 
	$(AR) $(TARGETA) $(OBJECTS)

Makefile: gui.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/uitools.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/dll.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/lib/libQtXml.prl \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtCore.prl \
		/usr/lib/libQtUiTools.prl
	$(QMAKE) -unix -o Makefile gui.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/uitools.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/dll.prf:
/usr/share/qt4/mkspecs/features/shared.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/lib/libQtXml.prl:
/usr/lib/libQtGui.prl:
/usr/lib/libQtCore.prl:
/usr/lib/libQtUiTools.prl:
qmake:  FORCE
	@$(QMAKE) -unix -o Makefile gui.pro

dist: 
	@$(CHK_DIR_EXISTS) ../../../../tmp/obj/gui1.0.0 || $(MKDIR) ../../../../tmp/obj/gui1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) ../../../../tmp/obj/gui1.0.0/ && $(COPY_FILE) --parents Gui.h ../../../../tmp/obj/gui1.0.0/ && $(COPY_FILE) --parents Gui.cpp ../../../../tmp/obj/gui1.0.0/ && (cd `dirname ../../../../tmp/obj/gui1.0.0` && $(TAR) gui1.0.0.tar gui1.0.0 && $(COMPRESS) gui1.0.0.tar) && $(MOVE) `dirname ../../../../tmp/obj/gui1.0.0`/gui1.0.0.tar.gz . && $(DEL_FILE) -r ../../../../tmp/obj/gui1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) ../../../../dist/lib/kesq/plugins/display/$(TARGET) 
	-$(DEL_FILE) ../../../../dist/lib/kesq/plugins/display/$(TARGET0) ../../../../dist/lib/kesq/plugins/display/$(TARGET1) ../../../../dist/lib/kesq/plugins/display/$(TARGET2) $(TARGETA)
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: ../../../../tmp/moc/moc_Gui.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) ../../../../tmp/moc/moc_Gui.cpp
../../../../tmp/moc/moc_Gui.cpp: Gui.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) Gui.h -o ../../../../tmp/moc/moc_Gui.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean 

####### Compile

../../../../tmp/obj/Gui.o: Gui.cpp Gui.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ../../../../tmp/obj/Gui.o Gui.cpp

../../../../tmp/obj/moc_Gui.o: ../../../../tmp/moc/moc_Gui.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ../../../../tmp/obj/moc_Gui.o ../../../../tmp/moc/moc_Gui.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

