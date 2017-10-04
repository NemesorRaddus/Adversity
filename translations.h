#ifndef TRANSLATIONS_H
#define TRANSLATIONS_H

#include <QMap>
#include <QObject>

#include "filereaderwriter.h"

class TranslationsDB : public QObject
{
    Q_OBJECT
public:
    TranslationsDB(const QString &pathToAssets) noexcept;

    void loadLanguage(const QString &lang) noexcept;
    void clear() noexcept
    {
        m_currentLanguage.clear();
        m_translations.clear();
    }

    Q_INVOKABLE QString translate(const QString &text) noexcept
    {
        return m_translations.value(text).value({},text);
    }
    Q_INVOKABLE QString translate(const QString &text, const QString &context) noexcept
    {
        return m_translations.value(text).value(context,text);
    }

    inline QString currentLanguage() const noexcept
    {
        return m_currentLanguage;
    }

private:
    void loadOverrides() noexcept;

    typedef QString Text;
    typedef QString Context;
    typedef QString Translation;

    QString m_pathToLocalesDir;
    QString m_currentLanguage;//lang code
    QMap <Text, QMap <Context, Translation> > m_translations;
    XmlFileReader m_xmlReader;
};

#endif // TRANSLATIONS_H
