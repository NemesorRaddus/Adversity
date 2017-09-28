#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QSettings>
#include <QElapsedTimer>
#include <QStandardPaths>
#include <QDir>
#include <QTimer>

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

#include <QDebug>

class Global : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE static double roundDouble(double d, unsigned prec) noexcept;
    Q_INVOKABLE static QString alterNormalTextToInternal(QString normalText) noexcept;
    Q_INVOKABLE static QString sanitize(QString script) noexcept;
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
    inline auto missionsLogger() noexcept
    {
        return m_missionsLogger;
    }
    inline auto buildingsLogger() noexcept
    {
        return m_buildingsLogger;
    }
    inline auto mercenariesLogger() noexcept
    {
        return m_mercenariesLogger;
    }
    inline auto xmlLogger() noexcept
    {
        return m_xmlLogger;
    }

    inline auto qtLogger() noexcept
    {
        return m_qtLogger;
    }

    static void redirectQtMsgs(QtMsgType type, const QMessageLogContext &, const QString &msg) noexcept;

    Q_INVOKABLE inline QString outputPath() const noexcept
    {
        return m_outputPath;
    }

private:
    bool isLoggingEnabled() const noexcept;

    QString m_outputPath;
    std::shared_ptr <spdlog::sinks::app_start_rotating_file_sink_st> m_output;
    std::shared_ptr <spdlog::sinks::null_sink_st> m_noOutput;//probably could change those 2 into one thing, but meh
    std::shared_ptr <spdlog::logger> m_mainLogger;
    std::shared_ptr <spdlog::logger> m_missionsLogger;
    std::shared_ptr <spdlog::logger> m_buildingsLogger;
    std::shared_ptr <spdlog::logger> m_mercenariesLogger;
    std::shared_ptr <spdlog::logger> m_xmlLogger;
    std::shared_ptr <spdlog::logger> m_qmlLogger;
    std::shared_ptr <spdlog::logger> m_qtLogger;
};

class Settings
{
public:
    enum AnimationsSpeed
    {
        AS_None,
        AS_Slow,
        AS_Normal,
        AS_Fast,
        AS_END
    };
    enum LogsAmount
    {
        LA_None,
        LA_Some,
        LA_Most,
        LA_All,
        LA_END
    };

    Settings() noexcept;

    void setAnimationsSpeed(AnimationsSpeed speed) noexcept;
    void showFPS(bool enabled) noexcept;
    void setLogsAmount(LogsAmount amount) noexcept;

    inline AnimationsSpeed animationsSpeed() const noexcept
    {
        return m_animsSpeed;
    }
    inline bool showsFPS() const noexcept
    {
        return m_showFPS;
    }
    inline LogsAmount logsAmount() const noexcept
    {
        return m_logsAmount;
    }

private:
    AnimationsSpeed m_animsSpeed;
    bool m_showFPS;
    LogsAmount m_logsAmount;
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
    Q_INVOKABLE inline QString currentVersionNumber() const noexcept
    {
        return m_buildInfo->versionNumber();
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

    Q_INVOKABLE void setAnimationsSpeed(unsigned speed) noexcept;
    Q_INVOKABLE inline unsigned animationSpeed() const noexcept
    {
        return static_cast<unsigned>(m_settings.animationsSpeed());
    }
    Q_INVOKABLE float animMultiplier() noexcept;

    Q_INVOKABLE void showFPS(bool show) noexcept;
    void acknowledgeFPSToggle() noexcept;

    Q_INVOKABLE void setLogsAmount(unsigned amount) noexcept;
    Q_INVOKABLE inline unsigned logsAmount() const noexcept
    {
        return static_cast<unsigned>(m_settings.logsAmount());
    }
    Q_INVOKABLE inline QString pathToLogs() const noexcept
    {
        return m_loggersHandler->outputPath();
    }

    inline LoggersHandler *loggers() const noexcept
    {
        return m_loggersHandler;
    }

    inline Settings settings() const noexcept
    {
        return m_settings;
    }

    inline const AppBuildInfo *appBuildInfo() const noexcept
    {
        return m_buildInfo;
    }

    Q_INVOKABLE void requestReadWritePermissions() noexcept;

public slots:
    void saveBase_slot() noexcept;

private:
    void connectAutosave() noexcept;
    void disconnectAutosave() noexcept;

    void loadAssets(const QString &pathToDir) noexcept;

    void loadVersionInfo() noexcept;

    void loadTranslations(const QString &lang) noexcept;

    void loadSettings() noexcept;
    void saveSettings() noexcept;

    void applyLoadedSettings() noexcept;

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
    Settings m_settings;
    QTimer *m_settingsApplierTimer;

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
