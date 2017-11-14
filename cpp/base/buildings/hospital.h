#pragma once

#include <QVector>

#include "building.h"
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
    explicit Hospital(Base *base, unsigned level, const QVector <HospitalLevelInfo> &levelsInfo) noexcept;

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
        return m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy * (m_mercenariesBeingHealed.size() - m_mercenariesBeingHealed.count(nullptr));
    }
    Q_INVOKABLE int useCostInEnergySingle() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy;
    }
    Q_INVOKABLE int useCostInEnergySingleAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).perCapitaCostInEnergy;
    }

    Q_INVOKABLE int basicCostInFoodSupplies() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).basicCostInFoodSupplies;
    }
    Q_INVOKABLE int useCostInFoodSupplies() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).perCapitaCostInFoodSupplies * (m_mercenariesBeingHealed.size() - m_mercenariesBeingHealed.count(nullptr));
    }
    Q_INVOKABLE int useCostInFoodSuppliesSingle() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).perCapitaCostInFoodSupplies;
    }
    Q_INVOKABLE int useCostInFoodSuppliesSingleAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).perCapitaCostInFoodSupplies;
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

    Q_INVOKABLE int amountOfSlots() const noexcept
    {
        return m_mercenariesBeingHealed.size();
    }
    Q_INVOKABLE int amountOfSlotsAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).amountOfSlots;
    }
    Mercenary *slot(int index) noexcept
    {
        return m_mercenariesBeingHealed.value(index,nullptr);
    }
    Q_INVOKABLE QString mercenaryNameInSlot(unsigned index) const noexcept;
    Q_INVOKABLE QString mercenaryProfessionInSlot(unsigned index) const noexcept;
    Q_INVOKABLE void placeMercenaryInSlot(unsigned slotIndex, const QString &mercenaryName) noexcept;
    Q_INVOKABLE void emptySlot(unsigned slotIndex) noexcept;
    void removeMercenary(const QString &name) noexcept;

    Q_INVOKABLE int hpRestoredPerDay() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).hpRestored;
    }
    Q_INVOKABLE int hpRestoredPerDayAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).hpRestored;
    }
    Q_INVOKABLE int daysToFullRecovery(const QString &name) const noexcept;
    int daysToFullRecovery(unsigned slotIndex) const noexcept;

    void healMercenaries() noexcept;

    void setRecoveryValuesForMercenary(unsigned index) noexcept; // mercenary pointed-to by index in those fncs must be valid!
    void setRecoveryValuesForMercenaries() noexcept;

    void setLevelsInfo(const QVector <HospitalLevelInfo> &info) noexcept;

    Q_INVOKABLE unsigned upgradeTimeRemaining() noexcept;

    void registerUpgradeCompletion() noexcept
    {
        m_isBeingUpgraded=0;
        resizeSlotsAfterUpgrade();
    }

    void resizeSlotsAfterUpgrade() noexcept;

private:
    void setSlot(unsigned index, Mercenary *mercenary) noexcept
    {
        if (index<m_mercenariesBeingHealed.size())
            m_mercenariesBeingHealed[index]=mercenary;
    }

    QVector <HospitalLevelInfo> m_levelsInfo;

    QVector <Mercenary *> m_mercenariesBeingHealed;
};
