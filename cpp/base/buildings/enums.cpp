#include "enums.h"

#include <QString>

#include "general/game.h"
#include "logging/loggershandler.h"

BuildingEnums::Building BuildingEnums::fromQStringToBuildingEnum(const QString &building) noexcept
{
    if (building=="Central Unit")
        return B_CentralUnit;
    if (building=="Powerplant")
        return B_Powerplant;
    if (building=="Factory")
        return B_Factory;
    if (building=="Cool Room")
        return B_CoolRoom;
    if (building=="Storage Room")
        return B_StorageRoom;
    if (building=="Aetherite Silo")
        return B_AetheriteSilo;
    if (building=="Hospital")
        return B_Hospital;
    if (building=="Barracks")
        return B_Barracks;
    if (building=="Docking Station")
        return B_DockingStation;
    if (building=="Training Ground")
        return B_TrainingGround;
    if (building=="Gym")
        return B_Gym;
    if (building=="Laboratory")
        return B_Laboratory;
    if (building=="Playing Field")
        return B_PlayingField;
    if (building=="Bar")
        return B_Bar;
    if (building=="Shrine")
        return B_Shrine;
    if (building=="Seclusion")
        return B_Seclusion;
    Game::gameInstance()->loggers()->mainLogger()->warn("QString->Building enum conversion failed for {}",building.toStdString());
}

QString BuildingEnums::fromBuildingEnumToQString(BuildingEnums::Building building) noexcept
{
    if (building==B_CentralUnit)
        return "Central Unit";
    if (building==B_Powerplant)
        return "Powerplant";
    if (building==B_Factory)
        return "Factory";
    if (building==B_CoolRoom)
        return "Cool Room";
    if (building==B_StorageRoom)
        return "Storage Room";
    if (building==B_AetheriteSilo)
        return "Aetherite Silo";
    if (building==B_Hospital)
        return "Hospital";
    if (building==B_Barracks)
        return "Barracks";
    if (building==B_DockingStation)
        return "Docking Station";
    if (building==B_TrainingGround)
        return "Training Ground";
    if (building==B_Gym)
        return "Gym";
    if (building==B_Laboratory)
        return "Laboratory";
    if (building==B_PlayingField)
        return "Playing Field";
    if (building==B_Bar)
        return "Bar";
    if (building==B_Shrine)
        return "Shrine";
    if (building==B_Seclusion)
        return "Seclusion";
    Game::gameInstance()->loggers()->mainLogger()->warn("Building enum->QString conversion failed for {}",static_cast<unsigned>(building));
}
