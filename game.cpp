#include "game.h"

#include <QDebug>
#include <h4x.h>

Game *Game::m_ptrToGameObject;
QQmlApplicationEngine *Game::m_ptrToEngine;

double Global::roundDouble(double d, unsigned prec) noexcept
{
    std::stringstream ss;
    ss << std::fixed;
    ss.precision(prec);
    ss << d;
    return QString(ss.str().data()).toDouble();
}

QString Global::alterNormalTextToInternal(QString normalText) noexcept
{
    normalText.remove(' ');
    normalText.remove('/');
    normalText.remove('\\');
    normalText.remove('\'');
    normalText.remove('\"');
    normalText.remove('|');

    normalText.replace('ć','c');
    normalText.replace('ę','e');
    normalText.replace('ł','l');
    normalText.replace('ń','n');
    normalText.replace('ó','o');
    normalText.replace('ś','s');
    normalText.replace('ź','z');
    normalText.replace('ż','z');

    normalText.replace('Ć','C');
    normalText.replace('Ę','E');
    normalText.replace('Ł','L');
    normalText.replace('Ń','N');
    normalText.replace('Ó','O');
    normalText.replace('Ś','S');
    normalText.replace('Ź','Z');
    normalText.replace('Ż','Z');

    return normalText;
}

LandsInfo::LandsInfo(const QVector<Land *> *lands) noexcept
    : m_lands(lands), m_preparedLand(nullptr) {}

void LandsInfo::prepareLandAt(unsigned index) noexcept
{
    if (index<m_lands->size())
        m_preparedLand=(*m_lands)[index];
}

LoggersHandler::LoggersHandler() noexcept
{
    QString path;
#ifdef ANDROID // QStandardPaths was giving strange paths for Android devices
    path = "/storage/emulated/0/Android/data/com.raddosgames.adversity";
#else
    path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
#endif
    QDir d;
    d.mkpath(path);
    m_output = std::make_shared<spdlog::sinks::rotating_file_sink_st>(path.toStdString()+"/adversity.log",1024*1024,20);
    m_mainLogger = std::make_shared<spdlog::logger>("main", m_output);
    m_xmlLogger = std::make_shared<spdlog::logger>("xml", m_output);
    m_qmlLogger = std::make_shared<spdlog::logger>("qml", m_output);

    spdlog::register_logger(m_mainLogger);
    spdlog::register_logger(m_xmlLogger);
    spdlog::register_logger(m_qmlLogger);

    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] (%n) %l: %v");
}

void LoggersHandler::setLevel(spdlog::level::level_enum lvl) noexcept
{
    m_mainLogger->set_level(lvl);
    m_xmlLogger->set_level(lvl);
    m_qmlLogger->set_level(lvl);
}

void LoggersHandler::trace(const QString &msg) noexcept
{
    m_qmlLogger->trace(msg.toStdString());
}

void LoggersHandler::debug(const QString &msg) noexcept
{
    m_qmlLogger->debug(msg.toStdString());
}

void LoggersHandler::info(const QString &msg) noexcept
{
    m_qmlLogger->info(msg.toStdString());
}

void LoggersHandler::warn(const QString &msg) noexcept
{
    m_qmlLogger->warn(msg.toStdString());
}

void LoggersHandler::error(const QString &msg) noexcept
{
    m_qmlLogger->error(msg.toStdString());
}

void LoggersHandler::critical(const QString &msg) noexcept
{
    m_qmlLogger->critical(msg.toStdString());
}

void LoggersHandler::traceIf(bool cond, const QString &msg) noexcept
{
    m_qmlLogger->trace_if(cond, msg.toStdString());
}

void LoggersHandler::debugIf(bool cond, const QString &msg) noexcept
{
    m_qmlLogger->debug_if(cond, msg.toStdString());
}

void LoggersHandler::infoIf(bool cond, const QString &msg) noexcept
{
    m_qmlLogger->info_if(cond, msg.toStdString());
}

void LoggersHandler::warnIf(bool cond, const QString &msg) noexcept
{
    m_qmlLogger->warn_if(cond, msg.toStdString());
}

void LoggersHandler::errorIf(bool cond, const QString &msg) noexcept
{
    m_qmlLogger->error_if(cond, msg.toStdString());
}

void LoggersHandler::criticalIf(bool cond, const QString &msg) noexcept
{
    m_qmlLogger->critical_if(cond, msg.toStdString());
}

Game::Game(QObject *parent) noexcept
    : QObject(parent)
{
    m_startupTimer=new QElapsedTimer;
    m_startupTimer->start();
    qInfo()<<QString("[0.000] Game object initialization has started");

    m_ptrToGameObject=this;

    m_buildInfo=new AppBuildInfo;
    loadVersionInfo();

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

    m_globalsExportToQML=new Global;

    connectAutosave();

    m_loggersHandler = new LoggersHandler;m_loggersHandler->mainLogger()->debug("HEJ");
}

Game::~Game() noexcept
{
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

void Game::setLocale(const QString &locale) noexcept
{
    if (locale!=m_translations->currentLanguage())
        loadTranslations(locale);
    //TODO in QML on lang selection screen add call to update() of everything
}

void Game::showReportNotification() noexcept
{
    QMetaObject::invokeMethod(m_ptrToEngine->rootObjects().value(0), "showReportNotification");
}

void Game::saveBase_slot() noexcept
{
    QByteArray ba;
    SaveParser::writeData(ba,m_base->getSaveData());
    QSettings().setValue("save01",ba);
}

void Game::addDoStBan(QString name, unsigned daysAmount) noexcept
{
    m_base->heroDockingStationBans().insert(name,daysAmount);
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
    QMap <QPair <BaseEnums::Building, unsigned>, BuildingUpgradeRequirements> bureqs;

    auto culi = xmlReader.getCentralUnitLevelsInfo(pathToDir+"base/buildingLevelsInfo/centralUnit.xml");
    m_base->centralUnit()->setLevelsInfo(culi.first);
    for (int i=0;i<culi.second.size();++i)
        bureqs.insert({BaseEnums::B_CentralUnit,i},culi.second[i]);

    auto hli = xmlReader.getHospitalLevelsInfo(pathToDir+"base/buildingLevelsInfo/hospital.xml");
    m_base->hospital()->setLevelsInfo(hli.first);
    for (int i=0;i<hli.second.size();++i)
        bureqs.insert({BaseEnums::B_Hospital,i},hli.second[i]);

    auto tgli = xmlReader.getTrainingGroundLevelsInfo(pathToDir+"base/buildingLevelsInfo/trainingGround.xml");
    m_base->trainingGround()->setLevelsInfo(tgli.first);
    for (int i=0;i<tgli.second.size();++i)
        bureqs.insert({BaseEnums::B_TrainingGround,i},tgli.second[i]);

    auto gli = xmlReader.getGymLevelsInfo(pathToDir+"base/buildingLevelsInfo/gym.xml");
    m_base->gym()->setLevelsInfo(gli.first);
    for (int i=0;i<gli.second.size();++i)
        bureqs.insert({BaseEnums::B_Gym,i},gli.second[i]);

    auto lli = xmlReader.getLaboratoryLevelsInfo(pathToDir+"base/buildingLevelsInfo/laboratory.xml");
    m_base->laboratory()->setLevelsInfo(lli.first);
    for (int i=0;i<lli.second.size();++i)
        bureqs.insert({BaseEnums::B_Laboratory,i},lli.second[i]);

    auto pfli = xmlReader.getPlayingFieldLevelsInfo(pathToDir+"base/buildingLevelsInfo/playingField.xml");
    m_base->playingField()->setLevelsInfo(pfli.first);
    for (int i=0;i<pfli.second.size();++i)
        bureqs.insert({BaseEnums::B_PlayingField,i},pfli.second[i]);

    auto bli = xmlReader.getBarLevelsInfo(pathToDir+"base/buildingLevelsInfo/bar.xml");
    m_base->bar()->setLevelsInfo(bli.first);
    for (int i=0;i<bli.second.size();++i)
        bureqs.insert({BaseEnums::B_Bar,i},bli.second[i]);

    auto sli = xmlReader.getShrineLevelsInfo(pathToDir+"base/buildingLevelsInfo/shrine.xml");
    m_base->shrine()->setLevelsInfo(sli.first);
    for (int i=0;i<sli.second.size();++i)
        bureqs.insert({BaseEnums::B_Shrine,i},sli.second[i]);

    auto s1li = xmlReader.getSeclusionLevelsInfo(pathToDir+"base/buildingLevelsInfo/seclusion.xml");
    m_base->seclusion()->setLevelsInfo(s1li.first);
    for (int i=0;i<s1li.second.size();++i)
        bureqs.insert({BaseEnums::B_Seclusion,i},s1li.second[i]);

    auto pli = xmlReader.getPowerplantLevelsInfo(pathToDir+"base/buildingLevelsInfo/powerplant.xml");
    m_base->powerplant()->setLevelsInfo(pli.first);
    for (int i=0;i<pli.second.size();++i)
        bureqs.insert({BaseEnums::B_Powerplant,i},pli.second[i]);

    auto fli = xmlReader.getFactoryLevelsInfo(pathToDir+"base/buildingLevelsInfo/factory.xml");
    m_base->factory()->setLevelsInfo(fli.first);
    for (int i=0;i<fli.second.size();++i)
        bureqs.insert({BaseEnums::B_Factory,i},fli.second[i]);

    auto crli = xmlReader.getCoolRoomLevelsInfo(pathToDir+"base/buildingLevelsInfo/coolRoom.xml");
    m_base->coolRoom()->setLevelsInfo(crli.first);
    for (int i=0;i<crli.second.size();++i)
        bureqs.insert({BaseEnums::B_CoolRoom,i},crli.second[i]);

    auto srli = xmlReader.getStorageRoomLevelsInfo(pathToDir+"base/buildingLevelsInfo/storageRoom.xml");
    m_base->storageRoom()->setLevelsInfo(srli.first);
    for (int i=0;i<srli.second.size();++i)
        bureqs.insert({BaseEnums::B_StorageRoom,i},srli.second[i]);

    auto asli = xmlReader.getAetheriteSiloLevelsInfo(pathToDir+"base/buildingLevelsInfo/aetheriteSilo.xml");
    m_base->aetheriteSilo()->setLevelsInfo(asli.first);
    for (int i=0;i<asli.second.size();++i)
        bureqs.insert({BaseEnums::B_AetheriteSilo,i},asli.second[i]);

    auto b1li = xmlReader.getBarracksLevelsInfo(pathToDir+"base/buildingLevelsInfo/barracks.xml");
    m_base->barracks()->setLevelsInfo(b1li.first);
    for (int i=0;i<b1li.second.size();++i)
        bureqs.insert({BaseEnums::B_Barracks,i},b1li.second[i]);

    auto dsli = xmlReader.getDockingStationLevelsInfo(pathToDir+"base/buildingLevelsInfo/dockingStation.xml");
    m_base->dockingStation()->setLevelsInfo(dsli.first);
    for (int i=0;i<dsli.second.size();++i)
        bureqs.insert({BaseEnums::B_DockingStation,i},dsli.second[i]);

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
