TEMPLATE = app

QT += qml quick
CONFIG += c++14

INCLUDEPATH += $$PWD/cpp/
CONFIG += object_parallel_to_source # so that o files generated from files with the same names don't replace each other

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-sources

android {
    QT += androidextras
}

SOURCES += cpp/main.cpp \
    cpp/assets_pool/assetspool.cpp \
    cpp/base/base.cpp \
    cpp/base/buildings/aetheritesilo.cpp \
    cpp/base/buildings/bar.cpp \
    cpp/base/buildings/barracks.cpp \
    cpp/base/buildings/building.cpp \
    cpp/base/buildings/centralunit.cpp \
    cpp/base/buildings/coolroom.cpp \
    cpp/base/buildings/dockingstation.cpp \
    cpp/base/buildings/enums.cpp \
    cpp/base/buildings/factory.cpp \
    cpp/base/buildings/gym.cpp \
    cpp/base/buildings/hospital.cpp \
    cpp/base/buildings/laboratory.cpp \
    cpp/base/buildings/playingfield.cpp \
    cpp/base/buildings/powerplant.cpp \
    cpp/base/buildings/seclusion.cpp \
    cpp/base/buildings/shrine.cpp \
    cpp/base/buildings/storageroom.cpp \
    cpp/base/buildings/trainingground.cpp \
    cpp/base/enums.cpp \
    cpp/clock/gameclock.cpp \
    cpp/clock/time.cpp \
    cpp/clock/timer_alarms/buildingupgrade.cpp \
    cpp/clock/timer_alarms/enums.cpp \
    cpp/clock/timer_alarms/missionend.cpp \
    cpp/clock/timer_alarms/timeralarm.cpp \
    cpp/clock/timeralarmscontainer.cpp \
    cpp/database/database.cpp \
    cpp/database/enums.cpp \
    cpp/equipment/enums.cpp \
    cpp/equipment/equipment.cpp \
    cpp/file_io/saves/saveparser.cpp \
    cpp/file_io/xml_files/xmlreader.cpp \
    cpp/general/appbuildinfo.cpp \
    cpp/general/game.cpp \
    cpp/general/globalutilities.cpp \
    cpp/general/randomizer.cpp \
    cpp/general/settings.cpp \
    cpp/h4x/h4x.cpp \
    cpp/logging/loggershandler.cpp \
    cpp/mercenaries/attributesset.cpp \
    cpp/mercenaries/enums.cpp \
    cpp/mercenaries/mercenariescontainer.cpp \
    cpp/mercenaries/mercenary.cpp \
    cpp/mercenaries/stressbordereffect.cpp \
    cpp/missions/encounter.cpp \
    cpp/missions/enums.cpp \
    cpp/missions/events/actionevents.cpp \
    cpp/missions/events/checkevents.cpp \
    cpp/missions/events/enums.cpp \
    cpp/missions/events/event.cpp \
    cpp/missions/events/otherevents.cpp \
    cpp/missions/events/value_scripts/expression.cpp \
    cpp/missions/events/value_scripts/valuerange.cpp \
    cpp/missions/land.cpp \
    cpp/missions/mission.cpp \
    cpp/qml_components/fpscounter.cpp \
    cpp/reports/basereports.cpp \
    cpp/reports/enums.cpp \
    cpp/reports/mercenaryreports.cpp \
    cpp/reports/missionreports.cpp \
    cpp/reports/report.cpp \
    cpp/reports/unifiedreport.cpp \
    cpp/translations/translations.cpp \
    cpp/general/savesmanager.cpp \
    cpp/file_io/saves/savedata.cpp

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
    cpp/assets_pool/assetspool.h \
    cpp/base/base.h \
    cpp/base/buildings/aetheritesilo.h \
    cpp/base/buildings/bar.h \
    cpp/base/buildings/barracks.h \
    cpp/base/buildings/building.h \
    cpp/base/buildings/centralunit.h \
    cpp/base/buildings/coolroom.h \
    cpp/base/buildings/dockingstation.h \
    cpp/base/buildings/enums.h \
    cpp/base/buildings/factory.h \
    cpp/base/buildings/gym.h \
    cpp/base/buildings/hospital.h \
    cpp/base/buildings/laboratory.h \
    cpp/base/buildings/playingfield.h \
    cpp/base/buildings/powerplant.h \
    cpp/base/buildings/seclusion.h \
    cpp/base/buildings/shrine.h \
    cpp/base/buildings/storageroom.h \
    cpp/base/buildings/trainingground.h \
    cpp/base/enums.h \
    cpp/clock/gameclock.h \
    cpp/clock/time.h \
    cpp/clock/timer_alarms/buildingupgrade.h \
    cpp/clock/timer_alarms/enums.h \
    cpp/clock/timer_alarms/missionend.h \
    cpp/clock/timer_alarms/timeralarm.h \
    cpp/clock/timeralarmscontainer.h \
    cpp/database/database.h \
    cpp/database/enums.h \
    cpp/equipment/enums.h \
    cpp/equipment/equipment.h \
    cpp/file_io/saves/saveparser.h \
    cpp/file_io/xml_files/xmlreader.h \
    cpp/general/appbuildinfo.h \
    cpp/general/game.h \
    cpp/general/globalutilities.h \
    cpp/general/randomizer.h \
    cpp/general/settings.h \
    cpp/h4x/h4x.h \
    cpp/logging/loggershandler.h \
    cpp/mercenaries/attributesset.h \
    cpp/mercenaries/enums.h \
    cpp/mercenaries/mercenariescontainer.h \
    cpp/mercenaries/mercenary.h \
    cpp/mercenaries/stressbordereffect.h \
    cpp/missions/encounter.h \
    cpp/missions/enums.h \
    cpp/missions/events/actionevents.h \
    cpp/missions/events/checkevents.h \
    cpp/missions/events/enums.h \
    cpp/missions/events/event.h \
    cpp/missions/events/otherevents.h \
    cpp/missions/events/value_scripts/expression.h \
    cpp/missions/events/value_scripts/valuerange.h \
    cpp/missions/land.h \
    cpp/missions/mission.h \
    cpp/qml_components/fpscounter.h \
    cpp/reports/basereports.h \
    cpp/reports/enums.h \
    cpp/reports/mercenaryreports.h \
    cpp/reports/missionreports.h \
    cpp/reports/report.h \
    cpp/reports/unifiedreport.h \
    cpp/stable.h \
    cpp/translations/translations.h \
    cpp/general/savesmanager.h \
    cpp/file_io/saves/savedata.h

PRECOMPILED_HEADER = cpp/stable.h

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
