#pragma once

#include <QVector>

#include "building.h"
#include "mercenaries/mercenary.h"

struct GymLevelInfo
{
    GymLevelInfo()
        : amountOfSlots(0), basicCostInEnergy(0), perCapitaCostInEnergy(0), proficiencyBonus(0), duration(0){}

    unsigned amountOfSlots;
    unsigned basicCostInEnergy;
    unsigned perCapitaCostInEnergy;
    int proficiencyBonus;
    unsigned duration;
};

class Gym : public Building
{
    Q_OBJECT
    friend class Base;
public:
    explicit Gym(Base *base, unsigned level, const QVector <GymLevelInfo> &levelsInfo) noexcept;

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
        int cnt=0;
        for (int i=0;i<m_mercenariesBeingTrained.size();++i)
            if (m_mercenariesBeingTrained[i].first==nullptr)
                ++cnt;
        return m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy * (m_mercenariesBeingTrained.size() - cnt);
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

    Q_INVOKABLE int amountOfSlots() const noexcept;
    Q_INVOKABLE int amountOfSlotsAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).amountOfSlots;
    }
    QPair <Mercenary *, unsigned> slot(int index) noexcept
    {
        return m_mercenariesBeingTrained.value(index,{nullptr,0});
    }
    Q_INVOKABLE QString mercenaryNameInSlot(unsigned index) const noexcept;
    Q_INVOKABLE QString mercenaryProfessionInSlot(unsigned index) const noexcept;
    Q_INVOKABLE void placeMercenaryInSlot(unsigned slotIndex, const QString &mercenaryName) noexcept;
    Q_INVOKABLE void emptySlot(unsigned slotIndex) noexcept;
    void removeMercenary(const QString &name) noexcept;

    Q_INVOKABLE int proficiencyBonus() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).proficiencyBonus;
    }
    Q_INVOKABLE int proficiencyBonusAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).proficiencyBonus;
    }

    Q_INVOKABLE int duration() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).duration;
    }
    Q_INVOKABLE int durationAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).duration;
    }

    void trainMercenaries() noexcept;

    void setLevelsInfo(const QVector <GymLevelInfo> &info) noexcept;

    Q_INVOKABLE unsigned upgradeTimeRemaining() noexcept;

    void registerUpgradeCompletion() noexcept
    {
        m_isBeingUpgraded=0;
        resizeSlotsAfterUpgrade();
    }

    void resizeSlotsAfterUpgrade() noexcept
    {
        while (m_mercenariesBeingTrained.size() < m_levelsInfo.value(currentLevel()).amountOfSlots)
            m_mercenariesBeingTrained+={nullptr,0};
        m_mercenariesBeingTrained.resize(m_levelsInfo.value(currentLevel()).amountOfSlots);//for downgrades
    }

    Q_INVOKABLE int remainingDaysOfTraining(const QString &mercenaryName) const noexcept;

private:
    void setSlot(unsigned index, Mercenary *mercenary, unsigned duration) noexcept
    {
        if (index<m_mercenariesBeingTrained.size())
        {
            m_mercenariesBeingTrained[index].first=mercenary;
            m_mercenariesBeingTrained[index].second=duration;
        }
    }

    QVector <GymLevelInfo> m_levelsInfo;

    QVector <QPair <Mercenary *, unsigned>> m_mercenariesBeingTrained;
};
