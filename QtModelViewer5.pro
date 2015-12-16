# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = app
TARGET = QtModelViewer5
DESTDIR = ../Win32/Debug
QT += core network opengl widgets gui
CONFIG += debug console
DEFINES += QT_DLL QT_OPENGL_LIB QT_WIDGETS_LIB _USE_MATH_DEFINES%(PreprocessorDefinitions) QT_NETWORK_LIB $(NOINHERIT)
INCLUDEPATH += ./IL \
    ./sdl \
    ./TUIO \
    ./oscpack \
    ./GeneratedFiles \
    . \
    ./GeneratedFiles/Debug \
    $(QTDIR)/../qt3d/include/Qt3D \
    $(QTDIR)/../qt3d/include
LIBS += -lopengl32 \
    -lDevIL \
    -lILU \
    -lILUT \
    -lglu32 \
    -lassimp \
    -lws2_32 \
    -lWINMM.LIB
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/debug
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(QtModelViewer5.pri)
win32:RC_FILE = QtModelViewer5.rc