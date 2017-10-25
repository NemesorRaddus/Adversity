#pragma once

#include <QString>
#include <QVector>

#include "base/buildings/dockingstation.h"
#include "clock/gameclock.h"
#include "clock/timer_alarms/buildingupgrade.h"
#include "clock/timer_alarms/missionend.h"
#include "database/database.h"
#include "mercenaries/mercenary.h"
#include "missions/events/event.h"
#include "missions/mission.h"
#include "reports/unifiedreport.h"

struct SaveData
{
    QString parserVersion;
    struct Overall
    {
        QString baseName;
        quint16 lastKnownDay;
        quint16 lastKnownHour;
        quint16 lastKnownMinute;
    } overall;
    struct Buildings
    {
        struct Levels
        {
            quint8 centralUnit;
            quint8 powerplant;
            quint8 factory;
            quint8 coolRoom;
            quint8 storageRoom;
            quint8 aetheriteSilo;
            quint8 hospital;
            quint8 barracks;
            quint8 dockingStation;
            quint8 trainingGround;
            quint8 gym;
            quint8 laboratory;
            quint8 playingField;
            quint8 bar;
            quint8 shrine;
            quint8 seclusion;
        } levels;
        struct CyclesSet
        {
            quint8 powerplant;
            quint8 factory;
        } cyclesSet;
        struct Upgrading
        {
            bool centralUnit;
            bool powerplant;
            bool factory;
            bool coolRoom;
            bool storageRoom;
            bool aetheriteSilo;
            bool hospital;
            bool barracks;
            bool dockingStation;
            bool trainingGround;
            bool gym;
            bool laboratory;
            bool playingField;
            bool bar;
            bool shrine;
            bool seclusion;
        } upgrading;
        struct Slots
        {
            QVector<QString> hospital;
            QVector<QPair<QString,quint8>> trainingGround;
            QVector<QPair<QString,quint8>> gym;
            QVector<QPair<QString,quint8>> laboratory;
            QVector<QString> playingField;
            QVector<QString> bar;
            QVector<QString> shrine;
            QVector<QString> seclusion;
        } mercenarySlots;
        struct DockingStationThings
        {
            QVector<QString> recruits;
            QVector<QPair<QString,quint8>> arrivingMercenaries;
            QVector<QPair<ActiveTransaction,quint8>> activeResourceTransactions;
            QVector<QString> equipments;
            QVector<QPair<QString,quint8>> arrivingEquipments;
        } dockingStationThings;
    } buildings;
    struct Resources
    {
        quint16 energy;
        quint16 buildingMaterials;
        quint16 foodSupplies;
        quint16 aetheriteOre;
    } resources;
    struct Alarms
    {
        QVector<QPair<quint8,BuildingUpgradeTimerAlarm>> buildingUpgrades;
        QVector<QPair<quint8,MissionEndTimerAlarm>> missionEnds;
        QVector<QPair<Time,QString>> missionAlarms;
    } alarms;
    struct Mercenaries
    {
        QVector<MercenaryDataHelper> hiredMercenaries;
    } mercenaries;
    struct Equipments
    {
        QVector<QString> freeArmor;
        QVector<QString> freeWeaponsTools;
    } equipments;
    struct Database
    {
        DatabaseUnlocksInfo unlocks;
        bool areThereNewDBEntries;
    } database;
    struct Missions
    {
        QVector<MissionDataHelper> missions;
        QVector<UnifiedReportDataHelper> reports;
    } missions;
    QByteArray raw;
};
