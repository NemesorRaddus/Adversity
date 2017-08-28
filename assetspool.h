#ifndef ASSETSPOOL_H
#define ASSETSPOOL_H

#include <QVector>

#include "hero.h"
#include "filereaderwriter.h"
#include "database.h"

#include <QDebug>

class AssetsPool
{
public:
    AssetsPool() noexcept;
    ~AssetsPool() noexcept;

    void load(const QString &pathToAssets) noexcept;
    bool isReady() const noexcept;
    void clear() noexcept;

    inline QStringList allHeroes() const noexcept
    {
        return m_heroesAll;
    }
    inline const QVector <Hero *> &loadedHeroes() const noexcept
    {
        return m_heroesLoaded;
    }
    void loadHeroAtPosFromList(unsigned index) noexcept;
    void loadHeroNamedFromList(const QString &name) noexcept;
    void unloadHero(unsigned index) noexcept;
    void unloadHero(const QString &name) noexcept;

    inline const QVector <Equipment *> &equipment() const noexcept
    {
        return m_equipment;
    }
    Equipment *makeEquipmentAtPos(unsigned index) noexcept;
    Equipment *makeEquipmentNamed(const QString &name) const noexcept;

    Database *makeStockDatabase() const noexcept;
    
    inline const QVector <Land *> &lands() const noexcept
    {
        return m_lands;
    }

private:
    void loadHeroesList(const QString &pathToDir) noexcept;
    void loadHero(const QString &path) noexcept;
    void loadEquipment(const QString &path) noexcept;
    void loadDatabase(const QString &pathToDir) noexcept;
    void loadLands(const QString &pathToDir) noexcept;

    bool m_isReady;
    QString m_pathToAssets;

    QVector <Hero *> m_heroesLoaded;
    QList <QString> m_heroesAll;

    QVector <Equipment *> m_equipment;

    Database *m_stockDatabase;

    QVector <Land *> m_lands;

    XmlFileReader m_reader;
};

#endif // ASSETSPOOL_H
