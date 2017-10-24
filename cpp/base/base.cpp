#include "base.h"

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
#include "equipment/equipment.h"
#include "file_io/saves/saveparser.h"
#include "general/appbuildinfo.h"
#include "general/game.h"
#include "logging/loggershandler.h"
#include "missions/mission.h"
#include "reports/basereports.h"
#include "reports/missionreports.h"
#include "reports/unifiedreport.h"

Base::Base(Game *gameObject) noexcept
    : QObject(nullptr), m_gameObject(gameObject), m_database(nullptr)
{
    MercenaryBuilder::init(this);

    m_gameClock=new GameClock;
    m_gameClock->setBasePtr(this);

    m_centralUnit=new CentralUnit(this,1,{});
    m_hospital=new Hospital(this,0,{});
    m_trainingGround=new TrainingGround(this,0,{});
    m_gym=new Gym(this,0,{});
    m_laboratory=new Laboratory(this,0,{});
    m_playingField=new PlayingField(this,0,{});
    m_bar=new Bar(this,0,{});
    m_shrine=new Shrine(this,0,{});
    m_seclusion=new Seclusion(this,0,{});
    m_powerplant=new Powerplant(this,1,{});
    m_factory=new Factory(this,1,{});
    m_coolRoom=new CoolRoom(this,1,{});
    m_storageRoom=new StorageRoom(this,1,{});
    m_aetheriteSilo=new AetheriteSilo(this,1,{});
    m_barracks=new Barracks(this,1,{});
    m_dockingStation=new DockingStation(this,1,{});

    m_buildings.insert(BuildingEnums::B_CentralUnit,m_centralUnit);
    m_buildings.insert(BuildingEnums::B_Hospital,m_hospital);
    m_buildings.insert(BuildingEnums::B_TrainingGround,m_trainingGround);
    m_buildings.insert(BuildingEnums::B_Gym,m_gym);
    m_buildings.insert(BuildingEnums::B_Laboratory,m_laboratory);
    m_buildings.insert(BuildingEnums::B_PlayingField,m_playingField);
    m_buildings.insert(BuildingEnums::B_Bar,m_bar);
    m_buildings.insert(BuildingEnums::B_Shrine,m_shrine);
    m_buildings.insert(BuildingEnums::B_Seclusion,m_seclusion);
    m_buildings.insert(BuildingEnums::B_Powerplant,m_powerplant);
    m_buildings.insert(BuildingEnums::B_Factory,m_factory);
    m_buildings.insert(BuildingEnums::B_CoolRoom,m_coolRoom);
    m_buildings.insert(BuildingEnums::B_StorageRoom,m_storageRoom);
    m_buildings.insert(BuildingEnums::B_AetheriteSilo,m_aetheriteSilo);
    m_buildings.insert(BuildingEnums::B_Barracks,m_barracks);
    m_buildings.insert(BuildingEnums::B_DockingStation,m_dockingStation);

    m_mercenaries=new MercenariesContainer(this);

    m_missionInitializer=new MissionInitializer(this);
}

void Base::setupNewBase() noexcept
{
    m_energy=250;
    m_foodSupplies=24;
    m_buildingMaterials=5;
    m_aetherite=50;

    m_dockingStation->prepareRecruits();
    m_dockingStation->prepareEquipments();

    m_mercenaries->setAmountOfSlots(m_barracks->mercenariesLimit());//setting mercenaries limit
    m_gameObject->assetsPool().loadMercenaryNamedFromList("HeinzWitt");
    auto loadedH = m_gameObject->assetsPool().loadedMercenaries();
    for (auto e : loadedH)
        if (e->name() == "HeinzWitt")
        {
            m_mercenaries->addMercenary(e);
            break;
        }

    m_database=m_gameObject->assetsPool().makeStockDatabase();
    Game::gameInstance()->loggers()->buildingsLogger()->trace("[{}]Base has been set up",gameClock()->currentTime().toQString().toStdString());
}

Base::~Base() noexcept
{
    delete m_centralUnit;
    delete m_hospital;
    delete m_trainingGround;
    delete m_gym;
    delete m_laboratory;
    delete m_playingField;
    delete m_bar;
    delete m_shrine;
    delete m_seclusion;
    delete m_powerplant;
    delete m_factory;
    delete m_coolRoom;
    delete m_storageRoom;
    delete m_aetheriteSilo;
    delete m_barracks;
    delete m_dockingStation;

    delete m_gameClock;

    delete m_mercenaries;

    if (m_database!=nullptr)
        delete m_database;

    delete m_missionInitializer;
}

void Base::loadSaveData(const SaveData &data) noexcept
{
    Game::gameInstance()->loggers()->mainLogger()->trace("Loading save...");
    Game::gameInstance()->loggers()->mainLogger()->trace("Save content:");
    Game::gameInstance()->loggers()->mainLogger()->trace(QString(data.raw.toHex()).toStdString());
    if (m_database!=nullptr)
        delete m_database;
    m_database=m_gameObject->assetsPool().makeStockDatabase();

    m_buildingLevels.insert(BuildingEnums::B_CentralUnit,data.buildings.levels.centralUnit);//buildings levels loading
    m_buildingLevels.insert(BuildingEnums::B_Hospital,data.buildings.levels.hospital);
    m_buildingLevels.insert(BuildingEnums::B_TrainingGround,data.buildings.levels.trainingGround);
    m_buildingLevels.insert(BuildingEnums::B_Gym,data.buildings.levels.gym);
    m_buildingLevels.insert(BuildingEnums::B_Laboratory,data.buildings.levels.laboratory);
    m_buildingLevels.insert(BuildingEnums::B_PlayingField,data.buildings.levels.playingField);
    m_buildingLevels.insert(BuildingEnums::B_Bar,data.buildings.levels.bar);
    m_buildingLevels.insert(BuildingEnums::B_Shrine,data.buildings.levels.shrine);
    m_buildingLevels.insert(BuildingEnums::B_Seclusion,data.buildings.levels.seclusion);
    m_buildingLevels.insert(BuildingEnums::B_Powerplant,data.buildings.levels.powerplant);
    m_buildingLevels.insert(BuildingEnums::B_Factory,data.buildings.levels.factory);
    m_buildingLevels.insert(BuildingEnums::B_CoolRoom,data.buildings.levels.coolRoom);
    m_buildingLevels.insert(BuildingEnums::B_StorageRoom,data.buildings.levels.storageRoom);
    m_buildingLevels.insert(BuildingEnums::B_AetheriteSilo,data.buildings.levels.aetheriteSilo);
    m_buildingLevels.insert(BuildingEnums::B_Barracks,data.buildings.levels.barracks);
    m_buildingLevels.insert(BuildingEnums::B_DockingStation,data.buildings.levels.dockingStation);

    m_hospital->resizeSlotsAfterUpgrade();//resizing slots in buildings
    m_trainingGround->resizeSlotsAfterUpgrade();
    m_gym->resizeSlotsAfterUpgrade();
    m_laboratory->resizeSlotsAfterUpgrade();
    m_playingField->resizeSlotsAfterUpgrade();
    m_bar->resizeSlotsAfterUpgrade();
    m_shrine->resizeSlotsAfterUpgrade();
    m_seclusion->resizeSlotsAfterUpgrade();

    for (int i=0;i<data.buildings.dockingStationThings.recruits.size();++i)//loading needed mercenaries in AssetsPool
        m_gameObject->assetsPool().loadMercenaryNamedFromList(data.buildings.dockingStationThings.recruits[i]);
    for (int i=0;i<data.mercenaries.hiredMercenaries.size();++i)
        m_gameObject->assetsPool().loadMercenaryNamedFromList(data.mercenaries.hiredMercenaries[i].name);

    m_mercenaries->setAmountOfSlots(m_barracks->mercenariesLimit());//setting mercenaries limit

    m_powerplant->setCurrentCycles(data.buildings.cyclesSet.powerplant);//setting cycles
    m_factory->setCurrentCycles(data.buildings.cyclesSet.factory);

    m_centralUnit->setIsBeingUpgraded(data.buildings.upgrading.centralUnit);//setting upgrades
    m_powerplant->setIsBeingUpgraded(data.buildings.upgrading.powerplant);
    m_factory->setIsBeingUpgraded(data.buildings.upgrading.factory);
    m_coolRoom->setIsBeingUpgraded(data.buildings.upgrading.coolRoom);
    m_storageRoom->setIsBeingUpgraded(data.buildings.upgrading.storageRoom);
    m_aetheriteSilo->setIsBeingUpgraded(data.buildings.upgrading.aetheriteSilo);
    m_hospital->setIsBeingUpgraded(data.buildings.upgrading.hospital);
    m_barracks->setIsBeingUpgraded(data.buildings.upgrading.barracks);
    m_dockingStation->setIsBeingUpgraded(data.buildings.upgrading.dockingStation);
    m_trainingGround->setIsBeingUpgraded(data.buildings.upgrading.trainingGround);
    m_gym->setIsBeingUpgraded(data.buildings.upgrading.gym);
    m_laboratory->setIsBeingUpgraded(data.buildings.upgrading.laboratory);
    m_playingField->setIsBeingUpgraded(data.buildings.upgrading.playingField);
    m_bar->setIsBeingUpgraded(data.buildings.upgrading.bar);
    m_shrine->setIsBeingUpgraded(data.buildings.upgrading.shrine);
    m_seclusion->setIsBeingUpgraded(data.buildings.upgrading.seclusion);

    for (int i=0;i<data.equipments.freeArmor.size();++i)//creating owned equipment
        m_availableEquipment.push_back(Game::gameInstance()->assetsPool().makeEquipmentNamed(data.equipments.freeArmor[i]));
    for (int i=0;i<data.equipments.freeWeaponsTools.size();++i)
        m_availableEquipment.push_back(Game::gameInstance()->assetsPool().makeEquipmentNamed(data.equipments.freeWeaponsTools[i]));

    for (int i=0;i<data.mercenaries.hiredMercenaries.size();++i)//adding mercenaries
        m_mercenaries->addMercenary(MercenaryBuilder::qobjectifyMercenaryData(data.mercenaries.hiredMercenaries[i]));

    for (int i=0;i<data.buildings.dockingStationThings.recruits.size();++i)//adding possible recruits
        for (int j=0;j<m_gameObject->assetsPool().loadedMercenaries().size();++j)
            if (m_gameObject->assetsPool().loadedMercenaries()[j]->name() == data.buildings.dockingStationThings.recruits[i])
            {
                m_dockingStation->addRecruitFromSave(m_gameObject->assetsPool().loadedMercenaries()[j]);
                break;
            }

    for (int i=0;i<data.buildings.dockingStationThings.equipments.size();++i)//adding buyable equipments
        m_dockingStation->addEquipmentFromSave(m_gameObject->assetsPool().makeEquipmentNamed(data.buildings.dockingStationThings.equipments[i]));

    for (int i=0;i<data.buildings.dockingStationThings.arrivingMercenaries.size();++i)//adding arriving mercenaries
        for (int j=0;j<m_mercenaries->amountOfMercenaries();++j)
            if (m_mercenaries->getMercenary(j)->name() == data.buildings.dockingStationThings.arrivingMercenaries[i].first)
            {
                m_dockingStation->addArrivingMercenaryFromSave({m_mercenaries->getMercenary(j),static_cast<unsigned>(data.buildings.dockingStationThings.arrivingMercenaries[i].second)});
                break;
            }

    for (int i=0;i<data.buildings.dockingStationThings.arrivingEquipments.size();++i)//adding arriving equipments
        for (int j=0;j<m_gameObject->assetsPool().equipment().size();++j)
            if (m_gameObject->assetsPool().equipment()[j]->name() == data.buildings.dockingStationThings.arrivingEquipments[i].first)
            {
                m_dockingStation->addArrivingEquipmentFromSave({m_gameObject->assetsPool().equipment()[j],static_cast<unsigned>(data.buildings.dockingStationThings.arrivingEquipments[i].second)});
                break;
            }

    QVector <QPair <ActiveTransaction, unsigned> > actTr;
    for (int i=0;i<data.buildings.dockingStationThings.activeResourceTransactions.size();++i)//set active resource transactions
        actTr+={data.buildings.dockingStationThings.activeResourceTransactions[i].first, static_cast<unsigned>(data.buildings.dockingStationThings.activeResourceTransactions[i].second)};
    m_dockingStation->setActiveTransactionsFromSave(actTr);

    for (int i=0;i<data.buildings.mercenarySlots.hospital.size();++i)//setting slots in buildings
        m_hospital->setSlot(i,!data.buildings.mercenarySlots.hospital[i].isEmpty() ? m_mercenaries->getMercenary(m_mercenaries->findMercenary(data.buildings.mercenarySlots.hospital[i])) : nullptr);
    for (int i=0;i<data.buildings.mercenarySlots.trainingGround.size();++i)
        m_trainingGround->setSlot(i,!data.buildings.mercenarySlots.trainingGround[i].first.isEmpty() ? m_mercenaries->getMercenary(m_mercenaries->findMercenary(data.buildings.mercenarySlots.trainingGround[i].first)) : nullptr, static_cast<unsigned>(data.buildings.mercenarySlots.trainingGround[i].second));
    for (int i=0;i<data.buildings.mercenarySlots.gym.size();++i)
        m_gym->setSlot(i,!data.buildings.mercenarySlots.gym[i].first.isEmpty() ? m_mercenaries->getMercenary(m_mercenaries->findMercenary(data.buildings.mercenarySlots.gym[i].first)) : nullptr, static_cast<unsigned>(data.buildings.mercenarySlots.gym[i].second));
    for (int i=0;i<data.buildings.mercenarySlots.laboratory.size();++i)
        m_laboratory->setSlot(i,!data.buildings.mercenarySlots.laboratory[i].first.isEmpty() ? m_mercenaries->getMercenary(m_mercenaries->findMercenary(data.buildings.mercenarySlots.laboratory[i].first)) : nullptr, static_cast<unsigned>(data.buildings.mercenarySlots.laboratory[i].second));
    for (int i=0;i<data.buildings.mercenarySlots.playingField.size();++i)
        m_playingField->setSlot(i,!data.buildings.mercenarySlots.playingField[i].isEmpty() ? m_mercenaries->getMercenary(m_mercenaries->findMercenary(data.buildings.mercenarySlots.playingField[i])) : nullptr);
    for (int i=0;i<data.buildings.mercenarySlots.bar.size();++i)
        m_bar->setSlot(i,!data.buildings.mercenarySlots.bar[i].isEmpty() ? m_mercenaries->getMercenary(m_mercenaries->findMercenary(data.buildings.mercenarySlots.bar[i])) : nullptr);
    for (int i=0;i<data.buildings.mercenarySlots.shrine.size();++i)
        m_shrine->setSlot(i,!data.buildings.mercenarySlots.shrine[i].isEmpty() ? m_mercenaries->getMercenary(m_mercenaries->findMercenary(data.buildings.mercenarySlots.shrine[i])) : nullptr);
    for (int i=0;i<data.buildings.mercenarySlots.seclusion.size();++i)
        m_seclusion->setSlot(i,!data.buildings.mercenarySlots.seclusion[i].isEmpty() ? m_mercenaries->getMercenary(m_mercenaries->findMercenary(data.buildings.mercenarySlots.seclusion[i])) : nullptr);

    m_energy=data.resources.energy;//setting resources
    m_foodSupplies=data.resources.foodSupplies;
    m_buildingMaterials=data.resources.buildingMaterials;
    m_aetherite=data.resources.aetheriteOre;

    m_gameClock->clearAlarms();//setting alarms in GameClock
    for (int i=0;i<data.alarms.buildingUpgrades.size();++i)
    {
        m_gameClock->addAlarm(data.alarms.buildingUpgrades[i].first, static_cast<TimerAlarm*>(new BuildingUpgradeTimerAlarm (this,data.alarms.buildingUpgrades[i].second.buildingName(), data.alarms.buildingUpgrades[i].second.buildingLevel())));
    }

    m_gameClock->updateClock({data.overall.lastKnownDay, data.overall.lastKnownHour, data.overall.lastKnownMinute});//setting date and time in GameClock

    m_database->setUnlocksInfo(data.database.unlocks);//database
    m_database->setAreThereNewUnlockedEntries(data.database.areThereNewDBEntries);

    for (const auto &e : data.missions.reports)//reports
        m_reports+=new UnifiedReport{e};

    for (auto e : data.missions.missions)//missions
        m_missions+=MissionBuilder::qobjectifyMissionData(e,this);

    for (int i=0;i<data.alarms.missionEnds.size();++i)//setting alarms in GameClock, part 2
    {
        auto me=data.alarms.missionEnds[i];
        me.second.setBasePtr(this);
        m_gameClock->addAlarm(me.first, static_cast<TimerAlarm*>(new MissionEndTimerAlarm (this,me.second.mission())));
    }
    for (int i=0;i<data.alarms.missionAlarms.size();++i)
    {
        QPair <Time, Mission *> ma;
        ma.first=data.alarms.missionAlarms[i].first;
        for (auto e : m_missions)
            if (e->assignedMercenary()->name() == data.alarms.missionAlarms[i].second)
            {
                ma.second=e;
                break;
            }
        m_gameClock->addMissionAlarm(ma.first,ma.second);
    }
    Game::gameInstance()->loggers()->mainLogger()->trace("Save loaded");
}

SaveData Base::getSaveData() noexcept
{
    SaveData data;

    Game::gameInstance()->loggers()->mainLogger()->trace("Creating save data...");

    data.parserVersion = m_gameObject->currentVersion()->versionNumber();

    data.buildings.levels.centralUnit=m_buildingLevels.value(BuildingEnums::B_CentralUnit,0);
    data.buildings.levels.hospital=m_buildingLevels.value(BuildingEnums::B_Hospital,0);
    data.buildings.levels.trainingGround=m_buildingLevels.value(BuildingEnums::B_TrainingGround,0);
    data.buildings.levels.gym=m_buildingLevels.value(BuildingEnums::B_Gym,0);
    data.buildings.levels.laboratory=m_buildingLevels.value(BuildingEnums::B_Laboratory,0);
    data.buildings.levels.playingField=m_buildingLevels.value(BuildingEnums::B_PlayingField,0);
    data.buildings.levels.bar=m_buildingLevels.value(BuildingEnums::B_Bar,0);
    data.buildings.levels.shrine=m_buildingLevels.value(BuildingEnums::B_Shrine,0);
    data.buildings.levels.seclusion=m_buildingLevels.value(BuildingEnums::B_Seclusion,0);
    data.buildings.levels.powerplant=m_buildingLevels.value(BuildingEnums::B_Powerplant,0);
    data.buildings.levels.factory=m_buildingLevels.value(BuildingEnums::B_Factory,0);
    data.buildings.levels.coolRoom=m_buildingLevels.value(BuildingEnums::B_CoolRoom,0);
    data.buildings.levels.storageRoom=m_buildingLevels.value(BuildingEnums::B_StorageRoom,0);
    data.buildings.levels.aetheriteSilo=m_buildingLevels.value(BuildingEnums::B_AetheriteSilo,0);
    data.buildings.levels.barracks=m_buildingLevels.value(BuildingEnums::B_Barracks,0);
    data.buildings.levels.dockingStation=m_buildingLevels.value(BuildingEnums::B_DockingStation,0);

    data.buildings.cyclesSet.powerplant=m_powerplant->currentCycles();
    data.buildings.cyclesSet.factory=m_factory->currentCycles();

    data.buildings.upgrading.centralUnit=m_centralUnit->isBeingUpgraded();
    data.buildings.upgrading.powerplant=m_powerplant->isBeingUpgraded();
    data.buildings.upgrading.factory=m_factory->isBeingUpgraded();
    data.buildings.upgrading.coolRoom=m_coolRoom->isBeingUpgraded();
    data.buildings.upgrading.storageRoom=m_storageRoom->isBeingUpgraded();
    data.buildings.upgrading.aetheriteSilo=m_aetheriteSilo->isBeingUpgraded();
    data.buildings.upgrading.hospital=m_hospital->isBeingUpgraded();
    data.buildings.upgrading.barracks=m_barracks->isBeingUpgraded();
    data.buildings.upgrading.dockingStation=m_dockingStation->isBeingUpgraded();
    data.buildings.upgrading.trainingGround=m_trainingGround->isBeingUpgraded();
    data.buildings.upgrading.gym=m_gym->isBeingUpgraded();
    data.buildings.upgrading.laboratory=m_laboratory->isBeingUpgraded();
    data.buildings.upgrading.playingField=m_playingField->isBeingUpgraded();
    data.buildings.upgrading.bar=m_bar->isBeingUpgraded();
    data.buildings.upgrading.shrine=m_shrine->isBeingUpgraded();
    data.buildings.upgrading.seclusion=m_seclusion->isBeingUpgraded();

    for (int i=0;i<m_availableEquipment.size();++i)
    {
        if (m_availableEquipment[i]->type()==EquipmentEnums::T_Armor)
            data.equipments.freeArmor.push_back(m_availableEquipment[i]->name());
        else if (m_availableEquipment[i]->type()==EquipmentEnums::T_WeaponTool)
            data.equipments.freeWeaponsTools.push_back(m_availableEquipment[i]->name());
    }

    for (int i=0;i<m_mercenaries->amountOfMercenaries();++i)
        data.mercenaries.hiredMercenaries.push_back(MercenaryBuilder::deqobjectifyMercenary(m_mercenaries->mercenaries()[i]));

    data.buildings.dockingStationThings.recruits=m_dockingStation->getRecruitsNames().toVector();

    data.buildings.dockingStationThings.equipments=m_dockingStation->availableEquipmentsNames();

    for (int i=0;i<m_dockingStation->arrivingMercenaries().size();++i)
        data.buildings.dockingStationThings.arrivingMercenaries.push_back({m_dockingStation->arrivingMercenaries()[i].first->name(), static_cast<quint8>(m_dockingStation->arrivingMercenaries()[i].second)});

    for (int i=0;i<m_dockingStation->arrivingEquipments().size();++i)
        data.buildings.dockingStationThings.arrivingEquipments.push_back({m_dockingStation->arrivingEquipments()[i].first->name(), static_cast<quint8>(m_dockingStation->arrivingEquipments()[i].second)});

    auto actTr=m_dockingStation->activeTransactions();
    for (int i=0;i<actTr.size();++i)
        data.buildings.dockingStationThings.activeResourceTransactions+={actTr[i].first,static_cast<quint8>(actTr[i].second)};

    for (int i=0;i<m_hospital->amountOfSlots();++i)
        data.buildings.mercenarySlots.hospital.push_back(m_hospital->slot(i)!=nullptr ? m_hospital->slot(i)->name() : "");
    for (int i=0;i<m_trainingGround->amountOfSlots();++i)
    {
        auto p=m_trainingGround->slot(i);
        if (p.first!=nullptr)
            data.buildings.mercenarySlots.trainingGround.push_back({p.first->name(), static_cast<quint8>(p.second)});
        else
            data.buildings.mercenarySlots.trainingGround.push_back({"",0});
    }
    for (int i=0;i<m_gym->amountOfSlots();++i)
    {
        auto p=m_gym->slot(i);
        if (p.first!=nullptr)
            data.buildings.mercenarySlots.gym.push_back({p.first->name(), static_cast<quint8>(p.second)});
        else
            data.buildings.mercenarySlots.gym.push_back({"",0});
    }
    for (int i=0;i<m_laboratory->amountOfSlots();++i)
    {
        auto p=m_laboratory->slot(i);
        if (p.first!=nullptr)
            data.buildings.mercenarySlots.laboratory.push_back({p.first->name(), static_cast<quint8>(p.second)});
        else
            data.buildings.mercenarySlots.laboratory.push_back({"",0});
    }
    for (int i=0;i<m_playingField->amountOfSlots();++i)
        data.buildings.mercenarySlots.playingField.push_back(m_playingField->slot(i)!=nullptr ? m_playingField->slot(i)->name() : "");
    for (int i=0;i<m_bar->amountOfSlots();++i)
        data.buildings.mercenarySlots.bar.push_back(m_bar->slot(i)!=nullptr ? m_bar->slot(i)->name() : "");
    for (int i=0;i<m_shrine->amountOfSlots();++i)
        data.buildings.mercenarySlots.shrine.push_back(m_shrine->slot(i)!=nullptr ? m_shrine->slot(i)->name() : "");
    for (int i=0;i<m_seclusion->amountOfSlots();++i)
        data.buildings.mercenarySlots.seclusion.push_back(m_seclusion->slot(i)!=nullptr ? m_seclusion->slot(i)->name() : "");

    data.resources.energy=m_energy;
    data.resources.foodSupplies=m_foodSupplies;
    data.resources.buildingMaterials=m_buildingMaterials;
    data.resources.aetheriteOre=m_aetherite;

    data.overall.lastKnownDay=m_gameClock->currentDay();
    data.overall.lastKnownHour=m_gameClock->currentHour();
    data.overall.lastKnownMinute=m_gameClock->currentMin();

    QVector <QPair<quint8,BuildingUpgradeTimerAlarm>> buTimerAlarms;
    QVector <QPair<quint8,MissionEndTimerAlarm>> meTimerAlarms;
    QVector <QPair<unsigned,TimerAlarm*>> timerAlarms = m_gameClock->getAllAlarms();
    for (int i=0;i<timerAlarms.size();++i)
    {
        if (timerAlarms[i].second->type()==TimerAlarmEnums::AT_BuildingUpgrade)
            buTimerAlarms.push_back({timerAlarms[i].first,*static_cast<BuildingUpgradeTimerAlarm*>(timerAlarms[i].second)});
        else if (timerAlarms[i].second->type()==TimerAlarmEnums::AT_MissionEnd)
            meTimerAlarms.push_back({timerAlarms[i].first,*static_cast<MissionEndTimerAlarm*>(timerAlarms[i].second)});
    }
    data.alarms.buildingUpgrades=buTimerAlarms;
    data.alarms.missionEnds=meTimerAlarms;
    buTimerAlarms.clear();
    meTimerAlarms.clear();

    QVector <QPair <Time, QString> > mals;
    for (auto e : m_gameClock->missionAlarms())
        mals+={e.first,e.second->assignedMercenary()->name()};
    data.alarms.missionAlarms=mals;

    data.database.unlocks=m_database->unlockedEntries();
    data.database.areThereNewDBEntries=m_database->areThereNewEntries();

    for (auto e : m_missions)
        data.missions.missions+=MissionBuilder::deqobjectifyMission(e);

    for (const auto &e : m_reports)
        data.missions.reports+=*e;

    Game::gameInstance()->loggers()->mainLogger()->trace("Saving save data");

    return data;
}

CentralUnit *Base::centralUnit() noexcept
{
    return static_cast<CentralUnit *>(m_buildings.value(BuildingEnums::B_CentralUnit));
}

Hospital *Base::hospital() noexcept
{
    return static_cast<Hospital *>(m_buildings.value(BuildingEnums::B_Hospital));
}

TrainingGround *Base::trainingGround() noexcept
{
    return static_cast<TrainingGround *>(m_buildings.value(BuildingEnums::B_TrainingGround));
}

Gym *Base::gym() noexcept
{
    return static_cast<Gym *>(m_buildings.value(BuildingEnums::B_Gym));
}

Laboratory *Base::laboratory() noexcept
{
    return static_cast<Laboratory *>(m_buildings.value(BuildingEnums::B_Laboratory));
}

PlayingField *Base::playingField() noexcept
{
    return static_cast<PlayingField *>(m_buildings.value(BuildingEnums::B_PlayingField));
}

Bar *Base::bar() noexcept
{
    return static_cast<Bar *>(m_buildings.value(BuildingEnums::B_Bar));
}

Shrine *Base::shrine() noexcept
{
    return static_cast<Shrine *>(m_buildings.value(BuildingEnums::B_Shrine));
}

Seclusion *Base::seclusion() noexcept
{
    return static_cast<Seclusion *>(m_buildings.value(BuildingEnums::B_Seclusion));
}

Powerplant *Base::powerplant() noexcept
{
    return static_cast<Powerplant *>(m_buildings.value(BuildingEnums::B_Powerplant));
}

Factory *Base::factory() noexcept
{
    return static_cast<Factory *>(m_buildings.value(BuildingEnums::B_Factory));
}

CoolRoom *Base::coolRoom() noexcept
{
    return static_cast<CoolRoom *>(m_buildings.value(BuildingEnums::B_CoolRoom));
}

StorageRoom *Base::storageRoom() noexcept
{
    return static_cast<StorageRoom *>(m_buildings.value(BuildingEnums::B_StorageRoom));
}

AetheriteSilo *Base::aetheriteSilo() noexcept
{
    return static_cast<AetheriteSilo *>(m_buildings.value(BuildingEnums::B_AetheriteSilo));
}

Barracks *Base::barracks() noexcept
{
    return static_cast<Barracks *>(m_buildings.value(BuildingEnums::B_Barracks));
}

DockingStation *Base::dockingStation() noexcept
{
    return static_cast<DockingStation *>(m_buildings.value(BuildingEnums::B_DockingStation));
}

void Base::startNewDay() noexcept
{
    Game::gameInstance()->loggers()->mainLogger()->trace("[{}] Starting new day",gameClock()->currentTime().toQString().toStdString());
    if (m_gameClock->currentDay() % 7 == 1)
        startNewWeek();

    handleMercenariesAtDayEnd();

    activateBuildingsAtDayEnd();

    QVector<TimerAlarm *> timeoutedAlarms = m_gameClock->moveToNextDayAndGetTimeoutedResults();

    for (int i=0;i<timeoutedAlarms.size();++i)
    {
        if (timeoutedAlarms[i]->type() == TimerAlarmEnums::AT_BuildingUpgrade)
        {
            auto buta = static_cast<BuildingUpgradeTimerAlarm*>(timeoutedAlarms[i]);
            addReport(new UnifiedReport(new BuildingUpgradeReport(buta->buildingName(), buta->buildingLevel(), m_gameClock->currentTime())));
            m_buildingLevels.insert(buta->buildingName(), buta->buildingLevel());
            m_buildings[buta->buildingName()]->registerUpgradeCompletion();
        }
        else if (timeoutedAlarms[i]->type() == TimerAlarmEnums::AT_MissionEnd)
        {
            auto meta = static_cast<MissionEndTimerAlarm*>(timeoutedAlarms[i]);
            if (!meta->mission()->assignedMercenary()->isDead())
                meta->mission()->end();
            auto mercenary = meta->mission()->assignedMercenary();
            removeMission(meta->mission());
            if (!mercenary->isDead())
                addReport(new UnifiedReport(new MissionEndReport(mercenary->pathToArt(), mercenary->name(), m_gameClock->currentTime())));
        }
    }

    for (int i=0;i<timeoutedAlarms.size();++i)
        delete timeoutedAlarms[i];

    for (auto &e : m_missions)
        e->handleNewDay();

    m_mercenaries->setAmountOfSlots(m_barracks->mercenariesLimit());

    for (auto mercenaryName : m_mercenaryDockingStationBans.keys())
    {
        if (m_mercenaryDockingStationBans.value(mercenaryName)==1)
        {
            m_mercenaryDockingStationBans.erase(m_mercenaryDockingStationBans.find(mercenaryName));
            continue;
        }
        m_mercenaryDockingStationBans.insert(mercenaryName,m_mercenaryDockingStationBans.value(mercenaryName)-1);
    }
    m_dockingStation->doRecrutationStuff();
    m_dockingStation->doBuyingEquipmentStuff();

    m_dockingStation->handleActiveTransactions();

    Game::gameInstance()->loggers()->buildingsLogger()->trace("[{}] Current resources:",gameClock()->currentTime().toQString().toStdString());
    Game::gameInstance()->loggers()->buildingsLogger()->trace("    Aetherite: {}",m_aetherite);
    Game::gameInstance()->loggers()->buildingsLogger()->trace("    Building materials: {}",m_buildingMaterials);
    Game::gameInstance()->loggers()->buildingsLogger()->trace("    Energy: {}",m_energy);
    Game::gameInstance()->loggers()->buildingsLogger()->trace("    Food Supplies: {}",m_foodSupplies);
}

void Base::startNewWeek() noexcept
{
    m_dockingStation->prepareRecruits();
    m_dockingStation->prepareEquipments();

    handleMercenariesAtWeekEnd();
}

BuildingUpgradeRequirements Base::buildingRequirements(BuildingEnums::Building buildingName, unsigned level) const noexcept
{
    return m_buildingRequirements.value({buildingName,level});
}

int Base::currentTotalSalary() const noexcept
{
    int r=0;
    for (auto e : m_mercenaries->mercenaries())
        if (e->currentActivity() != MercenaryEnums::CA_Arriving)
            r+=e->salary();
    return r;
}

void Base::setCurrentEnergyAmount(unsigned amount) noexcept
{
    if (amount <= currentEnergyLimit())
        m_energy = amount;
}

void Base::setCurrentFoodSuppliesAmount(unsigned amount) noexcept
{
    if (amount <= currentFoodSuppliesLimit())
        m_foodSupplies = amount;
}

void Base::setCurrentBuildingMaterialsAmount(unsigned amount) noexcept
{
    if (amount <= currentBuildingMaterialsLimit())
        m_buildingMaterials = amount;
}

void Base::setCurrentAetheriteAmount(unsigned amount) noexcept
{
    if (amount <= currentAetheriteLimit())
        m_aetherite = amount;
}

void Base::decreaseEnergyAmount(unsigned amount) noexcept
{
    m_energy = m_energy>amount ? m_energy-amount : 0;
}

void Base::decreaseFoodSuppliesAmount(unsigned amount) noexcept
{
    m_foodSupplies = m_foodSupplies>amount ? m_foodSupplies-amount : 0;
}

void Base::decreaseBuildingMaterialsAmount(unsigned amount) noexcept
{
    m_buildingMaterials = m_buildingMaterials>amount ? m_buildingMaterials-amount : 0;
}

void Base::decreaseAetheriteAmount(unsigned amount) noexcept
{
    m_aetherite = m_aetherite>amount ? m_aetherite-amount : 0;
}

void Base::increaseEnergyAmount(unsigned amount) noexcept
{
    m_energy = m_energy+amount<currentEnergyLimit() ? m_energy+amount : currentEnergyLimit();
}

void Base::increaseFoodSuppliesAmount(unsigned amount) noexcept
{
    m_foodSupplies = m_foodSupplies+amount<currentFoodSuppliesLimit() ? m_foodSupplies+amount : currentFoodSuppliesLimit();
}

void Base::increaseBuildingMaterialsAmount(unsigned amount) noexcept
{
    m_buildingMaterials = m_buildingMaterials+amount<currentBuildingMaterialsLimit() ? m_buildingMaterials+amount : currentBuildingMaterialsLimit();
}

void Base::increaseAetheriteAmount(unsigned amount) noexcept
{
    m_aetherite = m_aetherite+amount<currentAetheriteLimit() ? m_aetherite+amount : currentAetheriteLimit();
}

int Base::currentEnergyIncome() const noexcept
{
    int r=0;
    for (int i=0;i<static_cast<int>(BuildingEnums::B_END);++i)
        r-=m_buildings.value(static_cast<BuildingEnums::Building>(i))->currentCostInEnergy();
    return r;
}

int Base::currentFoodSuppliesIncome() const noexcept
{
    int r=0;
    for (int i=0;i<static_cast<int>(BuildingEnums::B_END);++i)
        r-=m_buildings.value(static_cast<BuildingEnums::Building>(i))->currentCostInFoodSupplies();
    for (auto e : m_mercenaries->mercenaries())
        r-=e->dailyFoodConsumption();
    return r;
}

int Base::currentBuildingMaterialsIncome() const noexcept
{
    int r=0;
    for (int i=0;i<static_cast<int>(BuildingEnums::B_END);++i)
        r-=m_buildings.value(static_cast<BuildingEnums::Building>(i))->currentCostInBuildingMaterials();
    return r;
}

int Base::currentAetheriteIncome() const noexcept
{
    int r=0;
    for (int i=0;i<static_cast<int>(BuildingEnums::B_END);++i)
        r-=m_buildings.value(static_cast<BuildingEnums::Building>(i))->currentCostInAetherite();
    return r;
}

int Base::currentEnergyLimit() noexcept
{
    return powerplant()->energyLimit();
}

int Base::currentFoodSuppliesLimit() noexcept
{
    return coolRoom()->foodSuppliesLimit();
}

int Base::currentBuildingMaterialsLimit() noexcept
{
    return storageRoom()->buildingMaterialsLimit();
}

int Base::currentAetheriteLimit() noexcept
{
    return aetheriteSilo()->aetheriteLimit();
}

void Base::setBuildingLevel(BuildingEnums::Building buildingName, unsigned level) noexcept
{
    m_buildingLevels.insert(buildingName,level);
}

void Base::setBuildingDescription(BuildingEnums::Building buildingName, const QString &desc) noexcept
{
    m_buildingDescriptions.insert(buildingName,desc);
}

void Base::setBuildingDescriptions(const QVector<QPair<BuildingEnums::Building, QString> > &descs) noexcept
{
    for (int i=0;i<descs.size();++i)
        m_buildingDescriptions.insert(descs[i].first,descs[i].second);
}

void Base::setBuildingRequirements(const QMap<QPair<BuildingEnums::Building, unsigned>, BuildingUpgradeRequirements> &reqs) noexcept
{
    m_buildingRequirements=reqs;
}

Building *Base::getBuilding(BuildingEnums::Building buildingName) noexcept
{
    switch (buildingName) {
    case BuildingEnums::B_AetheriteSilo:
        return m_aetheriteSilo;
    case BuildingEnums::B_Bar:
        return m_bar;
    case BuildingEnums::B_Barracks:
        return m_barracks;
    case BuildingEnums::B_CentralUnit:
        return m_centralUnit;
    case BuildingEnums::B_CoolRoom:
        return m_coolRoom;
    case BuildingEnums::B_DockingStation:
        return m_dockingStation;
    case BuildingEnums::B_Factory:
        return m_factory;
    case BuildingEnums::B_Gym:
        return m_gym;
    case BuildingEnums::B_Hospital:
        return m_hospital;
    case BuildingEnums::B_Laboratory:
        return m_laboratory;
    case BuildingEnums::B_PlayingField:
        return m_playingField;
    case BuildingEnums::B_Powerplant:
        return m_powerplant;
    case BuildingEnums::B_Seclusion:
        return m_seclusion;
    case BuildingEnums::B_Shrine:
        return m_shrine;
    case BuildingEnums::B_StorageRoom:
        return m_storageRoom;
    case BuildingEnums::B_TrainingGround:
        return m_trainingGround;
    default:
        Game::gameInstance()->loggers()->buildingsLogger()->warn("BuildingEnums::Building enum->Building * conversion failed for {}", static_cast<unsigned>(buildingName));
        return nullptr;
    }
}

void Base::recalculateAmountOfMercenarySlots() const noexcept
{
    m_mercenaries->setAmountOfSlots(m_barracks->mercenariesLimit());;
}

unsigned Base::amountOfAvailableArmors() const noexcept
{
    unsigned r=0;
    for (auto e : m_availableEquipment)
        if (e->type() == EquipmentEnums::T_Armor)
            ++r;
    return r;
}

unsigned Base::amountOfAvailableWeaponsTools() const noexcept
{
    unsigned r=0;
    for (auto e : m_availableEquipment)
        if (e->type() == EquipmentEnums::T_WeaponTool)
            ++r;
    return r;
}

void Base::prepareAvailableEquipment(unsigned index) noexcept
{
    if (index<m_availableEquipment.size())
        m_preparedAvailableEquipment=m_availableEquipment[index];
}

void Base::startMission(Mission *mission) noexcept
{
    m_missions+=mission;
    mission->start();
}

void Base::removeMission(Mission *mission) noexcept
{
    for (int i=0;i<m_missions.size();++i)
        if (m_missions[i] == mission)
        {
            delete m_missions[i];
            m_missions.remove(i);
            break;
        }
}

void Base::prepareMission(unsigned index) noexcept
{
    if (index<m_missions.size())
        m_preparedMission=m_missions[index];
}

void Base::prepareReport(unsigned index) noexcept
{
    if (index<m_reports.size())
        m_preparedReport=m_reports[index];
}

void Base::prepareNewReport(unsigned index) noexcept
{
    if (index<m_newReports.size())
        m_preparedReport=m_newReports[index];
}

void Base::addReport(UnifiedReport *report) noexcept
{
    m_reports+=report;
    if (m_reports.size()>m_maxReportsAmount)
    {
        delete m_reports.first();
        m_reports.removeFirst();
    }
    m_newReports+=report;
    if (m_newReports.size()>m_maxReportsAmount)
        m_newReports.removeFirst();
    m_gameObject->showReportNotification();
    Game::gameInstance()->loggers()->mainLogger()->trace("[{}] Received a new report: {}",m_gameClock->currentTime().toQString().toStdString(), report->msg().toStdString());
}

void Base::registerLatestReportInMission(Mission *mission) noexcept
{
    if (m_reports.isEmpty() || mission==nullptr)
        return;

    mission->addRelatedReport(m_reports.last());
}

void Base::markAllAsRead() noexcept
{
    m_newReports.clear();
}

void Base::removeReport(unsigned index) noexcept
{
    if (index<m_reports.size())
    {
        delete m_reports[index];
        m_reports.remove(index);
    }
}

void Base::clearReports() noexcept
{
    m_newReports.clear();
    for (auto &e : m_reports)
        delete e;
    m_reports.clear();
}

int Base::remainingMissionDaysForMercenary(const QString &mercenaryName)
{
    for (const auto &e : m_mercenaries->mercenaries())
        if (e->name() == mercenaryName)
        {
            if (e->currentActivity() != MercenaryEnums::CA_OnMission)
                return -2;
            if (e->isCommunicationAvailable())
                return e->assignedMission()->remainingDays();
            else
                return -1;
        }
    return -3;
}

void Base::activateBuildingsAtDayEnd() noexcept
{
    int basicEnergyCost=0;
    for (int i=0;i<static_cast<int>(BuildingEnums::B_END);++i)
        basicEnergyCost+=m_buildings.value(static_cast<BuildingEnums::Building>(i))->basicCostInEnergy();
    if (basicEnergyCost < m_energy)
        m_energy-=basicEnergyCost;
    else
        m_energy=0;

    bar()->destressMercenaries();
    factory()->exchangeResources();
    gym()->trainMercenaries();
    hospital()->healMercenaries();
    laboratory()->trainMercenaries();
    playingField()->destressMercenaries();
    powerplant()->exchangeResources();
    seclusion()->destressMercenaries();
    shrine()->destressMercenaries();
    trainingGround()->trainMercenaries();
}

void Base::handleMercenariesAtDayEnd() noexcept
{
    m_mercenaries->handleNewDay();
}

void Base::handleMercenariesAtWeekEnd() noexcept
{
    m_mercenaries->handleNewWeek();
}
