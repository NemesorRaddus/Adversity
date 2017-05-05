#include "assetspool.h"

#include <QDebug>

AssetsPool::AssetsPool()
{

}

void AssetsPool::load(const QString &pathToAssets) noexcept
{

}

bool AssetsPool::isReady() const noexcept
{
    if (m_heroes.isEmpty() || m_heroes.isEmpty())
        return 0;
    return 1;
}

void AssetsPool::clear() noexcept
{
    for (int i=0;i<m_heroes.size();++i)
        delete m_heroes[i];
    m_heroes.clear();

    for (int i=0;i<m_equipment.size();++i)
        delete m_equipment[i];
    m_equipment.clear();
}
