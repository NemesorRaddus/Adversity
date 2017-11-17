#pragma once

#include <QVector>

#include "base/enums.h"
#include "base/buildings/enums.h"
#include "base/buildings/building.h"
#include "base/buildings/dockingstation.h"
#include "base/buildings/upgraderequirements.h"

class Equipment;
class Database;
class Mercenary;
class Land;
class XmlFileReader;

class AssetsPool
{
public:
    AssetsPool() noexcept;
    ~AssetsPool() noexcept;

    void load(const QString &pathToAssets) noexcept;
    bool isReady() const noexcept;
    void clear() noexcept;

    inline BuildingsRequirementsMap buildingUpgradeRequirements() const noexcept
    {
        return m_buildingUpgradeRequirements;
    }

    AnyBuildingLevelsInfo *buildingLevelInfo(BuildingEnums::Building building) const noexcept;

    QString buildingDescription(BuildingEnums::Building building) const noexcept;
    inline QMap <BuildingEnums::Building, QString> buildingDescriptions() const noexcept
    {
        return m_buildingDescriptions;
    }

    inline DockingStationTradingTables dockingStationTradingTables() const noexcept
    {
        return m_dockingStationTradingTables;
    }

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
    void loadBuildingsInfo(const QString &pathToDir) noexcept;
    void loadBuildingsLevelsInfo(const QString &pathToDir) noexcept;
    void loadDockingStationTradingTables(const QString &pathToDir) noexcept;
    void loadBuildingsDescriptions(const QString &pathToDir) noexcept;
    void loadMercenariesList(const QString &pathToDir) noexcept;
    void loadMercenary(const QString &path) noexcept;
    void loadEquipment(const QString &path) noexcept;
    void loadDatabase(const QString &pathToDir) noexcept;
    void loadLands(const QString &pathToDir) noexcept;

    bool m_isReady;
    QString m_pathToAssets;

    BuildingsRequirementsMap m_buildingUpgradeRequirements;
    QMap <BuildingEnums::Building, AnyBuildingLevelsInfo *> m_buildingLevelsInfo;
    QMap <BuildingEnums::Building, QString> m_buildingDescriptions;
    DockingStationTradingTables m_dockingStationTradingTables;

    QVector <Mercenary *> m_mercenariesLoaded;
    QList <QString> m_mercenariesAll;

    QVector <Equipment *> m_equipment;

    Database *m_stockDatabase;

    QVector <Land *> m_lands;

    XmlFileReader *m_reader;
};
