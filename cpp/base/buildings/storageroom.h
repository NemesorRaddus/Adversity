#pragma once

#include <QVector>

#include "building.h"

struct StorageRoomLevelInfo
{
    StorageRoomLevelInfo()
        : buildingMaterialsLimit(0), basicCostInEnergy(0){}

    unsigned buildingMaterialsLimit;
    unsigned basicCostInEnergy;
};

class StorageRoom : public Building
{
    Q_OBJECT
public:
    explicit StorageRoom(Base *base, unsigned level, const QVector <StorageRoomLevelInfo> &levelsInfo) noexcept;

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

    Q_INVOKABLE int buildingMaterialsLimit() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).buildingMaterialsLimit;
    }
    Q_INVOKABLE int buildingMaterialsLimitAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).buildingMaterialsLimit;
    }

    void setLevelsInfo(const QVector <StorageRoomLevelInfo> &info) noexcept;

    Q_INVOKABLE unsigned upgradeTimeRemaining() noexcept;

private:
    QVector <StorageRoomLevelInfo> m_levelsInfo;
};
