#include "xmlfilereaderbase.h"

#include <QFile>
#include <QString>
#include <QXmlStreamReader>

XmlFileReaderBase::XmlFileReaderBase() noexcept
{
    m_xmlReader = new QXmlStreamReader();
}

XmlFileReaderBase::~XmlFileReaderBase() noexcept
{
    delete m_xmlReader;
}

bool XmlFileReaderBase::openXmlFile(const QString &path) noexcept
{
    QFile *f = new QFile(path);
    if (!f->open(QFile::ReadOnly))
        return 0;
    delete m_xmlReader;
    m_xmlReader = new QXmlStreamReader(f);
    return 1;
}
