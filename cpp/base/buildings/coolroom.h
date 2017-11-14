#pragma once

#include <QVector>

#include "building.h"

struct CoolRoomLevelInfo : public BuildingLevelInfo
{
    CoolRoomLevelInfo()
        : foodSuppliesLimit(0) {}

    unsigned foodSuppliesLimit;
};

class CoolRoom : public Building
{
    Q_OBJECT
public:
    explicit CoolRoom(Base *base, unsigned level, const QVector <CoolRoomLevelInfo> &levelsInfo) noexcept;

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

    Q_INVOKABLE int foodSuppliesLimit() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).foodSuppliesLimit;
    }
    Q_INVOKABLE int foodSuppliesLimitAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).foodSuppliesLimit;
    }

    void setLevelsInfo(const QVector <CoolRoomLevelInfo> &info) noexcept;

    Q_INVOKABLE unsigned upgradeTimeRemaining() noexcept;

private:
    QVector <CoolRoomLevelInfo> m_levelsInfo;
};
