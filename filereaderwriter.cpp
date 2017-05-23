#include "filereaderwriter.h"

#include "game.h"

#include <QDebug>

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
        return {};

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
        return {};
    return r;
}

QPair<QVector<HospitalLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getHospitalLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return {};

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
        return {};
    return r;
}

QPair<QVector<TrainingGroundLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getTrainingGroundLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return {};

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
                    info.proficiencyBonus=attrs.value("proficiencyBonus").toInt();
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
        return {};
    return r;
}

QPair<QVector<GymLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getGymLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return {};

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
                    info.combatEffectivenessBonus=attrs.value("combatEffectivenessBonus").toInt();
                    info.proficiencyBonus=attrs.value("proficiencyBonus").toInt();
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
        return {};
    return r;
}

QPair<QVector<LaboratoryLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getLaboratoryLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return {};

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
                    info.combatEffectivenessBonus=attrs.value("combatEffectivenessBonus").toInt();
                    info.proficiencyBonus=attrs.value("proficiencyBonus").toInt();
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
        return {};
    return r;
}

QPair<QVector<PlayingFieldLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getPlayingFieldLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return {};

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
        return {};
    return r;
}

QPair<QVector<BarLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getBarLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return {};

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
        return {};
    return r;
}

QPair<QVector<ShrineLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getShrineLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return {};

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
        return {};
    return r;
}

QPair<QVector<SeclusionLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getSeclusionLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return {};

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
        return {};
    return r;
}

QPair<QVector<PowerplantLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getPowerplantLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return {};

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
        return {};
    return r;
}

QPair<QVector<FactoryLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getFactoryLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return {};

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
        return {};
    return r;
}

QPair<QVector<CoolRoomLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getCoolRoomLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return {};

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
        return {};
    return r;
}

QPair<QVector<StorageRoomLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getStorageRoomLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return {};

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
        return {};
    return r;
}

QPair<QVector<AetheriteSiloLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getAetheriteSiloLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return {};

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
        return {};
    return r;
}

QPair<QVector<BarracksLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getBarracksLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return {};

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
                    info.heroesLimit=attrs.value("heroesLimit").toUInt();

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
        return {};
    return r;
}

QPair<QVector<DockingStationLevelInfo>, QVector<BuildingUpgradeRequirements> > XmlFileReader::getDockingStationLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return {};

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
        return {};
    return r;
}

QVector<QPair <BaseEnums::Building, QString> > XmlFileReader::getBuildingDescriptions(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return {};

    QVector <QPair <BaseEnums::Building, QString> > r;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="buildingDescriptions")
        {
            while (m_xmlReader->readNextStartElement())
            {
                if (m_xmlReader->name()=="buildingDescription")
                {
                    QXmlStreamAttributes attrs = m_xmlReader->attributes();
                    r.push_back({BaseEnums::fromQStringToBuildingEnum(attrs.value("name").toString()),attrs.value("description").toString()});
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
        return {};
    }
    return r;
}

QList<QString> XmlFileReader::getHeroesNamesList(const QString &pathToHeroesDir) noexcept
{
    return QDir(pathToHeroesDir).entryList({"*.xml"});
}

Hero *XmlFileReader::getHero(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return {};

    HeroBuilder hB;

    if (m_xmlReader->readNextStartElement())
    {
        if (m_xmlReader->name()=="hero")
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
                    hB.setLuck(attrs.value("luck").toFloat());
                    hB.setHealth(attrs.value("health").toInt());
                    hB.setHealthLimit(attrs.value("healthLimit").toInt());
                    hB.setDailyHealthRecovery(attrs.value("dailyHealthRecovery").toInt());
                    hB.setStress(attrs.value("stress").toInt());
                    hB.setStressResistance(attrs.value("stressResistance").toFloat());
                    hB.setStressLimit(attrs.value("stressLimit").toInt());
                    hB.setStressBorder(attrs.value("stressBorder").toInt());
                    hB.setDailyStressRecovery(attrs.value("dailyStressRecovery").toInt());
                    hB.setSalary(attrs.value("salary").toInt());
                    hB.setDailyFoodConsumption(attrs.value("dailyFoodConsumption").toInt());
                    hB.setNature(HeroEnums::fromQStringToNatureEnum(attrs.value("nature").toString()));
                }
                else if (m_xmlReader->name()=="stressBorderEffect")
                {
                    attrs = m_xmlReader->attributes();

                    HeroStressBorderEffect sbe;
                    sbe.effectName=HeroEnums::fromQStringToStressBorderEffectEnum(attrs.value("name").toString());
                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="param")
                            sbe.effectParams.push_back(static_cast<QVariant>(m_xmlReader->attributes().value("value").toString()));
                        else
                            m_xmlReader->skipCurrentElement();
                    }
                    hB.setStressBorderEffect(sbe);
                }
                else if (m_xmlReader->name()=="equipment")
                {
                    while (m_xmlReader->readNextStartElement())
                    {
                        if (m_xmlReader->name()=="armor")
                        {
                            attrs = m_xmlReader->attributes();
                            for (int i=0;i<ptrToGameObject->assetsPool().equipment().size();++i)
                                if (ptrToGameObject->assetsPool().equipment()[i]->name() == attrs.value("name").toString())
                                {
                                    hB.setAndEquipArmor(ptrToGameObject->assetsPool().equipment()[i]);
                                    break;
                                }
                        }
                        else if (m_xmlReader->name()=="weaponTool")
                        {
                            attrs = m_xmlReader->attributes();
                            for (int i=0;i<ptrToGameObject->assetsPool().equipment().size();++i)
                                if (ptrToGameObject->assetsPool().equipment()[i]->name() == attrs.value("name").toString())
                                {
                                    hB.setAndEquipWeaponTool(ptrToGameObject->assetsPool().equipment()[i],attrs.value("slot").toInt());
                                    break;
                                }
                        }
                        else
                            m_xmlReader->skipCurrentElement();
                    }
                }
                else if (m_xmlReader->name()=="additionalData")
                {
                    attrs = m_xmlReader->attributes();

                    hB.setIsDead(static_cast<bool>(attrs.value("dead").toInt()));
                    hB.setIsDead(static_cast<bool>(attrs.value("stressBorderEffectActive").toInt()));

                    hB.setNoSignalDaysRemaining(attrs.value("noSigDaysRem").toInt());

                    hB.setCarriedEnergy(attrs.value("carriedEnergy").toInt());
                    hB.setCarriedFoodSupplies(attrs.value("carriedFoodSupplies").toInt());
                    hB.setCarriedBuildingMaterials(attrs.value("carriedBuildingMaterials").toInt());
                    hB.setCarriedAetheriteOre(attrs.value("carriedAetheriteOre").toInt());
                }
                else
                    m_xmlReader->skipCurrentElement();
            }
        }
        else
            m_xmlReader->raiseError("Incorrect file");
    }

    if (m_xmlReader->hasError())
        return NULL;
    return hB.getHero();
}

QVector<Equipment *> XmlFileReader::getEquipment(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return {};

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
                                    if (attrs.value("varName")=="combatEfficiency")
                                        eqB.setCombatEffectivenessBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="proficiency")
                                        eqB.setProficiencyBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="cleverness")
                                        eqB.setClevernessBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="luck")
                                        eqB.setLuckBonus(attrs.value("value").toFloat());
                                    else if (attrs.value("varName")=="health")
                                        eqB.setHealthBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="healthLimit")
                                        eqB.setHealthLimitBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="dailyHealthRecovery")
                                        eqB.setDailyHealthRecoveryBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="stress")
                                        eqB.setStressBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="stressResistance")
                                        eqB.setStressResistanceBonus(attrs.value("value").toFloat());
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
                                    if (attrs.value("varName")=="combatEfficiency")
                                        eqB.setCombatEffectivenessBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="proficiency")
                                        eqB.setProficiencyBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="cleverness")
                                        eqB.setClevernessBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="luck")
                                        eqB.setLuckBonus(attrs.value("value").toFloat());
                                    else if (attrs.value("varName")=="health")
                                        eqB.setHealthBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="healthLimit")
                                        eqB.setHealthLimitBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="dailyHealthRecovery")
                                        eqB.setDailyHealthRecoveryBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="stress")
                                        eqB.setStressBonus(attrs.value("value").toInt());
                                    else if (attrs.value("varName")=="stressResistance")
                                        eqB.setStressResistanceBonus(attrs.value("value").toFloat());
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
        return {};
    }
    return r;
}

QMap<QString, QMap<QString, QString> > XmlFileReader::getTranslations(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return {};

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
        return {};
    return r;
}
