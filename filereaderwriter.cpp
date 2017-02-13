#include "filereaderwriter.h"

bool XmlFileReader::openXmlFile(const QString &path) noexcept
{
    m_xmlReader.setDevice(new QFile(path));
    return isXmlFileOpened();
}

bool XmlFileReader::isXmlFileOpened() const noexcept
{
    return m_xmlReader.device()!=0 ? true : false;
}

TechTree *XmlFileReader::getTechTree() noexcept
{
    if (!isXmlFileOpened())
        return NULL;

    TechTreeBuilder *techTreeBuilder = new TechTreeBuilder();
    if (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.name()=="techtree")
        {
            while (m_xmlReader.readNextStartElement())
            {
                if (m_xmlReader.name()=="building")
                {
                    QPair < QPair <BaseEnums::Building, unsigned>, TechTreeBuildingRequirements> element;

                    element.first.first = BaseEnums::fromQStringToBuildingEnum(m_xmlReader.attributes().value("name").toString());
                    element.first.second = m_xmlReader.attributes().value("level").toUInt();

                    while (m_xmlReader.readNextStartElement())
                    {
                        if (m_xmlReader.name()=="requirements")
                        {
                            element.second.requiredBuildingMaterials = m_xmlReader.attributes().value("resources").toUInt();
                            element.second.requiredTime = m_xmlReader.attributes().value("time").toUInt();

                            while (m_xmlReader.readNextStartElement())
                            {
                                if (m_xmlReader.name()=="building")
                                {
                                    QPair <BaseEnums::Building,unsigned> requiredBuilding;

                                    requiredBuilding.first = BaseEnums::fromQStringToBuildingEnum(m_xmlReader.attributes().value("name").toString());
                                    requiredBuilding.second = m_xmlReader.attributes().value("level").toUInt();

                                    element.second.requiredBuildingLevels.insert(requiredBuilding.first,requiredBuilding.second);
                                }
                                else
                                    m_xmlReader.skipCurrentElement();
                            }
                        }
                        else
                            m_xmlReader.skipCurrentElement();
                    }
                    techTreeBuilder->addUpgrade(element.first,element.second);
                }
                else
                    m_xmlReader.skipCurrentElement();
            }
        }
        else
            m_xmlReader.raiseError("Incorrect file");
    }
    if (m_xmlReader.hasError())
    {
        delete techTreeBuilder;
        return NULL;
    }
    TechTree *ret=techTreeBuilder->getTechTree();
    delete techTreeBuilder;
    return ret;
}

TechTree *XmlFileReader::getTechTree(const QString &path) noexcept
{
    return openXmlFile(path) ? getTechTree() : NULL;
}

QVector<CentralUnitLevelInfo> *XmlFileReader::getCentralUnitLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return NULL;

    QVector <CentralUnitLevelInfo> *r=NULL;

    if (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.name()=="centralUnitLevelsInfo")
        {
            r=new QVector <CentralUnitLevelInfo>;
            while (m_xmlReader.readNextStartElement())
            {
                if (m_xmlReader.name()=="levelInfo")
                {
                    unsigned level=0;
                    CentralUnitLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader.attributes();
                    level=attrs.value("level").toUInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();

                    r->insert(level,info);
                }
                else
                    m_xmlReader.skipCurrentElement();
            }
        }
        else
            m_xmlReader.raiseError("Incorrect file");
    }
    if (m_xmlReader.hasError())
    {
        delete r;
        return NULL;
    }
    return r;
}

QVector<HospitalLevelInfo> *XmlFileReader::getHospitalLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return NULL;

    QVector <HospitalLevelInfo> *r=NULL;

    if (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.name()=="hospitalLevelsInfo")
        {
            r=new QVector <HospitalLevelInfo>;
            while (m_xmlReader.readNextStartElement())
            {
                if (m_xmlReader.name()=="levelInfo")
                {
                    unsigned level=0;
                    HospitalLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader.attributes();
                    level=attrs.value("level").toUInt();
                    info.amountOfSlots=attrs.value("slots").toUInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();
                    info.perCapitaCostInEnergy=attrs.value("perCapitaCostEnergy").toUInt();
                    info.basicCostInFoodSupplies=attrs.value("basicCostFood").toUInt();
                    info.perCapitaCostInFoodSupplies=attrs.value("perCapitaCostFood").toUInt();

                    r->insert(level,info);
                }
                else
                    m_xmlReader.skipCurrentElement();
            }
        }
        else
            m_xmlReader.raiseError("Incorrect file");
    }
    if (m_xmlReader.hasError())
    {
        delete r;
        return NULL;
    }
    return r;
}

QVector<TrainingGroundLevelInfo> *XmlFileReader::getTrainingGroundLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return NULL;

    QVector <TrainingGroundLevelInfo> *r=NULL;

    if (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.name()=="trainingGroundLevelsInfo")
        {
            r=new QVector <TrainingGroundLevelInfo>;
            while (m_xmlReader.readNextStartElement())
            {
                if (m_xmlReader.name()=="levelInfo")
                {
                    unsigned level=0;
                    TrainingGroundLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader.attributes();
                    level=attrs.value("level").toUInt();
                    info.amountOfSlots=attrs.value("slots").toInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();
                    info.perCapitaCostInEnergy=attrs.value("perCapitaCostEnergy").toUInt();

                    r->insert(level,info);
                }
                else
                    m_xmlReader.skipCurrentElement();
            }
        }
        else
            m_xmlReader.raiseError("Incorrect file");
    }
    if (m_xmlReader.hasError())
    {
        delete r;
        return NULL;
    }
    return r;
}

QVector<GymLevelInfo> *XmlFileReader::getGymLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return NULL;

    QVector <GymLevelInfo> *r=NULL;

    if (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.name()=="gymLevelsInfo")
        {
            r=new QVector <GymLevelInfo>;
            while (m_xmlReader.readNextStartElement())
            {
                if (m_xmlReader.name()=="levelInfo")
                {
                    unsigned level=0;
                    GymLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader.attributes();
                    level=attrs.value("level").toUInt();
                    info.amountOfSlots=attrs.value("slots").toInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();
                    info.perCapitaCostInEnergy=attrs.value("perCapitaCostEnergy").toUInt();
                    info.combatEffectivenessBonus=attrs.value("combatEffectivenessBonus").toInt();
                    info.proficiencyBonus=attrs.value("proficiencyBonus").toInt();
                    info.clevernessBonus=attrs.value("clevernessBonus").toInt();

                    r->insert(level,info);
                }
                else
                    m_xmlReader.skipCurrentElement();
            }
        }
        else
            m_xmlReader.raiseError("Incorrect file");
    }
    if (m_xmlReader.hasError())
    {
        delete r;
        return NULL;
    }
    return r;
}

QVector<LaboratoryLevelInfo> *XmlFileReader::getLaboratoryLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return NULL;

    QVector <LaboratoryLevelInfo> *r=NULL;

    if (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.name()=="laboratoryLevelsInfo")
        {
            r=new QVector <LaboratoryLevelInfo>;
            while (m_xmlReader.readNextStartElement())
            {
                if (m_xmlReader.name()=="levelInfo")
                {
                    unsigned level=0;
                    LaboratoryLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader.attributes();
                    level=attrs.value("level").toUInt();
                    info.amountOfSlots=attrs.value("slots").toInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();
                    info.perCapitaCostInEnergy=attrs.value("perCapitaCostEnergy").toUInt();
                    info.combatEffectivenessBonus=attrs.value("combatEffectivenessBonus").toInt();
                    info.proficiencyBonus=attrs.value("proficiencyBonus").toInt();
                    info.clevernessBonus=attrs.value("clevernessBonus").toInt();

                    r->insert(level,info);
                }
                else
                    m_xmlReader.skipCurrentElement();
            }
        }
        else
            m_xmlReader.raiseError("Incorrect file");
    }
    if (m_xmlReader.hasError())
    {
        delete r;
        return NULL;
    }
    return r;
}

QVector<PlayingFieldLevelInfo> *XmlFileReader::getPlayingFieldLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return NULL;

    QVector <PlayingFieldLevelInfo> *r=NULL;

    if (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.name()=="playingFieldLevelsInfo")
        {
            r=new QVector <PlayingFieldLevelInfo>;
            while (m_xmlReader.readNextStartElement())
            {
                if (m_xmlReader.name()=="levelInfo")
                {
                    unsigned level=0;
                    PlayingFieldLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader.attributes();
                    level=attrs.value("level").toUInt();
                    info.amountOfSlots=attrs.value("slots").toInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();
                    info.perCapitaCostInEnergy=attrs.value("perCapitaCostEnergy").toUInt();
                    info.stressReductionForActive=attrs.value("stressReductionActive").toInt();
                    info.stressReductionForConvivial=attrs.value("stressReductionConvivial").toInt();
                    info.stressReductionForRecluse=attrs.value("stressReductionRecluse").toInt();
                    info.stressReductionForReligious=attrs.value("stressReductionReligious").toInt();

                    r->insert(level,info);
                }
                else
                    m_xmlReader.skipCurrentElement();
            }
        }
        else
            m_xmlReader.raiseError("Incorrect file");
    }
    if (m_xmlReader.hasError())
    {
        delete r;
        return NULL;
    }
    return r;
}

QVector<BarLevelInfo> *XmlFileReader::getBarLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return NULL;

    QVector <BarLevelInfo> *r=NULL;

    if (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.name()=="barLevelsInfo")
        {
            r=new QVector <BarLevelInfo>;
            while (m_xmlReader.readNextStartElement())
            {
                if (m_xmlReader.name()=="levelInfo")
                {
                    unsigned level=0;
                    BarLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader.attributes();
                    level=attrs.value("level").toUInt();
                    info.amountOfSlots=attrs.value("slots").toInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();
                    info.perCapitaCostInEnergy=attrs.value("perCapitaCostEnergy").toUInt();
                    info.stressReductionForActive=attrs.value("stressReductionActive").toInt();
                    info.stressReductionForConvivial=attrs.value("stressReductionConvivial").toInt();
                    info.stressReductionForRecluse=attrs.value("stressReductionRecluse").toInt();
                    info.stressReductionForReligious=attrs.value("stressReductionReligious").toInt();

                    r->insert(level,info);
                }
                else
                    m_xmlReader.skipCurrentElement();
            }
        }
        else
            m_xmlReader.raiseError("Incorrect file");
    }
    if (m_xmlReader.hasError())
    {
        delete r;
        return NULL;
    }
    return r;
}

QVector<ShrineLevelInfo> *XmlFileReader::getShrineLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return NULL;

    QVector <ShrineLevelInfo> *r=NULL;

    if (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.name()=="shrineLevelsInfo")
        {
            r=new QVector <ShrineLevelInfo>;
            while (m_xmlReader.readNextStartElement())
            {
                if (m_xmlReader.name()=="levelInfo")
                {
                    unsigned level=0;
                    ShrineLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader.attributes();
                    level=attrs.value("level").toUInt();
                    info.amountOfSlots=attrs.value("slots").toInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();
                    info.perCapitaCostInEnergy=attrs.value("perCapitaCostEnergy").toUInt();
                    info.stressReductionForActive=attrs.value("stressReductionActive").toInt();
                    info.stressReductionForConvivial=attrs.value("stressReductionConvivial").toInt();
                    info.stressReductionForRecluse=attrs.value("stressReductionRecluse").toInt();
                    info.stressReductionForReligious=attrs.value("stressReductionReligious").toInt();

                    r->insert(level,info);
                }
                else
                    m_xmlReader.skipCurrentElement();
            }
        }
        else
            m_xmlReader.raiseError("Incorrect file");
    }
    if (m_xmlReader.hasError())
    {
        delete r;
        return NULL;
    }
    return r;
}

QVector<SeclusionLevelInfo> *XmlFileReader::getSeclusionLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return NULL;

    QVector <SeclusionLevelInfo> *r=NULL;

    if (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.name()=="seclusionLevelsInfo")
        {
            r=new QVector <SeclusionLevelInfo>;
            while (m_xmlReader.readNextStartElement())
            {
                if (m_xmlReader.name()=="levelInfo")
                {
                    unsigned level=0;
                    SeclusionLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader.attributes();
                    level=attrs.value("level").toUInt();
                    info.amountOfSlots=attrs.value("slots").toInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();
                    info.perCapitaCostInEnergy=attrs.value("perCapitaCostEnergy").toUInt();
                    info.stressReductionForActive=attrs.value("stressReductionActive").toInt();
                    info.stressReductionForConvivial=attrs.value("stressReductionConvivial").toInt();
                    info.stressReductionForRecluse=attrs.value("stressReductionRecluse").toInt();
                    info.stressReductionForReligious=attrs.value("stressReductionReligious").toInt();

                    r->insert(level,info);
                }
                else
                    m_xmlReader.skipCurrentElement();
            }
        }
        else
            m_xmlReader.raiseError("Incorrect file");
    }
    if (m_xmlReader.hasError())
    {
        delete r;
        return NULL;
    }
    return r;
}

QVector<PowerPlantLevelInfo> *XmlFileReader::getPowerPlantLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return NULL;

    QVector <PowerPlantLevelInfo> *r=NULL;

    if (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.name()=="powerPlantLevelsInfo")
        {
            r=new QVector <PowerPlantLevelInfo>;
            while (m_xmlReader.readNextStartElement())
            {
                if (m_xmlReader.name()=="levelInfo")
                {
                    unsigned level=0;
                    PowerPlantLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader.attributes();
                    level=attrs.value("level").toUInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();
                    info.aetheriteOreTaken=attrs.value("aetheriteTaken").toUInt();
                    info.energyGiven=attrs.value("energyGiven").toUInt();

                    r->insert(level,info);
                }
                else
                    m_xmlReader.skipCurrentElement();
            }
        }
        else
            m_xmlReader.raiseError("Incorrect file");
    }
    if (m_xmlReader.hasError())
    {
        delete r;
        return NULL;
    }
    return r;
}

QVector<FactoryLevelInfo> *XmlFileReader::getFactoryLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return NULL;

    QVector <FactoryLevelInfo> *r=NULL;

    if (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.name()=="factoryLevelsInfo")
        {
            r=new QVector <FactoryLevelInfo>;
            while (m_xmlReader.readNextStartElement())
            {
                if (m_xmlReader.name()=="levelInfo")
                {
                    unsigned level=0;
                    FactoryLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader.attributes();
                    level=attrs.value("level").toUInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();
                    info.aetheriteOreTaken=attrs.value("aetheriteTaken").toUInt();
                    info.buildingMaterialsGiven=attrs.value("buildingMaterialsGiven").toUInt();

                    r->insert(level,info);
                }
                else
                    m_xmlReader.skipCurrentElement();
            }
        }
        else
            m_xmlReader.raiseError("Incorrect file");
    }
    if (m_xmlReader.hasError())
    {
        delete r;
        return NULL;
    }
    return r;
}

QVector<CoolRoomLevelInfo> *XmlFileReader::getCoolRoomLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return NULL;

    QVector <CoolRoomLevelInfo> *r=NULL;

    if (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.name()=="coolRoomLevelsInfo")
        {
            r=new QVector <CoolRoomLevelInfo>;
            while (m_xmlReader.readNextStartElement())
            {
                if (m_xmlReader.name()=="levelInfo")
                {
                    unsigned level=0;
                    CoolRoomLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader.attributes();
                    level=attrs.value("level").toUInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();
                    info.foodSuppliesLimit=attrs.value("foodSuppliesLimit").toUInt();

                    r->insert(level,info);
                }
                else
                    m_xmlReader.skipCurrentElement();
            }
        }
        else
            m_xmlReader.raiseError("Incorrect file");
    }
    if (m_xmlReader.hasError())
    {
        delete r;
        return NULL;
    }
    return r;
}

QVector<StorageRoomLevelInfo> *XmlFileReader::getStorageRoomLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return NULL;

    QVector <StorageRoomLevelInfo> *r=NULL;

    if (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.name()=="storageRoomLevelsInfo")
        {
            r=new QVector <StorageRoomLevelInfo>;
            while (m_xmlReader.readNextStartElement())
            {
                if (m_xmlReader.name()=="levelInfo")
                {
                    unsigned level=0;
                    StorageRoomLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader.attributes();
                    level=attrs.value("level").toUInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();
                    info.buildingMaterialsLimit=attrs.value("buildingMaterialsLimit").toUInt();

                    r->insert(level,info);
                }
                else
                    m_xmlReader.skipCurrentElement();
            }
        }
        else
            m_xmlReader.raiseError("Incorrect file");
    }
    if (m_xmlReader.hasError())
    {
        delete r;
        return NULL;
    }
    return r;
}

QVector<AetheriteSiloLevelInfo> *XmlFileReader::getAetheriteSiloLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return NULL;

    QVector <AetheriteSiloLevelInfo> *r=NULL;

    if (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.name()=="aetheriteSiloLevelsInfo")
        {
            r=new QVector <AetheriteSiloLevelInfo>;
            while (m_xmlReader.readNextStartElement())
            {
                if (m_xmlReader.name()=="levelInfo")
                {
                    unsigned level=0;
                    AetheriteSiloLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader.attributes();
                    level=attrs.value("level").toUInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();
                    info.aetheriteOreLimit=attrs.value("aetheriteLimit").toUInt();

                    r->insert(level,info);
                }
                else
                    m_xmlReader.skipCurrentElement();
            }
        }
        else
            m_xmlReader.raiseError("Incorrect file");
    }
    if (m_xmlReader.hasError())
    {
        delete r;
        return NULL;
    }
    return r;
}

QVector<BarracksLevelInfo> *XmlFileReader::getBarracksLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return NULL;

    QVector <BarracksLevelInfo> *r=NULL;

    if (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.name()=="barracksLevelsInfo")
        {
            r=new QVector <BarracksLevelInfo>;
            while (m_xmlReader.readNextStartElement())
            {
                if (m_xmlReader.name()=="levelInfo")
                {
                    unsigned level=0;
                    BarracksLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader.attributes();
                    level=attrs.value("level").toUInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();
                    info.heroesLimit=attrs.value("heroesLimit").toUInt();

                    r->insert(level,info);
                }
                else
                    m_xmlReader.skipCurrentElement();
            }
        }
        else
            m_xmlReader.raiseError("Incorrect file");
    }
    if (m_xmlReader.hasError())
    {
        delete r;
        return NULL;
    }
    return r;
}

QVector<DockingStationLevelInfo> *XmlFileReader::getDockingStationLevelsInfo(const QString &path) noexcept
{
    if (!openXmlFile(path))
        return NULL;

    QVector <DockingStationLevelInfo> *r=NULL;

    if (m_xmlReader.readNextStartElement())
    {
        if (m_xmlReader.name()=="dockingStationLevelsInfo")
        {
            r=new QVector <DockingStationLevelInfo>;
            while (m_xmlReader.readNextStartElement())
            {
                if (m_xmlReader.name()=="levelInfo")
                {
                    unsigned level=0;
                    DockingStationLevelInfo info;

                    QXmlStreamAttributes attrs = m_xmlReader.attributes();
                    level=attrs.value("level").toUInt();
                    info.basicCostInEnergy=attrs.value("basicCostEnergy").toUInt();
                    info.recruitsAmount=attrs.value("recruitsAmount").toUInt();

                    r->insert(level,info);
                }
                else
                    m_xmlReader.skipCurrentElement();
            }
        }
        else
            m_xmlReader.raiseError("Incorrect file");
    }
    if (m_xmlReader.hasError())
    {
        delete r;
        return NULL;
    }
    return r;
}

bool XmlFileWriter::openXmlFile(const QString &path) noexcept
{
    m_xmlWriter.setDevice(new QFile(path));
    return isXmlFileOpened();
}

bool XmlFileWriter::isXmlFileOpened() const noexcept
{
    return m_xmlWriter.device()!=0 ? true : false;
}

void XmlFileWriter::saveTechTree(const TechTree &techTree) noexcept//FIXME
{
    if (!isXmlFileOpened())
        return;

    m_xmlWriter.setAutoFormatting(1);
    m_xmlWriter.writeStartDocument();
    m_xmlWriter.writeStartElement("techtree");

    for (int buildingNameEnumValue=0; buildingNameEnumValue < static_cast <int> (BaseEnums::B_END); ++buildingNameEnumValue)
        for (int buildingLevel=1; techTree.isThereSuchUpgrade(QPair <BaseEnums::Building, int> (static_cast <BaseEnums::Building> (buildingNameEnumValue), buildingLevel)); ++buildingLevel)
        {
            m_xmlWriter.writeStartElement("building");

            m_xmlWriter.writeTextElement("name", BaseEnums::fromBuildingEnumToQString(static_cast <BaseEnums::Building> (buildingNameEnumValue)));
            m_xmlWriter.writeTextElement("level", QString::number(buildingLevel));

            m_xmlWriter.writeStartElement("requirements");

            TechTreeBuildingRequirements reqs = techTree.getRequirementsForUpgrade(QPair <BaseEnums::Building, int> (static_cast <BaseEnums::Building> (buildingNameEnumValue), buildingLevel));

            for (int requiredBuildingNameEnumValue=0; requiredBuildingNameEnumValue < static_cast <int> (BaseEnums::B_END); ++requiredBuildingNameEnumValue)
                for (int requiredBuildingLevel=1; reqs.requiredBuildingLevels.contains(static_cast <BaseEnums::Building> (requiredBuildingNameEnumValue)); ++requiredBuildingLevel)
                {
                    m_xmlWriter.writeStartElement("building");

                    m_xmlWriter.writeTextElement("name", BaseEnums::fromBuildingEnumToQString(static_cast <BaseEnums::Building> (requiredBuildingNameEnumValue)));
                    m_xmlWriter.writeTextElement("level", QString::number(requiredBuildingLevel));

                    m_xmlWriter.writeEndElement();
                }
            m_xmlWriter.writeTextElement("resource",QString::number(reqs.requiredBuildingMaterials));
            m_xmlWriter.writeTextElement("time",QString::number(reqs.requiredTime));

            m_xmlWriter.writeEndElement();
        }
    m_xmlWriter.writeEndElement();
    m_xmlWriter.writeEndDocument();
}

void XmlFileWriter::saveTechTree(const TechTree &techTree, const QString &path) noexcept
{
    if (openXmlFile(path))
        saveTechTree(techTree);
}

void XmlFileWriter::saveHospitalLevelInfo(QVector<HospitalLevelInfo> *info, const QString &path) noexcept
{
    if (!openXmlFile(path))
        return;

    m_xmlWriter.setAutoFormatting(1);
    m_xmlWriter.writeStartDocument();

    m_xmlWriter.writeStartElement("hospitalLevelsInfo");

    for (int i=0;i < info->size();++i)
    {
        m_xmlWriter.writeStartElement("levelInfo");

        m_xmlWriter.writeAttribute("level",QString::number(i));
        m_xmlWriter.writeAttribute("slots",QString::number((*info)[i].amountOfSlots));
        m_xmlWriter.writeAttribute("basicCostEnergy",QString::number((*info)[i].basicCostInEnergy));
        m_xmlWriter.writeAttribute("perCapitaCostEnergy",QString::number((*info)[i].perCapitaCostInEnergy));
        m_xmlWriter.writeAttribute("basicCostFood",QString::number((*info)[i].basicCostInFoodSupplies));
        m_xmlWriter.writeAttribute("perCapitaCostFood",QString::number((*info)[i].perCapitaCostInFoodSupplies));

        m_xmlWriter.writeEndElement();
    }

    m_xmlWriter.writeEndElement();
    m_xmlWriter.writeEndDocument();
}
