#include "assetspool.h"

#include "base/buildings/building.h"
#include "database/database.h"
#include "equipment/equipment.h"
#include "file_io/xml_files/xmlreader.h"
#include "mercenaries/mercenary.h"
#include "missions/land.h"

AssetsPool::AssetsPool() noexcept
    : m_isReady(0)
{
    m_stockDatabase=new Database;
    m_reader=new XmlFileReader;
}

AssetsPool::~AssetsPool() noexcept
{
    delete m_reader;
    delete m_stockDatabase;
    clear();
}

void AssetsPool::load(const QString &pathToAssets) noexcept
{
    clear();
    loadBuildingsInfo(pathToAssets+"base/");
    loadMercenariesList(pathToAssets+"mercenaries/mercenaries/");
    loadEquipment(pathToAssets+"mercenaries/equipment.xml");
    loadLands(pathToAssets+"lands/");
    loadDatabase(pathToAssets+"database/");
    m_isReady=1;
    m_pathToAssets=pathToAssets;
}

bool AssetsPool::isReady() const noexcept
{
    return m_isReady;
}

void AssetsPool::clear() noexcept
{
    m_buildingUpgradeRequirements.clear();

    m_buildingDescriptions.clear();
    m_dockingStationTradingTables.clear();

    for (int i=0;i<m_mercenariesLoaded.size();++i)
        delete m_mercenariesLoaded[i];
    m_mercenariesLoaded.clear();

    m_mercenariesAll.clear();

    for (int i=0;i<m_equipment.size();++i)
        delete m_equipment[i];
    m_equipment.clear();

    m_isReady=0;
    m_pathToAssets.clear();
}

QString AssetsPool::buildingDescription(BuildingEnums::Building building) const noexcept
{
    return m_buildingDescriptions.value(building);
}

void AssetsPool::loadMercenaryAtPosFromList(unsigned index) noexcept
{
    for (int i=0;i<m_mercenariesLoaded.size();++i)
        if (m_mercenariesLoaded[i]->name()==m_mercenariesAll[index])
            return;

    loadMercenary(m_pathToAssets+"mercenaries/mercenaries/"+m_mercenariesAll[index]+".xml");
}

void AssetsPool::loadMercenaryNamedFromList(const QString &name) noexcept
{
    for (int i=0;i<m_mercenariesAll.size();++i)
        if (m_mercenariesAll[i] == name)
        {
            loadMercenaryAtPosFromList(i);
            break;
        }
}

void AssetsPool::unloadMercenary(unsigned index) noexcept
{
    if (index<m_mercenariesLoaded.size())
    {
        delete m_mercenariesLoaded[index];
        m_mercenariesLoaded.remove(index);
    }
}

void AssetsPool::unloadMercenary(const QString &name) noexcept
{
    for (int i=0;i<m_mercenariesLoaded.size();++i)
        if (m_mercenariesLoaded[i]->name() == name)
        {
            unloadMercenary(i);
            break;
        }
}

Equipment *AssetsPool::makeEquipmentAtPos(unsigned index) noexcept
{
    if (index<m_equipment.size())
        return EquipmentBuilder::copyEquipment(m_equipment[index]);
    return nullptr;
}

Equipment *AssetsPool::makeEquipmentNamed(const QString &name) const noexcept
{
    for (int i=0;i<m_equipment.size();++i)
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
    loadDockingStationTradingTables(pathToDir);
    loadBuildingsDescriptions(pathToDir);
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
    m_mercenariesAll=m_reader->getMercenariesNamesList(pathToDir);
}

void AssetsPool::loadMercenary(const QString &path) noexcept
{
    m_mercenariesLoaded.push_back(m_reader->getMercenary(path));
}

void AssetsPool::loadEquipment(const QString &path) noexcept
{
    m_equipment=m_reader->getEquipment(path);
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
