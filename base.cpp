#include "base.h"

#include "timer.h"

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

unsigned Building::currentLevel() const noexcept
{
    return m_base->buildingLevel(m_buildingName);
}

TechTreeBuildingRequirements Building::requirementsForNextLevel() const noexcept
{
    return m_base->buildingRequirements(m_buildingName,currentLevel()+1);
}

bool Building::tryUpgrading() noexcept
{
    TechTreeBuildingRequirements reqs = requirementsForNextLevel();
    if (reqs.requiredBuildingMaterials > m_base->currentBuildingMaterialsAmount())
        return 0;
    for (int i=0;i<static_cast<int>(BaseEnums::B_END);++i)
        if (reqs.requiredBuildingLevels.value(static_cast<BaseEnums::Building>(i),0) > m_base->buildingLevel(static_cast<BaseEnums::Building>(i)))
            return 0;

    m_base->gameClock()->addAlarm(reqs.requiredTime,new BuildingUpgradeTimerAlarm(m_buildingName,currentLevel()+1));
    return 1;//FIX
}

QString Building::description() const noexcept
{
    return m_base->buildingDescription(m_buildingName);
}

Building::Building(BaseEnums::Building buildingName, Base *base, unsigned level) noexcept
    : m_buildingName(buildingName), m_base(base)
{
    m_base->setBuildingLevel(m_buildingName,level);
}

CentralUnit::CentralUnit(Base *base, unsigned level, const QVector<CentralUnitLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_CentralUnit, base, level), m_levelsInfo(levelsInfo)
{

}

Hospital::Hospital(Base *base, unsigned level, const QVector<HospitalLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_Hospital, base, level), m_levelsInfo(levelsInfo)
{
    m_heroesBeingHealed.fill(NULL,levelsInfo.value(level).amountOfSlots);
}

int Hospital::amountOfSlots() const noexcept
{
    return m_heroesBeingHealed.size();
}

void Hospital::healHeroes() noexcept
{
    for (int i=0;i<m_heroesBeingHealed.size();++i)
        if (m_heroesBeingHealed[i]!=NULL)
            m_heroesBeingHealed[i]->setHealth(m_heroesBeingHealed[i]->health() + m_levelsInfo.value(currentLevel()).hpRestored);
}

TrainingGround::TrainingGround(Base *base, unsigned level, const QVector<TrainingGroundLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_TrainingGround, base, level), m_levelsInfo(levelsInfo)
{
    m_heroesBeingTrained.fill(NULL,levelsInfo.value(level).amountOfSlots);
}

int TrainingGround::amountOfSlots() const noexcept
{
    return m_heroesBeingTrained.size();
}

void TrainingGround::trainHeroes() noexcept
{
    for (int i=0;i<m_heroesBeingTrained.size();++i)
        if (m_heroesBeingTrained[i]!=NULL)
        {
            m_heroesBeingTrained[i]->setCombatEffectiveness(m_heroesBeingTrained[i]->combatEffectiveness() + m_levelsInfo.value(currentLevel()).combatEffectivenessBonus);
            m_heroesBeingTrained[i]->setProficiency(m_heroesBeingTrained[i]->proficiency() + m_levelsInfo.value(currentLevel()).proficiencyBonus);
            m_heroesBeingTrained[i]->setCleverness(m_heroesBeingTrained[i]->cleverness() + m_levelsInfo.value(currentLevel()).clevernessBonus);
        }
}

Gym::Gym(Base *base, unsigned level, const QVector<GymLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_Gym, base, level), m_levelsInfo(levelsInfo)
{
    m_heroesBeingTrained.fill(NULL,levelsInfo.value(level).amountOfSlots);
}

int Gym::amountOfSlots() const noexcept
{
    return m_heroesBeingTrained.size();
}

void Gym::trainHeroes() noexcept
{

}

Laboratory::Laboratory(Base *base, unsigned level, const QVector<LaboratoryLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_Laboratory, base, level), m_levelsInfo(levelsInfo)
{
    m_heroesBeingTrained.fill(NULL,levelsInfo.value(level).amountOfSlots);
}

int Laboratory::amountOfSlots() const noexcept
{
    return m_heroesBeingTrained.size();
}

void Laboratory::trainHeroes() noexcept
{

}

PlayingField::PlayingField(Base *base, unsigned level, const QVector<PlayingFieldLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_PlayingField, base, level), m_levelsInfo(levelsInfo)
{
    m_heroesBeingDestressed.fill(NULL,levelsInfo.value(level).amountOfSlots);
}

int PlayingField::amountOfSlots() const noexcept
{
    return m_heroesBeingDestressed.size();
}

void PlayingField::destressHeroes() noexcept
{

}

Bar::Bar(Base *base, unsigned level, const QVector<BarLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_Bar, base, level), m_levelsInfo(levelsInfo)
{
    m_heroesBeingDestressed.fill(NULL,levelsInfo.value(level).amountOfSlots);
}

int Bar::amountOfSlots() const noexcept
{
    return m_heroesBeingDestressed.size();
}

void Bar::destressHeroes() noexcept
{

}

Shrine::Shrine(Base *base, unsigned level, const QVector<ShrineLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_Shrine, base, level), m_levelsInfo(levelsInfo)
{
    m_heroesBeingDestressed.fill(NULL,levelsInfo.value(level).amountOfSlots);
}

int Shrine::amountOfSlots() const noexcept
{
    return m_heroesBeingDestressed.size();
}

void Shrine::destressHeroes() noexcept
{

}

Seclusion::Seclusion(Base *base, unsigned level, const QVector<SeclusionLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_Seclusion, base, level), m_levelsInfo(levelsInfo)
{
    m_heroesBeingDestressed.fill(NULL,levelsInfo.value(level).amountOfSlots);
}

int Seclusion::amountOfSlots() const noexcept
{
    return m_heroesBeingDestressed.size();
}

void Seclusion::destressHeroes() noexcept
{

}

PowerPlant::PowerPlant(Base *base, unsigned level, const QVector<PowerPlantLevelInfo> &levelsInfo, bool isWorking) noexcept
    : Building(BaseEnums::B_PowerPlant, base, level), m_levelsInfo(levelsInfo), m_isWorking(isWorking)
{

}

void PowerPlant::exchangeResources() noexcept
{

}

void PowerPlant::setIsWorking(bool enable) noexcept
{
    m_isWorking=enable;
}

Factory::Factory(Base *base, unsigned level, const QVector<FactoryLevelInfo> &levelsInfo, bool isWorking) noexcept
    : Building(BaseEnums::B_Factory, base, level), m_levelsInfo(levelsInfo), m_isWorking(isWorking)
{

}

void Factory::exchangeResources() noexcept
{

}

void Factory::setIsWorking(bool enable) noexcept
{
    m_isWorking=enable;
}

CoolRoom::CoolRoom(Base *base, unsigned level, const QVector<CoolRoomLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_CoolRoom, base, level), m_levelsInfo(levelsInfo)
{

}

StorageRoom::StorageRoom(Base *base, unsigned level, const QVector<StorageRoomLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_StorageRoom, base, level), m_levelsInfo(levelsInfo)
{

}

AetheriteSilo::AetheriteSilo(Base *base, unsigned level, const QVector<AetheriteSiloLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_AetheriteSilo, base, level), m_levelsInfo(levelsInfo)
{

}

Barracks::Barracks(Base *base, unsigned level, const QVector<BarracksLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_Barracks, base, level), m_levelsInfo(levelsInfo)
{

}

DockingStation::DockingStation(Base *base, unsigned level, const QVector<DockingStationLevelInfo> &levelsInfo) noexcept
    : Building(BaseEnums::B_DockingStation, base, level), m_levelsInfo(levelsInfo)
{

}

Base::Base(QObject *parent) noexcept
    : QObject(parent)
{
    TechTreeBuilder *builder=new TechTreeBuilder();
    m_techTree=builder->getTechTree();
    delete builder;

    m_energy=0;
    m_foodSupplies=0;
    m_buildingMaterials=0;
    m_aetherite=0;

    m_gameClock=new GameClock;

    m_centralUnit=new CentralUnit(this,0,QVector<CentralUnitLevelInfo>());
    m_hospital=new Hospital(this,0,QVector <HospitalLevelInfo>());
    m_trainingGround=new TrainingGround(this,0,QVector<TrainingGroundLevelInfo>());
    m_gym=new Gym(this,0,QVector<GymLevelInfo>());
    m_laboratory=new Laboratory(this,0,QVector<LaboratoryLevelInfo>());
    m_playingField=new PlayingField(this,0,QVector<PlayingFieldLevelInfo>());
    m_bar=new Bar(this,0,QVector<BarLevelInfo>());
    m_shrine=new Shrine(this,0,QVector<ShrineLevelInfo>());
    m_seclusion=new Seclusion(this,0,QVector<SeclusionLevelInfo>());
    m_powerPlant=new PowerPlant(this,0,QVector<PowerPlantLevelInfo>(),1);
    m_factory=new Factory(this,0,QVector<FactoryLevelInfo>(),1);
    m_coolRoom=new CoolRoom(this,0,QVector<CoolRoomLevelInfo>());
    m_storageRoom=new StorageRoom(this,0,QVector<StorageRoomLevelInfo>());
    m_aetheriteSilo=new AetheriteSilo(this,0,QVector<AetheriteSiloLevelInfo>());
    m_barracks=new Barracks(this,0,QVector<BarracksLevelInfo>());
    m_dockingStation=new DockingStation(this,0,QVector<DockingStationLevelInfo>());

    m_buildings.insert(BaseEnums::B_CentralUnit,m_centralUnit);
    m_buildings.insert(BaseEnums::B_Hospital,m_hospital);
    m_buildings.insert(BaseEnums::B_TrainingGround,m_trainingGround);
    m_buildings.insert(BaseEnums::B_Gym,m_gym);
    m_buildings.insert(BaseEnums::B_Laboratory,m_laboratory);
    m_buildings.insert(BaseEnums::B_PlayingField,m_playingField);
    m_buildings.insert(BaseEnums::B_Bar,m_bar);
    m_buildings.insert(BaseEnums::B_Shrine,m_shrine);
    m_buildings.insert(BaseEnums::B_Seclusion,m_seclusion);
    m_buildings.insert(BaseEnums::B_PowerPlant,m_powerPlant);
    m_buildings.insert(BaseEnums::B_Factory,m_factory);
    m_buildings.insert(BaseEnums::B_CoolRoom,m_coolRoom);
    m_buildings.insert(BaseEnums::B_StorageRoom,m_storageRoom);
    m_buildings.insert(BaseEnums::B_AetheriteSilo,m_aetheriteSilo);
    m_buildings.insert(BaseEnums::B_Barracks,m_barracks);
    m_buildings.insert(BaseEnums::B_DockingStation,m_dockingStation);

    setBuildingDescription(BaseEnums::B_CentralUnit,"Description of Central Unit");//TESTINGONLY
}

Base::~Base() noexcept
{
    //delete m_techTree;
}

void Base::activateBuildingsAtDayEnd() noexcept
{
    bar()->destressHeroes();
    factory()->exchangeResources();
    gym()->trainHeroes();
    hospital()->healHeroes();
    laboratory()->trainHeroes();
    playingField()->destressHeroes();
    powerPlant()->exchangeResources();
    seclusion()->destressHeroes();
    shrine()->destressHeroes();
    trainingGround()->trainHeroes();
}

TechTreeBuildingRequirements Base::buildingRequirements(BaseEnums::Building buildingName, unsigned level) const noexcept
{
    return m_techTree->getRequirementsForUpgrade(QPair <BaseEnums::Building, int>(buildingName,level));
}

void Base::setBuildingLevel(BaseEnums::Building buildingName, unsigned level) noexcept
{
    m_buildingLevels.insert(buildingName,level);
}

void Base::setBuildingDescription(BaseEnums::Building buildingName, const QString &desc) noexcept
{
    m_buildingDescriptions.insert(buildingName,desc);
}
