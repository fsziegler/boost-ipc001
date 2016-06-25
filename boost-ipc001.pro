#-------------------------------------------------
#
# Project created by QtCreator 2016-06-24T23:10:02
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = boost-ipc001
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../usr/lib/i386-linux-gnu/release/ -lboost_program_options
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../usr/lib/i386-linux-gnu/debug/ -lboost_program_options
else:unix: LIBS += -L$$PWD/../../../../../usr/lib/i386-linux-gnu/ -lboost_program_options

INCLUDEPATH += $$PWD/../../../../../usr/include/boost
DEPENDPATH += $$PWD/../../../../../usr/include/boost

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../usr/lib/i386-linux-gnu/release/libboost_program_options.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../usr/lib/i386-linux-gnu/debug/libboost_program_options.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../usr/lib/i386-linux-gnu/release/boost_program_options.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../../../usr/lib/i386-linux-gnu/debug/boost_program_options.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../../../usr/lib/i386-linux-gnu/libboost_program_options.a

QMAKE_POST_LINK += pwd;
QMAKE_POST_LINK += ../boost-ipc001/ziegversion.sh
