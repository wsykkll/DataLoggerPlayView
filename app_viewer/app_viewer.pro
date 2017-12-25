# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = app
TARGET = app_viewer
DESTDIR = ../Win32/Release
QT += core xml opengl widgets gui
CONFIG += release
DEFINES += WIN64 QT_DLL QT_OPENGL_LIB QT_WIDGETS_LIB QT_XML_LIB
INCLUDEPATH += ../../../../../../cmake/libQGLViewer-2.6.3/QGLViewer \
    ../../../../../../wsy/OpenCV-2.1.0/build/include \
    ./../header_msg \
    ../../../../../../cmake/boost_1_60_0 \
    ./GeneratedFiles \
    . \
    ./GeneratedFiles/Release
LIBS += -L"./CoordinateTrans" \
    -L"../../../../../../wsy/OpenCV-2.1.0/build/lib" \
    -L"./libjpeg" \
    -L"../../../../../../cmake/boost_1_60_0/stage/lib" \
    -lopengl32 \
    -lglu32 \
    -lC:/msys32/mingw32/lib/libglib-2.0.dll.a \
    -llcm \
    -lcv210 \
    -lcxcore210 \
    -lhighgui210 \
    -lQGLViewer2 \
    -llib3ds \
    -llibjpeg \
    -lCoordinateTrans
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/release
OBJECTS_DIR += release
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(app_viewer.pri)
