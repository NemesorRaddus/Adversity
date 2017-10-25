#pragma once

#include <QVector>

#include "building.h"

struct AetheriteSiloLevelInfo
{
    AetheriteSiloLevelInfo()
        : aetheriteOreLimit(0), basicCostInEnergy(0){}

    unsigned aetheriteOreLimit;
    unsigned basicCostInEnergy;
};

class AetheriteSilo : public Building
{
    Q_OBJECT
public:
    explicit AetheriteSilo(Base *base, unsigned level, const QVector <AetheriteSiloLevelInfo> &levelsInfo) noexcept;

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
        return 0;
    }

    Q_INVOKABLE int basicCostInAetherite() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE int useCostInAetherite() const noexcept
    {
        return 0;
    }

    Q_INVOKABLE int aetheriteLimit() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).aetheriteOreLimit;
    }
    Q_INVOKABLE int aetheriteLimitAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).aetheriteOreLimit;
    }

    void setLevelsInfo(const QVector <AetheriteSiloLevelInfo> &info) noexcept;

    Q_INVOKABLE unsigned upgradeTimeRemaining() noexcept;

private:
    QVector <AetheriteSiloLevelInfo> m_levelsInfo;
};
