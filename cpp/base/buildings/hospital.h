#pragma once

#include <QVector>

#include "base/buildings/building.h"
#include "base/buildings/levelsinfo.h"
#include "mercenaries/mercenary.h"

struct HospitalLevelInfo : public BuildingLevelInfo
{
    HospitalLevelInfo()
        : amountOfSlots(0), perCapitaCostInEnergy(0), basicCostInFoodSupplies(0), perCapitaCostInFoodSupplies(0), hpRestored(0) {}

    unsigned amountOfSlots;
    unsigned perCapitaCostInEnergy;
    unsigned basicCostInFoodSupplies;
    unsigned perCapitaCostInFoodSupplies;
    unsigned hpRestored;
};

class Hospital : public Building
{
    Q_OBJECT

    friend class Base;

public:
    explicit Hospital(Base *base, unsigned level, const AnyBuildingLevelsInfo *levelsInfo) noexcept;

    Q_INVOKABLE int useCostInEnergy() const noexcept;
    Q_INVOKABLE int useCostInEnergySingle() const noexcept;
    Q_INVOKABLE int useCostInEnergySingleAfterUpgrade() const noexcept;

    Q_INVOKABLE int basicCostInFoodSupplies() const noexcept;
    Q_INVOKABLE int useCostInFoodSupplies() const noexcept;
    Q_INVOKABLE int useCostInFoodSuppliesSingle() const noexcept;
    Q_INVOKABLE int useCostInFoodSuppliesSingleAfterUpgrade() const noexcept;

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
    Mercenary *slot(int index) noexcept;
    Q_INVOKABLE QString mercenaryNameInSlot(unsigned index) const noexcept;
    Q_INVOKABLE QString mercenaryProfessionInSlot(unsigned index) const noexcept;
    Q_INVOKABLE void placeMercenaryInSlot(unsigned slotIndex, const QString &mercenaryName) noexcept;
    Q_INVOKABLE void emptySlot(unsigned slotIndex) noexcept;
    void removeMercenary(const QString &name) noexcept;

    Q_INVOKABLE int hpRestoredPerDay() const noexcept;
    Q_INVOKABLE int hpRestoredPerDayAfterUpgrade() const noexcept;
    Q_INVOKABLE int daysToFullRecovery(const QString &name) const noexcept;
    int daysToFullRecovery(unsigned slotIndex) const noexcept;

    void healMercenaries() noexcept;

    void setRecoveryValuesForMercenary(unsigned index) noexcept; // mercenary pointed-to by index in those fncs must be valid!
    void setRecoveryValuesForMercenaries() noexcept;

    void setLevelsInfo(const QVector <HospitalLevelInfo *> &info) noexcept;

    Q_INVOKABLE unsigned upgradeTimeRemaining() noexcept;

    void registerUpgradeCompletion() noexcept;

    void resizeSlotsAfterUpgrade() noexcept;

private:
    HospitalLevelInfo *currentLevelInfo() const noexcept;
    HospitalLevelInfo *nextLevelInfo() const noexcept;

    void setSlot(unsigned index, Mercenary *mercenary) noexcept;

    QVector <Mercenary *> m_mercenariesBeingHealed;
};
