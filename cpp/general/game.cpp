#include "general/game.h"

#include <QElapsedTimer>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QTimer>
#include <QDebug>

#include "libs/APeR-0.1.0/aper.h"

#include "base/base.h"
#include "base/buildings/aetheritesilo.h"
#include "base/buildings/bar.h"
#include "base/buildings/barracks.h"
#include "base/buildings/centralunit.h"
#include "base/buildings/coolroom.h"
#include "base/buildings/dockingstation.h"
#include "base/buildings/factory.h"
#include "base/buildings/gym.h"
#include "base/buildings/hospital.h"
#include "base/buildings/laboratory.h"
#include "base/buildings/playingfield.h"
#include "base/buildings/powerplant.h"
#include "base/buildings/seclusion.h"
#include "base/buildings/shrine.h"
#include "base/buildings/storageroom.h"
#include "base/buildings/trainingground.h"
#include "clock/gameclock.h"
#include "clock/timer_alarms/buildingupgrade.h"
#include "clock/timer_alarms/missionend.h"
#include "file_io/saves/savedata.h"
#include "file_io/saves/saveparser.h"
#include "file_io/xml_files/xmlreader.h"
#include "general/appbuildinfo.h"
#include "general/globalutilities.h"
#include "general/randomizer.h"
#include "h4x/h4x.h"
#include "logging/loggershandler.h"
#include "missions/land.h"
#include "missions/mission.h"
#include "reports/unifiedreport.h"
#include "translations/translations.h"

Game *Game::m_ptrToGameObject;
QQmlApplicationEngine *Game::m_ptrToEngine;

Game::Game(QObject *parent) noexcept
    : QObject(parent)
{
    m_ptrToGameObject=this;

    m_buildInfo=new AppBuildInfo;
    loadVersionInfo();

    loadSettings();

    m_permissionsManager = new APeR::PermissionsManager;

    m_loggersHandler = new LoggersHandler;

    m_startupTimer=new QElapsedTimer;
    m_startupTimer->start();
    qInfo()<<QString("[0.000] Game object initialization has started");

    m_translations=new TranslationsDB(":/");
    if (!QSettings().contains("lang"))
    {
        if (QLocale::system().name()!="pl_PL" && QLocale::system().name()!="en_GB")
            QSettings().setValue("lang","en_GB");
        else
            QSettings().setValue("lang",QLocale::system().name());
    }
    setLocale(QSettings().value("lang").toString());

    m_base=new Base(this);

    m_h4xLogic=new H4X;

    m_globalsExportToQML=new GlobalUtilities;

    connectAutosave();
}

Game::~Game() noexcept
{
    saveSettings();
    qInfo()<<"["+QString::number(m_startupTimer->elapsed()/1000)+'.'+QString("%1").arg(m_startupTimer->elapsed()%1000, 3, 10, QChar('0'))+"] Deleting game";
    disconnectAutosave();

    delete m_lands;

    delete m_globalsExportToQML;

    delete m_h4xLogic;

    delete m_base;

    delete m_translations;

    delete m_buildInfo;

    qInfo()<<"["+QString::number(m_startupTimer->elapsed()/1000)+'.'+QString("%1").arg(m_startupTimer->elapsed()%1000, 3, 10, QChar('0'))+"] Game has been deleted";
    delete m_startupTimer;

    delete m_loggersHandler;

    delete m_permissionsManager;
}

void Game::setQMLEnginePtr(QQmlApplicationEngine *engine) noexcept
{
    m_ptrToEngine=engine;
}

void Game::createNewBase(const QString &pathToAssetsDir) noexcept
{
    m_currentPathToAssets=pathToAssetsDir;

    disconnectAutosave();

    delete m_base;
    m_base = new Base(this);
    qInfo()<<"["+QString::number(m_startupTimer->elapsed()/1000)+'.'+QString("%1").arg(m_startupTimer->elapsed()%1000, 3, 10, QChar('0'))+"] Base has been created";

    loadAssets(pathToAssetsDir);
    qInfo()<<"["+QString::number(m_startupTimer->elapsed()/1000)+'.'+QString("%1").arg(m_startupTimer->elapsed()%1000, 3, 10, QChar('0'))+"] Assets have been loaded";

    m_base->setupNewBase();
    qInfo()<<"["+QString::number(m_startupTimer->elapsed()/1000)+'.'+QString("%1").arg(m_startupTimer->elapsed()%1000, 3, 10, QChar('0'))+"] Base has been set up";

    connectAutosave();
}

void Game::loadExistingBase(const QString &pathToAssetsDir) noexcept
{
    QByteArray ba=QSettings().value("save01").toByteArray();
    if (ba.isEmpty())
        return createNewBase(pathToAssetsDir);

    m_currentPathToAssets=pathToAssetsDir;

    disconnectAutosave();

    delete m_base;
    m_base = new Base(this);
    qInfo()<<"["+QString::number(m_startupTimer->elapsed()/1000)+'.'+QString("%1").arg(m_startupTimer->elapsed()%1000, 3, 10, QChar('0'))+"] Base has been created";

    loadAssets(pathToAssetsDir);
    qInfo()<<"["+QString::number(m_startupTimer->elapsed()/1000)+'.'+QString("%1").arg(m_startupTimer->elapsed()%1000, 3, 10, QChar('0'))+"] Assets have been loaded";

    m_base->loadSaveData(SaveParser::readData(ba));
    qInfo()<<"["+QString::number(m_startupTimer->elapsed()/1000)+'.'+QString("%1").arg(m_startupTimer->elapsed()%1000, 3, 10, QChar('0'))+"] Save has been loaded";

    connectAutosave();
}

void Game::saveBase() noexcept
{
    QByteArray ba;
    SaveParser::writeData(ba,m_base->getSaveData());
    QSettings().setValue("save01",ba);
}

QString Game::currentVersionNumber() const noexcept
{
    return m_buildInfo->versionNumber();
}

void Game::setLocale(const QString &locale) noexcept
{
    if (locale!=m_translations->currentLanguage())
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
    return m_startupTimer!=nullptr ? m_startupTimer->elapsed() : 0;
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

void Game::saveBase_slot() noexcept
{
    QByteArray ba;
    SaveParser::writeData(ba,m_base->getSaveData());
    QSettings().setValue("save01",ba);
}

void Game::addDoStBan(QString name, unsigned daysAmount) noexcept
{
    m_base->mercenaryDockingStationBans().insert(name,daysAmount);
}

void Game::connectAutosave() noexcept
{
    connect(m_base->gameClock(),SIGNAL(doAutosave()),this,SLOT(saveBase_slot()));
}

void Game::disconnectAutosave() noexcept
{
    disconnect(m_base->gameClock(),SIGNAL(doAutosave()),this,SLOT(saveBase_slot()));
}

void Game::loadAssets(const QString &pathToDir) noexcept
{
    XmlFileReader xmlReader;
    m_base->setBuildingDescriptions(xmlReader.getBuildingDescriptions(pathToDir+"base/descriptions.xml"));
    //levels infos
    {
    QMap <QPair <BuildingEnums::Building, unsigned>, BuildingUpgradeRequirements> bureqs;

    auto culi = xmlReader.getCentralUnitLevelsInfo(pathToDir+"base/buildingLevelsInfo/centralUnit.xml");
    m_base->centralUnit()->setLevelsInfo(culi.first);
    for (int i=0;i<culi.second.size();++i)
        bureqs.insert({BuildingEnums::B_CentralUnit,i},culi.second[i]);

    auto hli = xmlReader.getHospitalLevelsInfo(pathToDir+"base/buildingLevelsInfo/hospital.xml");
    m_base->hospital()->setLevelsInfo(hli.first);
    for (int i=0;i<hli.second.size();++i)
        bureqs.insert({BuildingEnums::B_Hospital,i},hli.second[i]);

    auto tgli = xmlReader.getTrainingGroundLevelsInfo(pathToDir+"base/buildingLevelsInfo/trainingGround.xml");
    m_base->trainingGround()->setLevelsInfo(tgli.first);
    for (int i=0;i<tgli.second.size();++i)
        bureqs.insert({BuildingEnums::B_TrainingGround,i},tgli.second[i]);

    auto gli = xmlReader.getGymLevelsInfo(pathToDir+"base/buildingLevelsInfo/gym.xml");
    m_base->gym()->setLevelsInfo(gli.first);
    for (int i=0;i<gli.second.size();++i)
        bureqs.insert({BuildingEnums::B_Gym,i},gli.second[i]);

    auto lli = xmlReader.getLaboratoryLevelsInfo(pathToDir+"base/buildingLevelsInfo/laboratory.xml");
    m_base->laboratory()->setLevelsInfo(lli.first);
    for (int i=0;i<lli.second.size();++i)
        bureqs.insert({BuildingEnums::B_Laboratory,i},lli.second[i]);

    auto pfli = xmlReader.getPlayingFieldLevelsInfo(pathToDir+"base/buildingLevelsInfo/playingField.xml");
    m_base->playingField()->setLevelsInfo(pfli.first);
    for (int i=0;i<pfli.second.size();++i)
        bureqs.insert({BuildingEnums::B_PlayingField,i},pfli.second[i]);

    auto bli = xmlReader.getBarLevelsInfo(pathToDir+"base/buildingLevelsInfo/bar.xml");
    m_base->bar()->setLevelsInfo(bli.first);
    for (int i=0;i<bli.second.size();++i)
        bureqs.insert({BuildingEnums::B_Bar,i},bli.second[i]);

    auto sli = xmlReader.getShrineLevelsInfo(pathToDir+"base/buildingLevelsInfo/shrine.xml");
    m_base->shrine()->setLevelsInfo(sli.first);
    for (int i=0;i<sli.second.size();++i)
        bureqs.insert({BuildingEnums::B_Shrine,i},sli.second[i]);

    auto s1li = xmlReader.getSeclusionLevelsInfo(pathToDir+"base/buildingLevelsInfo/seclusion.xml");
    m_base->seclusion()->setLevelsInfo(s1li.first);
    for (int i=0;i<s1li.second.size();++i)
        bureqs.insert({BuildingEnums::B_Seclusion,i},s1li.second[i]);

    auto pli = xmlReader.getPowerplantLevelsInfo(pathToDir+"base/buildingLevelsInfo/powerplant.xml");
    m_base->powerplant()->setLevelsInfo(pli.first);
    for (int i=0;i<pli.second.size();++i)
        bureqs.insert({BuildingEnums::B_Powerplant,i},pli.second[i]);

    auto fli = xmlReader.getFactoryLevelsInfo(pathToDir+"base/buildingLevelsInfo/factory.xml");
    m_base->factory()->setLevelsInfo(fli.first);
    for (int i=0;i<fli.second.size();++i)
        bureqs.insert({BuildingEnums::B_Factory,i},fli.second[i]);

    auto crli = xmlReader.getCoolRoomLevelsInfo(pathToDir+"base/buildingLevelsInfo/coolRoom.xml");
    m_base->coolRoom()->setLevelsInfo(crli.first);
    for (int i=0;i<crli.second.size();++i)
        bureqs.insert({BuildingEnums::B_CoolRoom,i},crli.second[i]);

    auto srli = xmlReader.getStorageRoomLevelsInfo(pathToDir+"base/buildingLevelsInfo/storageRoom.xml");
    m_base->storageRoom()->setLevelsInfo(srli.first);
    for (int i=0;i<srli.second.size();++i)
        bureqs.insert({BuildingEnums::B_StorageRoom,i},srli.second[i]);

    auto asli = xmlReader.getAetheriteSiloLevelsInfo(pathToDir+"base/buildingLevelsInfo/aetheriteSilo.xml");
    m_base->aetheriteSilo()->setLevelsInfo(asli.first);
    for (int i=0;i<asli.second.size();++i)
        bureqs.insert({BuildingEnums::B_AetheriteSilo,i},asli.second[i]);

    auto b1li = xmlReader.getBarracksLevelsInfo(pathToDir+"base/buildingLevelsInfo/barracks.xml");
    m_base->barracks()->setLevelsInfo(b1li.first);
    for (int i=0;i<b1li.second.size();++i)
        bureqs.insert({BuildingEnums::B_Barracks,i},b1li.second[i]);

    auto dsli = xmlReader.getDockingStationLevelsInfo(pathToDir+"base/buildingLevelsInfo/dockingStation.xml");
    m_base->dockingStation()->setLevelsInfo(dsli.first);
    for (int i=0;i<dsli.second.size();++i)
        bureqs.insert({BuildingEnums::B_DockingStation,i},dsli.second[i]);

    m_base->setBuildingRequirements(bureqs);
    }
    m_base->dockingStation()->setTradingTables(xmlReader.getDockingStationTradingTable(pathToDir+"base/dockingStationTradingTables.xml"));

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