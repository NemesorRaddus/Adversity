TEMPLATE = app

QT += qml quick
CONFIG += c++14

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-sources

SOURCES += main.cpp \
    hero.cpp \
    base.cpp \
    equipment.cpp \
    event.cpp \
    filereaderwriter.cpp \
    game.cpp

RESOURCES += \
    res.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    hero.h \
    base.h \
    equipment.h \
    event.h \
    filereaderwriter.h \
    game.h

DISTFILES += \
    android-sources/AndroidManifest.xml

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/'libs/RDesignPattern 1.0.4 Desktop MinGW 5.3.0 Qt 5.8/release/' -lRDesignPattern
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/'libs/RDesignPattern 1.0.4 Desktop MinGW 5.3.0 Qt 5.8/debug/' -lRDesignPattern

INCLUDEPATH += $$PWD/'libs/RDesignPattern 1.0.4 Desktop MinGW 5.3.0 Qt 5.8'
DEPENDPATH += $$PWD/'libs/RDesignPattern 1.0.4 Desktop MinGW 5.3.0 Qt 5.8'

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/'libs/RDesignPattern 1.0.4 Desktop MinGW 5.3.0 Qt 5.8/release/libRDesignPattern.a'
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/'libs/RDesignPattern 1.0.4 Desktop MinGW 5.3.0 Qt 5.8/debug/libRDesignPattern.a'
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/'libs/RDesignPattern 1.0.4 Desktop MinGW 5.3.0 Qt 5.8/release/RDesignPattern.lib'
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/'libs/RDesignPattern 1.0.4 Desktop MinGW 5.3.0 Qt 5.8/debug/RDesignPattern.lib'
