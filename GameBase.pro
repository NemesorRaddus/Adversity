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
    game.cpp \
    timer.cpp \
    saveparser.cpp

RESOURCES += \
    res.qrc \
    assets.qrc \
    qmlfiles.qrc

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
    game.h \
    timer.h \
    saveparser.h

DISTFILES += \
    android-sources/AndroidManifest.xml

CONFIG(release, debug|release) {
    #This is a release build
    DEFINES += QT_NO_DEBUG_OUTPUT
} else {
    #This is a debug build
}
