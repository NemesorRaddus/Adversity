#pragma once

#include <QVector>

#include "mercenary.h"
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

    inline QStringList allMercenaries() const noexcept
    {
        return m_mercenariesAll;
    }
    inline const QVector <Mercenary *> &loadedMercenaries() const noexcept
    {
        return m_mercenariesLoaded;
    }
    void loadMercenaryAtPosFromList(unsigned index) noexcept;
    void loadMercenaryNamedFromList(const QString &name) noexcept;
    void unloadMercenary(unsigned index) noexcept;
    void unloadMercenary(const QString &name) noexcept;

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
    void loadMercenariesList(const QString &pathToDir) noexcept;
    void loadMercenary(const QString &path) noexcept;
    void loadEquipment(const QString &path) noexcept;
    void loadDatabase(const QString &pathToDir) noexcept;
    void loadLands(const QString &pathToDir) noexcept;

    bool m_isReady;
    QString m_pathToAssets;

    QVector <Mercenary *> m_mercenariesLoaded;
    QList <QString> m_mercenariesAll;

    QVector <Equipment *> m_equipment;

    Database *m_stockDatabase;

    QVector <Land *> m_lands;

    XmlFileReader m_reader;
};
