#ifndef BASE_H
#define BASE_H

#include <QVector>
#include <QMap>
#include <QObject>

#include "hero.h"
#include "saveparser.h"

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

protected:
    explicit Building(BaseEnums::Building buildingName, Base *base, unsigned level) noexcept;
    Base *base() noexcept
    {
        return m_base;
    }

private:
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
public:
    explicit Hospital(Base *base, unsigned level, const QVector <HospitalLevelInfo> &levelsInfo) noexcept;

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
        return m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy * (m_heroesBeingHealed.size() - m_heroesBeingHealed.count(NULL));
    }

    Q_INVOKABLE int basicCostInFoodSupplies() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).basicCostInFoodSupplies;
    }
    Q_INVOKABLE int useCostInFoodSupplies() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).perCapitaCostInFoodSupplies * (m_heroesBeingHealed.size() - m_heroesBeingHealed.count(NULL));
    }

    Q_INVOKABLE  int basicCostInBuildingMaterials() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE  int useCostInBuildingMaterials() const noexcept
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
    Q_INVOKABLE Hero *slot(int index) noexcept
    {
        return m_heroesBeingHealed.value(index,NULL);
    }

    Q_INVOKABLE int hpRestoredPerDay() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).hpRestored;
    }

    void healHeroes() noexcept;

    void setLevelsInfo(const QVector <HospitalLevelInfo> &info) noexcept;

private:
    QVector <HospitalLevelInfo> m_levelsInfo;

    QVector <Hero *> m_heroesBeingHealed;
};

struct TrainingGroundLevelInfo
{
    TrainingGroundLevelInfo()
        : amountOfSlots(0), basicCostInEnergy(0), perCapitaCostInEnergy(0), combatEffectivenessBonus(0), proficiencyBonus(0), clevernessBonus(0), duration(0){}

    unsigned amountOfSlots;
    unsigned basicCostInEnergy;
    unsigned perCapitaCostInEnergy;
    int combatEffectivenessBonus;
    int proficiencyBonus;
    int clevernessBonus;
    unsigned duration;
};

class TrainingGround : public Building
{
    Q_OBJECT
public:
    explicit TrainingGround(Base *base, unsigned level, const QVector <TrainingGroundLevelInfo> &levelsInfo) noexcept;

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
        return m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy * (m_heroesBeingTrained.size() - m_heroesBeingTrained.count(NULL));
    }

    Q_INVOKABLE int basicCostInFoodSupplies() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE int useCostInFoodSupplies() const noexcept
    {
        return 0;
    }

    Q_INVOKABLE  int basicCostInBuildingMaterials() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE  int useCostInBuildingMaterials() const noexcept
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
    Q_INVOKABLE Hero *slot(int index) noexcept
    {
        return m_heroesBeingTrained.value(index,NULL);
    }

    Q_INVOKABLE int combatEffectivenessBonus() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).combatEffectivenessBonus;
    }
    Q_INVOKABLE int proficiencyBonus() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).proficiencyBonus;
    }
    Q_INVOKABLE int clevernessBonus() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).clevernessBonus;
    }

    void trainHeroes() noexcept;

    void setLevelsInfo(const QVector <TrainingGroundLevelInfo> &info) noexcept;

private:
    QVector <TrainingGroundLevelInfo> m_levelsInfo;

    QVector <Hero *> m_heroesBeingTrained;
};

struct GymLevelInfo
{
    GymLevelInfo()
        : amountOfSlots(0), basicCostInEnergy(0), perCapitaCostInEnergy(0), combatEffectivenessBonus(0), proficiencyBonus(0), clevernessBonus(0), duration(0){}

    unsigned amountOfSlots;
    unsigned basicCostInEnergy;
    unsigned perCapitaCostInEnergy;
    int combatEffectivenessBonus;
    int proficiencyBonus;
    int clevernessBonus;
    unsigned duration;
};

class Gym : public Building
{
    Q_OBJECT
public:
    explicit Gym(Base *base, unsigned level, const QVector <GymLevelInfo> &levelsInfo) noexcept;

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
        return m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy * (m_heroesBeingTrained.size() - m_heroesBeingTrained.count(NULL));
    }

    Q_INVOKABLE int basicCostInFoodSupplies() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE int useCostInFoodSupplies() const noexcept
    {
        return 0;
    }

    Q_INVOKABLE  int basicCostInBuildingMaterials() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE  int useCostInBuildingMaterials() const noexcept
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
    Q_INVOKABLE Hero *slot(int index) noexcept
    {
        return m_heroesBeingTrained.value(index,NULL);
    }

    Q_INVOKABLE int combatEffectivenessBonus() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).combatEffectivenessBonus;
    }
    Q_INVOKABLE int proficiencyBonus() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).proficiencyBonus;
    }
    Q_INVOKABLE int clevernessBonus() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).clevernessBonus;
    }

    void trainHeroes() noexcept;

    void setLevelsInfo(const QVector <GymLevelInfo> &info) noexcept;

private:
    QVector <GymLevelInfo> m_levelsInfo;

    QVector <Hero *> m_heroesBeingTrained;
};

struct LaboratoryLevelInfo
{
    LaboratoryLevelInfo()
        : amountOfSlots(0), basicCostInEnergy(0), perCapitaCostInEnergy(0), combatEffectivenessBonus(0), proficiencyBonus(0), clevernessBonus(0), duration(0){}

    unsigned amountOfSlots;
    unsigned basicCostInEnergy;
    unsigned perCapitaCostInEnergy;
    int combatEffectivenessBonus;
    int proficiencyBonus;
    int clevernessBonus;
    unsigned duration;
};

class Laboratory : public Building
{
    Q_OBJECT
public:
    explicit Laboratory(Base *base, unsigned level, const QVector <LaboratoryLevelInfo> &levelsInfo) noexcept;

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
        return m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy * (m_heroesBeingTrained.size() - m_heroesBeingTrained.count(NULL));
    }

    Q_INVOKABLE int basicCostInFoodSupplies() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE int useCostInFoodSupplies() const noexcept
    {
        return 0;
    }

    Q_INVOKABLE  int basicCostInBuildingMaterials() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE  int useCostInBuildingMaterials() const noexcept
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
    Q_INVOKABLE Hero *slot(int index) noexcept
    {
        return m_heroesBeingTrained.value(index,NULL);
    }

    Q_INVOKABLE int combatEffectivenessBonus() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).combatEffectivenessBonus;
    }
    Q_INVOKABLE int proficiencyBonus() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).proficiencyBonus;
    }
    Q_INVOKABLE int clevernessBonus() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).clevernessBonus;
    }

    void trainHeroes() noexcept;

    void setLevelsInfo(const QVector <LaboratoryLevelInfo> &info) noexcept;

private:
    QVector <LaboratoryLevelInfo> m_levelsInfo;

    QVector <Hero *> m_heroesBeingTrained;
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
public:
    explicit PlayingField(Base *base, unsigned level, const QVector <PlayingFieldLevelInfo> &levelsInfo) noexcept;

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
        return m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy * (m_heroesBeingDestressed.size() - m_heroesBeingDestressed.count(NULL));
    }

    Q_INVOKABLE int basicCostInFoodSupplies() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE int useCostInFoodSupplies() const noexcept
    {
        return 0;
    }

    Q_INVOKABLE  int basicCostInBuildingMaterials() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE  int useCostInBuildingMaterials() const noexcept
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
    Q_INVOKABLE Hero *slot(int index) noexcept
    {
        return m_heroesBeingDestressed.value(index,NULL);
    }

    void destressHeroes() noexcept;

    void setLevelsInfo(const QVector <PlayingFieldLevelInfo> &info) noexcept;

private:
    QVector <PlayingFieldLevelInfo> m_levelsInfo;

    QVector <Hero *> m_heroesBeingDestressed;
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
public:
    explicit Bar(Base *base, unsigned level, const QVector <BarLevelInfo> &levelsInfo) noexcept;

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
        return m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy * (m_heroesBeingDestressed.size() - m_heroesBeingDestressed.count(NULL));
    }

    Q_INVOKABLE int basicCostInFoodSupplies() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE int useCostInFoodSupplies() const noexcept
    {
        return 0;
    }

    Q_INVOKABLE  int basicCostInBuildingMaterials() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE  int useCostInBuildingMaterials() const noexcept
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
    Q_INVOKABLE Hero *slot(int index) noexcept
    {
        return m_heroesBeingDestressed.value(index,NULL);
    }

    void destressHeroes() noexcept;

    void setLevelsInfo(const QVector <BarLevelInfo> &info) noexcept;

private:
    QVector <BarLevelInfo> m_levelsInfo;

    QVector <Hero *> m_heroesBeingDestressed;
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
public:
    explicit Shrine(Base *base, unsigned level, const QVector <ShrineLevelInfo> &levelsInfo) noexcept;

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
        return m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy * (m_heroesBeingDestressed.size() - m_heroesBeingDestressed.count(NULL));
    }

    Q_INVOKABLE int basicCostInFoodSupplies() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE int useCostInFoodSupplies() const noexcept
    {
        return 0;
    }

    Q_INVOKABLE  int basicCostInBuildingMaterials() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE  int useCostInBuildingMaterials() const noexcept
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
    Q_INVOKABLE Hero *slot(int index) noexcept
    {
        return m_heroesBeingDestressed.value(index,NULL);
    }

    void destressHeroes() noexcept;

    void setLevelsInfo(const QVector <ShrineLevelInfo> &info) noexcept;

private:
    QVector <ShrineLevelInfo> m_levelsInfo;

    QVector <Hero *> m_heroesBeingDestressed;
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
public:
    explicit Seclusion(Base *base, unsigned level, const QVector <SeclusionLevelInfo> &levelsInfo) noexcept;

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
        return m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy * (m_heroesBeingDestressed.size() - m_heroesBeingDestressed.count(NULL));
    }

    Q_INVOKABLE int basicCostInFoodSupplies() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE int useCostInFoodSupplies() const noexcept
    {
        return 0;
    }

    Q_INVOKABLE  int basicCostInBuildingMaterials() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE  int useCostInBuildingMaterials() const noexcept
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
    Q_INVOKABLE Hero *slot(int index) noexcept
    {
        return m_heroesBeingDestressed.value(index,NULL);
    }

    void destressHeroes() noexcept;

    void setLevelsInfo(const QVector <SeclusionLevelInfo> &info) noexcept;

private:
    QVector <SeclusionLevelInfo> m_levelsInfo;

    QVector <Hero *> m_heroesBeingDestressed;
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
        return (unsigned)0-(m_levelsInfo.value(currentLevel()).energyGiven * m_currentCycles);
    }

    Q_INVOKABLE int basicCostInFoodSupplies() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE int useCostInFoodSupplies() const noexcept
    {
        return 0;
    }

    Q_INVOKABLE  int basicCostInBuildingMaterials() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE  int useCostInBuildingMaterials() const noexcept
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

    Q_INVOKABLE int energyLimit() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).energyLimit;
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

    void setLevelsInfo(const QVector <PowerplantLevelInfo> &info) noexcept;

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

    Q_INVOKABLE  int basicCostInBuildingMaterials() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE  int useCostInBuildingMaterials() const noexcept
    {
        return (unsigned)0-(m_levelsInfo.value(currentLevel()).buildingMaterialsGiven * m_currentCycles);
    }

    Q_INVOKABLE int basicCostInAetherite() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE int useCostInAetherite() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).aetheriteOreTaken * m_currentCycles;
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

    void setLevelsInfo(const QVector <FactoryLevelInfo> &info) noexcept;

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

    Q_INVOKABLE  int basicCostInBuildingMaterials() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE  int useCostInBuildingMaterials() const noexcept
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

    void setLevelsInfo(const QVector <CoolRoomLevelInfo> &info) noexcept;

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

    Q_INVOKABLE  int basicCostInBuildingMaterials() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE  int useCostInBuildingMaterials() const noexcept
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

    void setLevelsInfo(const QVector <StorageRoomLevelInfo> &info) noexcept;

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

    Q_INVOKABLE  int basicCostInBuildingMaterials() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE  int useCostInBuildingMaterials() const noexcept
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

    void setLevelsInfo(const QVector <AetheriteSiloLevelInfo> &info) noexcept;

private:
    QVector <AetheriteSiloLevelInfo> m_levelsInfo;
};

struct BarracksLevelInfo
{
    BarracksLevelInfo()
        : heroesLimit(0), basicCostInEnergy(0){}

    unsigned heroesLimit;
    unsigned basicCostInEnergy;
};

class Barracks : public Building
{
    Q_OBJECT
public:
    explicit Barracks(Base *base, unsigned level, const QVector <BarracksLevelInfo> &levelsInfo) noexcept;

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

    Q_INVOKABLE  int basicCostInBuildingMaterials() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE  int useCostInBuildingMaterials() const noexcept
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

    Q_INVOKABLE int heroesLimit() const noexcept
    {
        return m_levelsInfo.value(currentLevel()).heroesLimit;
    }

    void setLevelsInfo(const QVector <BarracksLevelInfo> &info) noexcept;

private:
    QVector <BarracksLevelInfo> m_levelsInfo;
};

struct DockingStationLevelInfo
{
    DockingStationLevelInfo()
        : recruitsAmount(0), basicCostInEnergy(0){}

    unsigned recruitsAmount;
    unsigned basicCostInEnergy;
};

class DockingStation : public Building
{
    Q_OBJECT
public:
    explicit DockingStation(Base *base, unsigned level, const QVector <DockingStationLevelInfo> &levelsInfo) noexcept;

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

    Q_INVOKABLE  int basicCostInBuildingMaterials() const noexcept
    {
        return 0;
    }
    Q_INVOKABLE  int useCostInBuildingMaterials() const noexcept
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

    void setLevelsInfo(const QVector <DockingStationLevelInfo> &info) noexcept;

private:
    QVector <DockingStationLevelInfo> m_levelsInfo;
};

class GameClock;

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

public:
    explicit Base(QObject *parent=0) noexcept;
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
    Q_INVOKABLE void activateBuildingsAtDayEnd() noexcept;

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
    Q_INVOKABLE int currentEnergyAmount() const noexcept
    {
        return m_energy;
    }
    Q_INVOKABLE int currentFoodSuppliesAmount() const noexcept
    {
        return m_foodSupplies;
    }
    Q_INVOKABLE int currentBuildingMaterialsAmount() const noexcept
    {
        return m_buildingMaterials;
    }
    Q_INVOKABLE int currentAetheriteAmount() const noexcept
    {
        return m_aetherite;
    }

    void setCurrentEnergyAmount(unsigned amount) noexcept;
    void setCurrentFoodSuppliesAmount(unsigned amount) noexcept;
    void setCurrentBuildingMaterialsAmount(unsigned amount) noexcept;
    void setCurrentAetheriteAmount(unsigned amount) noexcept;

    Q_INVOKABLE int currentEnergyIncome() const noexcept
    {
        int r=0;
        for (int i=0;i<static_cast<int>(BaseEnums::B_END);++i)
            r-=m_buildings.value(static_cast<BaseEnums::Building>(i))->currentCostInEnergy();
        return r;
    }
    Q_INVOKABLE int currentFoodSuppliesIncome() const noexcept
    {
        int r=0;
        for (int i=0;i<static_cast<int>(BaseEnums::B_END);++i)
            r-=m_buildings.value(static_cast<BaseEnums::Building>(i))->currentCostInFoodSupplies();
        return r;
    }
    Q_INVOKABLE int currentBuildingMaterialsIncome() const noexcept
    {
        int r=0;
        for (int i=0;i<static_cast<int>(BaseEnums::B_END);++i)
            r-=m_buildings.value(static_cast<BaseEnums::Building>(i))->currentCostInBuildingMaterials();
        return r;
    }
    Q_INVOKABLE int currentAetheriteIncome() const noexcept
    {
        int r=0;
        for (int i=0;i<static_cast<int>(BaseEnums::B_END);++i)
            r-=m_buildings.value(static_cast<BaseEnums::Building>(i))->currentCostInAetherite();
        return r;
    }

    Q_INVOKABLE int currentEnergyLimit() noexcept
    {
        return powerplant()->energyLimit();
    }
    Q_INVOKABLE int currentFoodSuppliesLimit() noexcept
    {
        return coolRoom()->foodSuppliesLimit();
    }
    Q_INVOKABLE int currentBuildingMaterialsLimit() noexcept
    {
        return storageRoom()->buildingMaterialsLimit();
    }
    Q_INVOKABLE int currentAetheriteLimit() noexcept
    {
        return aetheriteSilo()->aetheriteLimit();
    }

    void setBuildingLevel(BaseEnums::Building buildingName, unsigned level) noexcept;
    void setBuildingDescription(BaseEnums::Building buildingName, const QString &desc) noexcept;
    void setBuildingDescriptions(const QVector <QPair <BaseEnums::Building, QString> > &desc) noexcept;

    void setBuildingRequirements(const QMap <QPair <BaseEnums::Building, unsigned>, BuildingUpgradeRequirements> &reqs) noexcept;

    //heroes
    QVector <Hero *> &heroes() noexcept
    {
        return m_heroes;
    }

    //game clock
    GameClock *gameClock() noexcept
    {
        return m_gameClock;
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

    //heroes
    QVector <Hero *> m_heroes;

    //game clock/timer
    GameClock *m_gameClock;
};

#endif // BASE_H
