#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QSettings>

#include "base.h"
#include "filereaderwriter.h"
#include "saveparser.h"
#include "timer.h"
#include "assetspool.h"
#include "translations.h"

#include <QDebug>

class QQmlEngine;
class QJSEngine;

class AppBuildInfo : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE QString versionNumber() const noexcept
    {
        return m_versionNumber;
    }
    Q_INVOKABLE QString buildTime() const noexcept
    {
        return m_buildTime;
    }
    Q_INVOKABLE QString buildType() const noexcept
    {
        return m_buildType;
    }
    Q_INVOKABLE QString toolkitName() const noexcept
    {
        return m_toolkitName;
    }
    Q_INVOKABLE QString additionalBuildInfo() const noexcept
    {
        return m_additionBuildInfo;
    }

    void setVersionNumber(const QString &versionNumber) noexcept
    {
        m_versionNumber=versionNumber;
    }
    void setBuildTime(const QString &buildTime) noexcept
    {
        m_buildTime=buildTime;
    }
    void setBuildType(const QString &buildType) noexcept
    {
        m_buildType=buildType;
    }
    void setToolkitName(const QString &toolkitName) noexcept
    {
        m_toolkitName=toolkitName;
    }
    void setAdditionBuildInfo(const QString &additionBuildInfo) noexcept
    {
        m_additionBuildInfo=additionBuildInfo;
    }

private:
    QString m_versionNumber, m_buildTime, m_buildType, m_toolkitName, m_additionBuildInfo;
};

static Game *ptrToGameObject;

class Game : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Base* base MEMBER m_base)
    Q_PROPERTY(AppBuildInfo* buildInfo MEMBER m_buildInfo)
    Q_PROPERTY(TranslationsDB* translator MEMBER m_translations)

public:
    explicit Game(QObject *parent = 0) noexcept;

    Q_INVOKABLE void createNewBase(const QString &pathToAssetsDir/*with ending / */) noexcept;//WARNING NEVER USED
    Q_INVOKABLE void loadExistingBase(const QString &pathToAssetsDir) noexcept;
    Q_INVOKABLE void saveBase() noexcept;

    Q_INVOKABLE void setLocale(const QString &locale) noexcept;
    Q_INVOKABLE QString tr(const QString &text) noexcept
    {
        return m_translations->translate(text);
    }
    Q_INVOKABLE QString tr(const QString &text, const QString &context) noexcept
    {
        return m_translations->translate(text,context);
    }

    Q_INVOKABLE unsigned randomize(unsigned bottom, unsigned top) noexcept
    {
        return Randomizer::randomBetweenAAndB(bottom,top);
    }

    AssetsPool &assetsPool() noexcept
    {
        return m_assetsPool;
    }

    static Game *gameInstance() noexcept
    {
        return ptrToGameObject;
    }

public slots:
    void saveBase_slot() noexcept;

private:
    void connectAutosave() noexcept;
    void disconnectAutosave() noexcept;

    void loadAssets(const QString &pathToDir) noexcept;

    void loadVersionInfo() noexcept;

    void loadTranslations(const QString &lang) noexcept;

    Base *m_base;
    QString m_currentPathToAssets;
    AppBuildInfo *m_buildInfo;
    AssetsPool m_assetsPool;
    TranslationsDB *m_translations;
};

static QObject *gameQObjectSingletontypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    Game *game =new Game();
    return game;
}

#endif // GAME_H
