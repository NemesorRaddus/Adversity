#pragma once

class QString;

namespace BaseEnums
{
    enum Resource
    {
        R_Energy,
        R_FoodSupplies,
        R_BuildingMaterials,
        R_AetheriteOre,
        R_END
    };

    Resource fromQStringToResourceEnum(const QString &resource) noexcept;
    QString fromResourceEnumToQString(Resource resource) noexcept;
}
