#include "saveparser.h"

#include <QDebug>

//File generated using Raddus Binary Data Parser Generator v1.0.1 Beta


SaveData SaveParser::readData(const QString &path)
{
    SaveData data;
    QFile file(path);
    if (file.open(QFile::ReadOnly))
    {
        QDataStream str(&file);
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
        str>>data.buildings.cyclesSet.powerPlant;
        str>>data.buildings.cyclesSet.factory;
        str>>data.resources.energy;
        str>>data.resources.buildingMaterials;
        str>>data.resources.foodSupplies;
        str>>data.resources.aetheriteOre;
        file.close();
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
        data.buildings.cyclesSet.powerPlant=0;
        data.buildings.cyclesSet.factory=0;
        data.resources.energy=0;
        data.resources.buildingMaterials=0;
        data.resources.foodSupplies=0;
        data.resources.aetheriteOre=0;
        QFile file2(path);
        if (file2.open(QFile::WriteOnly))
        {
            QDataStream str(&file2);
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
            str<<data.buildings.cyclesSet.powerPlant;
            str<<data.buildings.cyclesSet.factory;
            str<<data.resources.energy;
            str<<data.resources.buildingMaterials;
            str<<data.resources.foodSupplies;
            str<<data.resources.aetheriteOre;
            file2.close();
        }
    }
    return data;
}

void SaveParser::writeData(const QString &path, const SaveData& data)
{
    QFile file(path);
    if (file.open(QFile::WriteOnly))
    {
        QDataStream str(&file);
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
        str<<data.buildings.cyclesSet.powerPlant;
        str<<data.buildings.cyclesSet.factory;
        str<<data.resources.energy;
        str<<data.resources.buildingMaterials;
        str<<data.resources.foodSupplies;
        str<<data.resources.aetheriteOre;
        file.close();
    }
    else
    {
        //insert your error handling here
    }
}
