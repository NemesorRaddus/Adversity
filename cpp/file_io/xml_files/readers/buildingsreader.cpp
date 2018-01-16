#include "buildingsreader.h"

#include "base/buildings/specific/storage/aetheritesilo.h"
#include "base/buildings/specific/destressing/bar.h"
#include "base/buildings/specific/other/barracks.h"
#include "base/buildings/specific/other/centralunit.h"
#include "base/buildings/specific/storage/coolroom.h"
#include "base/buildings/specific/other/dockingstation.h"
#include "base/buildings/specific/production/factory.h"
#include "base/buildings/specific/training/gym.h"
#include "base/buildings/specific/other/hospital.h"
#include "base/buildings/specific/training/laboratory.h"
#include "base/buildings/specific/destressing/playingfield.h"
#include "base/buildings/specific/production/powerplant.h"
#include "base/buildings/specific/destressing/seclusion.h"
#include "base/buildings/specific/destressing/shrine.h"
#include "base/buildings/specific/storage/storageroom.h"
#include "base/buildings/specific/training/trainingground.h"
#include "base/buildings/upgraderequirements.h"
#include "general/globalutilities.h"

QPair<QVector<CentralUnitLevelInfo *>, QVector <BuildingUpgradeRequirements> > BuildingsReader::getCentralUnitLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<CentralUnitLevelInfo *>, QVector <BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="centralUnitLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level = 0;
                    CentralUnitLevelInfo *info = new CentralUnitLevelInfo;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level = attrs.value("level").toUInt();
                    info->basicCostInEnergy = attrs.value("basicCostEnergy").toUInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs = m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials = attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy = attrs.value("energy").toUInt();
                            reqs.requiredTime = attrs.value("time").toUInt();
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

QPair<QVector<HospitalLevelInfo *>, QVector <BuildingUpgradeRequirements> > BuildingsReader::getHospitalLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<HospitalLevelInfo *>, QVector <BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="hospitalLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level = 0;
                    HospitalLevelInfo *info = new HospitalLevelInfo;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level = attrs.value("level").toUInt();
                    info->amountOfSlots = attrs.value("slots").toUInt();
                    info->basicCostInEnergy = attrs.value("basicCostEnergy").toUInt();
                    info->perCapitaCostInEnergy = attrs.value("perCapitaCostEnergy").toUInt();
                    info->basicCostInFoodSupplies = attrs.value("basicCostFood").toUInt();
                    info->perCapitaCostInFoodSupplies = attrs.value("perCapitaCostFood").toUInt();
                    info->hpRestored = attrs.value("hpRestored").toUInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs = m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials = attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy = attrs.value("energy").toUInt();
                            reqs.requiredTime = attrs.value("time").toUInt();
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

QPair<QVector<TrainingGroundLevelInfo *>, QVector <BuildingUpgradeRequirements> > BuildingsReader::getTrainingGroundLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<TrainingGroundLevelInfo *>, QVector <BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="trainingGroundLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level = 0;
                    TrainingGroundLevelInfo *info = new TrainingGroundLevelInfo;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level = attrs.value("level").toUInt();
                    info->amountOfSlots = attrs.value("slots").toInt();
                    info->basicCostInEnergy = attrs.value("basicCostEnergy").toUInt();
                    info->perCapitaCostInEnergy = attrs.value("perCapitaCostEnergy").toUInt();
                    info->combatEffectivenessBonus = attrs.value("combatEffectivenessBonus").toInt();
                    info->duration = attrs.value("duration").toUInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs = m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials = attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy = attrs.value("energy").toUInt();
                            reqs.requiredTime = attrs.value("time").toUInt();
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

QPair<QVector<GymLevelInfo *>, QVector <BuildingUpgradeRequirements> > BuildingsReader::getGymLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<GymLevelInfo *>, QVector <BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="gymLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level = 0;
                    GymLevelInfo *info = new GymLevelInfo;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level = attrs.value("level").toUInt();
                    info->amountOfSlots = attrs.value("slots").toInt();
                    info->basicCostInEnergy = attrs.value("basicCostEnergy").toUInt();
                    info->perCapitaCostInEnergy = attrs.value("perCapitaCostEnergy").toUInt();
                    info->proficiencyBonus = attrs.value("proficiencyBonus").toInt();
                    info->duration = attrs.value("duration").toUInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs = m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials = attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy = attrs.value("energy").toUInt();
                            reqs.requiredTime = attrs.value("time").toUInt();
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

QPair<QVector<LaboratoryLevelInfo *>, QVector <BuildingUpgradeRequirements> > BuildingsReader::getLaboratoryLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<LaboratoryLevelInfo *>, QVector <BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="laboratoryLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level = 0;
                    LaboratoryLevelInfo *info = new LaboratoryLevelInfo;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level = attrs.value("level").toUInt();
                    info->amountOfSlots = attrs.value("slots").toInt();
                    info->basicCostInEnergy = attrs.value("basicCostEnergy").toUInt();
                    info->perCapitaCostInEnergy = attrs.value("perCapitaCostEnergy").toUInt();
                    info->clevernessBonus = attrs.value("clevernessBonus").toInt();
                    info->duration = attrs.value("duration").toUInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs = m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials = attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy = attrs.value("energy").toUInt();
                            reqs.requiredTime = attrs.value("time").toUInt();
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

QPair<QVector<PlayingFieldLevelInfo *>, QVector <BuildingUpgradeRequirements> > BuildingsReader::getPlayingFieldLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<PlayingFieldLevelInfo *>, QVector <BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="playingFieldLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level = 0;
                    PlayingFieldLevelInfo *info = new PlayingFieldLevelInfo;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level = attrs.value("level").toUInt();
                    info->amountOfSlots = attrs.value("slots").toInt();
                    info->basicCostInEnergy = attrs.value("basicCostEnergy").toUInt();
                    info->perCapitaCostInEnergy = attrs.value("perCapitaCostEnergy").toUInt();
                    info->stressReductionForActive = attrs.value("stressReductionActive").toInt();
                    info->stressReductionForConvivial = attrs.value("stressReductionConvivial").toInt();
                    info->stressReductionForRecluse = attrs.value("stressReductionRecluse").toInt();
                    info->stressReductionForReligious = attrs.value("stressReductionReligious").toInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs = m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials = attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy = attrs.value("energy").toUInt();
                            reqs.requiredTime = attrs.value("time").toUInt();
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

QPair<QVector<BarLevelInfo *>, QVector <BuildingUpgradeRequirements> > BuildingsReader::getBarLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<BarLevelInfo *>, QVector <BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="barLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level = 0;
                    BarLevelInfo *info = new BarLevelInfo;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level = attrs.value("level").toUInt();
                    info->amountOfSlots = attrs.value("slots").toInt();
                    info->basicCostInEnergy = attrs.value("basicCostEnergy").toUInt();
                    info->perCapitaCostInEnergy = attrs.value("perCapitaCostEnergy").toUInt();
                    info->stressReductionForActive = attrs.value("stressReductionActive").toInt();
                    info->stressReductionForConvivial = attrs.value("stressReductionConvivial").toInt();
                    info->stressReductionForRecluse = attrs.value("stressReductionRecluse").toInt();
                    info->stressReductionForReligious = attrs.value("stressReductionReligious").toInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs = m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials = attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy = attrs.value("energy").toUInt();
                            reqs.requiredTime = attrs.value("time").toUInt();
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

QPair<QVector<ShrineLevelInfo *>, QVector <BuildingUpgradeRequirements> > BuildingsReader::getShrineLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<ShrineLevelInfo *>, QVector <BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="shrineLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level = 0;
                    ShrineLevelInfo *info = new ShrineLevelInfo;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level = attrs.value("level").toUInt();
                    info->amountOfSlots = attrs.value("slots").toInt();
                    info->basicCostInEnergy = attrs.value("basicCostEnergy").toUInt();
                    info->perCapitaCostInEnergy = attrs.value("perCapitaCostEnergy").toUInt();
                    info->stressReductionForActive = attrs.value("stressReductionActive").toInt();
                    info->stressReductionForConvivial = attrs.value("stressReductionConvivial").toInt();
                    info->stressReductionForRecluse = attrs.value("stressReductionRecluse").toInt();
                    info->stressReductionForReligious = attrs.value("stressReductionReligious").toInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs = m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials = attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy = attrs.value("energy").toUInt();
                            reqs.requiredTime = attrs.value("time").toUInt();
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

QPair<QVector<SeclusionLevelInfo *>, QVector <BuildingUpgradeRequirements> > BuildingsReader::getSeclusionLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<SeclusionLevelInfo *>, QVector <BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="seclusionLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level = 0;
                    SeclusionLevelInfo *info = new SeclusionLevelInfo;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level = attrs.value("level").toUInt();
                    info->amountOfSlots = attrs.value("slots").toInt();
                    info->basicCostInEnergy = attrs.value("basicCostEnergy").toUInt();
                    info->perCapitaCostInEnergy = attrs.value("perCapitaCostEnergy").toUInt();
                    info->stressReductionForActive = attrs.value("stressReductionActive").toInt();
                    info->stressReductionForConvivial = attrs.value("stressReductionConvivial").toInt();
                    info->stressReductionForRecluse = attrs.value("stressReductionRecluse").toInt();
                    info->stressReductionForReligious = attrs.value("stressReductionReligious").toInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs = m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials = attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy = attrs.value("energy").toUInt();
                            reqs.requiredTime = attrs.value("time").toUInt();
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

QPair<QVector<PowerplantLevelInfo *>, QVector <BuildingUpgradeRequirements> > BuildingsReader::getPowerplantLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<PowerplantLevelInfo *>, QVector <BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="powerplantLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level = 0;
                    PowerplantLevelInfo *info = new PowerplantLevelInfo;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level = attrs.value("level").toUInt();
                    info->basicCostInEnergy = attrs.value("basicCostEnergy").toUInt();
                    info->aetheriteOreTaken = attrs.value("aetheriteTaken").toUInt();
                    info->energyGiven = attrs.value("energyGiven").toUInt();
                    info->maxCycles = attrs.value("maxCycles").toUInt();
                    info->energyLimit = attrs.value("energyLimit").toUInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs = m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials = attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy = attrs.value("energy").toUInt();
                            reqs.requiredTime = attrs.value("time").toUInt();
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

QPair<QVector<FactoryLevelInfo *>, QVector <BuildingUpgradeRequirements> > BuildingsReader::getFactoryLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<FactoryLevelInfo *>, QVector <BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="factoryLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level = 0;
                    FactoryLevelInfo *info = new FactoryLevelInfo;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level = attrs.value("level").toUInt();
                    info->basicCostInEnergy = attrs.value("basicCostEnergy").toUInt();
                    info->aetheriteOreTaken = attrs.value("aetheriteTaken").toUInt();
                    info->buildingMaterialsGiven = attrs.value("buildingMaterialsGiven").toUInt();
                    info->maxCycles = attrs.value("maxCycles").toUInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs = m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials = attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy = attrs.value("energy").toUInt();
                            reqs.requiredTime = attrs.value("time").toUInt();
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

QPair<QVector<CoolRoomLevelInfo *>, QVector <BuildingUpgradeRequirements> > BuildingsReader::getCoolRoomLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<CoolRoomLevelInfo *>, QVector <BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="coolRoomLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level = 0;
                    CoolRoomLevelInfo *info = new CoolRoomLevelInfo;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level = attrs.value("level").toUInt();
                    info->basicCostInEnergy = attrs.value("basicCostEnergy").toUInt();
                    info->foodSuppliesLimit = attrs.value("foodSuppliesLimit").toUInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs = m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials = attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy = attrs.value("energy").toUInt();
                            reqs.requiredTime = attrs.value("time").toUInt();
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

QPair<QVector<StorageRoomLevelInfo *>, QVector <BuildingUpgradeRequirements> > BuildingsReader::getStorageRoomLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<StorageRoomLevelInfo *>, QVector <BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="storageRoomLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level = 0;
                    StorageRoomLevelInfo *info = new StorageRoomLevelInfo;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level = attrs.value("level").toUInt();
                    info->basicCostInEnergy = attrs.value("basicCostEnergy").toUInt();
                    info->buildingMaterialsLimit = attrs.value("buildingMaterialsLimit").toUInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs = m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials = attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy = attrs.value("energy").toUInt();
                            reqs.requiredTime = attrs.value("time").toUInt();
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

QPair<QVector<AetheriteSiloLevelInfo *>, QVector <BuildingUpgradeRequirements> > BuildingsReader::getAetheriteSiloLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<AetheriteSiloLevelInfo *>, QVector <BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="aetheriteSiloLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level = 0;
                    AetheriteSiloLevelInfo *info = new AetheriteSiloLevelInfo;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level = attrs.value("level").toUInt();
                    info->basicCostInEnergy = attrs.value("basicCostEnergy").toUInt();
                    info->aetheriteOreLimit = attrs.value("aetheriteOreLimit").toUInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs = m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials = attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy = attrs.value("energy").toUInt();
                            reqs.requiredTime = attrs.value("time").toUInt();
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

QPair<QVector<BarracksLevelInfo *>, QVector <BuildingUpgradeRequirements> > BuildingsReader::getBarracksLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<BarracksLevelInfo *>, QVector <BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="barracksLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level = 0;
                    BarracksLevelInfo *info = new BarracksLevelInfo;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level = attrs.value("level").toUInt();
                    info->basicCostInEnergy = attrs.value("basicCostEnergy").toUInt();
                    info->mercenariesLimit = attrs.value("mercenariesLimit").toUInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs = m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials = attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy = attrs.value("energy").toUInt();
                            reqs.requiredTime = attrs.value("time").toUInt();
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

QPair<QVector<DockingStationLevelInfo *>, QVector <BuildingUpgradeRequirements> > BuildingsReader::getDockingStationLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QPair<QVector<DockingStationLevelInfo *>, QVector <BuildingUpgradeRequirements> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="dockingStationLevelsInfo")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="levelInfo")
                {
                    unsigned level = 0;
                    DockingStationLevelInfo *info = new DockingStationLevelInfo;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level = attrs.value("level").toUInt();
                    info->basicCostInEnergy = attrs.value("basicCostEnergy").toUInt();
                    info->recruitsAmount = attrs.value("recruitsAmount").toUInt();
                    info->waitingTime = attrs.value("waitingTime").toUInt();
                    info->profitability = attrs.value("profitability").toUInt();
                    info->equipmentsAmount = attrs.value("equipmentsAmount").toUInt();
                    info->maxTier = attrs.value("maxTier").toUInt();

                    BuildingUpgradeRequirements reqs;

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="requirements")
                        {
                            attrs = m_xmlReader->attributes();
                            reqs.requiredBuildingMaterials = attrs.value("buildingMaterials").toUInt();
                            reqs.requiredEnergy = attrs.value("energy").toUInt();
                            reqs.requiredTime = attrs.value("time").toUInt();
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

DockingStationTradingTables BuildingsReader::getDockingStationTradingTables(const QString &path) noexcept
{
    if (!openXmlFile(path))
    {
        qCritical()<<"Couldn't open "+path+".";
        return {};
    }

    QVector<QMap<QPair < BaseEnums::Resource, BaseEnums::Resource>, float> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="dockingStationTradingTables")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="tradingTable")
                {
                    unsigned level = 0;

                    QMap<QPair < BaseEnums::Resource, BaseEnums::Resource>, float> m;

                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    level = attrs.value("profitabilityLevel").toUInt();

                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="entry")
                        {
                            attrs = m_xmlReader->attributes();

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

QMap < BuildingEnums::Building, QString> BuildingsReader::getBuildingDescriptions(const QString &path) noexcept
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
