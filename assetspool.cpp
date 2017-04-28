#include "assetspool.h"

#include <QDebug>

AssetsPool::AssetsPool()
{

}

void AssetsPool::load(const QString &pathToAssets)
{
    //TODO add loading data assets from file, creating them using builder and adding them to the pool
}

bool AssetsPool::isReady() const
{
    if (m_heroes.isEmpty() || m_heroes.isEmpty())
        return 0;
    return 1;
}

void AssetsPool::clear()
{
    for (int i=0;i<m_heroes.size();++i)
        delete m_heroes[i];
    m_heroes.clear();

    for (int i=0;i<m_equipment.size();++i)
        delete m_equipment[i];
    m_equipment.clear();
}
