#pragma once

#include <QVector>

#include "base/buildings/building.h"
#include "base/buildings/levelsinfo.h"

struct AetheriteSiloLevelInfo : public BuildingLevelInfo
{
    AetheriteSiloLevelInfo()
        : aetheriteOreLimit(0) {}

    unsigned aetheriteOreLimit;
};

class AetheriteSilo : public Building
{
    Q_OBJECT

public:
    explicit AetheriteSilo(Base *base, unsigned level, const AnyBuildingLevelsInfo *levelsInfo) noexcept;

    Q_INVOKABLE inline int useCostInEnergy() const noexcept
    {
        return 0;
    }

    Q_INVOKABLE inline int basicCostInFoodSupplies() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE inline int useCostInFoodSupplies() const noexcept
    {
        return 0;
    }

    Q_INVOKABLE inline int basicCostInBuildingMaterials() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE inline int useCostInBuildingMaterials() const noexcept
    {
        return 0;
    }

    Q_INVOKABLE inline int basicCostInAetherite() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE inline int useCostInAetherite() const noexcept
    {
        return 0;
    }

    Q_INVOKABLE int aetheriteLimit() const noexcept;
    Q_INVOKABLE int aetheriteLimitAfterUpgrade() const noexcept;

    void setLevelsInfo(const QVector <AetheriteSiloLevelInfo *> &info) noexcept;

    Q_INVOKABLE unsigned upgradeTimeRemaining() noexcept;

private:
    AetheriteSiloLevelInfo *currentLevelInfo() const noexcept;
    AetheriteSiloLevelInfo *nextLevelInfo() const noexcept;
};
