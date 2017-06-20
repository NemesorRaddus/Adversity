#ifndef ASSETSPOOL_H
#define ASSETSPOOL_H

#include <QVector>

#include "hero.h"
#include "filereaderwriter.h"

#include <QDebug>

class AssetsPool
{
public:
    AssetsPool() noexcept;
    ~AssetsPool() noexcept;

    void load(const QString &pathToAssets) noexcept;
    bool isReady() const noexcept;
    void clear() noexcept;

    QStringList allHeroes() const noexcept
    {
        return m_heroesAll;
    }
    const QVector <Hero *> &loadedHeroes() noexcept
    {
        return m_heroesLoaded;
    }
    void loadHeroAtPosFromList(unsigned index) noexcept;
    void loadHeroNamedFromList(const QString &name) noexcept;
    void unloadHero(unsigned index) noexcept;

    const QVector <Equipment *> &equipment() noexcept
    {
        return m_equipment;
    }
    Equipment *makeEquipmentAtPos(unsigned index) noexcept;
    Equipment *makeEquipmentNamed(const QString &name) const noexcept;

private:
    void loadHeroesList(const QString &pathToDir) noexcept;
    void loadHero(const QString &path) noexcept;
    void loadEquipment(const QString &path) noexcept;

    bool m_isReady;
    QString m_pathToAssets;
    QVector <Hero *> m_heroesLoaded;
    QList <QString> m_heroesAll;
    QVector <Equipment *> m_equipment;
    XmlFileReader m_reader;
};

#endif // ASSETSPOOL_H
