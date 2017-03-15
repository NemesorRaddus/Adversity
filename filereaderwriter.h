#ifndef FILEREADERWRITER_H
#define FILEREADERWRITER_H

#include <QXmlStreamReader>
#include <QFile>

#include "base.h"
#include "equipment.h"
#include "event.h"
#include "hero.h"

class XmlFileReader
{
public:
    XmlFileReader() noexcept;

    bool openXmlFile(const QString &path) noexcept;

    QPair <QVector <CentralUnitLevelInfo>, QVector <BuildingUpgradeRequirements> > getCentralUnitLevelsInfo(const QString &path) noexcept;
    QPair <QVector <HospitalLevelInfo>, QVector <BuildingUpgradeRequirements> > getHospitalLevelsInfo(const QString &path) noexcept;
    QPair <QVector <TrainingGroundLevelInfo>, QVector <BuildingUpgradeRequirements> > getTrainingGroundLevelsInfo(const QString &path) noexcept;
    QPair <QVector <GymLevelInfo>, QVector <BuildingUpgradeRequirements> > getGymLevelsInfo(const QString &path) noexcept;
    QPair <QVector <LaboratoryLevelInfo>, QVector <BuildingUpgradeRequirements> > getLaboratoryLevelsInfo(const QString &path) noexcept;
    QPair <QVector <PlayingFieldLevelInfo>, QVector <BuildingUpgradeRequirements> > getPlayingFieldLevelsInfo(const QString &path) noexcept;
    QPair <QVector <BarLevelInfo>, QVector <BuildingUpgradeRequirements> > getBarLevelsInfo(const QString &path) noexcept;
    QPair <QVector <ShrineLevelInfo>, QVector <BuildingUpgradeRequirements> > getShrineLevelsInfo(const QString &path) noexcept;
    QPair <QVector <SeclusionLevelInfo>, QVector <BuildingUpgradeRequirements> > getSeclusionLevelsInfo(const QString &path) noexcept;
    QPair <QVector <PowerplantLevelInfo>, QVector <BuildingUpgradeRequirements> > getPowerplantLevelsInfo(const QString &path) noexcept;
    QPair <QVector <FactoryLevelInfo>, QVector <BuildingUpgradeRequirements> > getFactoryLevelsInfo(const QString &path) noexcept;
    QPair <QVector <CoolRoomLevelInfo>, QVector <BuildingUpgradeRequirements> > getCoolRoomLevelsInfo(const QString &path) noexcept;
    QPair <QVector <StorageRoomLevelInfo>, QVector <BuildingUpgradeRequirements> > getStorageRoomLevelsInfo(const QString &path) noexcept;
    QPair <QVector <AetheriteSiloLevelInfo>, QVector <BuildingUpgradeRequirements> > getAetheriteSiloLevelsInfo(const QString &path) noexcept;
    QPair <QVector <BarracksLevelInfo>, QVector <BuildingUpgradeRequirements> > getBarracksLevelsInfo(const QString &path) noexcept;
    QPair <QVector <DockingStationLevelInfo>, QVector <BuildingUpgradeRequirements> > getDockingStationLevelsInfo(const QString &path) noexcept;

    QVector <QPair <BaseEnums::Building, QString> > getBuildingDescriptions(const QString &path) noexcept;

private:
    QXmlStreamReader *m_xmlReader;
};

#endif // FILEREADERWRITER_H
