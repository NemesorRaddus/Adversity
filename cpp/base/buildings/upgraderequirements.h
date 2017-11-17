#pragma once

#include <QMap>

#include "base/buildings/enums.h"

struct BuildingUpgradeRequirements
{
    BuildingUpgradeRequirements() noexcept
        : requiredBuildingMaterials(0), requiredEnergy(0), requiredTime(0) {}
    explicit BuildingUpgradeRequirements(unsigned reqBuildingMat, unsigned reqEnergy, unsigned reqTime) noexcept
        : requiredBuildingMaterials(reqBuildingMat), requiredEnergy(reqEnergy), requiredTime(reqTime) {}

    unsigned requiredBuildingMaterials;
    unsigned requiredEnergy;
    unsigned requiredTime;
};

typedef QMap <QPair <BuildingEnums::Building, unsigned>, BuildingUpgradeRequirements> BuildingsRequirementsMap;

class BuildingsRequirementsHandler
{
public:
    explicit BuildingsRequirementsHandler(const BuildingsRequirementsMap &data) noexcept;

    BuildingUpgradeRequirements requirements(BuildingEnums::Building building, unsigned level) const noexcept;

private:
    BuildingsRequirementsMap m_data;
};
