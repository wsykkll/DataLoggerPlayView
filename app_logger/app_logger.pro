# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Add-in.
# ------------------------------------------------------

TEMPLATE = app
TARGET = app_logger
DESTDIR = ../Win32/Release
QT += core widgets gui
CONFIG += release
DEFINES += WIN64 QT_DLL QT_WIDGETS_LIB
INCLUDEPATH += ../../../../../../cmake/boost_1_60_0 \
    ./../header_msg \
    ./GeneratedFiles \
    . \
    ./GeneratedFiles/Release
LIBS += -L"../../../../../../cmake/boost_1_60_0/stage/lib" \
    -lC:/msys32/mingw32/lib/libglib-2.0.dll.a \
    -lC:/msys32/mingw32/lib/libgthread-2.0.dll.a \
    -llcm
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/release
OBJECTS_DIR += release
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles
include(app_logger.pri)
