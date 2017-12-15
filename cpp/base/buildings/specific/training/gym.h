#pragma once

#include <QVector>

#include "base/buildings/building.h"
#include "base/buildings/levelsinfo.h"
#include "mercenaries/mercenary.h"

struct GymLevelInfo : public BuildingLevelInfo
{
    GymLevelInfo()
        : amountOfSlots(0), perCapitaCostInEnergy(0), proficiencyBonus(0), duration(0) {}

    unsigned amountOfSlots;
    unsigned perCapitaCostInEnergy;
    int proficiencyBonus;
    unsigned duration;
};

class Gym : public Building
{
    Q_OBJECT

    friend class Base;

public:
    explicit Gym(Base *base, unsigned level, const AnyBuildingLevelsInfo *levelsInfo) noexcept;

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

    Q_INVOKABLE int proficiencyBonus() const noexcept;
    Q_INVOKABLE int proficiencyBonusAfterUpgrade() const noexcept;

    Q_INVOKABLE int duration() const noexcept;
    Q_INVOKABLE int durationAfterUpgrade() const noexcept;

    void trainMercenaries() noexcept;

    void setLevelsInfo(const QVector <GymLevelInfo *> &info) noexcept;

    Q_INVOKABLE unsigned upgradeTimeRemaining() noexcept;

    void registerUpgradeCompletion() noexcept;

    void resizeSlotsAfterUpgrade() noexcept;

    Q_INVOKABLE int remainingDaysOfTraining(const QString &mercenaryName) const noexcept;

private:
    GymLevelInfo *currentLevelInfo() const noexcept;
    GymLevelInfo *nextLevelInfo() const noexcept;

    void setSlot(unsigned index, Mercenary *mercenary, unsigned duration) noexcept;

    QVector <QPair <Mercenary *, unsigned>> m_mercenariesBeingTrained;
};
