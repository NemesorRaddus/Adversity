#pragma once

#include <QVector>

#include "base/buildings/building.h"
#include "base/buildings/levelsinfo.h"

struct PowerplantLevelInfo : public BuildingLevelInfo
{
    PowerplantLevelInfo()
        : aetheriteOreTaken(0), energyLimit(0), energyGiven(0), maxCycles(0) {}

    unsigned aetheriteOreTaken;
    unsigned energyLimit;
    unsigned energyGiven;
    unsigned maxCycles;
};

class Powerplant : public Building
{
    Q_OBJECT

public:
    explicit Powerplant(Base *base, unsigned level, const AnyBuildingLevelsInfo *levelsInfo) noexcept;

    Q_INVOKABLE int useCostInEnergy() const noexcept;
    Q_INVOKABLE int productionInEnergySingle() const noexcept;
    Q_INVOKABLE int productionInEnergySingleAfterUpgrade() const noexcept;

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
    Q_INVOKABLE int useCostInAetherite() const noexcept;
    Q_INVOKABLE int useCostInAetheriteSingle() const noexcept;
    Q_INVOKABLE int useCostInAetheriteSingleAfterUpgrade() const noexcept;

    Q_INVOKABLE int energyLimit() const noexcept;
    Q_INVOKABLE int energyLimitAfterUpgrade() const noexcept;

    void exchangeResources() noexcept;

    Q_INVOKABLE void setCurrentCycles(unsigned amount) noexcept;
    Q_INVOKABLE inline unsigned currentCycles() const noexcept
    {
        return m_currentCycles;
    }
    Q_INVOKABLE unsigned maxCycles() const noexcept;
    Q_INVOKABLE unsigned maxCyclesAfterUpgrade() const noexcept;

    void setLevelsInfo(const QVector <PowerplantLevelInfo *> &info) noexcept;

    Q_INVOKABLE unsigned upgradeTimeRemaining() noexcept;

private:
    PowerplantLevelInfo *currentLevelInfo() const noexcept;
    PowerplantLevelInfo *nextLevelInfo() const noexcept;

    unsigned m_currentCycles;
};
