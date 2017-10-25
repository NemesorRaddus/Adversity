#include "enums.h"

#include <QString>

#include "general/game.h"
#include "logging/loggershandler.h"

BaseEnums::Resource BaseEnums::fromQStringToResourceEnum(const QString &resource) noexcept
{
    if (resource=="Energy")
        return R_Energy;
    if (resource=="Food Supplies")
        return R_FoodSupplies;
    if (resource=="Building Materials")
        return R_BuildingMaterials;
    if (resource=="Aetherite")
        return R_AetheriteOre;
    Game::gameInstance()->loggers()->mainLogger()->warn("QString->Resource enum conversion failed for {}",resource.toStdString());
}

QString BaseEnums::fromResourceEnumToQString(BaseEnums::Resource resource) noexcept
{
    if (resource==R_Energy)
        return "Energy";
    if (resource==R_FoodSupplies)
        return "Food Supplies";
    if (resource==R_BuildingMaterials)
        return "Building Materials";
    if (resource==R_AetheriteOre)
        return "Aetherite";
    Game::gameInstance()->loggers()->mainLogger()->warn("Resource enum->QString conversion failed for {}",static_cast<unsigned>(resource));
}
