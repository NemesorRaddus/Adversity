#include "game.h"

#include <QDebug>
#include <h4x.h>

Game *Game::ptrToGameObject;

double Global::roundDouble(double d, unsigned prec) noexcept
{
    return d>=0 ? static_cast<double>(static_cast<int>(d*pow(10,prec)+0.5))/(pow(10,prec)) : static_cast<double>(static_cast<int>(d*pow(10,prec)-0.5))/(pow(10,prec));
}

QString Global::alterNormalTextToInternal(QString normalText) noexcept
{
    normalText.remove(' ');
    normalText.remove('/');

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

Game::Game(QObject *parent) noexcept
    : QObject(parent)
{
    m_startupTimer=new QElapsedTimer;
    m_startupTimer->start();
    qInfo()<<QString("[0.000] Game object initialization has started");

    ptrToGameObject=this;

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
}

Game::~Game() noexcept
{
    qInfo()<<"["+QString::number(m_startupTimer->elapsed()/1000)+'.'+QString("%1").arg(m_startupTimer->elapsed()%1000, 3, 10, QChar('0'))+"] Deleting game";
    disconnectAutosave();

    delete m_globalsExportToQML;

    delete m_h4xLogic;

    delete m_base;

    delete m_translations;

    delete m_buildInfo;

    qInfo()<<"["+QString::number(m_startupTimer->elapsed()/1000)+'.'+QString("%1").arg(m_startupTimer->elapsed()%1000, 3, 10, QChar('0'))+"] Game has been deleted";
    delete m_startupTimer;
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
