#include "miscreader.h"

QMap<QString, QMap<QString, QString> > MiscReader::getTranslations(const QString &path) noexcept
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
