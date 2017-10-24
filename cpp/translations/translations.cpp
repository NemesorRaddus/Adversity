#include "translations.h"

TranslationsDB::TranslationsDB(const QString &pathToAssets) noexcept
    : m_pathToLocalesDir(pathToAssets+"locales/") {}

void TranslationsDB::loadLanguage(const QString &lang) noexcept
{
    auto trs=m_xmlReader.getTranslations(m_pathToLocalesDir+lang+".xml");
    if (!trs.isEmpty())
    {
        m_currentLanguage=lang;
        m_translations=trs;
    }

    loadOverrides();
}

void TranslationsDB::loadOverrides() noexcept
{
    auto trs=m_xmlReader.getTranslations(m_pathToLocalesDir+"override.xml");
    if (!trs.isEmpty())
    {
        for (auto it=trs.begin();it!=trs.end();++it)
        {
            if (m_translations.contains(it.key()))
            {
                for (auto it2=it.value().begin();it2!=it.value().end();++it2)
                    m_translations[it.key()].insert(it2.key(),it2.value());
            }
            else
                m_translations.insert(it.key(),it.value());
        }
    }
}
