#pragma once

#include <QVector>

#include "base/buildings/building.h"
#include "base/buildings/levelsinfo.h"

struct BarracksLevelInfo : public BuildingLevelInfo
{
    BarracksLevelInfo()
        : mercenariesLimit(0) {}

    unsigned mercenariesLimit;
    unsigned basicCostInEnergy;
};

class Barracks : public Building
{
    Q_OBJECT

public:
    explicit Barracks(Base *base, unsigned level, const AnyBuildingLevelsInfo *levelsInfo) noexcept;

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

    Q_INVOKABLE int mercenariesLimit() const noexcept;
    Q_INVOKABLE int mercenariesLimitAfterUpgrade() const noexcept;

    void setLevelsInfo(const QVector <BarracksLevelInfo *> &info) noexcept;

    Q_INVOKABLE unsigned upgradeTimeRemaining() noexcept;

private:
    BarracksLevelInfo *currentLevelInfo() const noexcept;
    BarracksLevelInfo *nextLevelInfo() const noexcept;
};
