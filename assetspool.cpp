#include "assetspool.h"

#include <QDebug>

AssetsPool::AssetsPool() noexcept
    : m_isReady(0)
{
    m_stockDatabase=new Database;
}

AssetsPool::~AssetsPool() noexcept
{
    delete m_stockDatabase;
    clear();
}

void AssetsPool::load(const QString &pathToAssets) noexcept
{
    clear();
    loadHeroesList(pathToAssets+"mercenaries/mercenaries/");
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
    for (int i=0;i<m_heroesLoaded.size();++i)
        delete m_heroesLoaded[i];
    m_heroesLoaded.clear();

    m_heroesAll.clear();

    for (int i=0;i<m_equipment.size();++i)
        delete m_equipment[i];
    m_equipment.clear();

    m_isReady=0;
    m_pathToAssets.clear();
}

void AssetsPool::loadHeroAtPosFromList(unsigned index) noexcept
{
    for (int i=0;i<m_heroesLoaded.size();++i)
        if (m_heroesLoaded[i]->name()==m_heroesAll[index])
            return;

    loadHero(m_pathToAssets+"mercenaries/mercenaries/"+m_heroesAll[index]+".xml");
}

void AssetsPool::loadHeroNamedFromList(const QString &name) noexcept
{
    for (int i=0;i<m_heroesAll.size();++i)
        if (m_heroesAll[i] == name)
        {
            loadHeroAtPosFromList(i);
            break;
        }
}

void AssetsPool::unloadHero(unsigned index) noexcept
{
    if (index<m_heroesLoaded.size())
    {
        delete m_heroesLoaded[index];
        m_heroesLoaded.remove(index);
    }
}

void AssetsPool::unloadHero(const QString &name) noexcept
{
    for (int i=0;i<m_heroesLoaded.size();++i)
        if (m_heroesLoaded[i]->name() == name)
        {
            unloadHero(i);
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
    return m_stockDatabase->copyDBWithoutUnlocks();
}

void AssetsPool::loadHeroesList(const QString &pathToDir) noexcept
{
    m_heroesAll=m_reader.getHeroesNamesList(pathToDir);
}

void AssetsPool::loadHero(const QString &path) noexcept
{
    m_heroesLoaded.push_back(m_reader.getHero(path));
}

void AssetsPool::loadEquipment(const QString &path) noexcept
{
    m_equipment=m_reader.getEquipment(path);
}

void AssetsPool::loadDatabase(const QString &pathToDir) noexcept
{
    QVector <DatabaseEntry> entries;
    auto dbFiles = m_reader.getDatabaseFilesList(pathToDir);

    for (auto e : dbFiles)
        entries += m_reader.getDatabaseEntries(pathToDir+e);

    m_stockDatabase->loadEntries(entries);
}

void AssetsPool::loadLands(const QString &pathToDir) noexcept
{
    LandBuilder lb;
    auto landNames = m_reader.getLandsNamesList(pathToDir);

    for (auto e : landNames)
    {
        auto info = m_reader.getLandInfo(pathToDir+e+"/info.xml");
        lb.setInfo(info);

        auto encCont = m_reader.getEncounters(pathToDir+e+"/encounters.xml");
        lb.setAssociatedEncountersContainer(encCont);

        m_lands += lb.getLand();
    }
}
