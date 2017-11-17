#pragma once

#include <QVector>

#include "base/buildings/building.h"
#include "base/buildings/levelsinfo.h"

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
    explicit CoolRoom(Base *base, unsigned level, const AnyBuildingLevelsInfo *levelsInfo) noexcept;

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

    Q_INVOKABLE int foodSuppliesLimit() const noexcept;
    Q_INVOKABLE int foodSuppliesLimitAfterUpgrade() const noexcept;

    void setLevelsInfo(const QVector <CoolRoomLevelInfo *> &info) noexcept;

    Q_INVOKABLE unsigned upgradeTimeRemaining() noexcept;

private:
    CoolRoomLevelInfo *currentLevelInfo() const noexcept;
    CoolRoomLevelInfo *nextLevelInfo() const noexcept;
};
