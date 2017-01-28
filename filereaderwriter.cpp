#include "filereaderwriter.h"

bool FileReader::openXmlFile(const QString &path) noexcept
{
    m_xmlReader.setDevice(new QFile(path));
    return isXmlFileOpened();
}

bool FileReader::isXmlFileOpened() const noexcept
{
    return m_xmlReader.device()!=0 ? true : false;
}

TechTree *FileReader::getTechTree() noexcept
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

                    while (m_xmlReader.readNextStartElement())
                    {
                        if (m_xmlReader.name()=="name")
                            element.first.first=BaseEnums::fromQStringToBuildingEnum(m_xmlReader.readElementText());
                        else if (m_xmlReader.name()=="level")
                            element.first.second=m_xmlReader.readElementText().toUInt();
                        else if (m_xmlReader.name()=="requirements")
                        {
                            while (m_xmlReader.readNextStartElement())
                            {
                                if (m_xmlReader.name()=="building")
                                {
                                    QPair <BaseEnums::Building,unsigned> requiredBuilding;

                                    while (m_xmlReader.readNextStartElement())
                                    {
                                        if (m_xmlReader.name()=="name")
                                            requiredBuilding.first=BaseEnums::fromQStringToBuildingEnum(m_xmlReader.readElementText());
                                        else if (m_xmlReader.name()=="level")
                                            requiredBuilding.second=m_xmlReader.readElementText().toUInt();
                                        else
                                            m_xmlReader.skipCurrentElement();
                                    }
                                    element.second.requiredBuildingLevels.insert(requiredBuilding.first,requiredBuilding.second);
                                }
                                else if (m_xmlReader.name()=="resource")
                                    element.second.requiredBuildingMaterials=m_xmlReader.readElementText().toUInt();
                                else if (m_xmlReader.name()=="time")
                                    element.second.requiredTime=m_xmlReader.readElementText().toUInt();
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

TechTree *FileReader::getTechTree(const QString &path) noexcept
{
    return openXmlFile(path) ? getTechTree() : NULL;
}

bool FileWriter::openXmlFile(const QString &path) noexcept
{
    m_xmlWriter.setDevice(new QFile(path));
    return isXmlFileOpened();
}

bool FileWriter::isXmlFileOpened() const noexcept
{
    return m_xmlWriter.device()!=0 ? true : false;
}
