#pragma once

#include <QVector>

#include "building.h"

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
    explicit Factory(Base *base, unsigned level, const QVector <FactoryLevelInfo> &levelsInfo) noexcept;

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
        return 0;
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
        return 0-(m_levelsInfo.value(currentLevel()).buildingMaterialsGiven * m_currentCycles);
    }
    Q_INVOKABLE int productionInBuildingMaterialsSingle() const noexcept
    {
        return 0-(m_levelsInfo.value(currentLevel())).buildingMaterialsGiven;
    }
    Q_INVOKABLE int productionInBuildingMaterialsSingleAfterUpgrade() const noexcept
    {
        return 0-(m_levelsInfo.value(currentLevel()+1)).buildingMaterialsGiven;
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
        return m_levelsInfo.value(currentLevel()).aetheriteOreTaken;
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

    void setLevelsInfo(const QVector <FactoryLevelInfo> &info) noexcept;

    Q_INVOKABLE unsigned upgradeTimeRemaining() noexcept;

private:
    QVector <FactoryLevelInfo> m_levelsInfo;
    unsigned m_currentCycles;
};
