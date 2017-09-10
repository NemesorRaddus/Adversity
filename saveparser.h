#ifndef SAVEPARSER_H
#define SAVEPARSER_H

//File generated using Raddus Binary Data Parser Generator v1.0.1 Beta

#include <QDataStream>
#include <QFile>

#include <QString>
#include <QDateTime>
#include <QVector>

#include "database.h"

#include <QDebug>

class BuildingUpgradeTimerAlarm;
class MissionEndTimerAlarm;
struct HeroDataHelper;
class Equipment;
struct ActiveTransaction;
struct MissionDataHelper;
struct Time;

struct SaveData
{
    QString parserVersion;
    struct Overall
    {
        QString baseName;
        QDateTime lastKnownDate;
        quint16 lastKnownDay;
        quint16 lastKnownHour;
        quint16 lastKnownMinute;
        bool freezeGameProgress;
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
        } heroSlots;
        struct DockingStationThings
        {
            QVector<QString> recruits;
            QVector<QPair<QString,quint8>> arrivingHeroes;
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
    struct Heroes
    {
        QVector<HeroDataHelper> hiredHeroes;
    } heroes;
    struct Equipments
    {
        QVector<QString> freeArmor;
        QVector<QString> freeWeaponsTools;
    } equipments;
    struct Database
    {
        DatabaseUnlocksInfo unlocks;
    } database;
    struct Missions
    {
        QVector<MissionDataHelper> missions;
        QVector<QPair<Time,QPair<QString,QString>>> reports;
    } missions;
};

class SaveParser
{
public:
    static SaveData readData(QByteArray &array);
    static void writeData(QByteArray &array, const SaveData& data);
};

#endif // SAVEPARSER_H
