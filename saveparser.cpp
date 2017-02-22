#include "saveparser.h"

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
        str>>data.buildings.levels.powerPlant;
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
        str>>data.resources.energy;
        str>>data.resources.buildingMaterials;
        str>>data.resources.foodSupplies;
        str>>data.resources.aetheriteOre;
        file.close();
    }
    else
    {
        //insert your error handling here
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
        str<<data.buildings.levels.powerPlant;
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
