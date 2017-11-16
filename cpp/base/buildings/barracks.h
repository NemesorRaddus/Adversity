#pragma once

#include <QVector>

#include "building.h"

struct BarracksLevelInfo
{
    BarracksLevelInfo()
        : mercenariesLimit(0), basicCostInEnergy(0){}

    unsigned mercenariesLimit;
    unsigned basicCostInEnergy;
};

class Barracks : public Building
{
    Q_OBJECT
public:
    explicit Barracks(Base *base, unsigned level, const QVector <BarracksLevelInfo> &levelsInfo) noexcept;

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

    Q_INVOKABLE int mercenariesLimit() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).mercenariesLimit;
    }
    Q_INVOKABLE int mercenariesLimitAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).mercenariesLimit;
    }

    void setLevelsInfo(const QVector <BarracksLevelInfo> &info) noexcept;

    Q_INVOKABLE unsigned upgradeTimeRemaining() noexcept;

private:
    QVector <BarracksLevelInfo> m_levelsInfo;
};
