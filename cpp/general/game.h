#pragma once

#include <QObject>

#include "assets_pool/assetspool.h"
#include "settings.h"

class QQmlEngine;
class QQmlApplicationEngine;
class QJSEngine;
class QElapsedTimer;
class QTimer;

namespace APeR
{
    class PermissionsManager;
}

class Base;
class AppBuildInfo;
class GlobalUtilities;
class LoggersHandler;
class LandsInfo;
class H4X;
struct SaveData;
class SavesManager;
class TranslationsDB;

class Game : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Base* base MEMBER m_base)
    Q_PROPERTY(LandsInfo* lands MEMBER m_lands)
    Q_PROPERTY(AppBuildInfo* buildInfo MEMBER m_buildInfo)
    Q_PROPERTY(TranslationsDB* translator MEMBER m_translations)
    Q_PROPERTY(H4X* h4xLogic MEMBER m_h4xLogic)
    Q_PROPERTY(GlobalUtilities* globalsCpp MEMBER m_globalsExportToQML)
    Q_PROPERTY(LoggersHandler* logger MEMBER m_loggersHandler)
    Q_PROPERTY(SavesManager* savesManager MEMBER m_savesManager)

    friend class H4X;

public:
    explicit Game(QObject *parent = 0) noexcept;
    ~Game() noexcept;

    static void setQMLEnginePtr(QQmlApplicationEngine *engine) noexcept;

    void loadSave(const SaveData &save) noexcept;
    SaveData getSave() noexcept;
    void closeSave() noexcept;

    inline const AppBuildInfo *currentVersion() const noexcept
    {
        return m_buildInfo;
    }
    Q_INVOKABLE QString currentVersionNumber() const noexcept;

    Q_INVOKABLE void setLocale(const QString &locale) noexcept;
    Q_INVOKABLE QString tr(const QString &text) noexcept;
    Q_INVOKABLE QString tr(const QString &text, const QString &context) noexcept;

    Q_INVOKABLE unsigned randomize(unsigned bottom, unsigned top) noexcept;

    inline AssetsPool &assetsPool() noexcept
    {
        return m_assetsPool;
    }

    inline static Game *gameInstance() noexcept
    {
        return m_ptrToGameObject;
    }

    Q_INVOKABLE int startupTimerElapsed() noexcept;

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
    Q_INVOKABLE QString pathToLogs() const noexcept;

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
    void saveBase() noexcept;

private:
    void enableAutosave() noexcept;
    void disableAutosave() noexcept;

    void loadAssets(const QString &pathToDir) noexcept;

    void loadVersionInfo() noexcept;

    void loadTranslations(const QString &lang) noexcept;

    void loadSettings() noexcept;
    void saveSettings() noexcept;

    void applyLoadedSettings() noexcept;

    static Game *m_ptrToGameObject;

    const QString m_pathToAssetsDir = ":/data/";
    Base *m_base;
    bool m_isAutosaveActive;
    SavesManager *m_savesManager;
    LandsInfo *m_lands;
    AppBuildInfo *m_buildInfo;
    AssetsPool m_assetsPool;
    TranslationsDB *m_translations;
    QElapsedTimer *m_startupTimer;
    H4X *m_h4xLogic;
    GlobalUtilities *m_globalsExportToQML;
    LoggersHandler *m_loggersHandler;
    Settings m_settings;
    QTimer *m_settingsApplierTimer;
    APeR::PermissionsManager *m_permissionsManager;

    static QQmlApplicationEngine *m_ptrToEngine;
};

static QObject *gameQObjectSingletontypeProvider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    Game *game = new Game();
    return game;
}
