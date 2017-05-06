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
    loadHeroes(pathToAssets+"expeditions/mercenaries/mercenaries.xml");
    loadEquipment(pathToAssets+"expeditions/mercenaries/equipment.xml");
    m_isReady=1;
}

bool AssetsPool::isReady() const noexcept
{
    return m_isReady;
}

void AssetsPool::clear() noexcept
{
    for (int i=0;i<m_heroes.size();++i)
        delete m_heroes[i];
    m_heroes.clear();

    for (int i=0;i<m_equipment.size();++i)
        delete m_equipment[i];
    m_equipment.clear();

    m_isReady=0;
}

void AssetsPool::loadHeroes(const QString &path) noexcept
{
    m_heroes=m_reader.getHeroes(path);
}

void AssetsPool::loadEquipment(const QString &path) noexcept
{
    m_equipment=m_reader.getEquipment(path);
}
