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
    cpp/base/buildings/building.cpp \
    cpp/base/buildings/enums.cpp \
    cpp/base/buildings/levelsinfo.cpp \
    cpp/base/buildings/specific/destressing/bar.cpp \
    cpp/base/buildings/specific/destressing/playingfield.cpp \
    cpp/base/buildings/specific/destressing/seclusion.cpp \
    cpp/base/buildings/specific/destressing/shrine.cpp \
    cpp/base/buildings/specific/other/barracks.cpp \
    cpp/base/buildings/specific/other/centralunit.cpp \
    cpp/base/buildings/specific/other/dockingstation.cpp \
    cpp/base/buildings/specific/other/hospital.cpp \
    cpp/base/buildings/specific/production/factory.cpp \
    cpp/base/buildings/specific/production/powerplant.cpp \
    cpp/base/buildings/specific/storage/aetheritesilo.cpp \
    cpp/base/buildings/specific/storage/coolroom.cpp \
    cpp/base/buildings/specific/storage/storageroom.cpp \
    cpp/base/buildings/specific/training/gym.cpp \
    cpp/base/buildings/specific/training/laboratory.cpp \
    cpp/base/buildings/specific/training/trainingground.cpp \
    cpp/base/buildings/upgraderequirements.cpp \
    cpp/base/enums.cpp \
    cpp/base/managers/basemanagerinterface.cpp \
    cpp/base/managers/buildingsmanager.cpp \
    cpp/base/managers/equipmentmanager.cpp \
    cpp/base/managers/mercenariesmanager.cpp \
    cpp/base/managers/missionsmanager.cpp \
    cpp/base/managers/reportsmanager.cpp \
    cpp/base/managers/resourcesmanager.cpp \
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
    cpp/file_io/saves/savedata.cpp \
    cpp/file_io/saves/saveparser.cpp \
    cpp/file_io/xml_files/readers/buildingsreader.cpp \
    cpp/file_io/xml_files/readers/mercenariesreader.cpp \
    cpp/file_io/xml_files/readers/miscreader.cpp \
    cpp/file_io/xml_files/readers/missionsreader.cpp \
    cpp/file_io/xml_files/readers/xmlfilereaderbase.cpp \
    cpp/file_io/xml_files/xmlreader.cpp \
    cpp/general/appbuildinfo.cpp \
    cpp/general/game.cpp \
    cpp/general/globalutilities.cpp \
    cpp/general/randomizer.cpp \
    cpp/general/savesmanager.cpp \
    cpp/general/settings.cpp \
    cpp/h4x/h4x.cpp \
    cpp/logging/loggerabstraction.cpp \
    cpp/logging/loggershandler.cpp \
    cpp/logging/loggersprovider.cpp \
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
    cpp/translations/translations.cpp

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

HEADERS += \
    cpp/assets_pool/assetspool.h \
    cpp/base/base.h \
    cpp/base/buildings/building.h \
    cpp/base/buildings/enums.h \
    cpp/base/buildings/levelsinfo.h \
    cpp/base/buildings/specific/destressing/bar.h \
    cpp/base/buildings/specific/destressing/playingfield.h \
    cpp/base/buildings/specific/destressing/seclusion.h \
    cpp/base/buildings/specific/destressing/shrine.h \
    cpp/base/buildings/specific/other/barracks.h \
    cpp/base/buildings/specific/other/centralunit.h \
    cpp/base/buildings/specific/other/dockingstation.h \
    cpp/base/buildings/specific/other/hospital.h \
    cpp/base/buildings/specific/production/factory.h \
    cpp/base/buildings/specific/production/powerplant.h \
    cpp/base/buildings/specific/storage/aetheritesilo.h \
    cpp/base/buildings/specific/storage/coolroom.h \
    cpp/base/buildings/specific/storage/storageroom.h \
    cpp/base/buildings/specific/training/gym.h \
    cpp/base/buildings/specific/training/laboratory.h \
    cpp/base/buildings/specific/training/trainingground.h \
    cpp/base/buildings/upgraderequirements.h \
    cpp/base/enums.h \
    cpp/base/managers/basemanagerinterface.h \
    cpp/base/managers/buildingsmanager.h \
    cpp/base/managers/equipmentmanager.h \
    cpp/base/managers/mercenariesmanager.h \
    cpp/base/managers/missionsmanager.h \
    cpp/base/managers/reportsmanager.h \
    cpp/base/managers/resourcesmanager.h \
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
    cpp/file_io/saves/savedata.h \
    cpp/file_io/saves/saveparser.h \
    cpp/file_io/xml_files/readers/buildingsreader.h \
    cpp/file_io/xml_files/readers/mercenariesreader.h \
    cpp/file_io/xml_files/readers/miscreader.h \
    cpp/file_io/xml_files/readers/missionsreader.h \
    cpp/file_io/xml_files/readers/xmlfilereaderbase.h \
    cpp/file_io/xml_files/xmlreader.h \
    cpp/general/appbuildinfo.h \
    cpp/general/game.h \
    cpp/general/globalutilities.h \
    cpp/general/randomizer.h \
    cpp/general/savesmanager.h \
    cpp/general/settings.h \
    cpp/h4x/h4x.h \
    cpp/logging/loggerabstraction.h \
    cpp/logging/loggershandler.h \
    cpp/logging/loggersprovider.h \
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
    cpp/translations/translations.h

PRECOMPILED_HEADER = cpp/stable.h

OTHER_FILES += \
    android-sources/AndroidManifest.xml \
    android-sources/build.gradle \
    android-sources/src/org/qtproject/qt5/android/bindings/MyActivity.java \
    doc/Gra-spis.rtf \
    doc/nazewnictwo.odt \
    doc/versioning.txt \
    qml/H4XWindow.qml \
    save.txt \
    versionnumber.txt

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
