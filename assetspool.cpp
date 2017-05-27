#include "assetspool.h"

#include <QDebug>

AssetsPool::AssetsPool() noexcept
    : m_isReady(0)
{

}

AssetsPool::~AssetsPool() noexcept
{
    clear();
}

void AssetsPool::load(const QString &pathToAssets) noexcept
{
    clear();
    loadHeroesList(pathToAssets+"expeditions/mercenaries/");
    loadEquipment(pathToAssets+"expeditions/mercenaries/equipment.xml");
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

    loadHero(m_pathToAssets+"expeditions/mercenaries/"+m_heroesAll[index]+".xml");
}

void AssetsPool::unloadHero(unsigned index) noexcept
{
    if (index<m_heroesLoaded.size())
    {
        delete m_heroesLoaded[index];
        m_heroesLoaded.remove(index);
    }
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