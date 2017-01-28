#include "base.h"

BaseEnums::Resource BaseEnums::fromQStringToResourceEnum(const QString &resource) noexcept
{
    if (resource=="R_Energy")
        return R_Energy;
    if (resource=="R_FoodSupplies")
        return R_FoodSupplies;
    if (resource=="R_BuildingMaterials")
        return R_BuildingMaterials;
    if (resource=="R_AetheriteOre")
        return R_AetheriteOre;
}

QString BaseEnums::fromResourceEnumToQString(BaseEnums::Resource resource) noexcept
{
    if (resource==R_Energy)
        return "R_Energy";
    if (resource==R_FoodSupplies)
        return "R_FoodSupplies";
    if (resource==R_BuildingMaterials)
        return "R_BuildingMaterials";
    if (resource==R_AetheriteOre)
        return "R_AetheriteOre";
}

BaseEnums::Building BaseEnums::fromQStringToBuildingEnum(const QString &building) noexcept
{
    if (building=="B_CentralUnit")
        return B_CentralUnit;
    if (building=="B_PowerPlant")
        return B_PowerPlant;
    if (building=="B_Factory")
        return B_Factory;
    if (building=="B_CoolRoom")
        return B_CoolRoom;
    if (building=="B_StorageRoom")
        return B_StorageRoom;
    if (building=="B_AetheriteSilo")
        return B_AetheriteSilo;
    if (building=="B_Hospital")
        return B_Hospital;
    if (building=="B_Barracks")
        return B_Barracks;
    if (building=="B_DockingStation")
        return B_DockingStation;
    if (building=="B_TrainingGround")
        return B_TrainingGround;
    if (building=="B_Gym")
        return B_Gym;
    if (building=="B_Laboratory")
        return B_Laboratory;
    if (building=="B_PlayingField")
        return B_PlayingField;
    if (building=="B_Bar")
        return B_Bar;
    if (building=="B_Shrine")
        return B_Shrine;
    if (building=="B_Seclusion")
        return B_Seclusion;
}

QString BaseEnums::fromBuildingEnumToQString(BaseEnums::Building building) noexcept
{
    if (building==B_CentralUnit)
        return "B_CentralUnit";
    if (building==B_PowerPlant)
        return "B_PowerPlant";
    if (building==B_Factory)
        return "B_Factory";
    if (building==B_CoolRoom)
        return "B_CoolRoom";
    if (building==B_StorageRoom)
        return "B_StorageRoom";
    if (building==B_AetheriteSilo)
        return "B_AetheriteSilo";
    if (building==B_Hospital)
        return "B_Hospital";
    if (building==B_Barracks)
        return "B_Barracks";
    if (building==B_DockingStation)
        return "B_DockingStation";
    if (building==B_TrainingGround)
        return "B_TrainingGround";
    if (building==B_Gym)
        return "B_Gym";
    if (building==B_Laboratory)
        return "B_Laboratory";
    if (building==B_PlayingField)
        return "B_PlayingField";
    if (building==B_Bar)
        return "B_Bar";
    if (building==B_Shrine)
        return "B_Shrine";
    if (building==B_Seclusion)
        return "B_Seclusion";
}

TechTreeBuildingRequirements TechTree::getRequirementsForUpgrade(const QPair<BaseEnums::Building, int> &upgrade) const noexcept
{
    return m_nodes.value(upgrade);
}

void TechTree::addUpgradeNode(const QPair<BaseEnums::Building, int> &upgrade, const TechTreeBuildingRequirements &requirements) noexcept
{
    m_nodes.insert(upgrade,requirements);
}

void TechTree::reset() noexcept
{
    m_nodes.clear();
}

TechTreeBuilder::TechTreeBuilder() noexcept
{
    m_techTree=new TechTree();
}

TechTreeBuilder::~TechTreeBuilder() noexcept
{
    delete m_techTree;
}

TechTree *TechTreeBuilder::getTechTree() noexcept
{
    TechTree *ret=new TechTree();
    *ret=*m_techTree;
    return ret;
}

void TechTreeBuilder::resetTechTree() noexcept
{
    m_techTree->reset();
}

void TechTreeBuilder::addUpgrade(const QPair<BaseEnums::Building, int> &upgrade, const TechTreeBuildingRequirements &requirements) noexcept
{
    m_techTree->addUpgradeNode(upgrade,requirements);
}

int BuildingsBase::buildingLvl(BaseEnums::Building buildingName) const noexcept
{
    return m_buildingsLvls.value(buildingName,0);
}

void BuildingsBase::setBuildingLvl(BaseEnums::Building buildingName, int buildingLvl) noexcept
{
    m_buildingsLvls.insert(buildingName,buildingLvl);
}

void BuildingsBase::setIsPowerPlantWorking(bool isPowerPlantWorking) noexcept
{
    m_isPowerPlantWorking = isPowerPlantWorking;
}

void BuildingsBase::setIsFactoryWorking(bool isFactoryWorking) noexcept
{
    m_isFactoryWorking = isFactoryWorking;
}

BuildingsBase::BuildingsBase() noexcept
    : m_isPowerPlantWorking(true), m_isFactoryWorking(true)
{

}

int Hospital::amountOfSlotsInHospital() const noexcept
{
    //TODO
}

int Hospital::hospitalBasicCostInEnergy() const noexcept
{
    //TODO
}

int Hospital::hospitalUsageCostInEnergy() const noexcept
{
    //TODO
}

int Hospital::hospitalBasicCostInFoodSupplies() const noexcept
{
    //TODO
}

int Hospital::hospitalUsageCostInFoodSupplies() const noexcept
{
    //TODO
}

Hospital::Hospital() noexcept
{
    m_heroesInHospital.fill(NULL,amountOfSlotsInHospital());
}

void Hospital::healHeroes() noexcept
{
    //TODO
}

int StressNullifiers::amountOfSlotsInPlayingField() const noexcept
{
    //TODO
}

int StressNullifiers::amountOfSlotsInBar() const noexcept
{
    //TODO
}

int StressNullifiers::amountOfSlotsInShrine() const noexcept
{
    //TODO
}

int StressNullifiers::amountOfSlotsInSeclusion() const noexcept
{
    //TODO
}

int StressNullifiers::stressNullifiersBaseCostInEnergy() const noexcept
{
    //TODO
}

int StressNullifiers::stressNullifiersUsageCostInEnergy() const noexcept
{
    //TODO
}

StressNullifiers::StressNullifiers() noexcept
{
    m_heroesInPlayingField.fill(NULL,amountOfSlotsInPlayingField());
    m_heroesInBar.fill(NULL,amountOfSlotsInBar());
    m_heroesInShrine.fill(NULL,amountOfSlotsInShrine());
    m_heroesInSeclusion.fill(NULL,amountOfSlotsInSeclusion());
}

void StressNullifiers::destressHeroes() noexcept
{
    //TODO
}

int TrainingBuildings::amountOfSlotsInTrainingGround() const noexcept
{
    //TODO
}

int TrainingBuildings::amountOfSlotsInGym() const noexcept
{
    //TODO
}

int TrainingBuildings::amountOfSlotsInLaboratory() const noexcept
{
    //TODO
}

int TrainingBuildings::trainingBuildingsBaseCostInEnergy() const noexcept
{
    //TODO
}

int TrainingBuildings::trainingBuildingsUsageCostInEnergy() const noexcept
{
    //TODO
}

TrainingBuildings::TrainingBuildings() noexcept
{
    m_heroesInTrainingGround.fill(NULL,amountOfSlotsInTrainingGround());
    m_heroesInGym.fill(NULL,amountOfSlotsInGym());
    m_heroesInLaboratory.fill(NULL,amountOfSlotsInLaboratory());
}

void TrainingBuildings::trainHeroes() noexcept
{
    //TODO
}

int ResourceBuildings::currentEnergyLimit() const noexcept
{
    //TODO
}

int ResourceBuildings::currentEnergyIncome() const noexcept
{
    //TODO
}

int ResourceBuildings::currentFoodSuppliesLimit() const noexcept
{
    //TODO
}

int ResourceBuildings::currentFoodSuppliesIncome() const noexcept
{
    //TODO
}

int ResourceBuildings::currentBuildingMaterialsLimit() const noexcept
{
    //TODO
}

int ResourceBuildings::currentBuildingMaterialsIncome() const noexcept
{
    //TODO
}

int ResourceBuildings::currentAetheriteOreLimit() const noexcept
{
    //TODO
}

int ResourceBuildings::currentAetheriteOreIncome() const noexcept
{
    //TODO
}

void ResourceBuildings::gatherResources() noexcept
{
    //TODO
}

Base::Base() noexcept
{
    TechTreeBuilder *builder=new TechTreeBuilder();
    m_techTree=builder->getTechTree();
    delete builder;
}

Base::~Base() noexcept
{
    delete m_techTree;
}

bool Base::canUpgradeBuilding(BaseEnums::Building buildingName) const noexcept
{
    //TODO
}

void Base::upgradeBuilding(BaseEnums::Building buildingName) noexcept
{
    //TODO
}

void Base::activateBuildingsAtDayEnd() noexcept
{
    gatherResources();
    healHeroes();
    trainHeroes();
    destressHeroes();
}
