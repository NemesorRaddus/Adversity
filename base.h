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
        R_AetheriteOre
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
        B_Seclusion
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
    TechTree *m_techTree;
};

class BuildingsBase
{
public:
    int buildingLvl(BaseEnums::Building buildingName) const noexcept;
    void setBuildingLvl(BaseEnums::Building buildingName, int buildingLvl) noexcept;

    bool isPowerPlantWorking() const noexcept
    {
        return m_isPowerPlantWorking;
    }
    void setIsPowerPlantWorking(bool isPowerPlantWorking) noexcept;

    bool isFactoryWorking() const noexcept
    {
        return m_isFactoryWorking;
    }
    void setIsFactoryWorking(bool isFactoryWorking) noexcept;

protected:
    BuildingsBase() noexcept;

private:
    QMap <BaseEnums::Building, int> m_buildingsLvls;

    bool m_isPowerPlantWorking;
    bool m_isFactoryWorking;
};

class Hospital : public virtual BuildingsBase
{
public:
    int amountOfSlotsInHospital() const noexcept;
    Hero *slotInHospital(int index) noexcept
    {
        return m_heroesInHospital.value(index,NULL);
    }

    int hospitalBasicCostInEnergy() const noexcept;
    int hospitalUsageCostInEnergy() const noexcept;

    int hospitalBasicCostInFoodSupplies() const noexcept;
    int hospitalUsageCostInFoodSupplies() const noexcept;

protected:
    Hospital() noexcept;

    void healHeroes() noexcept;

private:
    QVector <Hero *> m_heroesInHospital;
};

class TrainingBuildings : public virtual BuildingsBase
{
public:
    int amountOfSlotsInTrainingGround() const noexcept;
    Hero *slotInTrainingGround(int index) noexcept
    {
        return m_heroesInTrainingGround.value(index,NULL);
    }

    int amountOfSlotsInGym() const noexcept;
    Hero *slotInGym(int index) noexcept
    {
        return m_heroesInGym.value(index,NULL);
    }

    int amountOfSlotsInLaboratory() const noexcept;
    Hero *slotInLaboratory(int index) noexcept
    {
        return m_heroesInLaboratory.value(index,NULL);
    }

    int trainingBuildingsBaseCostInEnergy() const noexcept;
    int trainingBuildingsUsageCostInEnergy() const noexcept;

protected:
    TrainingBuildings() noexcept;

    void trainHeroes() noexcept;

private:
    QVector <Hero *> m_heroesInTrainingGround;
    QVector <Hero *> m_heroesInGym;
    QVector <Hero *> m_heroesInLaboratory;

};

class StressNullifiers : public virtual BuildingsBase
{
public:
    int amountOfSlotsInPlayingField() const noexcept;
    Hero *slotInPlayingField(int index) noexcept
    {
        return m_heroesInPlayingField.value(index,NULL);
    }

    int amountOfSlotsInBar() const noexcept;
    Hero *slotInBar(int index) noexcept
    {
        return m_heroesInBar.value(index,NULL);
    }

    int amountOfSlotsInShrine() const noexcept;
    Hero *slotInShrine(int index) noexcept
    {
        return m_heroesInShrine.value(index,NULL);
    }

    int amountOfSlotsInSeclusion() const noexcept;
    Hero *slotInSeclusion(int index) noexcept
    {
        return m_heroesInSeclusion.value(index,NULL);
    }

    int stressNullifiersBaseCostInEnergy() const noexcept;
    int stressNullifiersUsageCostInEnergy() const noexcept;

protected:
    StressNullifiers() noexcept;

    void destressHeroes() noexcept;

private:
    QVector <Hero *> m_heroesInPlayingField;
    QVector <Hero *> m_heroesInBar;
    QVector <Hero *> m_heroesInShrine;
    QVector <Hero *> m_heroesInSeclusion;

};

class ResourceBuildings : public virtual BuildingsBase
{
public:
    int currentEnergyAmount() const noexcept
    {
        return m_energy;
    }
    int currentEnergyLimit() const noexcept;
    int currentEnergyIncome() const noexcept;

    int currentFoodSuppliesAmount() const noexcept
    {
        return m_foodSupplies;
    }
    int currentFoodSuppliesLimit() const noexcept;
    int currentFoodSuppliesIncome() const noexcept;

    int currentBuildingMaterialsAmount() const noexcept
    {
        return m_buildingMaterials;
    }
    int currentBuildingMaterialsLimit() const noexcept;
    int currentBuildingMaterialsIncome() const noexcept;

    int currentAetheriteOreAmount() const noexcept
    {
        return m_aetheriteOre;
    }
    int currentAetheriteOreLimit() const noexcept;
    int currentAetheriteOreIncome() const noexcept;

protected:
    ResourceBuildings() noexcept
        : m_energy(0), m_foodSupplies(0), m_buildingMaterials(0), m_aetheriteOre(0) {}

    void gatherResources() noexcept;

private:
    int m_energy;
    int m_foodSupplies;
    int m_buildingMaterials;
    int m_aetheriteOre;
};

class Base : public Hospital, public TrainingBuildings, public StressNullifiers, public ResourceBuildings
{
public:
    Base() noexcept;
    ~Base() noexcept;

    bool canUpgradeBuilding(BaseEnums::Building buildingName) const noexcept;
    void upgradeBuilding(BaseEnums::Building buildingName) noexcept;

    void activateBuildingsAtDayEnd() noexcept;

private:
    TechTree *m_techTree;
};

#endif // BASE_H
