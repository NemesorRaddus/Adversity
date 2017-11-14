#pragma once

#include <QVector>

#include "building.h"

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
    explicit Powerplant(Base *base, unsigned level, const QVector<PowerplantLevelInfo> &levelsInfo) noexcept;

    Q_INVOKABLE unsigned maxLevel() const noexcept
    {
        return m_levelsInfo.size()-1;
    }

    Q_INVOKABLE int basicCostInEnergy() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).basicCostInEnergy;
    }
    Q_INVOKABLE int basicCostInEnergyAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).basicCostInEnergy;
    }
    Q_INVOKABLE int useCostInEnergy() const noexcept
    {
        return 0-(m_levelsInfo.value(currentLevel()).energyGiven * m_currentCycles);
    }
    Q_INVOKABLE int productionInEnergySingle() const noexcept
    {
        return 0-(m_levelsInfo.value(currentLevel())).energyGiven;
    }
    Q_INVOKABLE int productionInEnergySingleAfterUpgrade() const noexcept
    {
        return 0-(m_levelsInfo.value(currentLevel()+1)).energyGiven;
    }

    Q_INVOKABLE int basicCostInFoodSupplies() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE int useCostInFoodSupplies() const noexcept
    {
        return 0;
    }

    Q_INVOKABLE int basicCostInBuildingMaterials() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE int useCostInBuildingMaterials() const noexcept
    {
        return 0;
    }

    Q_INVOKABLE int basicCostInAetherite() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE int useCostInAetherite() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).aetheriteOreTaken * m_currentCycles;
    }
    Q_INVOKABLE int useCostInAetheriteSingle() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).aetheriteOreTaken;
    }
    Q_INVOKABLE int useCostInAetheriteSingleAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).aetheriteOreTaken;
    }

    Q_INVOKABLE int energyLimit() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).energyLimit;
    }
    Q_INVOKABLE int energyLimitAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).energyLimit;
    }

    void exchangeResources() noexcept;

    Q_INVOKABLE void setCurrentCycles(unsigned amount) noexcept;
    Q_INVOKABLE unsigned currentCycles() const noexcept
    {
        return m_currentCycles;
    }
    Q_INVOKABLE unsigned maxCycles() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).maxCycles;
    }
    Q_INVOKABLE unsigned maxCyclesAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).maxCycles;
    }

    void setLevelsInfo(const QVector <PowerplantLevelInfo> &info) noexcept;

    Q_INVOKABLE unsigned upgradeTimeRemaining() noexcept;

private:
    QVector <PowerplantLevelInfo> m_levelsInfo;
    unsigned m_currentCycles;
};
