#pragma once

#include <QString>
#include <QObject>

#include "enums.h"

struct BuildingLevelInfo
{
public:
    unsigned basicCostInEnergy;

protected:
    BuildingLevelInfo()
        : basicCostInEnergy(0) {}
};

class Base;
struct BuildingUpgradeRequirements;

class Building : public QObject
{
    Q_OBJECT

public:
    Q_INVOKABLE virtual unsigned currentLevel() const noexcept;
    Q_INVOKABLE virtual unsigned maxLevel() const noexcept = 0;
    Q_INVOKABLE inline virtual bool maxLevelReached() const noexcept
    {
        return currentLevel()==maxLevel();
    }

    virtual BuildingUpgradeRequirements requirementsForNextLevel() const noexcept;
    Q_INVOKABLE virtual unsigned requirementsForNextLevelEnergy() const noexcept;
    Q_INVOKABLE virtual unsigned requirementsForNextLevelBM() const noexcept;
    Q_INVOKABLE virtual unsigned requirementsForNextLevelTime() const noexcept;

    Q_INVOKABLE virtual bool tryUpgrading() noexcept;

    Q_INVOKABLE virtual QString description() const noexcept;

    virtual int basicCostInEnergy() const noexcept = 0;
    virtual int basicCostInEnergyAfterUpgrade() const noexcept = 0;
    virtual int useCostInEnergy() const noexcept = 0;
    Q_INVOKABLE virtual int currentCostInEnergy() const noexcept
    {
        return basicCostInEnergy()+useCostInEnergy();
    }

    virtual int basicCostInFoodSupplies() const noexcept = 0;
    virtual int useCostInFoodSupplies() const noexcept = 0;
    Q_INVOKABLE virtual int currentCostInFoodSupplies() const noexcept
    {
        return basicCostInFoodSupplies()+useCostInFoodSupplies();
    }

    virtual int basicCostInBuildingMaterials() const noexcept = 0;
    virtual int useCostInBuildingMaterials() const noexcept = 0;
    Q_INVOKABLE virtual int currentCostInBuildingMaterials() const noexcept
    {
        return basicCostInBuildingMaterials()+useCostInBuildingMaterials();
    }

    virtual int basicCostInAetherite() const noexcept = 0;
    virtual int useCostInAetherite() const noexcept = 0;
    Q_INVOKABLE virtual int currentCostInAetherite() const noexcept
    {
        return basicCostInAetherite()+useCostInAetherite();
    }

    virtual void registerUpgradeCompletion() noexcept
    {
        m_isBeingUpgraded=0;
    }
    Q_INVOKABLE inline bool isBeingUpgraded() const noexcept
    {
        return m_isBeingUpgraded;
    }
    void setIsBeingUpgraded(bool isUpgraded) noexcept
    {
        m_isBeingUpgraded=isUpgraded;
    }

    Q_INVOKABLE virtual unsigned upgradeTimeRemaining() noexcept = 0;

protected:
    explicit Building(BuildingEnums::Building buildingName, Base *base, unsigned level) noexcept;
    Base *base() noexcept
    {
        return m_base;
    }

    bool m_isBeingUpgraded;

private:
    void registerUpgradeStart() noexcept
    {
        m_isBeingUpgraded=1;
    }

    Base *m_base;
    BuildingEnums::Building m_buildingName;
};
