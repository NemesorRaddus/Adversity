#include "assetspool.h"

#include "base/buildings/building.h"
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
#include "database/database.h"
#include "equipment/equipment.h"
#include "file_io/xml_files/xmlreader.h"
#include "mercenaries/mercenary.h"
#include "missions/land.h"

AssetsPool::AssetsPool() noexcept
    : m_isReady(0)
{
    m_stockDatabase = new Database;
    m_reader = new XmlFileReader;
}

AssetsPool::~AssetsPool() noexcept
{
    clear();
    delete m_reader;
    delete m_stockDatabase;
}

void AssetsPool::load(const QString &pathToAssets) noexcept
{
    clear();
    loadBuildingsInfo(pathToAssets+"base/");
    loadMercenariesList(pathToAssets+"mercenaries/mercenaries/");
    loadEquipment(pathToAssets+"mercenaries/equipment.xml");
    loadLands(pathToAssets+"lands/");
    loadDatabase(pathToAssets+"database/");
    m_isReady = 1;
    m_pathToAssets = pathToAssets;
}

bool AssetsPool::isReady() const noexcept
{
    return m_isReady;
}

void AssetsPool::clear() noexcept
{
    m_buildingUpgradeRequirements.clear();

    for (int i=0;i < static_cast<int>(BuildingEnums::B_END);++i)
    {
        auto ptr = m_buildingLevelsInfo.value(static_cast<BuildingEnums::Building>(i), nullptr);
        if (ptr != nullptr)
            delete ptr;
    }
    m_buildingLevelsInfo.clear();

    m_buildingDescriptions.clear();
    m_dockingStationTradingTables.clear();

    for (int i=0;i < m_mercenariesLoaded.size();++i)
        delete m_mercenariesLoaded[i];
    m_mercenariesLoaded.clear();

    m_mercenariesAll.clear();

    for (int i=0;i < m_equipment.size();++i)
        delete m_equipment[i];
    m_equipment.clear();

    m_stockDatabase->loadEntries({});

    m_isReady = 0;
    m_pathToAssets.clear();
}

AnyBuildingLevelsInfo *AssetsPool::buildingLevelInfo(BuildingEnums::Building building) const noexcept
{
    return m_buildingLevelsInfo.value(building, nullptr);
}

QString AssetsPool::buildingDescription(BuildingEnums::Building building) const noexcept
{
    return m_buildingDescriptions.value(building);
}

void AssetsPool::loadMercenaryAtPosFromList(unsigned index) noexcept
{
    for (int i=0;i < m_mercenariesLoaded.size();++i)
        if (m_mercenariesLoaded[i]->name() == m_mercenariesAll[index])
            return;

    loadMercenary(m_pathToAssets+"mercenaries/mercenaries/"+m_mercenariesAll[index]+".xml");
}

void AssetsPool::loadMercenaryNamedFromList(const QString &name) noexcept
{
    for (int i=0;i < m_mercenariesAll.size();++i)
        if (m_mercenariesAll[i] == name)
        {
            loadMercenaryAtPosFromList(i);
            break;
        }
}

void AssetsPool::unloadMercenary(unsigned index) noexcept
{
    if (index < m_mercenariesLoaded.size())
    {
        delete m_mercenariesLoaded[index];
        m_mercenariesLoaded.remove(index);
    }
}

void AssetsPool::unloadMercenary(const QString &name) noexcept
{
    for (int i=0;i < m_mercenariesLoaded.size();++i)
        if (m_mercenariesLoaded[i]->name() == name)
        {
            unloadMercenary(i);
            break;
        }
}

Equipment *AssetsPool::makeEquipmentAtPos(unsigned index) noexcept
{
    if (index < m_equipment.size())
        return EquipmentBuilder::copyEquipment(m_equipment[index]);
    return nullptr;
}

Equipment *AssetsPool::makeEquipmentNamed(const QString &name) const noexcept
{
    for (int i=0;i < m_equipment.size();++i)
    {
        if (m_equipment[i]->name() == name)
            return EquipmentBuilder::copyEquipment(m_equipment[i]);
    }
    return nullptr;
}

Database *AssetsPool::makeStockDatabase() const noexcept
{
    auto r = m_stockDatabase->copyDBWithoutUnlocks();
    r->unlockEntry("Hegos Plains");
    r->unlockEntry("Gedo Desert");
    r->unlockEntry("Aurora Forest");
    return r;
}

void AssetsPool::loadBuildingsInfo(const QString &pathToDir) noexcept
{
    loadBuildingsLevelsInfo(pathToDir+"buildingLevelsInfo/");
    loadDockingStationTradingTables(pathToDir);
    loadBuildingsDescriptions(pathToDir);
}

void AssetsPool::loadBuildingsLevelsInfo(const QString &pathToDir) noexcept
{
    auto &bureqs = m_buildingUpgradeRequirements;
    auto &buli = m_buildingLevelsInfo;

    auto culi = m_reader->getCentralUnitLevelsInfo(pathToDir+"centralUnit.xml");
    buli.insert(BuildingEnums::B_CentralUnit, new AnyBuildingLevelsInfo(culi.first));
    for (int i=0;i < culi.second.size();++i)
        bureqs.insert({BuildingEnums::B_CentralUnit,i},culi.second[i]);

    auto hli = m_reader->getHospitalLevelsInfo(pathToDir+"hospital.xml");
    buli.insert(BuildingEnums::B_Hospital, new AnyBuildingLevelsInfo(hli.first));
    for (int i=0;i < hli.second.size();++i)
        bureqs.insert({BuildingEnums::B_Hospital,i},hli.second[i]);

    auto tgli = m_reader->getTrainingGroundLevelsInfo(pathToDir+"trainingGround.xml");
    buli.insert(BuildingEnums::B_TrainingGround, new AnyBuildingLevelsInfo(tgli.first));
    for (int i=0;i < tgli.second.size();++i)
        bureqs.insert({BuildingEnums::B_TrainingGround,i},tgli.second[i]);

    auto gli = m_reader->getGymLevelsInfo(pathToDir+"gym.xml");
    buli.insert(BuildingEnums::B_Gym, new AnyBuildingLevelsInfo(gli.first));
    for (int i=0;i < gli.second.size();++i)
        bureqs.insert({BuildingEnums::B_Gym,i},gli.second[i]);

    auto lli = m_reader->getLaboratoryLevelsInfo(pathToDir+"laboratory.xml");
    buli.insert(BuildingEnums::B_Laboratory, new AnyBuildingLevelsInfo(lli.first));
    for (int i=0;i < lli.second.size();++i)
        bureqs.insert({BuildingEnums::B_Laboratory,i},lli.second[i]);

    auto pfli = m_reader->getPlayingFieldLevelsInfo(pathToDir+"playingField.xml");
    buli.insert(BuildingEnums::B_PlayingField, new AnyBuildingLevelsInfo(pfli.first));
    for (int i=0;i < pfli.second.size();++i)
        bureqs.insert({BuildingEnums::B_PlayingField,i},pfli.second[i]);

    auto bli = m_reader->getBarLevelsInfo(pathToDir+"bar.xml");
    buli.insert(BuildingEnums::B_Bar, new AnyBuildingLevelsInfo(bli.first));
    for (int i=0;i < bli.second.size();++i)
        bureqs.insert({BuildingEnums::B_Bar,i},bli.second[i]);

    auto sli = m_reader->getShrineLevelsInfo(pathToDir+"shrine.xml");
    buli.insert(BuildingEnums::B_Shrine, new AnyBuildingLevelsInfo(sli.first));
    for (int i=0;i < sli.second.size();++i)
        bureqs.insert({BuildingEnums::B_Shrine,i},sli.second[i]);

    auto s1li = m_reader->getSeclusionLevelsInfo(pathToDir+"seclusion.xml");
    buli.insert(BuildingEnums::B_Seclusion, new AnyBuildingLevelsInfo(s1li.first));
    for (int i=0;i < s1li.second.size();++i)
        bureqs.insert({BuildingEnums::B_Seclusion,i},s1li.second[i]);

    auto pli = m_reader->getPowerplantLevelsInfo(pathToDir+"powerplant.xml");
    buli.insert(BuildingEnums::B_Powerplant, new AnyBuildingLevelsInfo(pli.first));
    for (int i=0;i < pli.second.size();++i)
        bureqs.insert({BuildingEnums::B_Powerplant,i},pli.second[i]);

    auto fli = m_reader->getFactoryLevelsInfo(pathToDir+"factory.xml");
    buli.insert(BuildingEnums::B_Factory, new AnyBuildingLevelsInfo(fli.first));
    for (int i=0;i < fli.second.size();++i)
        bureqs.insert({BuildingEnums::B_Factory,i},fli.second[i]);

    auto crli = m_reader->getCoolRoomLevelsInfo(pathToDir+"coolRoom.xml");
    buli.insert(BuildingEnums::B_CoolRoom, new AnyBuildingLevelsInfo(crli.first));
    for (int i=0;i < crli.second.size();++i)
        bureqs.insert({BuildingEnums::B_CoolRoom,i},crli.second[i]);

    auto srli = m_reader->getStorageRoomLevelsInfo(pathToDir+"storageRoom.xml");
    buli.insert(BuildingEnums::B_StorageRoom, new AnyBuildingLevelsInfo(srli.first));
    for (int i=0;i < srli.second.size();++i)
        bureqs.insert({BuildingEnums::B_StorageRoom,i},srli.second[i]);

    auto asli = m_reader->getAetheriteSiloLevelsInfo(pathToDir+"aetheriteSilo.xml");
    buli.insert(BuildingEnums::B_AetheriteSilo, new AnyBuildingLevelsInfo(asli.first));
    for (int i=0;i < asli.second.size();++i)
        bureqs.insert({BuildingEnums::B_AetheriteSilo,i},asli.second[i]);

    auto b1li = m_reader->getBarracksLevelsInfo(pathToDir+"barracks.xml");
    buli.insert(BuildingEnums::B_Barracks, new AnyBuildingLevelsInfo(b1li.first));
    for (int i=0;i < b1li.second.size();++i)
        bureqs.insert({BuildingEnums::B_Barracks,i},b1li.second[i]);

    auto dsli = m_reader->getDockingStationLevelsInfo(pathToDir+"dockingStation.xml");
    buli.insert(BuildingEnums::B_DockingStation, new AnyBuildingLevelsInfo(dsli.first));
    for (int i=0;i < dsli.second.size();++i)
        bureqs.insert({BuildingEnums::B_DockingStation,i},dsli.second[i]);
}

void AssetsPool::loadDockingStationTradingTables(const QString &pathToDir) noexcept
{
    m_dockingStationTradingTables = m_reader->getDockingStationTradingTables(pathToDir+"dockingStationTradingTables.xml");
}

void AssetsPool::loadBuildingsDescriptions(const QString &pathToDir) noexcept
{
    m_buildingDescriptions = m_reader->getBuildingDescriptions(pathToDir+"descriptions.xml");
}

void AssetsPool::loadMercenariesList(const QString &pathToDir) noexcept
{
    m_mercenariesAll = m_reader->getMercenariesNamesList(pathToDir);
}

void AssetsPool::loadMercenary(const QString &path) noexcept
{
    m_mercenariesLoaded.push_back(m_reader->getMercenary(path));
}

void AssetsPool::loadEquipment(const QString &path) noexcept
{
    m_equipment = m_reader->getEquipment(path);
}

void AssetsPool::loadDatabase(const QString &pathToDir) noexcept
{
    QVector <DatabaseEntry> entries;
    auto dbFiles = m_reader->getDatabaseFilesList(pathToDir);

    for (auto e : dbFiles)
        entries += m_reader->getDatabaseEntries(pathToDir+e);

    m_stockDatabase->loadEntries(entries);
}

void AssetsPool::loadLands(const QString &pathToDir) noexcept
{
    LandBuilder lb;
    auto landNames = m_reader->getLandsNamesList(pathToDir);

    for (auto e : landNames)
    {
        auto info = m_reader->getLandInfo(pathToDir+e+"/info.xml");
        lb.setInfo(info);

        auto encCont = m_reader->getEncounters(pathToDir+e+"/encounters.xml");
        lb.setAssociatedEncountersContainer(encCont);

        m_lands += lb.getLand();
    }
}
