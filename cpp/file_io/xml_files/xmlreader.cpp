#include "xmlreader.h"

#include <QXmlStreamReader>
#include <QFile>
#include <QDir>
#include <QList>
#include <QDebug>

#include "base/buildings/aetheritesilo.h"
#include "base/buildings/bar.h"
#include "base/buildings/barracks.h"
#include "base/buildings/centralunit.h"
#include "base/buildings/coolroom.h"
#include "base/buildings/dockingstation.h"
#include "base/buildings/factory.h"
#include "base/buildings/gym.h"
#include "base/buildings/hospital.h"
#include "base/buildings/laboratory.h"
#include "base/buildings/playingfield.h"
#include "base/buildings/powerplant.h"
#include "base/buildings/seclusion.h"
#include "base/buildings/shrine.h"
#include "base/buildings/storageroom.h"
#include "base/buildings/trainingground.h"
#include "database/database.h"
#include "equipment/equipment.h"
#include "general/game.h"
#include "general/globalutilities.h"
#include "logging/loggershandler.h"
#include "mercenaries/mercenary.h"
#include "missions/encounter.h"
#include "missions/events/actionevents.h"
#include "missions/events/checkevents.h"
#include "missions/events/event.h"
#include "missions/events/otherevents.h"
#include "missions/events/value_scripts/valuerange.h"
#include "missions/land.h"

XmlFileReader::XmlFileReader() noexcept
{
    m_xmlReader=new QXmlStreamReader();
}

XmlFileReader::~XmlFileReader() noexcept
{
    delete m_xmlReader;
}

bool XmlFileReader::openXmlFile(const QString &path) noexcept
{
    QFile *f=new QFile(path);
    if (!f->open(QFile::ReadOnly))
        return 0;
    delete m_xmlReader;
    m_xmlReader=new QXmlStreamReader(f);
    return 1;
}

QPair<QVector<CentralUnitLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getCentralUnitLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<CentralUnitLevelInfo>, QVector<BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="centralUnitLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level=0;
                    CentralUnitLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level=attrs.value("level").toUInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs=m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials=attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy=attrs.value("energy").toUInt();
                            reqs.requiredTime=attrs.value("time").toUInt();
                            m_xmlReader->skipCurrentElement();
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }

                    r.first.insert(level,info);
                    r.second.insert(level,reqs);
                }
                else
                    m_xmlReader->skipCurrentElement();
            }
        }
        else
            m_xmlReader->raiseError("Incorrect file");
    }
    if (m_xmlReader->hasError())
    {
        qCritical()<<"Couldn't read "+path+" properly.";
        return {};
    }
    return r;
}

QPair<QVector<HospitalLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getHospitalLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<HospitalLevelInfo>, QVector<BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="hospitalLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level=0;
                    HospitalLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level=attrs.value("level").toUInt();
                    info.amountOfSlots=attrs.value("slots").toUInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();
                    info.perCapitaCostInEnergy=attrs.value("perCapitaCostEnergy").toUInt();
                    info.basicCostInFoodSupplies=attrs.value("basicCostFood").toUInt();
                    info.perCapitaCostInFoodSupplies=attrs.value("perCapitaCostFood").toUInt();
                    info.hpRestored=attrs.value("hpRestored").toUInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs=m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials=attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy=attrs.value("energy").toUInt();
                            reqs.requiredTime=attrs.value("time").toUInt();
                            m_xmlReader->skipCurrentElement();
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }

                    r.first.insert(level,info);
                    r.second.insert(level,reqs);
                }
                else
                    m_xmlReader->skipCurrentElement();
            }
        }
        else
            m_xmlReader->raiseError("Incorrect file");
    }
    if (m_xmlReader->hasError())
    {
        qCritical()<<"Couldn't read "+path+" properly.";
        return {};
    }
    return r;
}

QPair<QVector<TrainingGroundLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getTrainingGroundLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<TrainingGroundLevelInfo>, QVector<BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="trainingGroundLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level=0;
                    TrainingGroundLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level=attrs.value("level").toUInt();
                    info.amountOfSlots=attrs.value("slots").toInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();
                    info.perCapitaCostInEnergy=attrs.value("perCapitaCostEnergy").toUInt();
                    info.combatEffectivenessBonus=attrs.value("combatEffectivenessBonus").toInt();
                    info.duration=attrs.value("duration").toUInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs=m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials=attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy=attrs.value("energy").toUInt();
                            reqs.requiredTime=attrs.value("time").toUInt();
                            m_xmlReader->skipCurrentElement();
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }

                    r.first.insert(level,info);
                    r.second.insert(level,reqs);
                }
                else
                    m_xmlReader->skipCurrentElement();
            }
        }
        else
            m_xmlReader->raiseError("Incorrect file");
    }
    if (m_xmlReader->hasError())
    {
        qCritical()<<"Couldn't read "+path+" properly.";
        return {};
    }
    return r;
}

QPair<QVector<GymLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getGymLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<GymLevelInfo>, QVector<BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="gymLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level=0;
                    GymLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level=attrs.value("level").toUInt();
                    info.amountOfSlots=attrs.value("slots").toInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();
                    info.perCapitaCostInEnergy=attrs.value("perCapitaCostEnergy").toUInt();
                    info.proficiencyBonus=attrs.value("proficiencyBonus").toInt();
                    info.duration=attrs.value("duration").toUInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs=m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials=attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy=attrs.value("energy").toUInt();
                            reqs.requiredTime=attrs.value("time").toUInt();
                            m_xmlReader->skipCurrentElement();
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }

                    r.first.insert(level,info);
                    r.second.insert(level,reqs);
                }
                else
                    m_xmlReader->skipCurrentElement();
            }
        }
        else
            m_xmlReader->raiseError("Incorrect file");
    }
    if (m_xmlReader->hasError())
    {
        qCritical()<<"Couldn't read "+path+" properly.";
        return {};
    }
    return r;
}

QPair<QVector<LaboratoryLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getLaboratoryLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<LaboratoryLevelInfo>, QVector<BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="laboratoryLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level=0;
                    LaboratoryLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level=attrs.value("level").toUInt();
                    info.amountOfSlots=attrs.value("slots").toInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();
                    info.perCapitaCostInEnergy=attrs.value("perCapitaCostEnergy").toUInt();
                    info.clevernessBonus=attrs.value("clevernessBonus").toInt();
                    info.duration=attrs.value("duration").toUInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs=m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials=attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy=attrs.value("energy").toUInt();
                            reqs.requiredTime=attrs.value("time").toUInt();
                            m_xmlReader->skipCurrentElement();
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }

                    r.first.insert(level,info);
                    r.second.insert(level,reqs);
                }
                else
                    m_xmlReader->skipCurrentElement();
            }
        }
        else
            m_xmlReader->raiseError("Incorrect file");
    }
    if (m_xmlReader->hasError())
    {
        qCritical()<<"Couldn't read "+path+" properly.";
        return {};
    }
    return r;
}

QPair<QVector<PlayingFieldLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getPlayingFieldLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<PlayingFieldLevelInfo>, QVector<BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="playingFieldLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level=0;
                    PlayingFieldLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level=attrs.value("level").toUInt();
                    info.amountOfSlots=attrs.value("slots").toInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();
                    info.perCapitaCostInEnergy=attrs.value("perCapitaCostEnergy").toUInt();
                    info.stressReductionForActive=attrs.value("stressReductionActive").toInt();
                    info.stressReductionForConvivial=attrs.value("stressReductionConvivial").toInt();
                    info.stressReductionForRecluse=attrs.value("stressReductionRecluse").toInt();
                    info.stressReductionForReligious=attrs.value("stressReductionReligious").toInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs=m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials=attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy=attrs.value("energy").toUInt();
                            reqs.requiredTime=attrs.value("time").toUInt();
                            m_xmlReader->skipCurrentElement();
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }

                    r.first.insert(level,info);
                    r.second.insert(level,reqs);
                }
                else
                    m_xmlReader->skipCurrentElement();
            }
        }
        else
            m_xmlReader->raiseError("Incorrect file");
    }
    if (m_xmlReader->hasError())
    {
        qCritical()<<"Couldn't read "+path+" properly.";
        return {};
    }
    return r;
}

QPair<QVector<BarLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getBarLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<BarLevelInfo>, QVector<BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="barLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level=0;
                    BarLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level=attrs.value("level").toUInt();
                    info.amountOfSlots=attrs.value("slots").toInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();
                    info.perCapitaCostInEnergy=attrs.value("perCapitaCostEnergy").toUInt();
                    info.stressReductionForActive=attrs.value("stressReductionActive").toInt();
                    info.stressReductionForConvivial=attrs.value("stressReductionConvivial").toInt();
                    info.stressReductionForRecluse=attrs.value("stressReductionRecluse").toInt();
                    info.stressReductionForReligious=attrs.value("stressReductionReligious").toInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs=m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials=attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy=attrs.value("energy").toUInt();
                            reqs.requiredTime=attrs.value("time").toUInt();
                            m_xmlReader->skipCurrentElement();
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }

                    r.first.insert(level,info);
                    r.second.insert(level,reqs);
                }
                else
                    m_xmlReader->skipCurrentElement();
            }
        }
        else
            m_xmlReader->raiseError("Incorrect file");
    }
    if (m_xmlReader->hasError())
    {
        qCritical()<<"Couldn't read "+path+" properly.";
        return {};
    }
    return r;
}

QPair<QVector<ShrineLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getShrineLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<ShrineLevelInfo>, QVector<BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="shrineLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level=0;
                    ShrineLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level=attrs.value("level").toUInt();
                    info.amountOfSlots=attrs.value("slots").toInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();
                    info.perCapitaCostInEnergy=attrs.value("perCapitaCostEnergy").toUInt();
                    info.stressReductionForActive=attrs.value("stressReductionActive").toInt();
                    info.stressReductionForConvivial=attrs.value("stressReductionConvivial").toInt();
                    info.stressReductionForRecluse=attrs.value("stressReductionRecluse").toInt();
                    info.stressReductionForReligious=attrs.value("stressReductionReligious").toInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs=m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials=attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy=attrs.value("energy").toUInt();
                            reqs.requiredTime=attrs.value("time").toUInt();
                            m_xmlReader->skipCurrentElement();
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }

                    r.first.insert(level,info);
                    r.second.insert(level,reqs);
                }
                else
                    m_xmlReader->skipCurrentElement();
            }
        }
        else
            m_xmlReader->raiseError("Incorrect file");
    }
    if (m_xmlReader->hasError())
    {
        qCritical()<<"Couldn't read "+path+" properly.";
        return {};
    }
    return r;
}

QPair<QVector<SeclusionLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getSeclusionLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<SeclusionLevelInfo>, QVector<BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="seclusionLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level=0;
                    SeclusionLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level=attrs.value("level").toUInt();
                    info.amountOfSlots=attrs.value("slots").toInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();
                    info.perCapitaCostInEnergy=attrs.value("perCapitaCostEnergy").toUInt();
                    info.stressReductionForActive=attrs.value("stressReductionActive").toInt();
                    info.stressReductionForConvivial=attrs.value("stressReductionConvivial").toInt();
                    info.stressReductionForRecluse=attrs.value("stressReductionRecluse").toInt();
                    info.stressReductionForReligious=attrs.value("stressReductionReligious").toInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs=m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials=attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy=attrs.value("energy").toUInt();
                            reqs.requiredTime=attrs.value("time").toUInt();
                            m_xmlReader->skipCurrentElement();
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }

                    r.first.insert(level,info);
                    r.second.insert(level,reqs);
                }
                else
                    m_xmlReader->skipCurrentElement();
            }
        }
        else
            m_xmlReader->raiseError("Incorrect file");
    }
    if (m_xmlReader->hasError())
    {
        qCritical()<<"Couldn't read "+path+" properly.";
        return {};
    }
    return r;
}

QPair<QVector<PowerplantLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getPowerplantLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<PowerplantLevelInfo>, QVector<BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="powerplantLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level=0;
                    PowerplantLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level=attrs.value("level").toUInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();
                    info.aetheriteOreTaken=attrs.value("aetheriteTaken").toUInt();
                    info.energyGiven=attrs.value("energyGiven").toUInt();
                    info.maxCycles=attrs.value("maxCycles").toUInt();
                    info.energyLimit=attrs.value("energyLimit").toUInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs=m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials=attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy=attrs.value("energy").toUInt();
                            reqs.requiredTime=attrs.value("time").toUInt();
                            m_xmlReader->skipCurrentElement();
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }

                    r.first.insert(level,info);
                    r.second.insert(level,reqs);
                }
                else
                    m_xmlReader->skipCurrentElement();
            }
        }
        else
            m_xmlReader->raiseError("Incorrect file");
    }
    if (m_xmlReader->hasError())
    {
        qCritical()<<"Couldn't read "+path+" properly.";
        return {};
    }
    return r;
}

QPair<QVector<FactoryLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getFactoryLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<FactoryLevelInfo>, QVector<BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="factoryLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level=0;
                    FactoryLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level=attrs.value("level").toUInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();
                    info.aetheriteOreTaken=attrs.value("aetheriteTaken").toUInt();
                    info.buildingMaterialsGiven=attrs.value("buildingMaterialsGiven").toUInt();
                    info.maxCycles=attrs.value("maxCycles").toUInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs=m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials=attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy=attrs.value("energy").toUInt();
                            reqs.requiredTime=attrs.value("time").toUInt();
                            m_xmlReader->skipCurrentElement();
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }

                    r.first.insert(level,info);
                    r.second.insert(level,reqs);
                }
                else
                    m_xmlReader->skipCurrentElement();
            }
        }
        else
            m_xmlReader->raiseError("Incorrect file");
    }
    if (m_xmlReader->hasError())
    {
        qCritical()<<"Couldn't read "+path+" properly.";
        return {};
    }
    return r;
}

QPair<QVector<CoolRoomLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getCoolRoomLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<CoolRoomLevelInfo>, QVector<BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="coolRoomLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level=0;
                    CoolRoomLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level=attrs.value("level").toUInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();
                    info.foodSuppliesLimit=attrs.value("foodSuppliesLimit").toUInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs=m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials=attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy=attrs.value("energy").toUInt();
                            reqs.requiredTime=attrs.value("time").toUInt();
                            m_xmlReader->skipCurrentElement();
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }

                    r.first.insert(level,info);
                    r.second.insert(level,reqs);
                }
                else
                    m_xmlReader->skipCurrentElement();
            }
        }
        else
            m_xmlReader->raiseError("Incorrect file");
    }
    if (m_xmlReader->hasError())
    {
        qCritical()<<"Couldn't read "+path+" properly.";
        return {};
    }
    return r;
}

QPair<QVector<StorageRoomLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getStorageRoomLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<StorageRoomLevelInfo>, QVector<BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="storageRoomLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level=0;
                    StorageRoomLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level=attrs.value("level").toUInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();
                    info.buildingMaterialsLimit=attrs.value("buildingMaterialsLimit").toUInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs=m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials=attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy=attrs.value("energy").toUInt();
                            reqs.requiredTime=attrs.value("time").toUInt();
                            m_xmlReader->skipCurrentElement();
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }

                    r.first.insert(level,info);
                    r.second.insert(level,reqs);
                }
                else
                    m_xmlReader->skipCurrentElement();
            }
        }
        else
            m_xmlReader->raiseError("Incorrect file");
    }
    if (m_xmlReader->hasError())
    {
        qCritical()<<"Couldn't read "+path+" properly.";
        return {};
    }
    return r;
}

QPair<QVector<AetheriteSiloLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getAetheriteSiloLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<AetheriteSiloLevelInfo>, QVector<BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="aetheriteSiloLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level=0;
                    AetheriteSiloLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level=attrs.value("level").toUInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();
                    info.aetheriteOreLimit=attrs.value("aetheriteOreLimit").toUInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs=m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials=attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy=attrs.value("energy").toUInt();
                            reqs.requiredTime=attrs.value("time").toUInt();
                            m_xmlReader->skipCurrentElement();
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }

                    r.first.insert(level,info);
                    r.second.insert(level,reqs);
                    //m_xmlReader->skipCurrentElement();
                }
                else
                    m_xmlReader->skipCurrentElement();
            }
        }
        else
            m_xmlReader->raiseError("Incorrect file");
    }
    if (m_xmlReader->hasError())
    {
        qCritical()<<"Couldn't read "+path+" properly.";
        return {};
    }
    return r;
}

QPair<QVector<BarracksLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getBarracksLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<BarracksLevelInfo>, QVector<BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="barracksLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level=0;
                    BarracksLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level=attrs.value("level").toUInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();
                    info.mercenariesLimit=attrs.value("mercenariesLimit").toUInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs=m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials=attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy=attrs.value("energy").toUInt();
                            reqs.requiredTime=attrs.value("time").toUInt();
                            m_xmlReader->skipCurrentElement();
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }

                    r.first.insert(level,info);
                    r.second.insert(level,reqs);
                    //m_xmlReader->skipCurrentElement();
                }
                else
                    m_xmlReader->skipCurrentElement();
            }
        }
        else
            m_xmlReader->raiseError("Incorrect file");
    }
    if (m_xmlReader->hasError())
    {
        qCritical()<<"Couldn't read "+path+" properly.";
        return {};
    }
    return r;
}

QPair<QVector<DockingStationLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getDockingStationLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<DockingStationLevelInfo>, QVector<BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="dockingStationLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level=0;
                    DockingStationLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level=attrs.value("level").toUInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();
                    info.recruitsAmount=attrs.value("recruitsAmount").toUInt();
                    info.waitingTime=attrs.value("waitingTime").toUInt();
                    info.profitability=attrs.value("profitability").toUInt();
                    info.equipmentsAmount=attrs.value("equipmentsAmount").toUInt();
                    info.maxTier=attrs.value("maxTier").toUInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs=m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials=attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy=attrs.value("energy").toUInt();
                            reqs.requiredTime=attrs.value("time").toUInt();
                            m_xmlReader->skipCurrentElement();
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }

                    r.first.insert(level,info);
                    r.second.insert(level,reqs);
                }
                else
                    m_xmlReader->skipCurrentElement();
            }
        }
        else
            m_xmlReader->raiseError("Incorrect file");
    }
    if (m_xmlReader->hasError())
    {
        qCritical()<<"Couldn't read "+path+" properly.";
        return {};
    }
    return r;
}

DockingStationTradingTables XmlFileReader::getDockingStationTradingTables(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QVector<QMap<QPair<BaseEnums::Resource, BaseEnums::Resource>, float> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="dockingStationTradingTables")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="tradingTable")
                {
                    unsigned level=0;

                    QMap<QPair<BaseEnums::Resource, BaseEnums::Resource>, float> m;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level=attrs.value("profitabilityLevel").toUInt();

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="entry")
                        {
                            attrs=m_xmlReader->attributes();

                            m.insert({BaseEnums::fromQStringToResourceEnum(attrs.value("from").toString()), BaseEnums::fromQStringToResourceEnum(attrs.value("to").toString())}, GlobalUtilities::roundDouble(attrs.value("ratio").toFloat(),2));
                            m_xmlReader->skipCurrentElement();
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }

                    r.insert(level,m);
                }
                else
                    m_xmlReader->skipCurrentElement();
            }
        }
        else
            m_xmlReader->raiseError("Incorrect file");
    }
    if (m_xmlReader->hasError())
    {
        qCritical()<<"Couldn't read "+path+" properly.";
        return {};
    }
    return r;
}

QMap<BuildingEnums::Building, QString> XmlFileReader::getBuildingDescriptions(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QMap <BuildingEnums::Building, QString> r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="buildingDescriptions")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="buildingDescription")
                {
                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    r.insert(BuildingEnums::fromQStringToBuildingEnum(attrs.value("name").toString()),attrs.value("description").toString());
                    m_xmlReader->skipCurrentElement();
                }
                else
                    m_xmlReader->skipCurrentElement();
            }
        }
        else
            m_xmlReader->raiseError("Incorrect file");
    }
    if (m_xmlReader->hasError())
    {
        qCritical()<<"Couldn't read "+path+" properly.";
        return {};
    }
    return r;
}

QList<QString> XmlFileReader::getMercenariesNamesList(const QString &pathToMercenariesDir) noexcept
{
    if (!QDir(pathToMercenariesDir).exists())
        qCritical()<<"Directory "+pathToMercenariesDir+" doesn't exist.";

    auto r = QDir(pathToMercenariesDir).entryList({"*.xml"});
    for (int i=0;i<r.size();++i)
        r[i].remove(r[i].size()-4,4);
    if (r.isEmpty())
        qCritical("No mercenaries detected.");
    return r;
}

Mercenary *XmlFileReader::getMercenary(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    MercenaryBuilder hB;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="mercenary")
        {
            QXmlStreamAttributes attrs = m_xmlReader->attributes();
            hB.setName(attrs.value("name").toString());

            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="attributes")
                {
                    attrs = m_xmlReader->attributes();
                    hB.setCombatEffectiveness(attrs.value("combatEffectiveness").toInt());
                    hB.setProficiency(attrs.value("proficiency").toInt());
                    hB.setCleverness(attrs.value("cleverness").toInt());
                    hB.setLuck(GlobalUtilities::roundDouble(attrs.value("luck").toFloat(),2));
                    hB.setHealth(attrs.value("health").toInt());
                    hB.setHealthLimit(attrs.value("healthLimit").toInt());
                    hB.setDailyHealthRecovery(attrs.value("dailyHealthRecovery").toInt());
                    hB.setStress(attrs.value("stress").toInt());
                    hB.setStressResistance(GlobalUtilities::roundDouble(attrs.value("stressResistance").toFloat(),2));
                    hB.setStressLimit(attrs.value("stressLimit").toInt());
                    hB.setStressBorder(attrs.value("stressBorder").toInt());
                    hB.setDailyStressRecovery(attrs.value("dailyStressRecovery").toInt());
                    hB.setSalary(attrs.value("salary").toInt());
                    hB.setDailyFoodConsumption(attrs.value("dailyFoodConsumption").toInt());
                    hB.setNature(MercenaryEnums::fromQStringToNatureEnum(attrs.value("nature").toString()));
                    hB.setProfession(MercenaryEnums::fromQStringToProfessionEnum(attrs.value("profession").toString()));

                    m_xmlReader->skipCurrentElement();
                }
                else if (m_xmlReader->name()=="sbeList")
                {
                    QVector <MercenaryStressBorderEffect> sbes;
                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="sbe")
                            sbes.push_back({MercenaryEnums::fromQStringToStressBorderEffectEnum(m_xmlReader->readElementText())});
                        else
                            m_xmlReader->skipCurrentElement();
                    }
                    hB.setStressBorderEffects(sbes);
                }
                else if (m_xmlReader->name()=="equipment")
                {
                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="armor")
                        {
                            attrs = m_xmlReader->attributes();
                            for (int i=0;i<Game::gameInstance()->assetsPool().equipment().size();++i)
                                if (Game::gameInstance()->assetsPool().equipment()[i]->name() == attrs.value("name").toString())
                                {
                                    hB.setAndEquipArmor(Game::gameInstance()->assetsPool().makeEquipmentAtPos(i));
                                    break;
                                }
                        }
                        else if (m_xmlReader->name()=="weaponTool")
                        {
                            attrs = m_xmlReader->attributes();
                            for (int i=0;i<Game::gameInstance()->assetsPool().equipment().size();++i)
                                if (Game::gameInstance()->assetsPool().equipment()[i]->name() == attrs.value("name").toString())
                                {
                                    hB.setAndEquipWeaponTool(Game::gameInstance()->assetsPool().makeEquipmentAtPos(i),attrs.value("slot").toInt());
                                    break;
                                }
                        }
                        m_xmlReader->skipCurrentElement();
                    }
                }
                else if (m_xmlReader->name()=="additionalData")
                {
                    attrs = m_xmlReader->attributes();

                    hB.setIsDead(static_cast<bool>(attrs.value("dead").toInt()));
                    hB.setIsDead(static_cast<bool>(attrs.value("stressBorderEffectActive").toInt()));

                    hB.setNoSignalDaysRemaining(attrs.value("noSigDaysRem").toInt());

                    m_xmlReader->skipCurrentElement();
                }
                else
                    m_xmlReader->skipCurrentElement();
            }
        }
        else
            m_xmlReader->raiseError("Incorrect file");
    }

    if (m_xmlReader->hasError())
    {
        qCritical()<<"Couldn't read "+path+" properly.";
        return nullptr;
    }
    return hB.getMercenary();
}

QVector<Equipment *> XmlFileReader::getEquipment(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QVector <Equipment *> r;
    EquipmentBuilder eqB;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="equipmentList")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="weaponTool")
                {
                    eqB.setType(EquipmentEnums::T_WeaponTool);

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    eqB.setName(attrs.value("name").toString());
                    eqB.setTier(attrs.value("tier").toUInt());

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="effects")
                        {
                            while (m_xmlReader->readNextStartElement())
                            {
                                if (m_xmlReader->name()=="bonus")
                                {
                                    attrs = m_xmlReader->attributes();
                                    if (attrs.value("varName")=="combatEffectiveness")
                                        eqB.setCombatEffectivenessBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="proficiency")
                                        eqB.setProficiencyBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="cleverness")
                                        eqB.setClevernessBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="luck")
                                        eqB.setLuckBonus(GlobalUtilities::roundDouble(attrs.value("value").toFloat(),2));
                                    else if (attrs.value("varName")=="healthLimit")
                                        eqB.setHealthLimitBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="dailyHealthRecovery")
                                        eqB.setDailyHealthRecoveryBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="stressResistance")
                                        eqB.setStressResistanceBonus(GlobalUtilities::roundDouble(attrs.value("value").toFloat(),2));
                                    else if (attrs.value("varName")=="stressLimit")
                                        eqB.setStressLimitBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="stressBorder")
                                        eqB.setStressBorderBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="dailyStressRecovery")
                                        eqB.setDailyStressRecoveryBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="salary")
                                        eqB.setSalaryBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="dailyFoodConsumption")
                                        eqB.setDailyFoodConsumptionBonus(attrs.value("value").toInt());
                                    m_xmlReader->skipCurrentElement();
                                }
                                else
                                    m_xmlReader->skipCurrentElement();
                            }
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }

                    r.push_back(eqB.getEquipment());
                }
                else if (m_xmlReader->name()=="armor")
                {
                    eqB.setType(EquipmentEnums::T_Armor);

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    eqB.setName(attrs.value("name").toString());
                    eqB.setTier(attrs.value("tier").toUInt());

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="effects")
                        {
                            while (m_xmlReader->readNextStartElement())
                            {
                                if (m_xmlReader->name()=="bonus")
                                {
                                    attrs = m_xmlReader->attributes();
                                    if (attrs.value("varName")=="combatEffectiveness")
                                        eqB.setCombatEffectivenessBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="proficiency")
                                        eqB.setProficiencyBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="cleverness")
                                        eqB.setClevernessBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="luck")
                                        eqB.setLuckBonus(GlobalUtilities::roundDouble(attrs.value("value").toFloat(),2));
                                    else if (attrs.value("varName")=="healthLimit")
                                        eqB.setHealthLimitBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="dailyHealthRecovery")
                                        eqB.setDailyHealthRecoveryBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="stressResistance")
                                        eqB.setStressResistanceBonus(GlobalUtilities::roundDouble(attrs.value("value").toFloat(),2));
                                    else if (attrs.value("varName")=="stressLimit")
                                        eqB.setStressLimitBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="stressBorder")
                                        eqB.setStressBorderBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="dailyStressRecovery")
                                        eqB.setDailyStressRecoveryBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="salary")
                                        eqB.setSalaryBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="dailyFoodConsumption")
                                        eqB.setDailyFoodConsumptionBonus(attrs.value("value").toInt());
                                    m_xmlReader->skipCurrentElement();
                                }
                                else
                                    m_xmlReader->skipCurrentElement();
                            }
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }

                    r.push_back(eqB.getEquipment());
                }
                else
                    m_xmlReader->skipCurrentElement();
            }
        }
        else
            m_xmlReader->raiseError("Incorrect file");
    }
    if (m_xmlReader->hasError())
    {
        for (int i=0;i<r.size();++i)
            delete r[i];
        qCritical()<<"Couldn't read "+path+" properly.";
        return {};
    }

    Game::gameInstance()->loggers()->xmlLogger()->info("Loaded equipment at {}. Entries: {}", path.toStdString(), r.size());

    return r;
}

QMap<QString, QMap<QString, QString> > XmlFileReader::getTranslations(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QMap<QString, QMap<QString, QString> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="translations")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="text")
                {
                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    QString originalText=attrs.value("original").toString();
                    if (!r.contains(originalText))
                        r.insert(originalText,{});
                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="translation")
                        {
                            attrs = m_xmlReader->attributes();
                            r[originalText].insert(attrs.value("context").toString(),attrs.value("translated").toString());
                            m_xmlReader->skipCurrentElement();
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }
                }
                else
                    m_xmlReader->skipCurrentElement();
            }
        }
        else
            m_xmlReader->raiseError("Incorrect file");
    }
    if (m_xmlReader->hasError())
    {
        qCritical()<<"Couldn't read "+path+" properly.";
        return {};
    }
    return r;
}

QList<QString> XmlFileReader::getDatabaseFilesList(const QString &pathToDBDir) noexcept
{
    if (!QDir(pathToDBDir).exists())
        qCritical()<<"Directory "+pathToDBDir+" doesn't exist.";

    auto r = QDir(pathToDBDir).entryList({}, QDir::Files | QDir::NoDotAndDotDot);
    if (r.isEmpty())
        qCritical("No db files detected.");
    return r;
}

QVector<DatabaseEntry> XmlFileReader::getDatabaseEntries(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QVector <DatabaseEntry> r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="dbEntries")
        {
            auto attrs = m_xmlReader->attributes();
            DatabaseEnums::EntryType entriesType = DatabaseEnums::fromQStringToEntryTypeEnum(attrs.value("type").toString());

            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="entry")
                {
                    QString name, description;
                    QVector <QString> inhs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name() == "name")
                            name=m_xmlReader->readElementText();
                        else if (m_xmlReader->name() == "description")
                            description=m_xmlReader->readElementText();
                        else if (m_xmlReader->name() == "inhabitancies")
                        {
                            while (m_xmlReader->readNextStartElement())
                            {
                                if (m_xmlReader->name() == "inhabitancy")
                                    inhs+=m_xmlReader->readElementText();
                                else
                                    m_xmlReader->skipCurrentElement();
                            }
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }

                    r += {name,{description,entriesType,inhs}};
                }
                else
                    m_xmlReader->skipCurrentElement();
            }
        }
        else
            m_xmlReader->skipCurrentElement();
    }

    if (m_xmlReader->hasError())
    {
        qCritical()<<"Couldn't read "+path+" properly.";
        return {};
    }

    Game::gameInstance()->loggers()->xmlLogger()->info("Loaded db entries at {}. Entries: {}", path.toStdString(), r.size());

    return r;
}

QList<QString> XmlFileReader::getLandsNamesList(const QString &pathToLandsDir) noexcept
{
    if (!QDir(pathToLandsDir).exists())
        qCritical()<<"Directory "+pathToLandsDir+" doesn't exist.";

    auto r = QDir(pathToLandsDir).entryList({}, QDir::Dirs | QDir::NoDotAndDotDot);
    if (r.isEmpty())
        qCritical("No lands detected.");
    return r;
}

LandInfo XmlFileReader::getLandInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    LandInfo r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="land")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="name")
                    r.name=m_xmlReader->readElementText();
                else if (m_xmlReader->name()=="description")
                    r.description=m_xmlReader->readElementText();
                else if (m_xmlReader->name()=="position")
                {
                    auto attrs=m_xmlReader->attributes();
                    r.position={attrs.value("x").toInt(), attrs.value("y").toInt()};
                    m_xmlReader->skipCurrentElement();
                }
                else
                    m_xmlReader->skipCurrentElement();
            }
        }
        else
            m_xmlReader->raiseError("Parse error");
    }

    if (m_xmlReader->hasError())
    {
        qCritical()<<"Couldn't read "+path+" properly.";
        return {};
    }

    Game::gameInstance()->loggers()->xmlLogger()->info("Loaded land at {}.", path.toStdString());

    return r;
}

EncountersContainer *XmlFileReader::getEncounters(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return nullptr;
    }

    EncountersContainer *r = new EncountersContainer;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="encounters")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="encounter")
                {
                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    QString name=attrs.value("name").toString();
                    Event *rootev=getEvent(0);
                    unsigned probability = attrs.hasAttribute("probability") ? attrs.value("probability").toUInt() : 1;

                    if (m_xmlReader->hasError())
                    {
                        qCritical()<<"Couldn't read "+path+" properly.";
                        delete r;
                        return nullptr;
                    }

                    r->addEncounter(new Encounter(name, rootev, probability));
                }
                m_xmlReader->skipCurrentElement();//encounter/*
            }
        }
        else
            m_xmlReader->raiseError("Incorrect file");
    }

    Game::gameInstance()->loggers()->xmlLogger()->info("Loaded encounters at {}. Entries: {}", path.toStdString(), r->encounters().size());

    if (m_xmlReader->hasError())
    {
        qCritical()<<"Couldn't read "+path+" properly.";
        delete r;
        return nullptr;
    }
    return r;
}

Event *XmlFileReader::getEvent(bool alreadyRead) noexcept
{
    Event *r = nullptr;

    QString text;
    QVector <QString> ude;

    if (alreadyRead || m_xmlReader->readNextStartElement())
    {
        if (alreadyRead || m_xmlReader->name()=="event")
        {
            QXmlStreamAttributes attrs = m_xmlReader->attributes();
            auto type=attrs.value("type").toString();

            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="text")
                {
                    text=m_xmlReader->readElementText();
                }
                else if (m_xmlReader->name()=="unlockedDBEntries")
                {
                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="entry")
                        {
                            ude+=m_xmlReader->readElementText();
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }
                }
                else
                    break;
            }

            if (type=="Multi")
            {
                if (m_xmlReader->name()=="events")
                {
                    QVector <Event *> evs;
                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="event")
                        {
                            evs+=getEvent(1);
                            if (m_xmlReader->hasError())
                                return nullptr;
                        }
                    }
                    r=new MultiEvent(evs,text,ude);
                }
                m_xmlReader->skipCurrentElement();//event
            }
            else if (type=="Action")
            {
                auto subtype=attrs.value("subtype").toString();

                if (subtype=="Null")
                {
                    r=new NullEventResult(text,ude);
                }
                else if (subtype=="GiveHealth")
                {
                    if (m_xmlReader->name()=="addedValue")
                        r=new GiveHealthEventResult(parseValue(m_xmlReader->attributes().value("value").toString()),text,ude);
                    m_xmlReader->skipCurrentElement();//addedValue
                }
                else if (subtype=="GiveStress")
                {
                    if (m_xmlReader->name()=="addedValue")
                        r=new GiveStressEventResult(parseValue(m_xmlReader->attributes().value("value").toString()),text,ude);
                    m_xmlReader->skipCurrentElement();//addedValue
                }
                else if (subtype=="ModifyAttribute")
                {
                    if (m_xmlReader->name()=="modification")
                    {
                        AttributeModificationHelper mod;
                        attrs=m_xmlReader->attributes();

                        mod.attribute=MercenaryEnums::fromQStringToAttributeEnum(attrs.value("attribute").toString());
                        if (attrs.value("type").toString()=="+")
                            mod.type=AttributeModification::T_Add;
                        else if (attrs.value("type").toString()=="-")
                            mod.type=AttributeModification::T_Subtract;
                        else if (attrs.value("type").toString()=="*")
                            mod.type=AttributeModification::T_Multiply;
                        else if (attrs.value("type").toString()=="/")
                            mod.type=AttributeModification::T_Divide;
                        else if (attrs.value("type").toString()=="=")
                            mod.type=AttributeModification::T_Set;

                        mod.expressionRange=parseValue(attrs.value("value").toString());

                        mod.durationRange=parseValue(attrs.value("duration").toString());

                        r=new ModifyAttributeEventResult(mod,text,ude);
                    }
                    m_xmlReader->skipCurrentElement();//modification
                }
                else if (subtype=="Kill")
                {
                    r=new KillMercenaryEventResult(text,ude);
                }
                else if (subtype=="AddEquipment")
                {
                    if (m_xmlReader->name()=="equipment")
                    {
                        attrs = m_xmlReader->attributes();
                        for (int i=0;i<Game::gameInstance()->assetsPool().equipment().size();++i)
                            if (Game::gameInstance()->assetsPool().equipment()[i]->name() == attrs.value("name").toString())
                            {
                                r=new AddEquipmentEventResult(Game::gameInstance()->assetsPool().makeEquipmentAtPos(i),text,ude);
                                break;
                            }
                    }
                    else if (m_xmlReader->name()=="random")
                    {
                        attrs = m_xmlReader->attributes();

                        bool allowArmor=attrs.value("armor").toString()=="true" ? true : false;
                        bool allowWeaponTool=attrs.value("weaponTool").toString()=="true" ? true : false;
                        int flags=0;
                        if (allowArmor)
                            flags |= EquipmentEnums::T_Armor;
                        if (allowWeaponTool)
                            flags |= EquipmentEnums::T_WeaponTool;

                        r=new AddEquipmentRandomEventResult(parseValue(attrs.value("tier").toString()), flags,text,ude);
                    }
                    m_xmlReader->skipCurrentElement();//equipment/random
                }
                else if (subtype=="RemoveEquipment")
                {
                    if (m_xmlReader->name()=="armor")
                        r=new RemoveEquipmentEventResult(EquipmentEnums::T_Armor,0,text,ude);
                    else if (m_xmlReader->name()=="weaponTool")
                    {
                        attrs=m_xmlReader->attributes();
                        r=new RemoveEquipmentEventResult(EquipmentEnums::T_WeaponTool, attrs.value("slot").toInt(),text,ude);
                    }
                    m_xmlReader->skipCurrentElement();//armor/weaponTool
                }
                else if (subtype=="GiveResource")
                {
                    if (m_xmlReader->name()=="resource")
                    {
                        attrs=m_xmlReader->attributes();

                        r=new GiveResourceEventResult(BaseEnums::fromQStringToResourceEnum(attrs.value("type").toString()), parseValue(attrs.value("amount").toString()),text,ude);
                    }
                    else if (m_xmlReader->name()=="random")
                    {
                        attrs=m_xmlReader->attributes();

                        r=new GiveResourceRandomEventResult(parseValue(attrs.value("amount").toString()),text,ude);
                    }
                    m_xmlReader->skipCurrentElement();//resource
                }
                else if (subtype=="NoSignal")
                {
                    if (m_xmlReader->name()=="duration")
                        r=new NoSignalEventResult(parseValue(m_xmlReader->attributes().value("duration").toString()),text,ude);
                    m_xmlReader->skipCurrentElement();//duration
                }
                else
                    m_xmlReader->skipCurrentElement();

                if (subtype != "Null" && subtype != "Kill")
                    m_xmlReader->skipCurrentElement();//event
            }
            else if (type=="Check")
            {
                auto subtype=attrs.value("subtype").toString();

                if (subtype=="Value")
                {
                    Expression cond;
                    if (m_xmlReader->name()=="condition")
                    {
                        cond={m_xmlReader->attributes().value("condition").toString()};
                        m_xmlReader->skipCurrentElement();
                    }
                    else
                        m_xmlReader->raiseError("Parse error");

                    CheckEventResultsBuilder resb;
                    if (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="results")
                        {
                            while (m_xmlReader->readNextStartElement())
                            {
                                if (m_xmlReader->name()=="positive")
                                {
                                    while (m_xmlReader->readNextStartElement())
                                    {
                                        if (m_xmlReader->name()=="event")
                                        {
                                            Chance chance{m_xmlReader->attributes().value("chance").toUInt()};
                                            resb.addPositive({getEvent(1), chance});
                                            if (m_xmlReader->hasError())
                                                return nullptr;
                                        }
                                    }
                                }
                                else if (m_xmlReader->name()=="negative")
                                {
                                    while (m_xmlReader->readNextStartElement())
                                    {
                                        if (m_xmlReader->name()=="event")
                                        {
                                            Chance chance{m_xmlReader->attributes().value("chance").toUInt()};
                                            resb.addNegative({getEvent(1), chance});
                                            if (m_xmlReader->hasError())
                                                return nullptr;
                                        }
                                    }
                                }
                                else
                                    m_xmlReader->skipCurrentElement();
                            }
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }
                    else
                        m_xmlReader->raiseError("Parse error");

                    r=new ValueCheckEvent(cond, resb.get(),text,ude);
                }
                else if (subtype=="Equipment")
                {
                    EquipmentEnums::Category cond;
                    if (m_xmlReader->name()=="condition")
                    {
                        cond=EquipmentEnums::fromQStringToCategoryEnum(m_xmlReader->attributes().value("condition").toString());
                        m_xmlReader->skipCurrentElement();
                    }
                    else
                        m_xmlReader->raiseError("Parse error");

                    CheckEventResultsBuilder resb;
                    if (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="results")
                        {
                            while (m_xmlReader->readNextStartElement())
                            {
                                if (m_xmlReader->name()=="positive")
                                {
                                    while (m_xmlReader->readNextStartElement())
                                    {
                                        if (m_xmlReader->name()=="event")
                                        {
                                            Chance chance{m_xmlReader->attributes().value("chance").toInt()};
                                            resb.addPositive({getEvent(1), chance});
                                            if (m_xmlReader->hasError())
                                                return nullptr;
                                        }
                                    }
                                }
                                else if (m_xmlReader->name()=="negative")
                                {
                                    while (m_xmlReader->readNextStartElement())
                                    {
                                        if (m_xmlReader->name()=="event")
                                        {
                                            Chance chance{m_xmlReader->attributes().value("chance").toInt()};
                                            resb.addNegative({getEvent(1), chance});
                                            if (m_xmlReader->hasError())
                                                return nullptr;
                                        }
                                    }
                                }
                                else
                                    m_xmlReader->skipCurrentElement();
                            }
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }
                    else
                        m_xmlReader->raiseError("Parse error");

                    r=new EquipmentCheckEvent(cond, resb.get(),text,ude);
                }
                m_xmlReader->skipCurrentElement();//event
            }
            else if (type=="Possibility")
            {
                if (m_xmlReader->name()=="event")
                {
                    Chance chance{m_xmlReader->attributes().value("chance").toUInt()};
                    Event *ev=getEvent(1);
                    if (m_xmlReader->hasError())
                        return nullptr;
                    r=new PossibilityEvent(chance,ev,text,ude);
                }
                m_xmlReader->skipCurrentElement();//event
            }
            else
                m_xmlReader->raiseError("Parse error");
        }
        else
            m_xmlReader->skipCurrentElement();
    }
    if (m_xmlReader->hasError())
        return nullptr;
    if (r == nullptr)
        r=new NullEventResult;
    return r;
}

ValueRange XmlFileReader::parseValue(QString text) noexcept
{
    if (text.isEmpty())
        return {{"-1"}};//error

    int semcolPos=text.indexOf(';');
    
    char rangeok=0;
    if (text[0]=='<')
        rangeok |= 1;
    if (text[text.size()-1]=='>')
        rangeok |= 1<<1;
    if (semcolPos!=-1 && semcolPos>1 && semcolPos<text.size()-2)
        rangeok |= 1<<2;
    
    if (rangeok & (1|1<<1|1<<2))
        return {text.mid(1,semcolPos-1),text.mid(semcolPos+1,text.size()-semcolPos-2)};
    else if (rangeok==0)
        return {text};
    else
        return {{"-1"}};//error
}
