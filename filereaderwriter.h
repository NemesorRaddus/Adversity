#ifndef FILEREADERWRITER_H
#define FILEREADERWRITER_H

#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFile>

#include "base.h"
#include "equipment.h"
#include "event.h"
#include "hero.h"

class XmlFileReader
{
public:
    bool openXmlFile(const QString &path) noexcept;
    bool isXmlFileOpened() const noexcept;

    TechTree *getTechTree() noexcept;
    TechTree *getTechTree(const QString &path) noexcept;

    QVector <CentralUnitLevelInfo> *getCentralUnitLevelsInfo(const QString &path) noexcept;
    QVector <HospitalLevelInfo> *getHospitalLevelsInfo(const QString &path) noexcept;
    QVector <TrainingGroundLevelInfo> *getTrainingGroundLevelsInfo(const QString &path) noexcept;
    QVector <GymLevelInfo> *getGymLevelsInfo(const QString &path) noexcept;
    QVector <LaboratoryLevelInfo> *getLaboratoryLevelsInfo(const QString &path) noexcept;
    QVector <PlayingFieldLevelInfo> *getPlayingFieldLevelsInfo(const QString &path) noexcept;
    QVector <BarLevelInfo> *getBarLevelsInfo(const QString &path) noexcept;
    QVector <ShrineLevelInfo> *getShrineLevelsInfo(const QString &path) noexcept;
    QVector <SeclusionLevelInfo> *getSeclusionLevelsInfo(const QString &path) noexcept;
    QVector <PowerPlantLevelInfo> *getPowerPlantLevelsInfo(const QString &path) noexcept;
    QVector <FactoryLevelInfo> *getFactoryLevelsInfo(const QString &path) noexcept;
    QVector <CoolRoomLevelInfo> *getCoolRoomLevelsInfo(const QString &path) noexcept;
    QVector <StorageRoomLevelInfo> *getStorageRoomLevelsInfo(const QString &path) noexcept;
    QVector <AetheriteSiloLevelInfo> *getAetheriteSiloLevelsInfo(const QString &path) noexcept;
    QVector <BarracksLevelInfo> *getBarracksLevelsInfo(const QString &path) noexcept;
    QVector <DockingStationLevelInfo> *getDockingStationLevelsInfo(const QString &path) noexcept;

private:
    QXmlStreamReader m_xmlReader;
};

class XmlFileWriter
{
public:
    bool openXmlFile(const QString &path) noexcept;
    bool isXmlFileOpened() const noexcept;

    void saveTechTree(const TechTree &techTree) noexcept;
    void saveTechTree(const TechTree &techTree, const QString &path) noexcept;

    void saveHospitalLevelInfo(QVector <HospitalLevelInfo> *info, const QString &path) noexcept;

private:
    QXmlStreamWriter m_xmlWriter;
};

#endif // FILEREADERWRITER_H
