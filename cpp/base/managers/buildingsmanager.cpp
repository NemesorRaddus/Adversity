#include "buildingsmanager.h"

#include "base/base.h"
#include "base/buildings/specific/storage/aetheritesilo.h"
#include "base/buildings/specific/destressing/bar.h"
#include "base/buildings/specific/other/barracks.h"
#include "base/buildings/specific/other/centralunit.h"
#include "base/buildings/specific/storage/coolroom.h"
#include "base/buildings/specific/other/dockingstation.h"
#include "base/buildings/specific/production/factory.h"
#include "base/buildings/specific/training/gym.h"
#include "base/buildings/specific/other/hospital.h"
#include "base/buildings/specific/training/laboratory.h"
#include "base/buildings/specific/destressing/playingfield.h"
#include "base/buildings/specific/production/powerplant.h"
#include "base/buildings/specific/destressing/seclusion.h"
#include "base/buildings/specific/destressing/shrine.h"
#include "base/buildings/specific/storage/storageroom.h"
#include "base/buildings/specific/training/trainingground.h"
#include "general/game.h"
#include "logging/loggersprovider.h"

BuildingsManager::BuildingsManager(Base *base) noexcept
    : BaseManagerInterface(base), m_buildingRequirements(nullptr)
{
    m_centralUnit=new CentralUnit(base, 1, base->gameObject()->assetsPool().buildingLevelInfo(BuildingEnums::B_CentralUnit));
    m_hospital=new Hospital(base, 0, base->gameObject()->assetsPool().buildingLevelInfo(BuildingEnums::B_Hospital));
    m_trainingGround=new TrainingGround(base, 0, base->gameObject()->assetsPool().buildingLevelInfo(BuildingEnums::B_TrainingGround));
    m_gym=new Gym(base, 0, base->gameObject()->assetsPool().buildingLevelInfo(BuildingEnums::B_Gym));
    m_laboratory=new Laboratory(base,0, base->gameObject()->assetsPool().buildingLevelInfo(BuildingEnums::B_Laboratory));
    m_playingField=new PlayingField(base, 0, base->gameObject()->assetsPool().buildingLevelInfo(BuildingEnums::B_PlayingField));
    m_bar=new Bar(base, 0, base->gameObject()->assetsPool().buildingLevelInfo(BuildingEnums::B_Bar));
    m_shrine=new Shrine(base, 0, base->gameObject()->assetsPool().buildingLevelInfo(BuildingEnums::B_Shrine));
    m_seclusion=new Seclusion(base, 0, base->gameObject()->assetsPool().buildingLevelInfo(BuildingEnums::B_Seclusion));
    m_powerplant=new Powerplant(base, 1, base->gameObject()->assetsPool().buildingLevelInfo(BuildingEnums::B_Powerplant));
    m_factory=new Factory(base, 1, base->gameObject()->assetsPool().buildingLevelInfo(BuildingEnums::B_Factory));
    m_coolRoom=new CoolRoom(base, 1, base->gameObject()->assetsPool().buildingLevelInfo(BuildingEnums::B_CoolRoom));
    m_storageRoom=new StorageRoom(base, 1, base->gameObject()->assetsPool().buildingLevelInfo(BuildingEnums::B_StorageRoom));
    m_aetheriteSilo=new AetheriteSilo(base, 1, base->gameObject()->assetsPool().buildingLevelInfo(BuildingEnums::B_AetheriteSilo));
    m_barracks=new Barracks(base, 1, base->gameObject()->assetsPool().buildingLevelInfo(BuildingEnums::B_Barracks));
    m_dockingStation=new DockingStation(base, 1, base->gameObject()->assetsPool().buildingLevelInfo(BuildingEnums::B_DockingStation));m_buildings.insert(BuildingEnums::B_CentralUnit, static_cast<Building *>(m_centralUnit));

    m_buildings.insert(BuildingEnums::B_Hospital, static_cast<Building *>(m_hospital));
    m_buildings.insert(BuildingEnums::B_TrainingGround, static_cast<Building *>(m_trainingGround));
    m_buildings.insert(BuildingEnums::B_Gym, static_cast<Building *>(m_gym));
    m_buildings.insert(BuildingEnums::B_Laboratory, static_cast<Building *>(m_laboratory));
    m_buildings.insert(BuildingEnums::B_PlayingField, static_cast<Building *>(m_playingField));
    m_buildings.insert(BuildingEnums::B_Bar, static_cast<Building *>(m_bar));
    m_buildings.insert(BuildingEnums::B_Shrine, static_cast<Building *>(m_shrine));
    m_buildings.insert(BuildingEnums::B_Seclusion, static_cast<Building *>(m_seclusion));
    m_buildings.insert(BuildingEnums::B_Powerplant, static_cast<Building *>(m_powerplant));
    m_buildings.insert(BuildingEnums::B_Factory, static_cast<Building *>(m_factory));
    m_buildings.insert(BuildingEnums::B_CoolRoom, static_cast<Building *>(m_coolRoom));
    m_buildings.insert(BuildingEnums::B_StorageRoom, static_cast<Building *>(m_storageRoom));
    m_buildings.insert(BuildingEnums::B_AetheriteSilo, static_cast<Building *>(m_aetheriteSilo));
    m_buildings.insert(BuildingEnums::B_Barracks, static_cast<Building *>(m_barracks));
    m_buildings.insert(BuildingEnums::B_DockingStation, static_cast<Building *>(m_dockingStation));
}

BuildingsManager::~BuildingsManager() noexcept
{
    delete m_centralUnit;
    delete m_hospital;
    delete m_trainingGround;
    delete m_gym;
    delete m_laboratory;
    delete m_playingField;
    delete m_bar;
    delete m_shrine;
    delete m_seclusion;
    delete m_powerplant;
    delete m_factory;
    delete m_coolRoom;
    delete m_storageRoom;
    delete m_aetheriteSilo;
    delete m_barracks;
    delete m_dockingStation;
}

void BuildingsManager::initializeForNewBase() noexcept
{
    m_dockingStation->prepareRecruits();
    m_dockingStation->prepareEquipments();
}

CentralUnit *BuildingsManager::centralUnit() noexcept
{
    return static_cast<CentralUnit *>(m_buildings.value(BuildingEnums::B_CentralUnit));
}

Hospital *BuildingsManager::hospital() noexcept
{
    return static_cast<Hospital *>(m_buildings.value(BuildingEnums::B_Hospital));
}

TrainingGround *BuildingsManager::trainingGround() noexcept
{
    return static_cast<TrainingGround *>(m_buildings.value(BuildingEnums::B_TrainingGround));
}

Gym *BuildingsManager::gym() noexcept
{
    return static_cast<Gym *>(m_buildings.value(BuildingEnums::B_Gym));
}

Laboratory *BuildingsManager::laboratory() noexcept
{
    return static_cast<Laboratory *>(m_buildings.value(BuildingEnums::B_Laboratory));
}

PlayingField *BuildingsManager::playingField() noexcept
{
    return static_cast<PlayingField *>(m_buildings.value(BuildingEnums::B_PlayingField));
}

Bar *BuildingsManager::bar() noexcept
{
    return static_cast<Bar *>(m_buildings.value(BuildingEnums::B_Bar));
}

Shrine *BuildingsManager::shrine() noexcept
{
    return static_cast<Shrine *>(m_buildings.value(BuildingEnums::B_Shrine));
}

Seclusion *BuildingsManager::seclusion() noexcept
{
    return static_cast<Seclusion *>(m_buildings.value(BuildingEnums::B_Seclusion));
}

Powerplant *BuildingsManager::powerplant() noexcept
{
    return static_cast<Powerplant *>(m_buildings.value(BuildingEnums::B_Powerplant));
}

Factory *BuildingsManager::factory() noexcept
{
    return static_cast<Factory *>(m_buildings.value(BuildingEnums::B_Factory));
}

CoolRoom *BuildingsManager::coolRoom() noexcept
{
    return static_cast<CoolRoom *>(m_buildings.value(BuildingEnums::B_CoolRoom));
}

StorageRoom *BuildingsManager::storageRoom() noexcept
{
    return static_cast<StorageRoom *>(m_buildings.value(BuildingEnums::B_StorageRoom));
}

AetheriteSilo *BuildingsManager::aetheriteSilo() noexcept
{
    return static_cast<AetheriteSilo *>(m_buildings.value(BuildingEnums::B_AetheriteSilo));
}

Barracks *BuildingsManager::barracks() noexcept
{
    return static_cast<Barracks *>(m_buildings.value(BuildingEnums::B_Barracks));
}

DockingStation *BuildingsManager::dockingStation() noexcept
{
    return static_cast<DockingStation *>(m_buildings.value(BuildingEnums::B_DockingStation));
}

unsigned BuildingsManager::buildingLevel(BuildingEnums::Building buildingName) const noexcept
{
    return m_buildings[buildingName]->currentLevel();
}

BuildingUpgradeRequirements BuildingsManager::buildingRequirements(BuildingEnums::Building buildingName, unsigned level) const noexcept
{
    if (m_buildingRequirements == nullptr)
        return {};
    return m_buildingRequirements->requirements(buildingName, level);
}

QString BuildingsManager::buildingDescription(BuildingEnums::Building buildingName) const noexcept
{
    return m_buildingDescriptions.value(buildingName);
}

void BuildingsManager::setBuildingLevel(BuildingEnums::Building buildingName, unsigned level) noexcept
{
    m_buildings[buildingName]->setCurrentLevel(level);
}

void BuildingsManager::setBuildingDescription(BuildingEnums::Building buildingName, const QString &desc) noexcept
{
    m_buildingDescriptions.insert(buildingName,desc);
}

void BuildingsManager::setBuildingDescriptions(const QMap<BuildingEnums::Building, QString> &descs) noexcept
{
    m_buildingDescriptions = descs;
}

void BuildingsManager::setBuildingRequirements(const BuildingsRequirementsMap &reqs) noexcept
{
    if (m_buildingRequirements != nullptr)
        delete m_buildingRequirements;
    m_buildingRequirements = new BuildingsRequirementsHandler(reqs);
}

Building *BuildingsManager::getBuilding(BuildingEnums::Building buildingName) noexcept
{
    if (m_buildings.contains(buildingName))
        return m_buildings.value(buildingName);
    else
    {
        LoggersProvider::buildingsLogger()->warn("BuildingEnums::Building enum->Building * conversion failed for {}", static_cast<unsigned>(buildingName));
        return nullptr;
    }
}
