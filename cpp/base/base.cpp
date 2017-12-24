#include "base.h"

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
#include "base/managers/buildingsmanager.h"
#include "base/managers/equipmentmanager.h"
#include "base/managers/mercenariesmanager.h"
#include "base/managers/missionsmanager.h"
#include "base/managers/reportsmanager.h"
#include "base/managers/resourcesmanager.h"
#include "clock/gameclock.h"
#include "clock/timer_alarms/buildingupgrade.h"
#include "clock/timer_alarms/missionend.h"
#include "equipment/equipment.h"
#include "file_io/saves/savedata.h"
#include "file_io/saves/saveparser.h"
#include "general/appbuildinfo.h"
#include "general/game.h"
#include "logging/loggersprovider.h"
#include "mercenaries/mercenariescontainer.h"
#include "missions/mission.h"
#include "reports/basereports.h"
#include "reports/missionreports.h"
#include "reports/unifiedreport.h"

Base::Base(Game *gameObject) noexcept
    : QObject(nullptr), m_gameObject(gameObject), m_database(nullptr)
{
    MercenaryBuilder::init(this);

    m_buildingsManager = new BuildingsManager(this);
    m_equipmentManager = new EquipmentManager(this);
    m_mercenariesManager = new MercenariesManager(this);
    m_missionsManager = new MissionsManager(this);
    m_reportsManager = new ReportsManager(this);
    m_resourcesManager = new ResourcesManager(this);

    m_gameClock=new GameClock;
    m_gameClock->setBasePtr(this);

    loadAssets();
}

void Base::setupNewBase() noexcept
{
    resources()->initializeForNewBase();
    buildings()->initializeForNewBase();
    equipment()->initializeForNewBase();
    mercenaries()->initializeForNewBase();
    missions()->initializeForNewBase();
    reports()->initializeForNewBase();

    m_database=m_gameObject->assetsPool().makeStockDatabase();
    LoggersProvider::buildingsLogger()->trace("[{}] Base has been set up",gameClock()->currentTime().toQString().toStdString());
}

Base::~Base() noexcept
{
    delete m_resourcesManager;
    delete m_reportsManager;
    delete m_missionsManager;
    delete m_mercenariesManager;
    delete m_equipmentManager;
    delete m_buildingsManager;

    delete m_gameClock;

    if (m_database!=nullptr)
        delete m_database;
}

void Base::loadSaveData(const SaveData &data) noexcept
{
    LoggersProvider::mainLogger()->trace("Loading save...");
    LoggersProvider::mainLogger()->trace("Save content:");
    LoggersProvider::mainLogger()->trace(QString(data.raw.toHex()).toStdString());
    if (m_database!=nullptr)
        delete m_database;
    m_database=m_gameObject->assetsPool().makeStockDatabase();

    buildings()->centralUnit()->setCurrentLevel(data.buildings.levels.centralUnit);//buildings levels loading
    buildings()->hospital()->setCurrentLevel(data.buildings.levels.hospital);
    buildings()->trainingGround()->setCurrentLevel(data.buildings.levels.trainingGround);
    buildings()->gym()->setCurrentLevel(data.buildings.levels.gym);
    buildings()->laboratory()->setCurrentLevel(data.buildings.levels.laboratory);
    buildings()->playingField()->setCurrentLevel(data.buildings.levels.playingField);
    buildings()->bar()->setCurrentLevel(data.buildings.levels.bar);
    buildings()->shrine()->setCurrentLevel(data.buildings.levels.shrine);
    buildings()->seclusion()->setCurrentLevel(data.buildings.levels.seclusion);
    buildings()->powerplant()->setCurrentLevel(data.buildings.levels.powerplant);
    buildings()->factory()->setCurrentLevel(data.buildings.levels.factory);
    buildings()->coolRoom()->setCurrentLevel(data.buildings.levels.coolRoom);
    buildings()->storageRoom()->setCurrentLevel(data.buildings.levels.storageRoom);
    buildings()->aetheriteSilo()->setCurrentLevel(data.buildings.levels.aetheriteSilo);
    buildings()->barracks()->setCurrentLevel(data.buildings.levels.barracks);
    buildings()->dockingStation()->setCurrentLevel(data.buildings.levels.dockingStation);

    buildings()->hospital()->resizeSlotsAfterUpgrade();//resizing slots in buildings
    buildings()->trainingGround()->resizeSlotsAfterUpgrade();
    buildings()->gym()->resizeSlotsAfterUpgrade();
    buildings()->laboratory()->resizeSlotsAfterUpgrade();
    buildings()->playingField()->resizeSlotsAfterUpgrade();
    buildings()->bar()->resizeSlotsAfterUpgrade();
    buildings()->shrine()->resizeSlotsAfterUpgrade();
    buildings()->seclusion()->resizeSlotsAfterUpgrade();

    for (int i=0;i<data.buildings.dockingStationThings.recruits.size();++i)//loading needed mercenaries in AssetsPool
        m_gameObject->assetsPool().loadMercenaryNamedFromList(data.buildings.dockingStationThings.recruits[i]);
    for (int i=0;i<data.mercenaries.hiredMercenaries.size();++i)
        m_gameObject->assetsPool().loadMercenaryNamedFromList(data.mercenaries.hiredMercenaries[i].name);

    mercenaries()->mercenaries()->setAmountOfSlots(buildings()->m_barracks->mercenariesLimit());//setting mercenaries limit

    buildings()->powerplant()->setCurrentCycles(data.buildings.cyclesSet.powerplant);//setting cycles
    buildings()->factory()->setCurrentCycles(data.buildings.cyclesSet.factory);

    buildings()->centralUnit()->setIsBeingUpgraded(data.buildings.upgrading.centralUnit);//setting upgrades
    buildings()->powerplant()->setIsBeingUpgraded(data.buildings.upgrading.powerplant);
    buildings()->factory()->setIsBeingUpgraded(data.buildings.upgrading.factory);
    buildings()->coolRoom()->setIsBeingUpgraded(data.buildings.upgrading.coolRoom);
    buildings()->storageRoom()->setIsBeingUpgraded(data.buildings.upgrading.storageRoom);
    buildings()->aetheriteSilo()->setIsBeingUpgraded(data.buildings.upgrading.aetheriteSilo);
    buildings()->hospital()->setIsBeingUpgraded(data.buildings.upgrading.hospital);
    buildings()->barracks()->setIsBeingUpgraded(data.buildings.upgrading.barracks);
    buildings()->dockingStation()->setIsBeingUpgraded(data.buildings.upgrading.dockingStation);
    buildings()->trainingGround()->setIsBeingUpgraded(data.buildings.upgrading.trainingGround);
    buildings()->gym()->setIsBeingUpgraded(data.buildings.upgrading.gym);
    buildings()->laboratory()->setIsBeingUpgraded(data.buildings.upgrading.laboratory);
    buildings()->playingField()->setIsBeingUpgraded(data.buildings.upgrading.playingField);
    buildings()->bar()->setIsBeingUpgraded(data.buildings.upgrading.bar);
    buildings()->shrine()->setIsBeingUpgraded(data.buildings.upgrading.shrine);
    buildings()->seclusion()->setIsBeingUpgraded(data.buildings.upgrading.seclusion);

    for (int i=0;i<data.equipments.freeArmor.size();++i)//creating owned equipment
        equipment()->m_availableEquipment.push_back(Game::gameInstance()->assetsPool().makeEquipmentNamed(data.equipments.freeArmor[i]));
    for (int i=0;i<data.equipments.freeWeaponsTools.size();++i)
        equipment()->m_availableEquipment.push_back(Game::gameInstance()->assetsPool().makeEquipmentNamed(data.equipments.freeWeaponsTools[i]));

    for (int i=0;i<data.mercenaries.hiredMercenaries.size();++i)//adding mercenaries
        mercenaries()->mercenaries()->addMercenary(MercenaryBuilder::qobjectifyMercenaryData(data.mercenaries.hiredMercenaries[i]));

    for (int i=0;i<data.buildings.dockingStationThings.recruits.size();++i)//adding possible recruits
        for (int j=0;j<m_gameObject->assetsPool().loadedMercenaries().size();++j)
            if (m_gameObject->assetsPool().loadedMercenaries()[j]->name() == data.buildings.dockingStationThings.recruits[i])
            {
                buildings()->dockingStation()->addRecruitFromSave(m_gameObject->assetsPool().loadedMercenaries()[j]);
                break;
            }

    for (int i=0;i<data.buildings.dockingStationThings.equipments.size();++i)//adding buyable equipments
        buildings()->dockingStation()->addEquipmentFromSave(m_gameObject->assetsPool().makeEquipmentNamed(data.buildings.dockingStationThings.equipments[i]));

    for (int i=0;i<data.buildings.dockingStationThings.arrivingMercenaries.size();++i)//adding arriving mercenaries
        for (int j=0;j<mercenaries()->mercenaries()->amountOfMercenaries();++j)
            if (mercenaries()->m_mercenaries->getMercenary(j)->name() == data.buildings.dockingStationThings.arrivingMercenaries[i].first)
            {
                buildings()->dockingStation()->addArrivingMercenaryFromSave({mercenaries()->m_mercenaries->getMercenary(j),static_cast<unsigned>(data.buildings.dockingStationThings.arrivingMercenaries[i].second)});
                break;
            }

    for (int i=0;i<data.buildings.dockingStationThings.arrivingEquipments.size();++i)//adding arriving equipments
        for (int j=0;j<m_gameObject->assetsPool().equipment().size();++j)
            if (m_gameObject->assetsPool().equipment()[j]->name() == data.buildings.dockingStationThings.arrivingEquipments[i].first)
            {
                buildings()->dockingStation()->addArrivingEquipmentFromSave({m_gameObject->assetsPool().equipment()[j],static_cast<unsigned>(data.buildings.dockingStationThings.arrivingEquipments[i].second)});
                break;
            }

    QVector <QPair <ActiveTransaction, unsigned> > actTr;
    for (int i=0;i<data.buildings.dockingStationThings.activeResourceTransactions.size();++i)//set active resource transactions
        actTr+={data.buildings.dockingStationThings.activeResourceTransactions[i].first, static_cast<unsigned>(data.buildings.dockingStationThings.activeResourceTransactions[i].second)};
    buildings()->dockingStation()->setActiveTransactionsFromSave(actTr);

    for (int i=0;i<data.buildings.mercenarySlots.hospital.size();++i)//setting slots in buildings
        buildings()->hospital()->setSlot(i,!data.buildings.mercenarySlots.hospital[i].isEmpty() ? mercenaries()->mercenaries()->getMercenary(mercenaries()->mercenaries()->findMercenary(data.buildings.mercenarySlots.hospital[i])) : nullptr);
    for (int i=0;i<data.buildings.mercenarySlots.trainingGround.size();++i)
        buildings()->trainingGround()->setSlot(i,!data.buildings.mercenarySlots.trainingGround[i].first.isEmpty() ? mercenaries()->mercenaries()->getMercenary(mercenaries()->m_mercenaries->findMercenary(data.buildings.mercenarySlots.trainingGround[i].first)) : nullptr, static_cast<unsigned>(data.buildings.mercenarySlots.trainingGround[i].second));
    for (int i=0;i<data.buildings.mercenarySlots.gym.size();++i)
        buildings()->gym()->setSlot(i,!data.buildings.mercenarySlots.gym[i].first.isEmpty() ? mercenaries()->mercenaries()->getMercenary(mercenaries()->mercenaries()->findMercenary(data.buildings.mercenarySlots.gym[i].first)) : nullptr, static_cast<unsigned>(data.buildings.mercenarySlots.gym[i].second));
    for (int i=0;i<data.buildings.mercenarySlots.laboratory.size();++i)
        buildings()->laboratory()->setSlot(i,!data.buildings.mercenarySlots.laboratory[i].first.isEmpty() ? mercenaries()->mercenaries()->getMercenary(mercenaries()->mercenaries()->findMercenary(data.buildings.mercenarySlots.laboratory[i].first)) : nullptr, static_cast<unsigned>(data.buildings.mercenarySlots.laboratory[i].second));
    for (int i=0;i<data.buildings.mercenarySlots.playingField.size();++i)
        buildings()->playingField()->setSlot(i,!data.buildings.mercenarySlots.playingField[i].isEmpty() ? mercenaries()->mercenaries()->getMercenary(mercenaries()->mercenaries()->findMercenary(data.buildings.mercenarySlots.playingField[i])) : nullptr);
    for (int i=0;i<data.buildings.mercenarySlots.bar.size();++i)
        buildings()->bar()->setSlot(i,!data.buildings.mercenarySlots.bar[i].isEmpty() ? mercenaries()->mercenaries()->getMercenary(mercenaries()->mercenaries()->findMercenary(data.buildings.mercenarySlots.bar[i])) : nullptr);
    for (int i=0;i<data.buildings.mercenarySlots.shrine.size();++i)
        buildings()->shrine()->setSlot(i,!data.buildings.mercenarySlots.shrine[i].isEmpty() ? mercenaries()->mercenaries()->getMercenary(mercenaries()->mercenaries()->findMercenary(data.buildings.mercenarySlots.shrine[i])) : nullptr);
    for (int i=0;i<data.buildings.mercenarySlots.seclusion.size();++i)
        buildings()->seclusion()->setSlot(i,!data.buildings.mercenarySlots.seclusion[i].isEmpty() ? mercenaries()->mercenaries()->getMercenary(mercenaries()->mercenaries()->findMercenary(data.buildings.mercenarySlots.seclusion[i])) : nullptr);

    resources()->m_energy=data.resources.energy;//setting resources
    resources()->m_foodSupplies=data.resources.foodSupplies;
    resources()->m_buildingMaterials=data.resources.buildingMaterials;
    resources()->m_aetherite=data.resources.aetheriteOre;

    m_gameClock->clearAlarms();//setting alarms in GameClock
    for (int i=0;i<data.alarms.buildingUpgrades.size();++i)
    {
        m_gameClock->addAlarm(data.alarms.buildingUpgrades[i].first, static_cast<TimerAlarm*>(new BuildingUpgradeTimerAlarm (this,data.alarms.buildingUpgrades[i].second.buildingName(), data.alarms.buildingUpgrades[i].second.buildingLevel())));
    }

    m_gameClock->updateClock({data.overall.lastKnownDay, data.overall.lastKnownHour, data.overall.lastKnownMinute});//setting date and time in GameClock

    m_database->setUnlocksInfo(data.database.unlocks);//database
    m_database->setAreThereNewUnlockedEntries(data.database.areThereNewDBEntries);

    for (const auto &e : data.missions.reports)//reports
        reports()->m_reports+=new UnifiedReport{e};

    for (auto e : data.missions.missions)//missions
        missions()->m_missions+=MissionBuilder::qobjectifyMissionData(e,this);

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
        for (auto e : missions()->m_missions)
            if (e->assignedMercenary()->name() == data.alarms.missionAlarms[i].second)
            {
                ma.second=e;
                break;
            }
        m_gameClock->addMissionAlarm(ma.first,ma.second);
    }
    LoggersProvider::mainLogger()->trace("Save loaded");
}

SaveData Base::getSaveData() noexcept
{
    SaveData data;

    LoggersProvider::mainLogger()->trace("Creating save data...");

    data.parserVersion = m_gameObject->currentVersion()->versionNumber();

    data.buildings.levels.centralUnit=buildings()->centralUnit()->currentLevel();
    data.buildings.levels.hospital=buildings()->hospital()->currentLevel();
    data.buildings.levels.trainingGround=buildings()->trainingGround()->currentLevel();
    data.buildings.levels.gym=buildings()->gym()->currentLevel();
    data.buildings.levels.laboratory=buildings()->laboratory()->currentLevel();
    data.buildings.levels.playingField=buildings()->playingField()->currentLevel();
    data.buildings.levels.bar=buildings()->bar()->currentLevel();
    data.buildings.levels.shrine=buildings()->shrine()->currentLevel();
    data.buildings.levels.seclusion=buildings()->seclusion()->currentLevel();
    data.buildings.levels.powerplant=buildings()->powerplant()->currentLevel();
    data.buildings.levels.factory=buildings()->factory()->currentLevel();
    data.buildings.levels.coolRoom=buildings()->coolRoom()->currentLevel();
    data.buildings.levels.storageRoom=buildings()->storageRoom()->currentLevel();
    data.buildings.levels.aetheriteSilo=buildings()->aetheriteSilo()->currentLevel();
    data.buildings.levels.barracks=buildings()->barracks()->currentLevel();
    data.buildings.levels.dockingStation=buildings()->dockingStation()->currentLevel();

    data.buildings.cyclesSet.powerplant=buildings()->m_powerplant->currentCycles();
    data.buildings.cyclesSet.factory=buildings()->m_factory->currentCycles();

    data.buildings.upgrading.centralUnit=buildings()->m_centralUnit->isBeingUpgraded();
    data.buildings.upgrading.powerplant=buildings()->m_powerplant->isBeingUpgraded();
    data.buildings.upgrading.factory=buildings()->m_factory->isBeingUpgraded();
    data.buildings.upgrading.coolRoom=buildings()->m_coolRoom->isBeingUpgraded();
    data.buildings.upgrading.storageRoom=buildings()->m_storageRoom->isBeingUpgraded();
    data.buildings.upgrading.aetheriteSilo=buildings()->m_aetheriteSilo->isBeingUpgraded();
    data.buildings.upgrading.hospital=buildings()->m_hospital->isBeingUpgraded();
    data.buildings.upgrading.barracks=buildings()->m_barracks->isBeingUpgraded();
    data.buildings.upgrading.dockingStation=buildings()->m_dockingStation->isBeingUpgraded();
    data.buildings.upgrading.trainingGround=buildings()->m_trainingGround->isBeingUpgraded();
    data.buildings.upgrading.gym=buildings()->m_gym->isBeingUpgraded();
    data.buildings.upgrading.laboratory=buildings()->m_laboratory->isBeingUpgraded();
    data.buildings.upgrading.playingField=buildings()->m_playingField->isBeingUpgraded();
    data.buildings.upgrading.bar=buildings()->m_bar->isBeingUpgraded();
    data.buildings.upgrading.shrine=buildings()->m_shrine->isBeingUpgraded();
    data.buildings.upgrading.seclusion=buildings()->m_seclusion->isBeingUpgraded();

    for (int i=0;i<equipment()->m_availableEquipment.size();++i)
    {
        if (equipment()->m_availableEquipment[i]->type()==EquipmentEnums::T_Armor)
            data.equipments.freeArmor.push_back(equipment()->m_availableEquipment[i]->name());
        else if (equipment()->m_availableEquipment[i]->type()==EquipmentEnums::T_WeaponTool)
            data.equipments.freeWeaponsTools.push_back(equipment()->m_availableEquipment[i]->name());
    }

    for (int i=0;i<mercenaries()->m_mercenaries->amountOfMercenaries();++i)
        data.mercenaries.hiredMercenaries.push_back(MercenaryBuilder::deqobjectifyMercenary(mercenaries()->m_mercenaries->mercenaries()[i]));

    data.buildings.dockingStationThings.recruits=buildings()->m_dockingStation->getRecruitsNames().toVector();

    data.buildings.dockingStationThings.equipments=buildings()->m_dockingStation->availableEquipmentsNames();

    for (int i=0;i<buildings()->m_dockingStation->arrivingMercenaries().size();++i)
        data.buildings.dockingStationThings.arrivingMercenaries.push_back({buildings()->m_dockingStation->arrivingMercenaries()[i].first->name(), static_cast<quint8>(buildings()->m_dockingStation->arrivingMercenaries()[i].second)});

    for (int i=0;i<buildings()->m_dockingStation->arrivingEquipments().size();++i)
        data.buildings.dockingStationThings.arrivingEquipments.push_back({buildings()->m_dockingStation->arrivingEquipments()[i].first->name(), static_cast<quint8>(buildings()->m_dockingStation->arrivingEquipments()[i].second)});

    auto actTr=buildings()->m_dockingStation->activeTransactions();
    for (int i=0;i<actTr.size();++i)
        data.buildings.dockingStationThings.activeResourceTransactions+={actTr[i].first,static_cast<quint8>(actTr[i].second)};

    for (int i=0;i<buildings()->m_hospital->amountOfSlots();++i)
        data.buildings.mercenarySlots.hospital.push_back(buildings()->m_hospital->slot(i)!=nullptr ? buildings()->m_hospital->slot(i)->name() : "");
    for (int i=0;i<buildings()->m_trainingGround->amountOfSlots();++i)
    {
        auto p=buildings()->m_trainingGround->slot(i);
        if (p.first!=nullptr)
            data.buildings.mercenarySlots.trainingGround.push_back({p.first->name(), static_cast<quint8>(p.second)});
        else
            data.buildings.mercenarySlots.trainingGround.push_back({"",0});
    }
    for (int i=0;i<buildings()->m_gym->amountOfSlots();++i)
    {
        auto p=buildings()->m_gym->slot(i);
        if (p.first!=nullptr)
            data.buildings.mercenarySlots.gym.push_back({p.first->name(), static_cast<quint8>(p.second)});
        else
            data.buildings.mercenarySlots.gym.push_back({"",0});
    }
    for (int i=0;i<buildings()->m_laboratory->amountOfSlots();++i)
    {
        auto p=buildings()->m_laboratory->slot(i);
        if (p.first!=nullptr)
            data.buildings.mercenarySlots.laboratory.push_back({p.first->name(), static_cast<quint8>(p.second)});
        else
            data.buildings.mercenarySlots.laboratory.push_back({"",0});
    }
    for (int i=0;i<buildings()->m_playingField->amountOfSlots();++i)
        data.buildings.mercenarySlots.playingField.push_back(buildings()->m_playingField->slot(i)!=nullptr ? buildings()->m_playingField->slot(i)->name() : "");
    for (int i=0;i<buildings()->m_bar->amountOfSlots();++i)
        data.buildings.mercenarySlots.bar.push_back(buildings()->m_bar->slot(i)!=nullptr ? buildings()->m_bar->slot(i)->name() : "");
    for (int i=0;i<buildings()->m_shrine->amountOfSlots();++i)
        data.buildings.mercenarySlots.shrine.push_back(buildings()->m_shrine->slot(i)!=nullptr ? buildings()->m_shrine->slot(i)->name() : "");
    for (int i=0;i<buildings()->m_seclusion->amountOfSlots();++i)
        data.buildings.mercenarySlots.seclusion.push_back(buildings()->m_seclusion->slot(i)!=nullptr ? buildings()->m_seclusion->slot(i)->name() : "");

    data.resources.energy=resources()->m_energy;
    data.resources.foodSupplies=resources()->m_foodSupplies;
    data.resources.buildingMaterials=resources()->m_buildingMaterials;
    data.resources.aetheriteOre=resources()->m_aetherite;

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

    for (auto e : missions()->m_missions)
        data.missions.missions+=MissionBuilder::deqobjectifyMission(e);

    for (const auto &e : reports()->m_reports)
        data.missions.reports+=*e;

    LoggersProvider::mainLogger()->trace("Saving save data");

    return data;
}

void Base::startNewDay() noexcept
{
    LoggersProvider::mainLogger()->trace("[{}] Starting new day",gameClock()->currentTime().toQString().toStdString());
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
            reports()->addReport(new UnifiedReport(new BuildingUpgradeReport(buta->buildingName(), buta->buildingLevel(), m_gameClock->currentTime())));
            buildings()->getBuilding(buta->buildingName())->setCurrentLevel(buta->buildingLevel());
            buildings()->m_buildings[buta->buildingName()]->registerUpgradeCompletion();
        }
        else if (timeoutedAlarms[i]->type() == TimerAlarmEnums::AT_MissionEnd)
        {
            auto meta = static_cast<MissionEndTimerAlarm*>(timeoutedAlarms[i]);
            if (!meta->mission()->assignedMercenary()->isDead())
                meta->mission()->end();
            auto mercenary = meta->mission()->assignedMercenary();
            missions()->removeMission(meta->mission());
            if (!mercenary->isDead())
                reports()->addReport(new UnifiedReport(new MissionEndReport(mercenary->pathToArt(), mercenary->name(), m_gameClock->currentTime())));
        }
    }

    for (int i=0;i<timeoutedAlarms.size();++i)
        delete timeoutedAlarms[i];

    for (auto &e : missions()->m_missions)
        e->handleNewDay();

    mercenaries()->m_mercenaries->setAmountOfSlots(buildings()->m_barracks->mercenariesLimit());

    for (auto mercenaryName : mercenaries()->m_mercenaryDockingStationBans.keys())
    {
        if (mercenaries()->m_mercenaryDockingStationBans.value(mercenaryName)==1)
        {
            mercenaries()->m_mercenaryDockingStationBans.erase(mercenaries()->m_mercenaryDockingStationBans.find(mercenaryName));
            continue;
        }
        mercenaries()->m_mercenaryDockingStationBans.insert(mercenaryName, mercenaries()->m_mercenaryDockingStationBans.value(mercenaryName)-1);
    }
    buildings()->m_dockingStation->doRecrutationStuff();
    buildings()->m_dockingStation->doBuyingEquipmentStuff();

    buildings()->m_dockingStation->handleActiveTransactions();

    LoggersProvider::buildingsLogger()->trace("[{}] Current resources:",gameClock()->currentTime().toQString().toStdString());
    LoggersProvider::buildingsLogger()->trace("    Aetherite: {}",resources()->m_aetherite);
    LoggersProvider::buildingsLogger()->trace("    Building materials: {}",resources()->m_buildingMaterials);
    LoggersProvider::buildingsLogger()->trace("    Energy: {}",resources()->m_energy);
    LoggersProvider::buildingsLogger()->trace("    Food Supplies: {}",resources()->m_foodSupplies);
}

void Base::startNewWeek() noexcept
{
    buildings()->m_dockingStation->prepareRecruits();
    buildings()->m_dockingStation->prepareEquipments();

    handleMercenariesAtWeekEnd();
}

void Base::activateBuildingsAtDayEnd() noexcept
{
    int basicEnergyCost=0;
    for (int i=0;i<static_cast<int>(BuildingEnums::B_END);++i)
        basicEnergyCost+=buildings()->m_buildings.value(static_cast<BuildingEnums::Building>(i))->basicCostInEnergy();
    if (basicEnergyCost < resources()->m_energy)
        resources()->m_energy-=basicEnergyCost;
    else
        resources()->m_energy=0;

    buildings()->bar()->destressMercenaries();
    buildings()->factory()->exchangeResources();
    buildings()->gym()->trainMercenaries();
    buildings()->hospital()->healMercenaries();
    buildings()->laboratory()->trainMercenaries();
    buildings()->playingField()->destressMercenaries();
    buildings()->powerplant()->exchangeResources();
    buildings()->seclusion()->destressMercenaries();
    buildings()->shrine()->destressMercenaries();
    buildings()->trainingGround()->trainMercenaries();
}

void Base::handleMercenariesAtDayEnd() noexcept
{
    mercenaries()->m_mercenaries->handleNewDay();
}

void Base::handleMercenariesAtWeekEnd() noexcept
{
    mercenaries()->m_mercenaries->handleNewWeek();
}

void Base::loadAssets() noexcept
{
    buildings()->setBuildingRequirements(m_gameObject->assetsPool().buildingUpgradeRequirements());
    buildings()->setBuildingDescriptions(m_gameObject->assetsPool().buildingDescriptions());
    buildings()->m_dockingStation->setTradingTables(m_gameObject->assetsPool().dockingStationTradingTables());
}
