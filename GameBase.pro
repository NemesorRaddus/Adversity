TEMPLATE = app

QT += qml quick
CONFIG += c++14

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-sources

android {
    QT += androidextras
}

SOURCES += main.cpp \
    mercenary.cpp \
    base.cpp \
    equipment.cpp \
    event.cpp \
    filereaderwriter.cpp \
    game.cpp \
    timer.cpp \
    saveparser.cpp \
    assetspool.cpp \
    translations.cpp \
    h4x.cpp \
    fpscounter.cpp \
    database.cpp

RESOURCES += \
    qmlfiles.qrc \
    locales.qrc \
    dataassets.qrc \
    otherres.qrc \
    graphics_mercs.qrc \
    graphics_buildings.qrc \
    graphics_other.qrc \
    graphics_gui.qrc \
    graphics_equipments.qrc \
    graphics_missions.qrc \
    graphics_database.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    mercenary.h \
    base.h \
    equipment.h \
    event.h \
    filereaderwriter.h \
    game.h \
    timer.h \
    saveparser.h \
    assetspool.h \
    translations.h \
    h4x.h \
    fpscounter.h \
    stable.h \
    database.h

PRECOMPILED_HEADER = stable.h

DISTFILES += \
    android-sources/AndroidManifest.xml \
    android-sources/build.gradle \
    android-sources/src/org/qtproject/qt5/android/bindings/MyActivity.java \
    versionnumber.txt \
    save.txt \
    Gra-spis.rtf \
    qml/H4XWindow.qml

#APeR lib
SOURCES += libs/APeR-0.1.0/aper.cpp
HEADERS += libs/APeR-0.1.0/aper.h

CONFIG(release, debug|release) {
    #This is a release build
    DEFINES += QT_NO_DEBUG_OUTPUT
} else {
    #This is a debug build
    win32 {
        DEFINES += ENABLE_CONSOLE_WINDOW
    }
}
