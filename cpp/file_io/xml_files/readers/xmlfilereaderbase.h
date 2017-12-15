#pragma once

class QString;
class QXmlStreamReader;

class XmlFileReaderBase
{
public:
    XmlFileReaderBase() noexcept;
    virtual ~XmlFileReaderBase() noexcept;

protected:
    bool openXmlFile(const QString &path) noexcept;

    QXmlStreamReader *m_xmlReader;
};
