#include "game.h"

Game::Game(QObject *parent) noexcept
    : QObject(parent)
{
    m_base=new Base;

    connectAutosave();
}

void Game::createNewBase(const QString &pathToAssetsDir) noexcept
{
    m_currentPathToAssets=pathToAssetsDir;

    disconnectAutosave();

    delete m_base;
    m_base = new Base;

    loadAssets(pathToAssetsDir);

    connectAutosave();
}

void Game::loadExistingBase(const QString &pathToSaveFile, const QString &pathToAssetsDir) noexcept
{
    m_currentPathToSaveData=pathToSaveFile;
    m_currentPathToAssets=pathToAssetsDir;

    disconnectAutosave();

    delete m_base;
    m_base = new Base;

    loadAssets(pathToAssetsDir);

    m_base->loadSaveData(SaveParser::readData(pathToSaveFile));

    connectAutosave();
}

void Game::saveBase(const QString &pathToSaveFile) noexcept
{
    m_currentPathToSaveData=pathToSaveFile;
    SaveParser::writeData(pathToSaveFile,m_base->getSaveData());
}

void Game::saveBase() noexcept
{
    SaveParser::writeData(m_currentPathToSaveData,m_base->getSaveData());
}

void Game::connectAutosave() noexcept
{
    connect(m_base->gameClock(),SIGNAL(doAutosave()),this,SLOT(saveBase()));
}

void Game::disconnectAutosave() noexcept
{
    disconnect(m_base->gameClock(),SIGNAL(doAutosave()),this,SLOT(saveBase()));
}

void Game::loadAssets(const QString &pathToDir) noexcept
{
    XmlFileReader xmlReader;
    m_base->setBuildingDescriptions(xmlReader.getBuildingDescriptions(pathToDir+"base/descriptions.xml"));
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
    m_base->powerPlant()->setLevelsInfo(pli.first);
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
