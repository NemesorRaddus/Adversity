#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QSettings>
#include <QElapsedTimer>
#include <QStandardPaths>
#include <QDir>

#include <sstream>
#include <string>

#include "base.h"
#include "filereaderwriter.h"
#include "saveparser.h"
#include "timer.h"
#include "assetspool.h"
#include "translations.h"
#include "h4x.h"

#include "libs/spdlog-0.14.0/spdlog.h"

#define SPDLOG_TRACE_ON
#define SPDLOG_DEBUG_ON

#include <QDebug>

class Global : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE static double roundDouble(double d, unsigned prec) noexcept;
    Q_INVOKABLE static QString alterNormalTextToInternal(QString normalText) noexcept;
};

class QQmlEngine;
class QJSEngine;

class AppBuildInfo : public QObject
{
    Q_OBJECT

    friend class H4X;

public:
    Q_INVOKABLE inline QString versionNumber() const noexcept
    {
        return m_versionNumber;
    }
    Q_INVOKABLE inline QString buildTime() const noexcept
    {
        return m_buildTime;
    }
    Q_INVOKABLE inline QString buildType() const noexcept
    {
        return m_buildType;
    }
    Q_INVOKABLE inline QString toolkitName() const noexcept
    {
        return m_toolkitName;
    }
    Q_INVOKABLE inline QString additionalBuildInfo() const noexcept
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

class LandsInfo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Land* preparedLand MEMBER m_preparedLand)

public:
    explicit LandsInfo(const QVector <Land *> *lands) noexcept;

    Q_INVOKABLE inline unsigned amountOfLands() const noexcept
    {
        return m_lands->size();
    }

    Q_INVOKABLE void prepareLandAt(unsigned index) noexcept;

private:
    const QVector <Land *> *m_lands;
    Land *m_preparedLand;
};

class LoggersHandler : public QObject
{
    Q_OBJECT

public:
    LoggersHandler() noexcept;

    void setLevel(spdlog::level::level_enum lvl) noexcept;

    // For QML only!
    Q_INVOKABLE void trace(const QString &msg) noexcept;
    Q_INVOKABLE void debug(const QString &msg) noexcept;
    Q_INVOKABLE void info(const QString &msg) noexcept;
    Q_INVOKABLE void warn(const QString &msg) noexcept;
    Q_INVOKABLE void error(const QString &msg) noexcept;
    Q_INVOKABLE void critical(const QString &msg) noexcept;

    Q_INVOKABLE void traceIf(bool cond, const QString &msg) noexcept;
    Q_INVOKABLE void debugIf(bool cond, const QString &msg) noexcept;
    Q_INVOKABLE void infoIf(bool cond, const QString &msg) noexcept;
    Q_INVOKABLE void warnIf(bool cond, const QString &msg) noexcept;
    Q_INVOKABLE void errorIf(bool cond, const QString &msg) noexcept;
    Q_INVOKABLE void criticalIf(bool cond, const QString &msg) noexcept;

    // these are for C++
    inline auto mainLogger() noexcept
    {
        return m_mainLogger;
    }
    inline auto xmlLogger() noexcept
    {
        return m_xmlLogger;
    }

private:
    std::shared_ptr <spdlog::sinks::rotating_file_sink_st> m_output;
    std::shared_ptr <spdlog::logger> m_mainLogger;
    std::shared_ptr <spdlog::logger> m_xmlLogger;
    std::shared_ptr <spdlog::logger> m_qmlLogger;
};

class Game : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Base* base MEMBER m_base)
    Q_PROPERTY(LandsInfo* lands MEMBER m_lands)
    Q_PROPERTY(AppBuildInfo* buildInfo MEMBER m_buildInfo)
    Q_PROPERTY(TranslationsDB* translator MEMBER m_translations)
    Q_PROPERTY(H4X* h4xLogic MEMBER m_h4xLogic)
    Q_PROPERTY(Global* globalsCpp MEMBER m_globalsExportToQML)
    Q_PROPERTY(LoggersHandler* logger MEMBER m_loggersHandler)

    friend class H4X;

public:
    explicit Game(QObject *parent = 0) noexcept;
    ~Game() noexcept;

    static void setQMLEnginePtr(QQmlApplicationEngine *engine) noexcept;

    Q_INVOKABLE void createNewBase(const QString &pathToAssetsDir/*with ending / */) noexcept;//WARNING NEVER USED
    Q_INVOKABLE void loadExistingBase(const QString &pathToAssetsDir) noexcept;
    Q_INVOKABLE void saveBase() noexcept;

    inline const AppBuildInfo *currentVersion() const noexcept
    {
        return m_buildInfo;
    }

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

    inline AssetsPool &assetsPool() noexcept
    {
        return m_assetsPool;
    }

    inline static Game *gameInstance() noexcept
    {
        return m_ptrToGameObject;
    }

    Q_INVOKABLE int startupTimerElapsed() noexcept
    {
        return m_startupTimer!=nullptr ? m_startupTimer->elapsed() : 0;
    }

    void addDoStBan(QString name, unsigned daysAmount) noexcept;

    void showReportNotification() noexcept;

public slots:
    void saveBase_slot() noexcept;

private:
    void connectAutosave() noexcept;
    void disconnectAutosave() noexcept;

    void loadAssets(const QString &pathToDir) noexcept;

    void loadVersionInfo() noexcept;

    void loadTranslations(const QString &lang) noexcept;

    static Game *m_ptrToGameObject;

    Base *m_base;
    QString m_currentPathToAssets;
    LandsInfo *m_lands;
    AppBuildInfo *m_buildInfo;
    AssetsPool m_assetsPool;
    TranslationsDB *m_translations;
    QElapsedTimer *m_startupTimer;
    H4X *m_h4xLogic;
    Global *m_globalsExportToQML;
    LoggersHandler *m_loggersHandler;

    static QQmlApplicationEngine *m_ptrToEngine;
};

static QObject *gameQObjectSingletontypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    Game *game =new Game();
    return game;
}

#endif // GAME_H
