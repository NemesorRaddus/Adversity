#include "filereaderwriter.h"

#include <QDebug>

XmlFileReader::XmlFileReader() noexcept
{
    m_xmlReader=new QXmlStreamReader();
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
{qDebug()<<path;
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
        return {};qDebug()<<r.first.size();
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
