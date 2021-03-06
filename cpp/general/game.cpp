#include "game.h"

#include <QDataStream>
#include <QDebug>
#include <QElapsedTimer>
#include <QFile>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QTimer>

#include "libs/APeR-0.1.0/aper.h"

#include "base/base.h"
#include "base/buildings/specific/storage/aetheritesilo.h"
#include "base/buildings/specific/destressing/bar.h"
#include "base/buildings/specific/other/barracks.h"
#include "base/buildings/specific/other/centralunit.h"
#include "base/buildings/specific/storage/coolroom.h"
#include "base/buildings/specific/other/dockingstation.h"
#include "base/buildings/specific/production/factory.h"
#include "base/buildings/specific/training/gym.h"
#include "base/buildings/specific/other/hospital.h"
#include "base/buildings/specific/training/laboratory.h"
#include "base/buildings/specific/destressing/playingfield.h"
#include "base/buildings/specific/production/powerplant.h"
#include "base/buildings/specific/destressing/seclusion.h"
#include "base/buildings/specific/destressing/shrine.h"
#include "base/buildings/specific/storage/storageroom.h"
#include "base/buildings/specific/training/trainingground.h"
#include "base/managers/mercenariesmanager.h"
#include "clock/gameclock.h"
#include "clock/timer_alarms/buildingupgrade.h"
#include "clock/timer_alarms/missionend.h"
#include "file_io/saves/savedata.h"
#include "file_io/saves/saveparser.h"
#include "file_io/xml_files/xmlreader.h"
#include "general/appbuildinfo.h"
#include "general/globalutilities.h"
#include "general/randomizer.h"
#include "general/savesmanager.h"
#include "h4x/h4x.h"
#include "logging/loggershandler.h"
#include "missions/land.h"
#include "missions/mission.h"
#include "reports/unifiedreport.h"
#include "translations/translations.h"

Game *Game::m_ptrToGameObject;
QQmlApplicationEngine *Game::m_ptrToEngine;

Game::Game(QObject *parent) noexcept
    : QObject(parent), m_base(nullptr), m_isAutosaveActive(false)
{
    m_ptrToGameObject = this;

    m_buildInfo = new AppBuildInfo;
    loadVersionInfo();

    loadSettings();

    m_permissionsManager = new APeR::PermissionsManager;

    m_loggersHandler = new LoggersHandler;

    m_startupTimer = new QElapsedTimer;
    m_startupTimer->start();
    qInfo()<<QString("[0.000] Game object initialization has started");

    m_translations = new TranslationsDB(":/");
    if (!QSettings().contains("lang"))
    {
        if (QLocale::system().name()!="pl_PL" && QLocale::system().name()!="en_GB")
            QSettings().setValue("lang","en_GB");
        else
            QSettings().setValue("lang",QLocale::system().name());
    }
    setLocale(QSettings().value("lang").toString());

    m_savesManager = new SavesManager;

    loadAssets(m_pathToAssetsDir);
    qInfo()<<"["+QString::number(m_startupTimer->elapsed()/1000)+'.'+QString("%1").arg(m_startupTimer->elapsed()%1000, 3, 10, QChar('0'))+"] Assets have been loaded";

    m_h4xLogic=new H4X;

    m_globalsExportToQML=new GlobalUtilities;
}

Game::~Game() noexcept
{
    saveSettings();
    qInfo()<<"["+QString::number(m_startupTimer->elapsed()/1000)+'.'+QString("%1").arg(m_startupTimer->elapsed()%1000, 3, 10, QChar('0'))+"] Deleting game";
    disableAutosave();

    delete m_lands;

    delete m_globalsExportToQML;

    delete m_h4xLogic;

    if (m_base != nullptr)
        delete m_base;

    delete m_savesManager;

    delete m_translations;

    delete m_buildInfo;

    qInfo()<<"["+QString::number(m_startupTimer->elapsed()/1000)+'.'+QString("%1").arg(m_startupTimer->elapsed()%1000, 3, 10, QChar('0'))+"] Game has been deleted";
    delete m_startupTimer;

    delete m_loggersHandler;

    delete m_permissionsManager;
}

void Game::setQMLEnginePtr(QQmlApplicationEngine *engine) noexcept
{
    m_ptrToEngine = engine;
}

void Game::loadSave(const SaveData &save) noexcept
{
    disableAutosave();

    if (m_base != nullptr)
        delete m_base;
    m_base = new Base(this);
    qInfo()<<"["+QString::number(m_startupTimer->elapsed()/1000)+'.'+QString("%1").arg(m_startupTimer->elapsed()%1000, 3, 10, QChar('0'))+"] Base has been created";

    m_base->loadSaveData(save);
    qInfo()<<"["+QString::number(m_startupTimer->elapsed()/1000)+'.'+QString("%1").arg(m_startupTimer->elapsed()%1000, 3, 10, QChar('0'))+"] Save has been loaded";

    enableAutosave();
}

SaveData Game::getSave() noexcept
{
    if (m_base != nullptr)
        return m_base->getSaveData();
}

void Game::closeSave() noexcept
{
    if (m_base == nullptr)
        return;

    disableAutosave();
    delete m_base;
    m_base = nullptr;
}

QString Game::currentVersionNumber() const noexcept
{
    return m_buildInfo->versionNumber();
}

void Game::setLocale(const QString &locale) noexcept
{
    if (locale != m_translations->currentLanguage())
        loadTranslations(locale);
    //TODO in QML on lang selection screen add call to update() of everything
}

QString Game::tr(const QString &text) noexcept
{
    return m_translations->translate(text);
}

QString Game::tr(const QString &text, const QString &context) noexcept
{
    return m_translations->translate(text,context);
}

unsigned Game::randomize(unsigned bottom, unsigned top) noexcept
{
    return Randomizer::randomBetweenAAndB(bottom,top);
}

int Game::startupTimerElapsed() noexcept
{
    return m_startupTimer != nullptr ? m_startupTimer->elapsed() : 0;
}

void Game::addDoStBan(QString name, unsigned daysAmount) noexcept
{
    m_base->mercenaries()->mercenaryDockingStationBans().insert(name,daysAmount);
}

void Game::showReportNotification() noexcept
{
    QMetaObject::invokeMethod(m_ptrToEngine->rootObjects().value(0), "showReportNotification");
}

void Game::setAnimationsSpeed(unsigned speed) noexcept
{
    m_settings.setAnimationsSpeed(static_cast<Settings::AnimationsSpeed>(speed));
    H4X().forceUIUpdate();
}

float Game::animMultiplier() noexcept
{
    switch (m_settings.animationsSpeed()) {
    case Settings::AS_Fast:
        return 0.5;
    case Settings::AS_Normal:
        return 1;
    case Settings::AS_Slow:
        return 2;
    default:
        return 0.0000001;
    }
}

void Game::showFPS(bool show) noexcept
{
    if (show != m_settings.showsFPS())
    {
        H4X hax;
        hax.fps();
    }
}

void Game::acknowledgeFPSToggle() noexcept
{
    m_settings.showFPS(!m_settings.showsFPS());
}

void Game::setLogsAmount(unsigned amount) noexcept
{
    m_settings.setLogsAmount(static_cast<Settings::LogsAmount>(amount));
}

QString Game::pathToLogs() const noexcept
{
    return m_loggersHandler->outputPath();
}

void Game::requestReadWritePermissions() noexcept
{
    //    m_permissionsManager->requestPermissions(APeR::PermissionsManager::READ_EXTERNAL_STORAGE | APeR::PermissionsManager::WRITE_EXTERNAL_STORAGE, {});
}

void Game::saveBase() noexcept
{
    m_savesManager->updateSave(m_savesManager->currentSaveInUseIndex(), m_base->getSaveData());
}

void Game::enableAutosave() noexcept
{
    if (!m_isAutosaveActive)
    {
        connect(m_base->gameClock(),SIGNAL(doAutosave()),this,SLOT(saveBase()));
        m_isAutosaveActive=1;
    }
}

void Game::disableAutosave() noexcept
{
    if (m_isAutosaveActive)
    {
        disconnect(m_base->gameClock(),SIGNAL(doAutosave()),this,SLOT(saveBase()));
        m_isAutosaveActive=0;
    }
}

void Game::loadAssets(const QString &pathToDir) noexcept
{
    m_assetsPool.load(pathToDir);

    m_lands = new LandsInfo(&m_assetsPool.lands());
}

void Game::loadVersionInfo() noexcept
{
    QFile f{":/versioninfo"};
    if (f.open(QFile::ReadOnly))
    {
        QDataStream ds{&f};

        QString s;

        ds>>s;

        ds>>s>>s;
        m_buildInfo->setVersionNumber(s);
        ds>>s>>s;
        m_buildInfo->setBuildTime(s);
        ds>>s>>s;
        m_buildInfo->setBuildType(s);
        ds>>s>>s;
        m_buildInfo->setToolkitName(s);
        ds>>s>>s;
        m_buildInfo->setAdditionBuildInfo(s);

        f.close();
    }
}

void Game::loadTranslations(const QString &lang) noexcept
{
    m_translations->loadLanguage(lang);
}

void Game::loadSettings() noexcept
{
    if (!QSettings().contains("settings"))
        saveSettings();
    else
    {
        auto v = QSettings().value("settings").toByteArray();
        QDataStream ds{&v, QIODevice::ReadOnly};
        quint8 u;
        ds>>u;
        m_settings.setAnimationsSpeed(static_cast<Settings::AnimationsSpeed>(u));
        bool b;
        ds>>b;
        m_settings.showFPS(b);
        ds>>u;
        m_settings.setLogsAmount(static_cast<Settings::LogsAmount>(u));

        //changes to UI cannot be done now, so:
        m_settingsApplierTimer = new QTimer;
        m_settingsApplierTimer->setSingleShot(1);
        QObject::connect(m_settingsApplierTimer, &QTimer::timeout, [this](){
                applyLoadedSettings();
                m_settingsApplierTimer->deleteLater();
            });
        m_settingsApplierTimer->start(1000);
    }
}

void Game::saveSettings() noexcept
{
    QByteArray bytes;
    {
    QDataStream ds{&bytes, QIODevice::WriteOnly};
    ds<<static_cast<quint8>(m_settings.animationsSpeed());
    ds<<m_settings.showsFPS();
    ds<<static_cast<quint8>(m_settings.logsAmount());
    }
    QSettings().setValue("settings", bytes);
}

void Game::applyLoadedSettings() noexcept
{
    if (m_settings.showsFPS())
    {
        m_settings.showFPS(0);//because
        H4X().fps();//<- this inverts
    }
}
