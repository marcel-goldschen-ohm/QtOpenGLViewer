# Author: Marcel Paz Goldschen-Ohm
# Email: marcel.goldschen@gmail.com

# !!! Written for a MacOSX system. May need adjustment for another OS.
# Mac Xcode project generation:
# qmake -spec macx-xcode test.pro

TARGET = test
TEMPLATE = app
QT += core gui widgets opengl
CONFIG += c++11

# MACX application bundle
macx: CONFIG += app_bundle

# build dirs
#release: DESTDIR = Release
release: OBJECTS_DIR = Release/.obj
release: MOC_DIR = Release/.moc
release: RCC_DIR = Release/.rcc
release: UI_DIR = Release/.ui
#debug: DESTDIR = Debug
debug: OBJECTS_DIR = Debug/.obj
debug: MOC_DIR = Debug/.moc
debug: RCC_DIR = Debug/.rcc
debug: UI_DIR = Debug/.ui

# defines
debug: DEFINES += DEBUG
release: DEFINES += NDEBUG

HEADERS += test_QtOpenGLViewer.h
SOURCES += test_QtOpenGLViewer.cpp

HEADERS += ../QtOpenGLViewer.h
SOURCES += ../QtOpenGLViewer.cpp
