#pragma once

#include "xmlfilereaderbase.h"
#include "base/enums.h"
#include "base/buildings/enums.h"

template <typename T1, typename T2>
class QPair;
template <typename T>
class QVector;
template <typename T1, typename T2>
class QMap;

struct AetheriteSiloLevelInfo;
struct BarLevelInfo;
struct BarracksLevelInfo;
struct BuildingUpgradeRequirements;
struct CentralUnitLevelInfo;
struct CoolRoomLevelInfo;
struct DockingStationLevelInfo;
struct FactoryLevelInfo;
struct GymLevelInfo;
struct HospitalLevelInfo;
struct LaboratoryLevelInfo;
struct PlayingFieldLevelInfo;
struct PowerplantLevelInfo;
struct SeclusionLevelInfo;
struct ShrineLevelInfo;
struct StorageRoomLevelInfo;
struct TrainingGroundLevelInfo;
typedef QVector <QMap <QPair <BaseEnums::Resource, BaseEnums::Resource>, float> > DockingStationTradingTables;

class BuildingsReader : private virtual XmlFileReaderBase
{
public:
    BuildingsReader() noexcept = default;
    virtual ~BuildingsReader() noexcept = default;

    QPair <QVector <CentralUnitLevelInfo *>, QVector<BuildingUpgradeRequirements> > getCentralUnitLevelsInfo(const QString &path) noexcept;
    QPair <QVector <HospitalLevelInfo *>, QVector <BuildingUpgradeRequirements> > getHospitalLevelsInfo(const QString &path) noexcept;
    QPair <QVector <TrainingGroundLevelInfo *>, QVector <BuildingUpgradeRequirements> > getTrainingGroundLevelsInfo(const QString &path) noexcept;
    QPair <QVector <GymLevelInfo *>, QVector <BuildingUpgradeRequirements> > getGymLevelsInfo(const QString &path) noexcept;
    QPair <QVector <LaboratoryLevelInfo *>, QVector <BuildingUpgradeRequirements> > getLaboratoryLevelsInfo(const QString &path) noexcept;
    QPair <QVector <PlayingFieldLevelInfo *>, QVector <BuildingUpgradeRequirements> > getPlayingFieldLevelsInfo(const QString &path) noexcept;
    QPair <QVector <BarLevelInfo *>, QVector <BuildingUpgradeRequirements> > getBarLevelsInfo(const QString &path) noexcept;
    QPair <QVector <ShrineLevelInfo *>, QVector <BuildingUpgradeRequirements> > getShrineLevelsInfo(const QString &path) noexcept;
    QPair <QVector <SeclusionLevelInfo *>, QVector <BuildingUpgradeRequirements> > getSeclusionLevelsInfo(const QString &path) noexcept;
    QPair <QVector <PowerplantLevelInfo *>, QVector <BuildingUpgradeRequirements> > getPowerplantLevelsInfo(const QString &path) noexcept;
    QPair <QVector <FactoryLevelInfo *>, QVector <BuildingUpgradeRequirements> > getFactoryLevelsInfo(const QString &path) noexcept;
    QPair <QVector <CoolRoomLevelInfo *>, QVector <BuildingUpgradeRequirements> > getCoolRoomLevelsInfo(const QString &path) noexcept;
    QPair <QVector <StorageRoomLevelInfo *>, QVector <BuildingUpgradeRequirements> > getStorageRoomLevelsInfo(const QString &path) noexcept;
    QPair <QVector <AetheriteSiloLevelInfo *>, QVector <BuildingUpgradeRequirements> > getAetheriteSiloLevelsInfo(const QString &path) noexcept;
    QPair <QVector <BarracksLevelInfo *>, QVector <BuildingUpgradeRequirements> > getBarracksLevelsInfo(const QString &path) noexcept;
    QPair <QVector <DockingStationLevelInfo *>, QVector <BuildingUpgradeRequirements> > getDockingStationLevelsInfo(const QString &path) noexcept;

    DockingStationTradingTables getDockingStationTradingTables(const QString &path) noexcept;

    QMap <BuildingEnums::Building, QString> getBuildingDescriptions(const QString &path) noexcept;
};
