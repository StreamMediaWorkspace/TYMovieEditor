QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS += -std=c++0x -pthread
LIBS += -pthread


INCLUDEPATH += "./include"
INCLUDEPATH += "./include/libopenshot"
INCLUDEPATH += "./include/libopenshot/Qt"
INCLUDEPATH += "./include/libopenshot-audio"


win32{
    #DEFINES += _WIN32_WINNT=0x600
    INCLUDEPATH += "D:/project/msys32/mingw32/i686-w64-mingw32/include"

    CONFIG(debug, debug|release){
        LIBS += $$PWD/lib/Debug/libopenshot-audio.dll.a
        LIBS += $$PWD/lib/Debug/libopenshot.dll.a
    } else{
        LIBS += $$PWD/lib/Release/libopenshot-audio.dll.a
        LIBS += $$PWD/lib/Release/libopenshot.dll.a
    }
}

mac{
    INCLUDEPATH += $$PWD/include/mac/zmq
    INCLUDEPATH += /usr/local/include
    INCLUDEPATH += /usr/local/Cellar/jsoncpp/1.9.1/include

    CONFIG(debug, debug|release) {
        LIBS += $$PWD/lib/Release/libopenshot-audio.dylib
        LIBS += $$PWD/lib/Release/libopenshot.dylib
    } else {
        LIBS += $$PWD/lib/Release/libopenshot-audio.dylib
        LIBS += $$PWD/lib/Release/libopenshot.dylib
    }
}

SOURCES += \
    PlayerDemo.cpp \
    mainwindow.cpp \
    main.cpp \
    jsoncpp.cpp \

HEADERS += \
    mainwindow.h \
    ./include/libopenshot/Qt/PlayerDemo.h \
    ./include/json/json.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
