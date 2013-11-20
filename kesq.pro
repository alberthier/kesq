SUBDIRS += src/core \
 src/plugins/display/gui \
 src/plugins/input/keyboard \
 src/plugins/input/mouse \
 src/plugins/mediaproviders/filesystem \
 src/plugins/mediahandlers/mplayer \
 src/plugins/mediaproviders/staticlist \
 src/plugins/mediahandlers/system \
 src/plugins/input/lirc \
 src/plugins/mediahandlers/mpd
TEMPLATE = subdirs 
CONFIG += warn_on \
          qt \
          thread 
