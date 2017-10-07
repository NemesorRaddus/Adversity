#include "saveparser.h"

//File generated using Raddus Binary Data Parser Generator v1.0.1 Beta

#include "timer.h"
#include "hero.h"
#include "event.h"

#include <QDebug>

SaveData SaveParser::readData(QByteArray &array)
{
    QByteArray t=qUncompress(array);

    SaveData data;
    data.raw = array;
    if (!t.isEmpty())
    {
        QDataStream str(&t,QIODevice::ReadOnly);
        str>>data.parserVersion;
        str>>data.overall.baseName;
        str>>data.overall.lastKnownDay;
        str>>data.overall.lastKnownHour;
        str>>data.overall.lastKnownMinute;
        str>>data.buildings.levels.centralUnit;
        str>>data.buildings.levels.powerplant;
        str>>data.buildings.levels.factory;
        str>>data.buildings.levels.coolRoom;
        str>>data.buildings.levels.storageRoom;
        str>>data.buildings.levels.aetheriteSilo;
        str>>data.buildings.levels.hospital;
        str>>data.buildings.levels.barracks;
        str>>data.buildings.levels.dockingStation;
        str>>data.buildings.levels.trainingGround;
        str>>data.buildings.levels.gym;
        str>>data.buildings.levels.laboratory;
        str>>data.buildings.levels.playingField;
        str>>data.buildings.levels.bar;
        str>>data.buildings.levels.shrine;
        str>>data.buildings.levels.seclusion;
        str>>data.buildings.cyclesSet.powerplant;
        str>>data.buildings.cyclesSet.factory;
        str>>data.buildings.upgrading.centralUnit;
        str>>data.buildings.upgrading.powerplant;
        str>>data.buildings.upgrading.factory;
        str>>data.buildings.upgrading.coolRoom;
        str>>data.buildings.upgrading.storageRoom;
        str>>data.buildings.upgrading.aetheriteSilo;
        str>>data.buildings.upgrading.hospital;
        str>>data.buildings.upgrading.barracks;
        str>>data.buildings.upgrading.dockingStation;
        str>>data.buildings.upgrading.trainingGround;
        str>>data.buildings.upgrading.gym;
        str>>data.buildings.upgrading.laboratory;
        str>>data.buildings.upgrading.playingField;
        str>>data.buildings.upgrading.bar;
        str>>data.buildings.upgrading.shrine;
        str>>data.buildings.upgrading.seclusion;
        str>>data.buildings.heroSlots.hospital;
        str>>data.buildings.heroSlots.trainingGround;
        str>>data.buildings.heroSlots.gym;
        str>>data.buildings.heroSlots.laboratory;
        str>>data.buildings.heroSlots.playingField;
        str>>data.buildings.heroSlots.bar;
        str>>data.buildings.heroSlots.shrine;
        str>>data.buildings.heroSlots.seclusion;
        str>>data.buildings.dockingStationThings.recruits;
        str>>data.buildings.dockingStationThings.arrivingHeroes;
        str>>data.buildings.dockingStationThings.activeResourceTransactions;
        str>>data.buildings.dockingStationThings.equipments;
        str>>data.buildings.dockingStationThings.arrivingEquipments;
        str>>data.resources.energy;
        str>>data.resources.buildingMaterials;
        str>>data.resources.foodSupplies;
        str>>data.resources.aetheriteOre;
        str>>data.alarms.buildingUpgrades;
        str>>data.alarms.missionEnds;
        str>>data.alarms.missionAlarms;
        str>>data.heroes.hiredHeroes;
        str>>data.equipments.freeArmor;
        str>>data.equipments.freeWeaponsTools;
        str>>data.database.unlocks;
        str>>data.database.areThereNewDBEntries;
        str>>data.missions.missions;
        str>>data.missions.reports;
    }
    else
    {
        data.parserVersion.clear();
        data.overall.baseName.clear();
        data.overall.lastKnownDay=1;
        data.overall.lastKnownHour=0;
        data.overall.lastKnownMinute=0;
        data.buildings.levels.centralUnit=1;
        data.buildings.levels.powerplant=1;
        data.buildings.levels.factory=1;
        data.buildings.levels.coolRoom=1;
        data.buildings.levels.storageRoom=1;
        data.buildings.levels.aetheriteSilo=1;
        data.buildings.levels.hospital=0;
        data.buildings.levels.barracks=1;
        data.buildings.levels.dockingStation=1;
        data.buildings.levels.trainingGround=0;
        data.buildings.levels.gym=0;
        data.buildings.levels.laboratory=0;
        data.buildings.levels.playingField=0;
        data.buildings.levels.bar=0;
        data.buildings.levels.shrine=0;
        data.buildings.levels.seclusion=0;
        data.buildings.cyclesSet.powerplant=0;
        data.buildings.cyclesSet.factory=0;
        data.buildings.upgrading.centralUnit=false;
        data.buildings.upgrading.powerplant=false;
        data.buildings.upgrading.factory=false;
        data.buildings.upgrading.coolRoom=false;
        data.buildings.upgrading.storageRoom=false;
        data.buildings.upgrading.aetheriteSilo=false;
        data.buildings.upgrading.hospital=false;
        data.buildings.upgrading.barracks=false;
        data.buildings.upgrading.dockingStation=false;
        data.buildings.upgrading.trainingGround=false;
        data.buildings.upgrading.gym=false;
        data.buildings.upgrading.laboratory=false;
        data.buildings.upgrading.playingField=false;
        data.buildings.upgrading.bar=false;
        data.buildings.upgrading.shrine=false;
        data.buildings.upgrading.seclusion=false;
        data.buildings.heroSlots.hospital.clear();
        data.buildings.heroSlots.trainingGround.clear();
        data.buildings.heroSlots.gym.clear();
        data.buildings.heroSlots.laboratory.clear();
        data.buildings.heroSlots.playingField.clear();
        data.buildings.heroSlots.bar.clear();
        data.buildings.heroSlots.shrine.clear();
        data.buildings.heroSlots.seclusion.clear();
        data.buildings.dockingStationThings.recruits.clear();
        data.buildings.dockingStationThings.arrivingHeroes.clear();
        data.buildings.dockingStationThings.activeResourceTransactions.clear();
        data.buildings.dockingStationThings.equipments.clear();
        data.buildings.dockingStationThings.arrivingEquipments.clear();
        data.resources.energy=250;
        data.resources.buildingMaterials=5;
        data.resources.foodSupplies=24;
        data.resources.aetheriteOre=50;
        data.alarms.buildingUpgrades.clear();
        data.alarms.missionEnds.clear();
        data.alarms.missionAlarms.clear();
        data.heroes.hiredHeroes.clear();
        data.equipments.freeArmor.clear();
        data.equipments.freeWeaponsTools.clear();
        data.database.unlocks.clear();
        data.database.areThereNewDBEntries=false;
        data.missions.missions.clear();
        data.missions.reports.clear();

        writeData(array,data);
    }
    return data;
}

void SaveParser::writeData(QByteArray &array, const SaveData& data)
{
    QByteArray t;

    QDataStream str(&t,QIODevice::WriteOnly);
    str<<data.parserVersion;
    str<<data.overall.baseName;
    str<<data.overall.lastKnownDay;
    str<<data.overall.lastKnownHour;
    str<<data.overall.lastKnownMinute;
    str<<data.buildings.levels.centralUnit;
    str<<data.buildings.levels.powerplant;
    str<<data.buildings.levels.factory;
    str<<data.buildings.levels.coolRoom;
    str<<data.buildings.levels.storageRoom;
    str<<data.buildings.levels.aetheriteSilo;
    str<<data.buildings.levels.hospital;
    str<<data.buildings.levels.barracks;
    str<<data.buildings.levels.dockingStation;
    str<<data.buildings.levels.trainingGround;
    str<<data.buildings.levels.gym;
    str<<data.buildings.levels.laboratory;
    str<<data.buildings.levels.playingField;
    str<<data.buildings.levels.bar;
    str<<data.buildings.levels.shrine;
    str<<data.buildings.levels.seclusion;
    str<<data.buildings.cyclesSet.powerplant;
    str<<data.buildings.cyclesSet.factory;
    str<<data.buildings.upgrading.centralUnit;
    str<<data.buildings.upgrading.powerplant;
    str<<data.buildings.upgrading.factory;
    str<<data.buildings.upgrading.coolRoom;
    str<<data.buildings.upgrading.storageRoom;
    str<<data.buildings.upgrading.aetheriteSilo;
    str<<data.buildings.upgrading.hospital;
    str<<data.buildings.upgrading.barracks;
    str<<data.buildings.upgrading.dockingStation;
    str<<data.buildings.upgrading.trainingGround;
    str<<data.buildings.upgrading.gym;
    str<<data.buildings.upgrading.laboratory;
    str<<data.buildings.upgrading.playingField;
    str<<data.buildings.upgrading.bar;
    str<<data.buildings.upgrading.shrine;
    str<<data.buildings.upgrading.seclusion;
    str<<data.buildings.heroSlots.hospital;
    str<<data.buildings.heroSlots.trainingGround;
    str<<data.buildings.heroSlots.gym;
    str<<data.buildings.heroSlots.laboratory;
    str<<data.buildings.heroSlots.playingField;
    str<<data.buildings.heroSlots.bar;
    str<<data.buildings.heroSlots.shrine;
    str<<data.buildings.heroSlots.seclusion;
    str<<data.buildings.dockingStationThings.recruits;
    str<<data.buildings.dockingStationThings.arrivingHeroes;
    str<<data.buildings.dockingStationThings.activeResourceTransactions;
    str<<data.buildings.dockingStationThings.equipments;
    str<<data.buildings.dockingStationThings.arrivingEquipments;
    str<<data.resources.energy;
    str<<data.resources.buildingMaterials;
    str<<data.resources.foodSupplies;
    str<<data.resources.aetheriteOre;
    str<<data.alarms.buildingUpgrades;
    str<<data.alarms.missionEnds;
    str<<data.alarms.missionAlarms;
    str<<data.heroes.hiredHeroes;
    str<<data.equipments.freeArmor;
    str<<data.equipments.freeWeaponsTools;
    str<<data.database.unlocks;
    str<<data.database.areThereNewDBEntries;
    str<<data.missions.missions;
    str<<data.missions.reports;

    array=qCompress(t);
}
