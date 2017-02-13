#ifndef BASE_H
#define BASE_H

#include <QVector>
#include <QMap>
#include <QObject>

#include "hero.h"

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
        B_PowerPlant,
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

struct TechTreeBuildingRequirements
{
    QMap <BaseEnums::Building, unsigned> requiredBuildingLevels;
    unsigned requiredBuildingMaterials;
    unsigned requiredTime;
};

class TechTree
{
    friend class TechTreeBuilder;
public:
    TechTreeBuildingRequirements getRequirementsForUpgrade(const QPair <BaseEnums::Building, int> &upgrade) const noexcept;
    bool isThereSuchUpgrade(const QPair <BaseEnums::Building, int> &upgrade) const noexcept;

private:
    TechTree() noexcept {}

    void addUpgradeNode(const QPair <BaseEnums::Building, int> &upgrade, const TechTreeBuildingRequirements &requirements) noexcept;
    void reset() noexcept;

    QMap <QPair <BaseEnums::Building, int> , TechTreeBuildingRequirements> m_nodes;
};

class TechTreeBuilder
{
public:
    TechTreeBuilder() noexcept;
    ~TechTreeBuilder() noexcept;

    TechTree *getTechTree() noexcept;
    void resetTechTree() noexcept;

    void addUpgrade(const QPair <BaseEnums::Building, int> &upgrade, const TechTreeBuildingRequirements &requirements) noexcept;

private:
    TechTreeBuilder(const TechTreeBuilder &other) noexcept = delete;

    void operator =(const TechTreeBuilder &other) noexcept = delete;

    TechTree *m_techTree;
};

class Building : public QObject
{
public:
    Q_INVOKABLE unsigned currentLevel() const noexcept;
    Q_INVOKABLE TechTreeBuildingRequirements requirementsForNextLevel() const noexcept = delete;
    Q_INVOKABLE bool tryUpgrading() noexcept;

    Q_INVOKABLE int basicCostInEnergy() const noexcept = delete;
    Q_INVOKABLE int useCostInEnergy() const noexcept = delete;

    Q_INVOKABLE int basicCostInFoodSupplies() const noexcept = delete;
    Q_INVOKABLE int useCostInFoodSupplies() const noexcept = delete;

    Q_INVOKABLE int basicCostInAetherite() const noexcept = delete;
    Q_INVOKABLE int useCostInAetherite() const noexcept = delete;

protected:
    Building(Base *base, unsigned level) noexcept;

private:
    Base *m_base;
    unsigned m_level;
};

class Hospital : public Building
{
public:
    Hospital(Base *base, unsigned level, const QVector <HospitalLevelInfo> &levelsInfo) noexcept;

    Q_INVOKABLE int amountOfSlots() const noexcept;
    Q_INVOKABLE Hero *slot(int index) noexcept
    {
        return m_heroesBeingHealed.value(index,NULL);
    }

    void healHeroes() noexcept;

private:
    QVector <HospitalLevelInfo> m_levelsInfo;

    QVector <Hero *> m_heroesBeingHealed;
};

class BuildingsBase : public QObject
{
    Q_OBJECT
public:
    BuildingsBase() noexcept;

    Q_INVOKABLE int buildingLvl(BaseEnums::Building buildingName) const noexcept;
    Q_INVOKABLE void setBuildingLvl(BaseEnums::Building buildingName, int buildingLvl) noexcept;

    Q_INVOKABLE bool isPowerPlantWorking() const noexcept
    {
        return m_isPowerPlantWorking;
    }
    Q_INVOKABLE void setIsPowerPlantWorking(bool isPowerPlantWorking) noexcept;

    Q_INVOKABLE bool isFactoryWorking() const noexcept
    {
        return m_isFactoryWorking;
    }
    Q_INVOKABLE void setIsFactoryWorking(bool isFactoryWorking) noexcept;

private:
    QMap <BaseEnums::Building, int> m_buildingsLvls;

    bool m_isPowerPlantWorking;
    bool m_isFactoryWorking;
};

struct HospitalLevelInfo
{
    HospitalLevelInfo()
        : amountOfSlots(0), basicCostInEnergy(0), perCapitaCostInEnergy(0), basicCostInFoodSupplies(0), perCapitaCostInFoodSupplies(0){}

    unsigned amountOfSlots;
    unsigned basicCostInEnergy;
    unsigned perCapitaCostInEnergy;
    unsigned basicCostInFoodSupplies;
    unsigned perCapitaCostInFoodSupplies;
};

class Hospital : public QObject
{
    Q_OBJECT
public:
    Hospital(BuildingsBase *buildingsBase) noexcept;

    Q_INVOKABLE int amountOfSlotsInHospital() const noexcept;
    Q_INVOKABLE Hero *slotInHospital(int index) noexcept
    {
        return m_heroesInHospital.value(index,NULL);
    }

    Q_INVOKABLE int hospitalBasicCostInEnergy() const noexcept;
    Q_INVOKABLE int hospitalUsageCostInEnergy() const noexcept;

    Q_INVOKABLE int hospitalBasicCostInFoodSupplies() const noexcept;
    Q_INVOKABLE int hospitalUsageCostInFoodSupplies() const noexcept;

    void healHeroes() noexcept;

    void setLevelsInfo(const QVector <HospitalLevelInfo> &info) noexcept;

private:
    BuildingsBase *m_buildingsBase;
    QVector <HospitalLevelInfo> m_levelsInfo;

    QVector <Hero *> m_heroesInHospital;
};

struct TrainingGroundLevelInfo
{
    TrainingGroundLevelInfo()
        : amountOfSlots(0), basicCostInEnergy(0), perCapitaCostInEnergy(0){}

    unsigned amountOfSlots;
    unsigned basicCostInEnergy;
    unsigned perCapitaCostInEnergy;
};

struct GymLevelInfo
{
    GymLevelInfo()
        : amountOfSlots(0), basicCostInEnergy(0), perCapitaCostInEnergy(0){}

    unsigned amountOfSlots;
    unsigned basicCostInEnergy;
    unsigned perCapitaCostInEnergy;
};

struct LaboratoryLevelInfo
{
    LaboratoryLevelInfo()
        : amountOfSlots(0), basicCostInEnergy(0), perCapitaCostInEnergy(0){}

    unsigned amountOfSlots;
    unsigned basicCostInEnergy;
    unsigned perCapitaCostInEnergy;
};

class TrainingBuildings : public QObject
{
    Q_OBJECT
public:
    TrainingBuildings(BuildingsBase *buildingsBase) noexcept;

    Q_INVOKABLE int amountOfSlotsInTrainingGround() const noexcept;
    Q_INVOKABLE Hero *slotInTrainingGround(int index) noexcept
    {
        return m_heroesInTrainingGround.value(index,NULL);
    }

    Q_INVOKABLE int amountOfSlotsInGym() const noexcept;
    Q_INVOKABLE Hero *slotInGym(int index) noexcept
    {
        return m_heroesInGym.value(index,NULL);
    }

    Q_INVOKABLE int amountOfSlotsInLaboratory() const noexcept;
    Q_INVOKABLE Hero *slotInLaboratory(int index) noexcept
    {
        return m_heroesInLaboratory.value(index,NULL);
    }

    Q_INVOKABLE int trainingBuildingsBaseCostInEnergy() const noexcept;
    Q_INVOKABLE int trainingBuildingsUsageCostInEnergy() const noexcept;

    void trainHeroes() noexcept;

    void setTrainingGroundLevelsInfo(const QVector <TrainingGroundLevelInfo> &info) noexcept;
    void setGymLevelsInfo(const QVector <GymLevelInfo> &info) noexcept;
    void setLaboratoryLevelsInfo(const QVector <LaboratoryLevelInfo> &info) noexcept;

private:
    BuildingsBase *m_buildingsBase;

    QVector <TrainingGroundLevelInfo> m_trainingGroundLevelsInfo;
    QVector <GymLevelInfo> m_gymLevelsInfo;
    QVector <LaboratoryLevelInfo> m_laboratoryLevelsInfo;

    QVector <Hero *> m_heroesInTrainingGround;
    QVector <Hero *> m_heroesInGym;
    QVector <Hero *> m_heroesInLaboratory;

};

struct PlayingFieldLevelInfo
{
    PlayingFieldLevelInfo()
        : amountOfSlots(0), basicCostInEnergy(0), perCapitaCostInEnergy(0){}

    unsigned amountOfSlots;
    unsigned basicCostInEnergy;
    unsigned perCapitaCostInEnergy;
};

struct BarLevelInfo
{
    BarLevelInfo()
        : amountOfSlots(0), basicCostInEnergy(0), perCapitaCostInEnergy(0){}

    unsigned amountOfSlots;
    unsigned basicCostInEnergy;
    unsigned perCapitaCostInEnergy;
};

struct ShrineLevelInfo
{
    ShrineLevelInfo()
        : amountOfSlots(0), basicCostInEnergy(0), perCapitaCostInEnergy(0){}

    unsigned amountOfSlots;
    unsigned basicCostInEnergy;
    unsigned perCapitaCostInEnergy;
};

struct SeclusionLevelInfo
{
    SeclusionLevelInfo()
        : amountOfSlots(0), basicCostInEnergy(0), perCapitaCostInEnergy(0){}

    unsigned amountOfSlots;
    unsigned basicCostInEnergy;
    unsigned perCapitaCostInEnergy;
};

class StressNullifiers : public QObject
{
    Q_OBJECT
public:
    StressNullifiers(BuildingsBase *buildingsBase) noexcept;

    Q_INVOKABLE int amountOfSlotsInPlayingField() const noexcept;
    Q_INVOKABLE Hero *slotInPlayingField(int index) noexcept
    {
        return m_heroesInPlayingField.value(index,NULL);
    }

    Q_INVOKABLE int amountOfSlotsInBar() const noexcept;
    Q_INVOKABLE Hero *slotInBar(int index) noexcept
    {
        return m_heroesInBar.value(index,NULL);
    }

    Q_INVOKABLE int amountOfSlotsInShrine() const noexcept;
    Q_INVOKABLE Hero *slotInShrine(int index) noexcept
    {
        return m_heroesInShrine.value(index,NULL);
    }

    Q_INVOKABLE int amountOfSlotsInSeclusion() const noexcept;
    Q_INVOKABLE Hero *slotInSeclusion(int index) noexcept
    {
        return m_heroesInSeclusion.value(index,NULL);
    }

    Q_INVOKABLE int stressNullifiersBaseCostInEnergy() const noexcept;
    Q_INVOKABLE int stressNullifiersUsageCostInEnergy() const noexcept;

    void destressHeroes() noexcept;

    void setPlayingFieldLevelsInfo(const QVector <PlayingFieldLevelInfo> &info) noexcept;
    void setBarLevelsInfo(const QVector <BarLevelInfo> &info) noexcept;
    void setShrineLevelsInfo(const QVector <ShrineLevelInfo> &info) noexcept;
    void setSeclusionLevelsInfo(const QVector <SeclusionLevelInfo> &info) noexcept;

private:
    BuildingsBase *m_buildingsBase;

    QVector <PlayingFieldLevelInfo> m_playingFieldLevelsInfo;
    QVector <BarLevelInfo> m_barLevelsInfo;
    QVector <ShrineLevelInfo> m_shrineLevelsInfo;
    QVector <SeclusionLevelInfo> m_seclusionLevelsInfo;

    QVector <Hero *> m_heroesInPlayingField;
    QVector <Hero *> m_heroesInBar;
    QVector <Hero *> m_heroesInShrine;
    QVector <Hero *> m_heroesInSeclusion;

};

struct PowerPlantLevelInfo
{
    PowerPlantLevelInfo()
        : aetheriteOreTaken(0), energyGiven(0){}

    unsigned aetheriteOreTaken;
    unsigned energyGiven;
};

struct FactoryLevelInfo
{
    FactoryLevelInfo()
        : aetheriteOreTaken(0), buildingMaterialsGiven(0){}

    unsigned aetheriteOreTaken;
    unsigned buildingMaterialsGiven;
};

struct CoolRoomLevelInfo
{
    CoolRoomLevelInfo()
        : foodSuppliesLimit(0){}

    unsigned foodSuppliesLimit;
};

struct StorageRoomLevelInfo
{
    StorageRoomLevelInfo()
        : buildingMaterialsLimit(0){}

    unsigned buildingMaterialsLimit;
};

struct AetheriteSiloLevelInfo
{
    AetheriteSiloLevelInfo()
        : aetheriteOreLimit(0){}

    unsigned aetheriteOreLimit;
};

class ResourceBuildings : public QObject
{
    Q_OBJECT
public:
    ResourceBuildings(BuildingsBase *buildingsBase) noexcept
        : m_energy(0), m_foodSupplies(0), m_buildingMaterials(0), m_aetheriteOre(0) {}

    Q_INVOKABLE int currentEnergyAmount() const noexcept
    {
        return m_energy;
    }
    Q_INVOKABLE int currentEnergyLimit() const noexcept;
    Q_INVOKABLE int currentEnergyIncome() const noexcept;

    Q_INVOKABLE int currentFoodSuppliesAmount() const noexcept
    {
        return m_foodSupplies;
    }
    Q_INVOKABLE int currentFoodSuppliesLimit() const noexcept;
    Q_INVOKABLE int currentFoodSuppliesIncome() const noexcept;

    Q_INVOKABLE int currentBuildingMaterialsAmount() const noexcept
    {
        return m_buildingMaterials;
    }
    Q_INVOKABLE int currentBuildingMaterialsLimit() const noexcept;
    Q_INVOKABLE int currentBuildingMaterialsIncome() const noexcept;

    Q_INVOKABLE int currentAetheriteOreAmount() const noexcept
    {
        return m_aetheriteOre;
    }
    Q_INVOKABLE int currentAetheriteOreLimit() const noexcept;
    Q_INVOKABLE int currentAetheriteOreIncome() const noexcept;

    void gatherResources() noexcept;

    void setPowerPlantLevelsInfo(const QVector <PowerPlantLevelInfo> &info) noexcept;
    void setFactoryLevelsInfo(const QVector <FactoryLevelInfo> &info) noexcept;
    void setCoolRoomLevelsInfo(const QVector <CoolRoomLevelInfo> &info) noexcept;
    void setStorageRoomLevelsInfo(const QVector <StorageRoomLevelInfo> &info) noexcept;
    void setAetheriteOreLevelsInfo(const QVector <AetheriteSiloLevelInfo> &info) noexcept;

private:
    BuildingsBase *m_buildingsBase;

    QVector <PowerPlantLevelInfo> m_powerPlantLevelsInfo;
    QVector <FactoryLevelInfo> m_factoryLevelsInfo;
    QVector <CoolRoomLevelInfo> m_coolRoomLevelsInfo;
    QVector <StorageRoomLevelInfo> m_storageRoomLevelsInfo;
    QVector <AetheriteSiloLevelInfo> m_aetheriteSiloLevelsInfo;

    int m_energy;
    int m_foodSupplies;
    int m_buildingMaterials;
    int m_aetheriteOre;
};

class Base : public QObject
{
    Q_OBJECT
public:
    Base() noexcept;
    ~Base() noexcept;

    Q_INVOKABLE Hospital &hospital() noexcept;
    Q_INVOKABLE TrainingBuildings &trainingBuildings() noexcept;
    Q_INVOKABLE StressNullifiers &stressNullifiers() noexcept;
    Q_INVOKABLE ResourceBuildings &resourceBuildings() noexcept;

    Q_INVOKABLE bool canUpgradeBuilding(BaseEnums::Building buildingName) const noexcept;
    Q_INVOKABLE void upgradeBuilding(BaseEnums::Building buildingName) noexcept;

    Q_INVOKABLE void activateBuildingsAtDayEnd() noexcept;

private:
    BuildingsBase *m_buildingsBase;
    Hospital *m_hospital;
    TrainingBuildings *m_trainingBuildings;
    StressNullifiers *m_stressNullifiers;
    ResourceBuildings *m_resourceBuildings;

    TechTree *m_techTree;
};

#endif // BASE_H
