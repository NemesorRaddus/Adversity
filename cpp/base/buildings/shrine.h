#pragma once

#include <QVector>

#include "building.h"
#include "mercenaries/mercenary.h"

struct ShrineLevelInfo : public BuildingLevelInfo
{
    ShrineLevelInfo()
        : amountOfSlots(0), perCapitaCostInEnergy(0), stressReductionForActive(0), stressReductionForConvivial(0), stressReductionForRecluse(0), stressReductionForReligious(0) {}

    unsigned amountOfSlots;
    unsigned perCapitaCostInEnergy;
    int stressReductionForActive;
    int stressReductionForConvivial;
    int stressReductionForRecluse;
    int stressReductionForReligious;
};

class Shrine : public Building
{
    Q_OBJECT
    friend class Base;
public:
    explicit Shrine(Base *base, unsigned level, const QVector <ShrineLevelInfo> &levelsInfo) noexcept;

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
        return m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy * (m_mercenariesBeingDestressed.size() - m_mercenariesBeingDestressed.count(nullptr));
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

    Q_INVOKABLE int amountOfSlots() const noexcept
    {
        return m_mercenariesBeingDestressed.size();
    }
    Q_INVOKABLE int amountOfSlotsAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).amountOfSlots;
    }
    Mercenary *slot(int index) noexcept
    {
        return m_mercenariesBeingDestressed.value(index,nullptr);
    }
    Q_INVOKABLE QString mercenaryNameInSlot(unsigned index) const noexcept;
    Q_INVOKABLE QString mercenaryProfessionInSlot(unsigned index) const noexcept;
    Q_INVOKABLE void placeMercenaryInSlot(unsigned slotIndex, const QString &mercenaryName) noexcept;
    Q_INVOKABLE void emptySlot(unsigned slotIndex) noexcept;
    void removeMercenary(const QString &name) noexcept;

    Q_INVOKABLE int activeStressRelief() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).stressReductionForActive;
    }
    Q_INVOKABLE int activeStressReliefAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).stressReductionForActive;
    }
    Q_INVOKABLE int convivialStressRelief() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).stressReductionForConvivial;
    }
    Q_INVOKABLE int convivialStressReliefAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).stressReductionForConvivial;
    }
    Q_INVOKABLE int recluseStressRelief() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).stressReductionForRecluse;
    }
    Q_INVOKABLE int recluseStressReliefAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).stressReductionForRecluse;
    }
    Q_INVOKABLE int religiousStressRelief() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).stressReductionForReligious;
    }
    Q_INVOKABLE int religiousStressReliefAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).stressReductionForReligious;
    }

    void destressMercenaries() noexcept;

    void setRecoveryValuesForMercenary(unsigned index) noexcept;
    void setRecoveryValuesForMercenaries() noexcept;

    void setLevelsInfo(const QVector <ShrineLevelInfo> &info) noexcept;

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
        if (index<m_mercenariesBeingDestressed.size())
            m_mercenariesBeingDestressed[index]=mercenary;
    }

    QVector <ShrineLevelInfo> m_levelsInfo;

    QVector <Mercenary *> m_mercenariesBeingDestressed;
};
