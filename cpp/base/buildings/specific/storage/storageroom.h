#pragma once

#include <QVector>

#include "base/buildings/building.h"
#include "base/buildings/levelsinfo.h"

struct StorageRoomLevelInfo : public BuildingLevelInfo
{
    StorageRoomLevelInfo()
        : buildingMaterialsLimit(0) {}

    unsigned buildingMaterialsLimit;
};

class StorageRoom : public Building
{
    Q_OBJECT

public:
    explicit StorageRoom(Base *base, unsigned level, const AnyBuildingLevelsInfo *levelsInfo) noexcept;

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

    Q_INVOKABLE int buildingMaterialsLimit() const noexcept;
    Q_INVOKABLE int buildingMaterialsLimitAfterUpgrade() const noexcept;

    void setLevelsInfo(const QVector <StorageRoomLevelInfo *> &info) noexcept;

    Q_INVOKABLE unsigned upgradeTimeRemaining() noexcept;

private:
    StorageRoomLevelInfo *currentLevelInfo() const noexcept;
    StorageRoomLevelInfo *nextLevelInfo() const noexcept;
};
