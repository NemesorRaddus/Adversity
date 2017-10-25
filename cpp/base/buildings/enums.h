#pragma once

class QString;

namespace BuildingEnums
{
    enum Building
    {
        B_CentralUnit,
        B_Powerplant,
        B_Factory,
        B_CoolRoom,
        B_StorageRoom,
        B_AetheriteSilo,
        B_Hospital,
        B_Barracks,
        B_DockingStation,
        B_TrainingGround,
        B_Gym,
        B_Laboratory,
        B_PlayingField,
        B_Bar,
        B_Shrine,
        B_Seclusion,
        B_END
    };

    Building fromQStringToBuildingEnum(const QString &building) noexcept;
    QString fromBuildingEnumToQString(Building building) noexcept;
}
