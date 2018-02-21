#pragma once

#include <QVector>

#include "base/buildings/building.h"
#include "base/buildings/levelsinfo.h"
#include "mercenaries/mercenary.h"

struct BarLevelInfo : public BuildingLevelInfo
{
    BarLevelInfo()
        : amountOfSlots(0), perCapitaCostInEnergy(0), stressReductionForActive(0), stressReductionForConvivial(0), stressReductionForRecluse(0), stressReductionForReligious(0) {}

    unsigned amountOfSlots;
    unsigned perCapitaCostInEnergy;
    int stressReductionForActive;
    int stressReductionForConvivial;
    int stressReductionForRecluse;
    int stressReductionForReligious;
};

class Bar : public Building
{
    Q_OBJECT

    friend class Base;

public:
    explicit Bar(Base *base, unsigned level, const AnyBuildingLevelsInfo *levelsInfo) noexcept;

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
    Mercenary *slot(int index) noexcept;
    Q_INVOKABLE QString mercenaryNameInSlot(unsigned index) const noexcept;
    Q_INVOKABLE QString mercenaryProfessionInSlot(unsigned index) const noexcept;
    Q_INVOKABLE void placeMercenaryInSlot(unsigned slotIndex, const QString &mercenaryName) noexcept;
    Q_INVOKABLE void emptySlot(unsigned slotIndex) noexcept;
    void removeMercenary(const QString &name) noexcept;

    Q_INVOKABLE int activeStressRelief() const noexcept;
    Q_INVOKABLE int activeStressReliefAfterUpgrade() const noexcept;
    Q_INVOKABLE int convivialStressRelief() const noexcept;
    Q_INVOKABLE int convivialStressReliefAfterUpgrade() const noexcept;
    Q_INVOKABLE int recluseStressRelief() const noexcept;
    Q_INVOKABLE int recluseStressReliefAfterUpgrade() const noexcept;
    Q_INVOKABLE int religiousStressRelief() const noexcept;
    Q_INVOKABLE int religiousStressReliefAfterUpgrade() const noexcept;

    void destressMercenaries() noexcept;

    void setRecoveryValuesForMercenary(unsigned index) noexcept;
    void setRecoveryValuesForMercenaries() noexcept;

    void setLevelsInfo(const QVector < BarLevelInfo *> &info) noexcept;

    Q_INVOKABLE unsigned upgradeTimeRemaining() noexcept;

    void registerUpgradeCompletion() noexcept;

    void resizeSlotsAfterUpgrade() noexcept;

private:
    BarLevelInfo *currentLevelInfo() const noexcept;
    BarLevelInfo *nextLevelInfo() const noexcept;

    void setSlot(unsigned index, Mercenary *mercenary) noexcept;

    QVector <Mercenary *> m_mercenariesBeingDestressed;
};
