#-------------------------------------------------
#
# Project created by QtCreator 2013-11-13T13:17:10
#
#-------------------------------------------------

QT       += core gui
QT += network
QT += xml
QT += xmlpatterns
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QHoldemClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    src_gfx/graphicsscene.cpp \
    src_gfx/cardpixmap.cpp \
    src_threads/checkerthread.cpp \
    src_network/networkthread.cpp \
    src_ui/betcontrols.cpp \
    src_gfx/textitem.cpp \
    src_gfx/rectitem.cpp

HEADERS  += mainwindow.h \
    src_headers/toplevel.h \
    src_gfx/graphicsscene.h \
    src_gfx/gfx.h \
    src_gfx/cardpixmap.h \
    src_threads/checkerthread.h \
    src_threads/threads.h \
    src_network/networkthread.h \
    src_network/network.h \
    src_ui/betcontrols.h \
    src_gfx/textitem.h \
    src_gfx/rectitem.h

RESOURCES += \
    src_resources/cards.qrc

FORMS += \
    src_ui/betcontrols.ui
