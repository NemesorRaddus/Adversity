#pragma once

#include <QVector>

#include "base/buildings/building.h"
#include "base/buildings/levelsinfo.h"

struct FactoryLevelInfo : public BuildingLevelInfo
{
    FactoryLevelInfo()
        : aetheriteOreTaken(0), buildingMaterialsGiven(0), maxCycles(0) {}

    unsigned aetheriteOreTaken;
    unsigned buildingMaterialsGiven;
    unsigned maxCycles;
};

class Factory : public Building
{
    Q_OBJECT

public:
    explicit Factory(Base *base, unsigned level, const AnyBuildingLevelsInfo *levelsInfo) noexcept;

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
    Q_INVOKABLE int useCostInBuildingMaterials() const noexcept;
    Q_INVOKABLE int productionInBuildingMaterialsSingle() const noexcept;
    Q_INVOKABLE int productionInBuildingMaterialsSingleAfterUpgrade() const noexcept;

    Q_INVOKABLE inline int basicCostInAetherite() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE int useCostInAetherite() const noexcept;
    Q_INVOKABLE int useCostInAetheriteSingle() const noexcept;
    Q_INVOKABLE int useCostInAetheriteSingleAfterUpgrade() const noexcept;

    void exchangeResources() noexcept;

    Q_INVOKABLE void setCurrentCycles(unsigned amount) noexcept;
    Q_INVOKABLE inline unsigned currentCycles() const noexcept
    {
        return m_currentCycles;
    }
    Q_INVOKABLE unsigned maxCycles() const noexcept;
    Q_INVOKABLE unsigned maxCyclesAfterUpgrade() const noexcept;

    void setLevelsInfo(const QVector <FactoryLevelInfo *> &info) noexcept;

    Q_INVOKABLE unsigned upgradeTimeRemaining() noexcept;

private:
    FactoryLevelInfo *currentLevelInfo() const noexcept;
    FactoryLevelInfo *nextLevelInfo() const noexcept;

    unsigned m_currentCycles;
};
