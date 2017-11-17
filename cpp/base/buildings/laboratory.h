#pragma once

#include <QVector>

#include "base/buildings/building.h"
#include "base/buildings/levelsinfo.h"
#include "mercenaries/mercenary.h"

struct LaboratoryLevelInfo : public BuildingLevelInfo
{
    LaboratoryLevelInfo()
        : amountOfSlots(0), perCapitaCostInEnergy(0), clevernessBonus(0), duration(0) {}

    unsigned amountOfSlots;
    unsigned perCapitaCostInEnergy;
    int clevernessBonus;
    unsigned duration;
};

class Laboratory : public Building
{
    Q_OBJECT

    friend class Base;

public:
    explicit Laboratory(Base *base, unsigned level, const AnyBuildingLevelsInfo *levelsInfo) noexcept;

    Q_INVOKABLE int useCostInEnergy() const noexcept;
    Q_INVOKABLE int useCostInEnergySingle() const noexcept;
    Q_INVOKABLE int useCostInEnergySingleAfterUpgrade() const noexcept;

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

    Q_INVOKABLE int amountOfSlots() const noexcept;
    Q_INVOKABLE int amountOfSlotsAfterUpgrade() const noexcept;
    QPair <Mercenary *, unsigned> slot(int index) noexcept;
    Q_INVOKABLE QString mercenaryNameInSlot(unsigned index) const noexcept;
    Q_INVOKABLE QString mercenaryProfessionInSlot(unsigned index) const noexcept;
    Q_INVOKABLE void placeMercenaryInSlot(unsigned slotIndex, const QString &mercenaryName) noexcept;
    Q_INVOKABLE void emptySlot(unsigned slotIndex) noexcept;
    void removeMercenary(const QString &name) noexcept;

    Q_INVOKABLE int clevernessBonus() const noexcept;
    Q_INVOKABLE int clevernessBonusAfterUpgrade() const noexcept;

    Q_INVOKABLE int duration() const noexcept;
    Q_INVOKABLE int durationAfterUpgrade() const noexcept;

    void trainMercenaries() noexcept;

    void setLevelsInfo(const QVector <LaboratoryLevelInfo *> &info) noexcept;

    Q_INVOKABLE unsigned upgradeTimeRemaining() noexcept;

    void registerUpgradeCompletion() noexcept;

    void resizeSlotsAfterUpgrade() noexcept;

    Q_INVOKABLE int remainingDaysOfTraining(const QString &mercenaryName) const noexcept;

private:
    LaboratoryLevelInfo *currentLevelInfo() const noexcept;
    LaboratoryLevelInfo *nextLevelInfo() const noexcept;

    void setSlot(unsigned index, Mercenary *mercenary, unsigned duration) noexcept;

    QVector <QPair <Mercenary *, unsigned>> m_mercenariesBeingTrained;
};
