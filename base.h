#ifndef BASE_H
#define BASE_H

#include <QVector>
#include <QMap>
#include <QObject>

#include "equipment.h"
#include "mercenary.h"
#include "saveparser.h"
#include "database.h"

#include <QDebug>

struct BaseEnums
{
    enum Resource
    {
        R_Energy,
        R_FoodSupplies,
        R_BuildingMaterials,
        R_AetheriteOre,
        R_END
    };
    enum Building
    {
        B_CentralUnit,
        B_Powerplant,
        B_Factory,
        B_CoolRoom,
        B_StorageRoom,
        B_AetheriteSilo,
        B_Hospital,
        B_Barracks,
        B_DockingStation,
        B_TrainingGround,
        B_Gym,
        B_Laboratory,
        B_PlayingField,
        B_Bar,
        B_Shrine,
        B_Seclusion,
        B_END
    };

    static Resource fromQStringToResourceEnum(const QString &resource) noexcept;
    static QString fromResourceEnumToQString(Resource resource) noexcept;

    static Building fromQStringToBuildingEnum(const QString &building) noexcept;
    static QString fromBuildingEnumToQString(Building building) noexcept;
};

struct BuildingUpgradeRequirements
{
    BuildingUpgradeRequirements() noexcept
        : requiredBuildingMaterials(0), requiredEnergy(0), requiredTime(0){}
    explicit BuildingUpgradeRequirements(unsigned reqBuildingMat, unsigned reqEnergy, unsigned reqTime) noexcept
        : requiredBuildingMaterials(reqBuildingMat), requiredEnergy(reqEnergy), requiredTime(reqTime){}

    unsigned requiredBuildingMaterials;
    unsigned requiredEnergy;
    unsigned requiredTime;
};

class Base;

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
    explicit Building(BaseEnums::Building buildingName, Base *base, unsigned level) noexcept;
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
    BaseEnums::Building m_buildingName;
};

struct CentralUnitLevelInfo
{
    CentralUnitLevelInfo()
        : basicCostInEnergy(0){}

    unsigned basicCostInEnergy;
};

class CentralUnit : public Building
{
    Q_OBJECT
public:
    explicit CentralUnit(Base *base, unsigned level, const QVector <CentralUnitLevelInfo> &levelsInfo) noexcept;

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
        return 0;
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

    void setLevelsInfo(const QVector <CentralUnitLevelInfo> &info) noexcept;

    Q_INVOKABLE unsigned upgradeTimeRemaining() noexcept;

private:
    QVector <CentralUnitLevelInfo> m_levelsInfo;
};

struct HospitalLevelInfo
{
    HospitalLevelInfo()
        : amountOfSlots(0), basicCostInEnergy(0), perCapitaCostInEnergy(0), basicCostInFoodSupplies(0), perCapitaCostInFoodSupplies(0), hpRestored(0){}

    unsigned amountOfSlots;
    unsigned basicCostInEnergy;
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

struct TrainingGroundLevelInfo
{
    TrainingGroundLevelInfo()
        : amountOfSlots(0), basicCostInEnergy(0), perCapitaCostInEnergy(0), combatEffectivenessBonus(0), duration(0){}

    unsigned amountOfSlots;
    unsigned basicCostInEnergy;
    unsigned perCapitaCostInEnergy;
    int combatEffectivenessBonus;
    unsigned duration;
};

class TrainingGround : public Building
{
    Q_OBJECT
    friend class Base;
public:
    explicit TrainingGround(Base *base, unsigned level, const QVector <TrainingGroundLevelInfo> &levelsInfo) noexcept;

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

    Q_INVOKABLE int amountOfSlots() const noexcept
    {
        return m_mercenariesBeingTrained.size();
    }
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

    Q_INVOKABLE int combatEffectivenessBonus() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).combatEffectivenessBonus;
    }
    Q_INVOKABLE int combatEffectivenessBonusAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).combatEffectivenessBonus;
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

    void setLevelsInfo(const QVector <TrainingGroundLevelInfo> &info) noexcept;

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

    QVector <TrainingGroundLevelInfo> m_levelsInfo;

    QVector <QPair <Mercenary *, unsigned>> m_mercenariesBeingTrained;
};

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

struct LaboratoryLevelInfo
{
    LaboratoryLevelInfo()
        : amountOfSlots(0), basicCostInEnergy(0), perCapitaCostInEnergy(0), clevernessBonus(0), duration(0){}

    unsigned amountOfSlots;
    unsigned basicCostInEnergy;
    unsigned perCapitaCostInEnergy;
    int clevernessBonus;
    unsigned duration;
};

class Laboratory : public Building
{
    Q_OBJECT
    friend class Base;
public:
    explicit Laboratory(Base *base, unsigned level, const QVector <LaboratoryLevelInfo> &levelsInfo) noexcept;

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

    Q_INVOKABLE int clevernessBonus() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).clevernessBonus;
    }
    Q_INVOKABLE int clevernessBonusAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).clevernessBonus;
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

    void setLevelsInfo(const QVector <LaboratoryLevelInfo> &info) noexcept;

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

    QVector <LaboratoryLevelInfo> m_levelsInfo;

    QVector <QPair <Mercenary *, unsigned>> m_mercenariesBeingTrained;
};

struct PlayingFieldLevelInfo
{
    PlayingFieldLevelInfo()
        : amountOfSlots(0), basicCostInEnergy(0), perCapitaCostInEnergy(0), stressReductionForActive(0), stressReductionForConvivial(0), stressReductionForRecluse(0), stressReductionForReligious(0){}

    unsigned amountOfSlots;
    unsigned basicCostInEnergy;
    unsigned perCapitaCostInEnergy;
    int stressReductionForActive;
    int stressReductionForConvivial;
    int stressReductionForRecluse;
    int stressReductionForReligious;
};

class PlayingField : public Building
{
    Q_OBJECT
    friend class Base;
public:
    explicit PlayingField(Base *base, unsigned level, const QVector <PlayingFieldLevelInfo> &levelsInfo) noexcept;

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

    void setLevelsInfo(const QVector <PlayingFieldLevelInfo> &info) noexcept;

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

    QVector <PlayingFieldLevelInfo> m_levelsInfo;

    QVector <Mercenary *> m_mercenariesBeingDestressed;
};

struct BarLevelInfo
{
    BarLevelInfo()
        : amountOfSlots(0), basicCostInEnergy(0), perCapitaCostInEnergy(0), stressReductionForActive(0), stressReductionForConvivial(0), stressReductionForRecluse(0), stressReductionForReligious(0){}

    unsigned amountOfSlots;
    unsigned basicCostInEnergy;
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
    explicit Bar(Base *base, unsigned level, const QVector <BarLevelInfo> &levelsInfo) noexcept;

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

    void setLevelsInfo(const QVector <BarLevelInfo> &info) noexcept;

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

    QVector <BarLevelInfo> m_levelsInfo;

    QVector <Mercenary *> m_mercenariesBeingDestressed;
};

struct ShrineLevelInfo
{
    ShrineLevelInfo()
        : amountOfSlots(0), basicCostInEnergy(0), perCapitaCostInEnergy(0), stressReductionForActive(0), stressReductionForConvivial(0), stressReductionForRecluse(0), stressReductionForReligious(0){}

    unsigned amountOfSlots;
    unsigned basicCostInEnergy;
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

struct SeclusionLevelInfo
{
    SeclusionLevelInfo()
        : amountOfSlots(0), basicCostInEnergy(0), perCapitaCostInEnergy(0), stressReductionForActive(0), stressReductionForConvivial(0), stressReductionForRecluse(0), stressReductionForReligious(0){}

    unsigned amountOfSlots;
    unsigned basicCostInEnergy;
    unsigned perCapitaCostInEnergy;
    int stressReductionForActive;
    int stressReductionForConvivial;
    int stressReductionForRecluse;
    int stressReductionForReligious;
};

class Seclusion : public Building
{
    Q_OBJECT
    friend class Base;
public:
    explicit Seclusion(Base *base, unsigned level, const QVector <SeclusionLevelInfo> &levelsInfo) noexcept;

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

    void setLevelsInfo(const QVector <SeclusionLevelInfo> &info) noexcept;

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

    QVector <SeclusionLevelInfo> m_levelsInfo;

    QVector <Mercenary *> m_mercenariesBeingDestressed;
};

struct PowerplantLevelInfo
{
    PowerplantLevelInfo()
        : aetheriteOreTaken(0), energyLimit(0), energyGiven(0), maxCycles(0), basicCostInEnergy(0){}

    unsigned aetheriteOreTaken;
    unsigned energyLimit;
    unsigned energyGiven;
    unsigned maxCycles;
    unsigned basicCostInEnergy;
};

class Powerplant : public Building
{
    Q_OBJECT
public:
    explicit Powerplant(Base *base, unsigned level, const QVector<PowerplantLevelInfo> &levelsInfo) noexcept;

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
        return 0-(m_levelsInfo.value(currentLevel()).energyGiven * m_currentCycles);
    }
    Q_INVOKABLE int productionInEnergySingle() const noexcept
    {
        return 0-(m_levelsInfo.value(currentLevel())).energyGiven;
    }
    Q_INVOKABLE int productionInEnergySingleAfterUpgrade() const noexcept
    {
        return 0-(m_levelsInfo.value(currentLevel()+1)).energyGiven;
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
        return m_levelsInfo.value(currentLevel()).aetheriteOreTaken * m_currentCycles;
    }
    Q_INVOKABLE int useCostInAetheriteSingle() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).aetheriteOreTaken;
    }
    Q_INVOKABLE int useCostInAetheriteSingleAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).aetheriteOreTaken;
    }

    Q_INVOKABLE int energyLimit() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).energyLimit;
    }
    Q_INVOKABLE int energyLimitAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).energyLimit;
    }

    void exchangeResources() noexcept;

    Q_INVOKABLE void setCurrentCycles(unsigned amount) noexcept;
    Q_INVOKABLE unsigned currentCycles() const noexcept
    {
        return m_currentCycles;
    }
    Q_INVOKABLE unsigned maxCycles() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).maxCycles;
    }
    Q_INVOKABLE unsigned maxCyclesAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).maxCycles;
    }

    void setLevelsInfo(const QVector <PowerplantLevelInfo> &info) noexcept;

    Q_INVOKABLE unsigned upgradeTimeRemaining() noexcept;

private:
    QVector <PowerplantLevelInfo> m_levelsInfo;
    unsigned m_currentCycles;
};

struct FactoryLevelInfo
{
    FactoryLevelInfo()
        : aetheriteOreTaken(0), buildingMaterialsGiven(0), basicCostInEnergy(0),maxCycles(0){}

    unsigned aetheriteOreTaken;
    unsigned buildingMaterialsGiven;
    unsigned maxCycles;
    unsigned basicCostInEnergy;
};

class Factory : public Building
{
    Q_OBJECT
public:
    explicit Factory(Base *base, unsigned level, const QVector <FactoryLevelInfo> &levelsInfo) noexcept;

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
        return 0;
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
        return 0-(m_levelsInfo.value(currentLevel()).buildingMaterialsGiven * m_currentCycles);
    }
    Q_INVOKABLE int productionInBuildingMaterialsSingle() const noexcept
    {
        return 0-(m_levelsInfo.value(currentLevel())).buildingMaterialsGiven;
    }
    Q_INVOKABLE int productionInBuildingMaterialsSingleAfterUpgrade() const noexcept
    {
        return 0-(m_levelsInfo.value(currentLevel()+1)).buildingMaterialsGiven;
    }

    Q_INVOKABLE int basicCostInAetherite() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE int useCostInAetherite() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).aetheriteOreTaken * m_currentCycles;
    }
    Q_INVOKABLE int useCostInAetheriteSingle() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).aetheriteOreTaken;
    }
    Q_INVOKABLE int useCostInAetheriteSingleAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).aetheriteOreTaken;
    }

    void exchangeResources() noexcept;

    Q_INVOKABLE void setCurrentCycles(unsigned amount) noexcept;
    Q_INVOKABLE unsigned currentCycles() const noexcept
    {
        return m_currentCycles;
    }
    Q_INVOKABLE unsigned maxCycles() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).maxCycles;
    }
    Q_INVOKABLE unsigned maxCyclesAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).maxCycles;
    }

    void setLevelsInfo(const QVector <FactoryLevelInfo> &info) noexcept;

    Q_INVOKABLE unsigned upgradeTimeRemaining() noexcept;

private:
    QVector <FactoryLevelInfo> m_levelsInfo;
    unsigned m_currentCycles;
};

struct CoolRoomLevelInfo
{
    CoolRoomLevelInfo()
        : foodSuppliesLimit(0), basicCostInEnergy(0){}

    unsigned foodSuppliesLimit;
    unsigned basicCostInEnergy;
};

class CoolRoom : public Building
{
    Q_OBJECT
public:
    explicit CoolRoom(Base *base, unsigned level, const QVector <CoolRoomLevelInfo> &levelsInfo) noexcept;

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
        return 0;
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

    Q_INVOKABLE int foodSuppliesLimit() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).foodSuppliesLimit;
    }
    Q_INVOKABLE int foodSuppliesLimitAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).foodSuppliesLimit;
    }

    void setLevelsInfo(const QVector <CoolRoomLevelInfo> &info) noexcept;

    Q_INVOKABLE unsigned upgradeTimeRemaining() noexcept;

private:
    QVector <CoolRoomLevelInfo> m_levelsInfo;
};

struct StorageRoomLevelInfo
{
    StorageRoomLevelInfo()
        : buildingMaterialsLimit(0), basicCostInEnergy(0){}

    unsigned buildingMaterialsLimit;
    unsigned basicCostInEnergy;
};

class StorageRoom : public Building
{
    Q_OBJECT
public:
    explicit StorageRoom(Base *base, unsigned level, const QVector <StorageRoomLevelInfo> &levelsInfo) noexcept;

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
        return 0;
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

    Q_INVOKABLE int buildingMaterialsLimit() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).buildingMaterialsLimit;
    }
    Q_INVOKABLE int buildingMaterialsLimitAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).buildingMaterialsLimit;
    }

    void setLevelsInfo(const QVector <StorageRoomLevelInfo> &info) noexcept;

    Q_INVOKABLE unsigned upgradeTimeRemaining() noexcept;

private:
    QVector <StorageRoomLevelInfo> m_levelsInfo;
};

struct AetheriteSiloLevelInfo
{
    AetheriteSiloLevelInfo()
        : aetheriteOreLimit(0), basicCostInEnergy(0){}

    unsigned aetheriteOreLimit;
    unsigned basicCostInEnergy;
};

class AetheriteSilo : public Building
{
    Q_OBJECT
public:
    explicit AetheriteSilo(Base *base, unsigned level, const QVector <AetheriteSiloLevelInfo> &levelsInfo) noexcept;

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
        return 0;
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

    Q_INVOKABLE int aetheriteLimit() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).aetheriteOreLimit;
    }
    Q_INVOKABLE int aetheriteLimitAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).aetheriteOreLimit;
    }

    void setLevelsInfo(const QVector <AetheriteSiloLevelInfo> &info) noexcept;

    Q_INVOKABLE unsigned upgradeTimeRemaining() noexcept;

private:
    QVector <AetheriteSiloLevelInfo> m_levelsInfo;
};

struct BarracksLevelInfo
{
    BarracksLevelInfo()
        : mercenariesLimit(0), basicCostInEnergy(0){}

    unsigned mercenariesLimit;
    unsigned basicCostInEnergy;
};

class Barracks : public Building
{
    Q_OBJECT
public:
    explicit Barracks(Base *base, unsigned level, const QVector <BarracksLevelInfo> &levelsInfo) noexcept;

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
        return 0;
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

    Q_INVOKABLE int mercenariesLimit() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).mercenariesLimit;
    }
    Q_INVOKABLE int mercenariesLimitAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).mercenariesLimit;
    }

    void setLevelsInfo(const QVector <BarracksLevelInfo> &info) noexcept;

    Q_INVOKABLE unsigned upgradeTimeRemaining() noexcept;

private:
    QVector <BarracksLevelInfo> m_levelsInfo;
};

struct DockingStationLevelInfo
{
    DockingStationLevelInfo()
        : recruitsAmount(0), waitingTime(0), profitability(0), equipmentsAmount(0), maxTier(0), basicCostInEnergy(0){}

    unsigned recruitsAmount;
    unsigned waitingTime;
    unsigned profitability;
    unsigned equipmentsAmount;
    unsigned maxTier;
    unsigned basicCostInEnergy;
};

struct ActiveTransaction
{
    ActiveTransaction()
        : sourceRes(BaseEnums::R_Energy), targetRes(BaseEnums::R_Energy), sourceAmount(0), targetAmount(0){}
    ActiveTransaction(BaseEnums::Resource _sourceRes, BaseEnums::Resource _targetRes, unsigned _sourceAmount, unsigned _targetAmount)
        : sourceRes(_sourceRes), targetRes(_targetRes), sourceAmount(_sourceAmount), targetAmount(_targetAmount){}

    BaseEnums::Resource sourceRes, targetRes;
    unsigned sourceAmount, targetAmount;
};

QDataStream &operator<<(QDataStream &stream, const ActiveTransaction &transaction) noexcept;
QDataStream &operator>>(QDataStream &stream, ActiveTransaction &transaction) noexcept;

class DockingStation : public Building
{
    Q_OBJECT

    Q_PROPERTY(Mercenary* recruitPreparedForQML MEMBER m_recruitPreparedForQML)
    Q_PROPERTY(Equipment* equipmentPreparedForQML MEMBER m_equipmentPreparedForQML)

    friend class Base;

public:
    explicit DockingStation(Base *base, unsigned level, const QVector <DockingStationLevelInfo> &levelsInfo) noexcept;

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
        return 0;
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

    Q_INVOKABLE int recruitsAmount() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).recruitsAmount;
    }
    Q_INVOKABLE int recruitsAmountAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).recruitsAmount;
    }
    Q_INVOKABLE int readyRecruitsAmount() const noexcept
    {
        return m_recruits.size();
    }
    void prepareRecruits() noexcept;
    Q_INVOKABLE void prepareRecruitForQML(unsigned slot) noexcept;
    Q_INVOKABLE void hireMercenary(const QString &name, unsigned eta) noexcept;
    void doRecrutationStuff() noexcept;
    QStringList getRecruitsNames() const noexcept;
    QVector <QPair <Mercenary *, unsigned> > arrivingMercenaries() noexcept
    {
        return m_arrivingMercenaries;
    }
    void cancelMercenaryArrival(const QString &name) noexcept;
    Q_INVOKABLE int waitingTime() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).waitingTime;
    }
    Q_INVOKABLE int waitingTimeAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).waitingTime;
    }

    Q_INVOKABLE int profitability() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).profitability;
    }
    Q_INVOKABLE int profitabilityAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).profitability;
    }

    Q_INVOKABLE int equipmentsAmount() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).equipmentsAmount;
    }
    Q_INVOKABLE int equipmentsAmountAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).equipmentsAmount;
    }

    Q_INVOKABLE int maxTier() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).maxTier;
    }
    Q_INVOKABLE int maxTierAfterUpgrade() const noexcept
    {
        return m_levelsInfo.value(currentLevel()+1).maxTier;
    }

    void setLevelsInfo(const QVector <DockingStationLevelInfo> &info) noexcept
    {
        m_levelsInfo=info;
    }
    void setTradingTables(const QVector <QMap <QPair <BaseEnums::Resource, BaseEnums::Resource>, float> > &tradingTables) noexcept
    {
        m_tradingTables=tradingTables;
    }

    Q_INVOKABLE unsigned upgradeTimeRemaining() noexcept;

    unsigned calculateTransaction(BaseEnums::Resource sourceRes, BaseEnums::Resource targetRes, unsigned sourceAmount) const noexcept;
    Q_INVOKABLE unsigned calculateTransaction(unsigned sourceRes, unsigned targetRes, unsigned targetAmount) const noexcept;

    Q_INVOKABLE void startTransaction(unsigned sourceRes, unsigned targetRes, unsigned targetAmount) noexcept;
    void handleActiveTransactions() noexcept;
    inline const QVector <QPair <ActiveTransaction, unsigned> > &activeTransactions() const noexcept
    {
        return m_activeTransactions;
    }

    QVector <QString> availableEquipmentsNames() const noexcept
    {
        QVector <QString> r;
        for (int i=0;i<m_equipments.size();++i)
            r+=m_equipments[i]->name();
        return r;
    }
    Q_INVOKABLE unsigned readyEquipmentsAmount() const noexcept
    {
        return m_equipments.size();
    }
    void prepareEquipments() noexcept;
    Q_INVOKABLE void prepareEquipmentForQML(unsigned pos) noexcept;
    Q_INVOKABLE void buyEquipment(unsigned pos, unsigned eta) noexcept;
    void doBuyingEquipmentStuff() noexcept;
    inline QVector <QPair <Equipment *, unsigned> > arrivingEquipments() noexcept
    {
        return m_arrivingEquipments;
    }

    Q_INVOKABLE int remainingDaysUntilMercenaryArrival(const QString &mercenaryName) const noexcept;

private:
    void loadRecruits() noexcept;
    void clearRecruits() noexcept;
    void addRecruitFromSave(Mercenary *mercenary) noexcept
    {
        m_recruits.push_back(mercenary);
    }
    void setActiveTransactionsFromSave(const QVector <QPair <ActiveTransaction, unsigned> > &transactions) noexcept
    {
        m_activeTransactions=transactions;
    }
    void addArrivingMercenaryFromSave(const QPair <Mercenary *, unsigned> &arrMercenary) noexcept
    {
        m_arrivingMercenaries+=arrMercenary;
    }
    void loadEquipments() noexcept;
    void clearEquipments() noexcept;
    void addEquipmentFromSave(Equipment *eq) noexcept;
    void addArrivingEquipmentFromSave(const QPair <Equipment *, unsigned> &arrEq) noexcept
    {
        m_arrivingEquipments+=arrEq;
    }

    QVector <DockingStationLevelInfo> m_levelsInfo;
    QVector <QMap <QPair <BaseEnums::Resource, BaseEnums::Resource>, float> > m_tradingTables;
    QVector <Mercenary *> m_recruits;
    Mercenary *m_recruitPreparedForQML;
    QVector <QPair <Mercenary *, unsigned> > m_arrivingMercenaries;//mercenary, ETA
    QVector <QPair <ActiveTransaction, unsigned> > m_activeTransactions;
    QVector <Equipment *> m_equipments;
    Equipment *m_equipmentPreparedForQML;
    QVector <QPair <Equipment *, unsigned> > m_arrivingEquipments;//eq, ETA
};

class GameClock;
class Game;
class MissionInitializer;
class UnifiedReport;

class Base : public QObject
{
    Q_OBJECT

    Q_PROPERTY(CentralUnit* centralUnit MEMBER m_centralUnit)
    Q_PROPERTY(Hospital* hospital MEMBER m_hospital)
    Q_PROPERTY(TrainingGround* trainingGround MEMBER m_trainingGround)
    Q_PROPERTY(Gym* gym MEMBER m_gym)
    Q_PROPERTY(Laboratory* laboratory MEMBER m_laboratory)
    Q_PROPERTY(PlayingField* playingField MEMBER m_playingField)
    Q_PROPERTY(Bar* bar MEMBER m_bar)
    Q_PROPERTY(Shrine* shrine MEMBER m_shrine)
    Q_PROPERTY(Seclusion* seclusion MEMBER m_seclusion)
    Q_PROPERTY(Powerplant* powerplant MEMBER m_powerplant)
    Q_PROPERTY(Factory* factory MEMBER m_factory)
    Q_PROPERTY(CoolRoom* coolRoom MEMBER m_coolRoom)
    Q_PROPERTY(StorageRoom* storageRoom MEMBER m_storageRoom)
    Q_PROPERTY(AetheriteSilo* aetheriteSilo MEMBER m_aetheriteSilo)
    Q_PROPERTY(Barracks* barracks MEMBER m_barracks)
    Q_PROPERTY(DockingStation* dockingStation MEMBER m_dockingStation)

    Q_PROPERTY(GameClock* gameClock MEMBER m_gameClock)

    Q_PROPERTY(MercenariesContainer* mercenaries MEMBER m_mercenaries)

    Q_PROPERTY(Equipment* preparedAvailableEquipment MEMBER m_preparedAvailableEquipment)

    Q_PROPERTY(MissionInitializer* missionInitializer MEMBER m_missionInitializer)

    Q_PROPERTY(Database* database MEMBER m_database)

    Q_PROPERTY(Mission* preparedMission MEMBER m_preparedMission)
    Q_PROPERTY(UnifiedReport* preparedReport MEMBER m_preparedReport)

    friend class H4X;

public:
    explicit Base(Game *gameObject) noexcept;
    void setupNewBase() noexcept;
    ~Base() noexcept;

    //save
    void loadSaveData(const SaveData &data) noexcept;//only use before proper game start
    SaveData getSaveData() noexcept;

    //buildings
    CentralUnit *centralUnit() noexcept
    {
        return static_cast<CentralUnit *>(m_buildings.value(BaseEnums::B_CentralUnit));
    }
    Hospital *hospital() noexcept
    {
        return static_cast<Hospital *>(m_buildings.value(BaseEnums::B_Hospital));
    }
    TrainingGround *trainingGround() noexcept
    {
        return static_cast<TrainingGround *>(m_buildings.value(BaseEnums::B_TrainingGround));
    }
    Gym *gym() noexcept
    {
        return static_cast<Gym *>(m_buildings.value(BaseEnums::B_Gym));
    }
    Laboratory *laboratory() noexcept
    {
        return static_cast<Laboratory *>(m_buildings.value(BaseEnums::B_Laboratory));
    }
    PlayingField *playingField() noexcept
    {
        return static_cast<PlayingField *>(m_buildings.value(BaseEnums::B_PlayingField));
    }
    Bar *bar() noexcept
    {
        return static_cast<Bar *>(m_buildings.value(BaseEnums::B_Bar));
    }
    Shrine *shrine() noexcept
    {
        return static_cast<Shrine *>(m_buildings.value(BaseEnums::B_Shrine));
    }
    Seclusion *seclusion() noexcept
    {
        return static_cast<Seclusion *>(m_buildings.value(BaseEnums::B_Seclusion));
    }
    Powerplant *powerplant() noexcept
    {
        return static_cast<Powerplant *>(m_buildings.value(BaseEnums::B_Powerplant));
    }
    Factory *factory() noexcept
    {
        return static_cast<Factory *>(m_buildings.value(BaseEnums::B_Factory));
    }
    CoolRoom *coolRoom() noexcept
    {
        return static_cast<CoolRoom *>(m_buildings.value(BaseEnums::B_CoolRoom));
    }
    StorageRoom *storageRoom() noexcept
    {
        return static_cast<StorageRoom *>(m_buildings.value(BaseEnums::B_StorageRoom));
    }
    AetheriteSilo *aetheriteSilo() noexcept
    {
        return static_cast<AetheriteSilo *>(m_buildings.value(BaseEnums::B_AetheriteSilo));
    }
    Barracks *barracks() noexcept
    {
        return static_cast<Barracks *>(m_buildings.value(BaseEnums::B_Barracks));
    }
    DockingStation *dockingStation() noexcept
    {
        return static_cast<DockingStation *>(m_buildings.value(BaseEnums::B_DockingStation));
    }

    Q_INVOKABLE void startNewDay() noexcept;

    Q_INVOKABLE void startNewWeek() noexcept;

    unsigned buildingLevel(BaseEnums::Building buildingName) const noexcept
    {
        return m_buildingLevels.value(buildingName,0);
    }
    BuildingUpgradeRequirements buildingRequirements(BaseEnums::Building buildingName, unsigned level) const noexcept;
    QString buildingDescription(BaseEnums::Building buildingName) const noexcept
    {
        return m_buildingDescriptions.value(buildingName);
    }

    //resources
    Q_INVOKABLE inline int currentEnergyAmount() const noexcept
    {
        return m_energy;
    }
    Q_INVOKABLE inline int currentFoodSuppliesAmount() const noexcept
    {
        return m_foodSupplies;
    }
    Q_INVOKABLE inline int currentBuildingMaterialsAmount() const noexcept
    {
        return m_buildingMaterials;
    }
    Q_INVOKABLE inline int currentAetheriteAmount() const noexcept
    {
        return m_aetherite;
    }

    Q_INVOKABLE int currentTotalSalary() const noexcept;

    void setCurrentEnergyAmount(unsigned amount) noexcept;
    void setCurrentFoodSuppliesAmount(unsigned amount) noexcept;
    void setCurrentBuildingMaterialsAmount(unsigned amount) noexcept;
    void setCurrentAetheriteAmount(unsigned amount) noexcept;

    inline bool canDecreaseEnergyAmount(unsigned amount) const noexcept
    {
        return m_energy>=amount;
    }
    inline bool canDecreaseFoodSuppliesAmount(unsigned amount) const noexcept
    {
        return m_foodSupplies>=amount;
    }
    inline bool canDecreaseBuildingMaterialsAmount(unsigned amount) const noexcept
    {
        return m_buildingMaterials>=amount;
    }
    inline bool canDecreaseAetheriteAmount(unsigned amount) const noexcept
    {
        return m_aetherite>=amount;
    }

    void decreaseEnergyAmount(unsigned amount) noexcept;
    void decreaseFoodSuppliesAmount(unsigned amount) noexcept;
    void decreaseBuildingMaterialsAmount(unsigned amount) noexcept;
    void decreaseAetheriteAmount(unsigned amount) noexcept;

    void increaseEnergyAmount(unsigned amount) noexcept;
    void increaseFoodSuppliesAmount(unsigned amount) noexcept;
    void increaseBuildingMaterialsAmount(unsigned amount) noexcept;
    void increaseAetheriteAmount(unsigned amount) noexcept;

    Q_INVOKABLE int currentEnergyIncome() const noexcept;
    Q_INVOKABLE int currentFoodSuppliesIncome() const noexcept;
    Q_INVOKABLE int currentBuildingMaterialsIncome() const noexcept;
    Q_INVOKABLE int currentAetheriteIncome() const noexcept;

    Q_INVOKABLE inline int currentEnergyLimit() noexcept
    {
        return powerplant()->energyLimit();
    }
    Q_INVOKABLE inline int currentFoodSuppliesLimit() noexcept
    {
        return coolRoom()->foodSuppliesLimit();
    }
    Q_INVOKABLE inline int currentBuildingMaterialsLimit() noexcept
    {
        return storageRoom()->buildingMaterialsLimit();
    }
    Q_INVOKABLE inline int currentAetheriteLimit() noexcept
    {
        return aetheriteSilo()->aetheriteLimit();
    }

    void setBuildingLevel(BaseEnums::Building buildingName, unsigned level) noexcept;
    void setBuildingDescription(BaseEnums::Building buildingName, const QString &desc) noexcept;
    void setBuildingDescriptions(const QVector <QPair <BaseEnums::Building, QString> > &desc) noexcept;

    void setBuildingRequirements(const QMap <QPair <BaseEnums::Building, unsigned>, BuildingUpgradeRequirements> &reqs) noexcept;

    Building *getBuilding(BaseEnums::Building buildingName) noexcept;

    //mercenaries
    inline MercenariesContainer *mercenaries() noexcept
    {
        return m_mercenaries;
    }
    inline QMap <QString, unsigned> &mercenaryDockingStationBans() noexcept
    {
        return m_mercenaryDockingStationBans;
    }
    void recalculateAmountOfMercenarySlots() const noexcept
    {
        m_mercenaries->setAmountOfSlots(m_barracks->mercenariesLimit());;
    }

    //equipment
    inline QVector <Equipment *> &availableEquipment() noexcept
    {
        return m_availableEquipment;
    }
    Q_INVOKABLE inline unsigned amountOfAvailableEquipment() const noexcept
    {
        return m_availableEquipment.size();
    }
    Q_INVOKABLE unsigned amountOfAvailableArmors() const noexcept;
    Q_INVOKABLE unsigned amountOfAvailableWeaponsTools() const noexcept;
    Q_INVOKABLE void prepareAvailableEquipment(unsigned index) noexcept;

    //game clock
    inline GameClock *gameClock() noexcept
    {
        return m_gameClock;
    }

    //missions
    void startMission(Mission *mission) noexcept;
    inline const QVector <Mission *> &missions() const noexcept
    {
        return m_missions;
    }
    inline Database *database() noexcept
    {
        return m_database;
    }
    void removeMission(Mission *mission) noexcept;

    Q_INVOKABLE inline unsigned amountOfMissions() const noexcept
    {
        return m_missions.size();
    }
    Q_INVOKABLE void prepareMission(unsigned index) noexcept;

    //reports
    Q_INVOKABLE inline unsigned amountOfReports() const noexcept
    {
        return m_reports.size();
    }
    Q_INVOKABLE inline unsigned amountOfNewReports() const noexcept
    {
        return m_newReports.size();
    }
    Q_INVOKABLE void prepareReport(unsigned index) noexcept;
    Q_INVOKABLE void prepareNewReport(unsigned index) noexcept;
    void addReport(UnifiedReport *report) noexcept;
    void registerLatestReportInMission(Mission *mission) noexcept;
    inline QVector <UnifiedReport *> &reports() noexcept
    {
        return m_reports;
    }
    Q_INVOKABLE void markAllAsRead() noexcept;
    Q_INVOKABLE void removeReport(unsigned index) noexcept;
    Q_INVOKABLE void clearReports() noexcept;

    Q_INVOKABLE int remainingMissionDaysForMercenary(const QString &mercenaryName);

    //game
    inline Game *gameObject() noexcept
    {
        return m_gameObject;
    }

private:
    //maps for buildings
    QMap <BaseEnums::Building, unsigned> m_buildingLevels;
    QMap <QPair <BaseEnums::Building, unsigned>, BuildingUpgradeRequirements> m_buildingRequirements;
    QMap <BaseEnums::Building, QString> m_buildingDescriptions;
    QMap <BaseEnums::Building, Building *> m_buildings;

    //direct pointers to specific buildings for QML
    CentralUnit *m_centralUnit;
    Hospital *m_hospital;
    TrainingGround *m_trainingGround;
    Gym *m_gym;
    Laboratory *m_laboratory;
    PlayingField *m_playingField;
    Bar *m_bar;
    Shrine *m_shrine;
    Seclusion *m_seclusion;
    Powerplant *m_powerplant;
    Factory *m_factory;
    CoolRoom *m_coolRoom;
    StorageRoom *m_storageRoom;
    AetheriteSilo *m_aetheriteSilo;
    Barracks *m_barracks;
    DockingStation *m_dockingStation;

    //resources
    unsigned m_energy;
    unsigned m_foodSupplies;
    unsigned m_buildingMaterials;
    unsigned m_aetherite;

    //mercenaries
    MercenariesContainer *m_mercenaries;
    QMap <QString, unsigned> m_mercenaryDockingStationBans;//in days; when banned, mercenary won't appear in docking station menu

    //equipment
    QVector <Equipment *> m_availableEquipment;
    Equipment *m_preparedAvailableEquipment;

    //game clock/timer
    void activateBuildingsAtDayEnd() noexcept;
    void handleMercenariesAtDayEnd() noexcept;
    void handleMercenariesAtWeekEnd() noexcept;

    GameClock *m_gameClock;

    //missions
    MissionInitializer *m_missionInitializer;
    Database *m_database;
    QVector <Mission *> m_missions;
    Mission *m_preparedMission;
    QVector <UnifiedReport *> m_reports;
    const unsigned m_maxReportsAmount=50;
    QVector <UnifiedReport *> m_newReports;
    UnifiedReport *m_preparedReport;

    //game
    Game *m_gameObject;
    bool m_freezeGameProgress;
};

#endif // BASE_H
