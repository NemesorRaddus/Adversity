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

bool TechTree::isThereSuchUpgrade(const QPair<BaseEnums::Building, int> &upgrade) const noexcept
{
    return m_nodes.contains(upgrade);
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

BuildingsBase::BuildingsBase() noexcept
    : m_isPowerPlantWorking(true), m_isFactoryWorking(true)
{

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

Hospital::Hospital(BuildingsBase *buildingsBase) noexcept
    : m_buildingsBase(buildingsBase)
{
    m_levelsInfo.resize(1);

    m_heroesInHospital.fill(NULL,amountOfSlotsInHospital());
}

int Hospital::amountOfSlotsInHospital() const noexcept
{
    return m_levelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_Hospital)).amountOfSlots;
}

int Hospital::hospitalBasicCostInEnergy() const noexcept
{
    return m_levelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_Hospital)).basicCostInEnergy;
}

int Hospital::hospitalUsageCostInEnergy() const noexcept
{
    return m_levelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_Hospital)).perCapitaCostInEnergy * (amountOfSlotsInHospital() - m_heroesInHospital.count(NULL));
}

int Hospital::hospitalBasicCostInFoodSupplies() const noexcept
{
    return m_levelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_Hospital)).basicCostInFoodSupplies;
}

int Hospital::hospitalUsageCostInFoodSupplies() const noexcept
{
    return m_levelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_Hospital)).perCapitaCostInFoodSupplies * (amountOfSlotsInHospital() - m_heroesInHospital.count(NULL));
}

void Hospital::healHeroes() noexcept
{
    //TODO
}

void Hospital::setLevelsInfo(const QVector<HospitalLevelInfo> &info) noexcept
{
    if (!info.isEmpty())
        m_levelsInfo=info;
}

TrainingBuildings::TrainingBuildings(BuildingsBase *buildingsBase) noexcept
    : m_buildingsBase(buildingsBase)
{
    m_trainingGroundLevelsInfo.resize(1);
    m_gymLevelsInfo.resize(1);
    m_laboratoryLevelsInfo.resize(1);

    m_heroesInTrainingGround.fill(NULL,amountOfSlotsInTrainingGround());
    m_heroesInGym.fill(NULL,amountOfSlotsInGym());
    m_heroesInLaboratory.fill(NULL,amountOfSlotsInLaboratory());
}

int TrainingBuildings::amountOfSlotsInTrainingGround() const noexcept
{
    return m_trainingGroundLevelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_TrainingGround)).amountOfSlots;
}

int TrainingBuildings::amountOfSlotsInGym() const noexcept
{
    return m_gymLevelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_Gym)).amountOfSlots;
}

int TrainingBuildings::amountOfSlotsInLaboratory() const noexcept
{
    return m_laboratoryLevelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_Laboratory)).amountOfSlots;
}

int TrainingBuildings::trainingBuildingsBaseCostInEnergy() const noexcept
{
    return m_trainingGroundLevelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_TrainingGround)).basicCostInEnergy +
            m_gymLevelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_Gym)).basicCostInEnergy +
            m_laboratoryLevelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_Laboratory)).basicCostInEnergy;
}

int TrainingBuildings::trainingBuildingsUsageCostInEnergy() const noexcept
{
    return m_trainingGroundLevelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_TrainingGround)).perCapitaCostInEnergy * (amountOfSlotsInTrainingGround() - m_heroesInTrainingGround.count(NULL)) +
            m_gymLevelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_Gym)).perCapitaCostInEnergy * (amountOfSlotsInGym() - m_heroesInGym.count(NULL)) +
            m_laboratoryLevelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_Laboratory)).perCapitaCostInEnergy * (amountOfSlotsInLaboratory() - m_heroesInLaboratory.count(NULL));
}

void TrainingBuildings::trainHeroes() noexcept
{
    //TODO
}

void TrainingBuildings::setTrainingGroundLevelsInfo(const QVector<TrainingGroundLevelInfo> &info) noexcept
{
    if (!info.isEmpty())
        m_trainingGroundLevelsInfo = info;
}

void TrainingBuildings::setGymLevelsInfo(const QVector<GymLevelInfo> &info) noexcept
{
    if (!info.isEmpty())
        m_gymLevelsInfo = info;
}

void TrainingBuildings::setLaboratoryLevelsInfo(const QVector<LaboratoryLevelInfo> &info) noexcept
{
    if (!info.isEmpty())
        m_laboratoryLevelsInfo = info;
}

StressNullifiers::StressNullifiers(BuildingsBase *buildingsBase) noexcept
    : m_buildingsBase(buildingsBase)
{
    m_heroesInPlayingField.fill(NULL,amountOfSlotsInPlayingField());
    m_heroesInBar.fill(NULL,amountOfSlotsInBar());
    m_heroesInShrine.fill(NULL,amountOfSlotsInShrine());
    m_heroesInSeclusion.fill(NULL,amountOfSlotsInSeclusion());
}

int StressNullifiers::amountOfSlotsInPlayingField() const noexcept
{
    return m_playingFieldLevelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_PlayingField)).amountOfSlots;
}

int StressNullifiers::amountOfSlotsInBar() const noexcept
{
    return m_barLevelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_Bar)).amountOfSlots;
}

int StressNullifiers::amountOfSlotsInShrine() const noexcept
{
    return m_shrineLevelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_Shrine)).amountOfSlots;
}

int StressNullifiers::amountOfSlotsInSeclusion() const noexcept
{
    return m_seclusionLevelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_Seclusion)).amountOfSlots;
}

int StressNullifiers::stressNullifiersBaseCostInEnergy() const noexcept
{
    return m_playingFieldLevelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_PlayingField)).basicCostInEnergy +
            m_barLevelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_Bar)).basicCostInEnergy +
            m_shrineLevelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_Shrine)).basicCostInEnergy +
            m_seclusionLevelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_Seclusion)).basicCostInEnergy;
}

int StressNullifiers::stressNullifiersUsageCostInEnergy() const noexcept
{
    return m_playingFieldLevelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_PlayingField)).perCapitaCostInEnergy * (amountOfSlotsInPlayingField() - m_heroesInPlayingField.count(NULL)) +
            m_barLevelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_Bar)).perCapitaCostInEnergy * (amountOfSlotsInBar() - m_heroesInBar.count(NULL)) +
            m_shrineLevelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_Shrine)).perCapitaCostInEnergy * (amountOfSlotsInShrine() - m_heroesInShrine.count(NULL)) +
            m_seclusionLevelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_Seclusion)).perCapitaCostInEnergy * (amountOfSlotsInSeclusion() - m_heroesInSeclusion.count(NULL));
}

void StressNullifiers::destressHeroes() noexcept
{
    //TODO
}

void StressNullifiers::setPlayingFieldLevelsInfo(const QVector<PlayingFieldLevelInfo> &info) noexcept
{
    if (!info.isEmpty())
        m_playingFieldLevelsInfo = info;
}

void StressNullifiers::setBarLevelsInfo(const QVector<BarLevelInfo> &info) noexcept
{
    if (!info.isEmpty())
        m_barLevelsInfo = info;
}

void StressNullifiers::setShrineLevelsInfo(const QVector<ShrineLevelInfo> &info) noexcept
{
    if (!info.isEmpty())
        m_shrineLevelsInfo = info;
}

void StressNullifiers::setSeclusionLevelsInfo(const QVector<SeclusionLevelInfo> &info) noexcept
{
    if (!info.isEmpty())
        m_seclusionLevelsInfo = info;
}

int ResourceBuildings::currentEnergyLimit() const noexcept
{
    return 9999999999;//TODO hmmm?
}

int ResourceBuildings::currentEnergyIncome() const noexcept
{
    return m_powerPlantLevelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_PowerPlant)).energyGiven;
}

int ResourceBuildings::currentFoodSuppliesLimit() const noexcept
{
    return m_coolRoomLevelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_CoolRoom)).foodSuppliesLimit;
}

int ResourceBuildings::currentFoodSuppliesIncome() const noexcept
{
    return 0;//TODO hmmm?
}

int ResourceBuildings::currentBuildingMaterialsLimit() const noexcept
{
    return m_storageRoomLevelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_StorageRoom)).buildingMaterialsLimit;
}

int ResourceBuildings::currentBuildingMaterialsIncome() const noexcept
{
    return m_factoryLevelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_Factory)).buildingMaterialsGiven;
}

int ResourceBuildings::currentAetheriteOreLimit() const noexcept
{
    return m_aetheriteSiloLevelsInfo.value(m_buildingsBase->buildingLvl(BaseEnums::B_AetheriteSilo)).aetheriteOreLimit;
}

int ResourceBuildings::currentAetheriteOreIncome() const noexcept
{
    return 0;//TODO hmmm?
}

void ResourceBuildings::gatherResources() noexcept
{
    //TODO
}

void ResourceBuildings::setPowerPlantLevelsInfo(const QVector<PowerPlantLevelInfo> &info) noexcept
{
    if (!info.isEmpty())
        m_powerPlantLevelsInfo = info;
}

void ResourceBuildings::setFactoryLevelsInfo(const QVector<FactoryLevelInfo> &info) noexcept
{
    if (!info.isEmpty())
        m_factoryLevelsInfo = info;
}

void ResourceBuildings::setCoolRoomLevelsInfo(const QVector<CoolRoomLevelInfo> &info) noexcept
{
    if (!info.isEmpty())
        m_coolRoomLevelsInfo = info;
}

void ResourceBuildings::setStorageRoomLevelsInfo(const QVector<StorageRoomLevelInfo> &info) noexcept
{
    if (!info.isEmpty())
        m_storageRoomLevelsInfo = info;
}

void ResourceBuildings::setAetheriteOreLevelsInfo(const QVector<AetheriteSiloLevelInfo> &info) noexcept
{
    if (!info.isEmpty())
        m_aetheriteSiloLevelsInfo = info;
}

Base::Base() noexcept
{
    TechTreeBuilder *builder=new TechTreeBuilder();
    m_techTree=builder->getTechTree();
    delete builder;

    m_buildingsBase = new BuildingsBase;
    m_hospital = new Hospital(m_buildingsBase);
    m_trainingBuildings = new TrainingBuildings(m_buildingsBase);
    m_stressNullifiers = new StressNullifiers(m_buildingsBase);
    m_resourceBuildings = new ResourceBuildings(m_buildingsBase);
}

Base::~Base() noexcept
{
    delete m_techTree;
    delete m_resourceBuildings;
    delete m_stressNullifiers;
    delete m_trainingBuildings;
    delete m_hospital;
    delete m_buildingsBase;
}

Hospital &Base::hospital() noexcept
{
    return *m_hospital;
}

TrainingBuildings &Base::trainingBuildings() noexcept
{
    return *m_trainingBuildings;
}

StressNullifiers &Base::stressNullifiers() noexcept
{
    return *m_stressNullifiers;
}

ResourceBuildings &Base::resourceBuildings() noexcept
{
    return *m_resourceBuildings;
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
    m_resourceBuildings->gatherResources();
    m_hospital->healHeroes();
    m_trainingBuildings->trainHeroes();
    m_stressNullifiers->destressHeroes();
}
