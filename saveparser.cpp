#include "saveparser.h"

//File generated using Raddus Binary Data Parser Generator v1.0.1 Beta

#include "timer.h"

#include <QDebug>

SaveData SaveParser::readData(QByteArray &array)
{
    SaveData data;
    if (!array.isEmpty())
    {
        QDataStream str(&array,QIODevice::ReadOnly);
        str>>data.overall.baseName;
        str>>data.overall.lastKnownDate;
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
        str>>data.resources.energy;
        str>>data.resources.buildingMaterials;
        str>>data.resources.foodSupplies;
        str>>data.resources.aetheriteOre;
        str>>data.alarms.buildingUpgrades;
    }
    else
    {
        data.overall.baseName="";
        data.overall.lastKnownDate=QDateTime::currentDateTime();
        data.overall.lastKnownDay=1;
        data.overall.lastKnownHour=12;
        data.overall.lastKnownMinute=0;
        data.buildings.levels.centralUnit=1;
        data.buildings.levels.powerplant=1;
        data.buildings.levels.factory=1;
        data.buildings.levels.coolRoom=1;
        data.buildings.levels.storageRoom=1;
        data.buildings.levels.aetheriteSilo=1;
        data.buildings.levels.hospital=0;
        data.buildings.levels.barracks=1;
        data.buildings.levels.dockingStation=0;
        data.buildings.levels.trainingGround=0;
        data.buildings.levels.gym=0;
        data.buildings.levels.laboratory=0;
        data.buildings.levels.playingField=0;
        data.buildings.levels.bar=0;
        data.buildings.levels.shrine=0;
        data.buildings.levels.seclusion=0;
        data.buildings.cyclesSet.powerplant=0;
        data.buildings.cyclesSet.factory=0;
        data.resources.energy=200;
        data.resources.buildingMaterials=5;
        data.resources.foodSupplies=5;
        data.resources.aetheriteOre=42;
        data.alarms.buildingUpgrades.clear();

        QDataStream str(&array,QIODevice::WriteOnly);
        str<<data.overall.baseName;
        str<<data.overall.lastKnownDate;
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
        str<<data.resources.energy;
        str<<data.resources.buildingMaterials;
        str<<data.resources.foodSupplies;
        str<<data.resources.aetheriteOre;
        str<<data.alarms.buildingUpgrades;
    }
    return data;
}

void SaveParser::writeData(QByteArray &array, const SaveData& data)
{
    QDataStream str(&array,QIODevice::WriteOnly);
    str<<data.overall.baseName;
    str<<data.overall.lastKnownDate;
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
    str<<data.resources.energy;
    str<<data.resources.buildingMaterials;
    str<<data.resources.foodSupplies;
    str<<data.resources.aetheriteOre;
    str<<data.alarms.buildingUpgrades;
}
