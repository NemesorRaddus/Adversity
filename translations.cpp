#include "translations.h"

TranslationsDB::TranslationsDB(const QString &pathToAssets) noexcept
    : m_pathToLocalesDir(pathToAssets+"locales/")
{

}

void TranslationsDB::loadLanguage(const QString &lang) noexcept
{
    auto trs=m_xmlReader.getTranslations(m_pathToLocalesDir+lang+".xml");
    if (!trs.isEmpty())
    {
        m_currentLanguage=lang;
        m_translations=trs;
    }
}
