#include "h4x.h"

#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>

#include "base/base.h"
#include "base/buildings/specific/other/dockingstation.h"
#include "base/managers/buildingsmanager.h"
#include "base/managers/mercenariesmanager.h"
#include "base/managers/reportsmanager.h"
#include "base/managers/resourcesmanager.h"
#include "clock/gameclock.h"
#include "clock/timer_alarms/buildingupgrade.h"
#include "clock/timer_alarms/timeralarm.h"
#include "database/database.h"
#include "general/game.h"
#include "mercenaries/mercenariescontainer.h"
#include "missions/mission.h"
#include "reports/missionreports.h"
#include "reports/unifiedreport.h"

#ifdef ENABLE_CONSOLE_WINDOW
bool MainWindowEventFilter::eventFilter(QObject *obj, QEvent *event) noexcept
{
    if (!*m_lock)
    {
        *m_lock = 1;
        if (event->type() == QEvent::Close)
            QMetaObject::invokeMethod(m_consoleWindow, "close");
        else if (event->type() == QEvent::Show)
            QMetaObject::invokeMethod(m_consoleWindow, "show");//doesn't work...
        else if (event->type() == QEvent::Hide)
            QMetaObject::invokeMethod(m_consoleWindow, "hide");//that too
        *m_lock = 0;
    }
    return QObject::eventFilter(obj, event);
}

bool ConsoleWindowEventFilter::eventFilter(QObject *obj, QEvent *event) noexcept
{
    if (!*m_lock)
    {
        *m_lock = 1;
        if (event->type() == QEvent::Close)
            QMetaObject::invokeMethod(m_mainWindow, "close");
        else if (event->type() == QEvent::Show)
            QMetaObject::invokeMethod(m_mainWindow, "show");//and that
        else if (event->type() == QEvent::Hide)
            QMetaObject::invokeMethod(m_mainWindow, "hide");//and that
        *m_lock = 0;
    }
    return QObject::eventFilter(obj, event);
}
#endif

H4X::H4X(QQmlApplicationEngine *engine)
    : m_autoUpdate(1)
{
    m_qmlEngine = engine;
    _h4xQmlEngine = engine;
}

H4X::H4X()
{
    m_qmlEngine = _h4xQmlEngine;
}

void H4X::doTimeTravel(int days, int hours, int minutes) noexcept
{
    int mins = (days*24 + hours)*60 + minutes;
    if (mins > 0)
        Game::gameInstance()->m_base->m_gameClock->updateClock(mins);
}

void H4X::speedUpTime(float multiplier) noexcept
{
    Game::gameInstance()->m_base->m_gameClock->m_realMinutesToOneGameDayRatio /= multiplier;
    QObject *win = m_qmlEngine->rootObjects().value(0);
    win->setProperty("gameTimerInterval",win->property("gameTimerInterval").toInt() / multiplier);
}

void H4X::slowDownTime(float multiplier) noexcept
{
    Game::gameInstance()->m_base->m_gameClock->m_realMinutesToOneGameDayRatio *= multiplier;
    QObject *win = m_qmlEngine->rootObjects().value(0);
    win->setProperty("gameTimerInterval",win->property("gameTimerInterval").toInt() * multiplier);
}

void H4X::freezeTime() noexcept
{
    QObject *win = m_qmlEngine->rootObjects().value(0);
    win->setProperty("gameTimerRunning",false);
}

void H4X::unfreezeTime() noexcept
{
    QObject *win = m_qmlEngine->rootObjects().value(0);
    win->setProperty("gameTimerRunning",true);
}

void H4X::setAetherite(unsigned amount) noexcept
{
    Game::gameInstance()->m_base->resources()->m_aetherite = amount;
}

void H4X::setBuildingMaterials(unsigned amount) noexcept
{
    Game::gameInstance()->m_base->resources()->m_buildingMaterials = amount;
}

void H4X::setEnergy(unsigned amount) noexcept
{
    Game::gameInstance()->m_base->resources()->m_energy = amount;
}

void H4X::setFoodSupplies(unsigned amount) noexcept
{
    Game::gameInstance()->m_base->resources()->m_foodSupplies = amount;
}

void H4X::refill() noexcept
{
    Game::gameInstance()->m_base->resources()->m_aetherite = Game::gameInstance()->m_base->resources()->currentAetheriteLimit();
    Game::gameInstance()->m_base->resources()->m_buildingMaterials = Game::gameInstance()->m_base->resources()->currentBuildingMaterialsLimit();
    Game::gameInstance()->m_base->resources()->m_energy = Game::gameInstance()->m_base->resources()->currentEnergyLimit();
    Game::gameInstance()->m_base->resources()->m_foodSupplies = Game::gameInstance()->m_base->resources()->currentFoodSuppliesLimit();
}

void H4X::getFreshMeat() noexcept
{
    Game::gameInstance()->m_base->buildings()->dockingStation()->prepareRecruits();
}

void H4X::getNewStuff() noexcept
{
    Game::gameInstance()->m_base->buildings()->dockingStation()->prepareEquipments();
}

void H4X::upgradeBuilding(const QString &buildingName) noexcept
{
    setBuildingLevel(buildingName,Game::gameInstance()->m_base->buildings()->buildingLevel(BuildingEnums::fromQStringToBuildingEnum(buildingName)) + 1);
}

void H4X::setBuildingLevel(const QString &buildingName, unsigned level) noexcept
{
    if (level > Game::gameInstance()->m_base->buildings()->getBuilding(BuildingEnums::fromQStringToBuildingEnum(buildingName))->maxLevel())
        return;

    Game::gameInstance()->m_base->buildings()->setBuildingLevel(BuildingEnums::fromQStringToBuildingEnum(buildingName),level);

    if (Game::gameInstance()->m_base->buildings()->getBuilding(BuildingEnums::fromQStringToBuildingEnum(buildingName))->isBeingUpgraded())
    {
        auto clock = Game::gameInstance()->m_base->m_gameClock;
        auto als = clock->getAllAlarms();
        for (int i=0;i < als.size();++i)
            if (als[i].second->type() == TimerAlarmEnums::AT_BuildingUpgrade && static_cast < BuildingUpgradeTimerAlarm*>(als[i].second)->buildingName() == BuildingEnums::fromQStringToBuildingEnum(buildingName))
            {
                clock->cancelAlarmAtPos(i);
                break;//upgrade status removed
            }
    }
    Game::gameInstance()->m_base->buildings()->getBuilding(BuildingEnums::fromQStringToBuildingEnum(buildingName))->registerUpgradeCompletion();//slots resized

    Game::gameInstance()->m_base->mercenaries()->recalculateAmountOfMercenarySlots();//barracks slots
}

void H4X::completeUpgrade(const QString &buildingName) noexcept
{
    if (Game::gameInstance()->m_base->buildings()->getBuilding(BuildingEnums::fromQStringToBuildingEnum(buildingName))->isBeingUpgraded())
        upgradeBuilding(buildingName);//+1
}

void H4X::burnItDown() noexcept
{
    auto clock = Game::gameInstance()->m_base->m_gameClock;
    auto als = clock->getAllAlarms();
    for (int i=0;i < als.size();++i)
        if (als[i].second->type() == TimerAlarmEnums::AT_BuildingUpgrade)
            clock->cancelAlarmAtPos(i);//remove all upgrade statuses

    Game::gameInstance()->m_base->buildings()->getBuilding(BuildingEnums::B_CentralUnit)->setCurrentLevel(1);
    Game::gameInstance()->m_base->buildings()->getBuilding(BuildingEnums::B_Hospital)->setCurrentLevel(0);
    Game::gameInstance()->m_base->buildings()->getBuilding(BuildingEnums::B_TrainingGround)->setCurrentLevel(0);
    Game::gameInstance()->m_base->buildings()->getBuilding(BuildingEnums::B_Gym)->setCurrentLevel(0);
    Game::gameInstance()->m_base->buildings()->getBuilding(BuildingEnums::B_Laboratory)->setCurrentLevel(0);
    Game::gameInstance()->m_base->buildings()->getBuilding(BuildingEnums::B_PlayingField)->setCurrentLevel(0);
    Game::gameInstance()->m_base->buildings()->getBuilding(BuildingEnums::B_Bar)->setCurrentLevel(0);
    Game::gameInstance()->m_base->buildings()->getBuilding(BuildingEnums::B_Shrine)->setCurrentLevel(0);
    Game::gameInstance()->m_base->buildings()->getBuilding(BuildingEnums::B_Seclusion)->setCurrentLevel(0);
    Game::gameInstance()->m_base->buildings()->getBuilding(BuildingEnums::B_Powerplant)->setCurrentLevel(1);
    Game::gameInstance()->m_base->buildings()->getBuilding(BuildingEnums::B_Factory)->setCurrentLevel(1);
    Game::gameInstance()->m_base->buildings()->getBuilding(BuildingEnums::B_CoolRoom)->setCurrentLevel(1);
    Game::gameInstance()->m_base->buildings()->getBuilding(BuildingEnums::B_StorageRoom)->setCurrentLevel(1);
    Game::gameInstance()->m_base->buildings()->getBuilding(BuildingEnums::B_AetheriteSilo)->setCurrentLevel(1);
    Game::gameInstance()->m_base->buildings()->getBuilding(BuildingEnums::B_Barracks)->setCurrentLevel(1);
    Game::gameInstance()->m_base->buildings()->getBuilding(BuildingEnums::B_DockingStation)->setCurrentLevel(1);
}

void H4X::setMercenaryAttribute(const QString &mercenaryName, const QString &attribute, QVariant value) noexcept
{
    int pos = Game::gameInstance()->m_base->mercenaries()->mercenaries()->findMercenary(mercenaryName);
    if (pos==-1)
        return;

    Game::gameInstance()->m_base->mercenaries()->mercenaries()->getMercenary(pos)->setAttributeValue(MercenaryEnums::fromQStringToAttributeEnum(attribute),value);
}

void H4X::hire(const QString &mercenaryName) noexcept
{
    if (Game::gameInstance()->m_base->buildings()->dockingStation()->getRecruitsNames().contains(mercenaryName))
    {
        Game::gameInstance()->m_base->buildings()->dockingStation()->hireMercenary(mercenaryName,0);
    }
    else
    {
        if (Game::gameInstance()->m_base->mercenaries()->mercenaries()->canAddMercenary())
        {
            if (Game::gameInstance()->assetsPool().allMercenaries().contains(mercenaryName))
            {
                Game::gameInstance()->assetsPool().loadMercenaryNamedFromList(mercenaryName);
                for (int i=0;i < Game::gameInstance()->assetsPool().loadedMercenaries().size();++i)
                    if (Game::gameInstance()->assetsPool().loadedMercenaries()[i]->name() == mercenaryName)
                    {
                        Game::gameInstance()->m_base->mercenaries()->mercenaries()->addMercenary(Game::gameInstance()->assetsPool().loadedMercenaries()[i]);
                        break;
                    }
            }
        }
    }
}

void H4X::kill(const QString &mercenaryName) noexcept
{
    for (int i=0;i < Game::gameInstance()->m_base->mercenaries()->mercenaries()->amountOfMercenaries();++i)
        if (Game::gameInstance()->m_base->mercenaries()->mercenaries()->getMercenary(i)->name() == mercenaryName && !Game::gameInstance()->m_base->mercenaries()->mercenaries()->getMercenary(i)->isDead())
        {
            Game::gameInstance()->m_base->mercenaries()->mercenaries()->getMercenary(i)->die();
            break;
        }
}

void H4X::dismiss(const QString &mercenaryName, unsigned banTime) noexcept
{
    for (int i=0;i < Game::gameInstance()->m_base->mercenaries()->mercenaries()->amountOfMercenaries();++i)
        if (Game::gameInstance()->m_base->mercenaries()->mercenaries()->getMercenary(i)->name() == mercenaryName && !Game::gameInstance()->m_base->mercenaries()->mercenaries()->getMercenary(i)->isDead())
        {
            Game::gameInstance()->m_base->mercenaries()->mercenaries()->getMercenary(i)->dismiss(banTime);
            break;
        }
}

void H4X::killThemAll() noexcept
{
    for (int i=0;i < Game::gameInstance()->m_base->mercenaries()->mercenaries()->amountOfMercenaries();)
    {
        if (!Game::gameInstance()->m_base->mercenaries()->mercenaries()->getMercenary(i)->isDead())
            Game::gameInstance()->m_base->mercenaries()->mercenaries()->getMercenary(i)->die();
        else
            ++i;
    }
}

void H4X::engulfThemInPain() noexcept
{
    for (int i=0;i < Game::gameInstance()->m_base->mercenaries()->mercenaries()->amountOfMercenaries();++i)
        if (!Game::gameInstance()->m_base->mercenaries()->mercenaries()->getMercenary(i)->isDead())
            Game::gameInstance()->m_base->mercenaries()->mercenaries()->getMercenary(i)->m_currentAttributesValues.health = 1;
}

void H4X::chaosComesForYou() noexcept
{
    for (int i=0;i < Game::gameInstance()->m_base->mercenaries()->mercenaries()->amountOfMercenaries();++i)
        if (!Game::gameInstance()->m_base->mercenaries()->mercenaries()->getMercenary(i)->isDead())
        {
            Game::gameInstance()->m_base->mercenaries()->mercenaries()->getMercenary(i)->m_currentAttributesValues.stress = Game::gameInstance()->m_base->mercenaries()->mercenaries()->getMercenary(i)->m_currentAttributesValues.stressLimit-1;
            if (!Game::gameInstance()->m_base->mercenaries()->mercenaries()->getMercenary(i)->isStressBorderEffectActive())
                Game::gameInstance()->m_base->mercenaries()->mercenaries()->getMercenary(i)->activateStressBorderEffect();
        }
}

void H4X::setMercenaryVariable(const QString &mercenaryName, const QString &varName, QVariant value) noexcept
{
    for (int i=0;i < Game::gameInstance()->m_base->mercenaries()->mercenaries()->amountOfMercenaries();++i)
        if (Game::gameInstance()->m_base->mercenaries()->mercenaries()->getMercenary(i)->name() == mercenaryName)
        {
            if (varName == "noSignalDays")
                Game::gameInstance()->m_base->mercenaries()->mercenaries()->getMercenary(i)->setNoSignalDaysRemaining(value.toInt());
            else if (varName == "isDead")
                Game::gameInstance()->m_base->mercenaries()->mercenaries()->getMercenary(i)->setIsDead(value.toBool());
            else if (varName == "carriedAetherite")
                Game::gameInstance()->m_base->mercenaries()->mercenaries()->getMercenary(i)->setCarriedAetheriteOre(value.toUInt());
            else if (varName == "carriedBuildingMaterials")
                Game::gameInstance()->m_base->mercenaries()->mercenaries()->getMercenary(i)->setCarriedBuildingMaterials(value.toUInt());
            else if (varName == "carriedEnergy")
                Game::gameInstance()->m_base->mercenaries()->mercenaries()->getMercenary(i)->setCarriedEnergy(value.toUInt());
            else if (varName == "carriedFoodSupplies")
                Game::gameInstance()->m_base->mercenaries()->mercenaries()->getMercenary(i)->setCarriedFoodSupplies(value.toUInt());
            break;
        }
}

void H4X::unlockDBEntry(const QString &entryName) noexcept
{
    Game::gameInstance()->m_base->database()->unlockEntry(entryName);
}

void H4X::receiveReport(const QString &msg, const QString &art) noexcept
{
    Game::gameInstance()->m_base->reports()->addReport(new UnifiedReport(Game::gameInstance()->m_base->gameClock()->currentTime(),msg,art));
}

void H4X::clearReports() noexcept
{
    Game::gameInstance()->m_base->reports()->clearReports();
}

void H4X::finishMission(const QString &mercenaryName) noexcept
{
    for (int i=0;i < Game::gameInstance()->m_base->mercenaries()->mercenaries()->amountOfMercenaries();++i)
        if (Game::gameInstance()->m_base->mercenaries()->mercenaries()->getMercenary(i)->name() == mercenaryName && Game::gameInstance()->m_base->mercenaries()->mercenaries()->getMercenary(i)->assignedMission() != nullptr)
        {
            Game::gameInstance()->m_base->mercenaries()->mercenaries()->getMercenary(i)->assignedMission()->forceEndSuccessfully();
            break;
        }
}

void H4X::forceUIUpdate() noexcept
{
    QObject *win = m_qmlEngine->rootObjects().value(0);
    win->setProperty("updateEverythingInAMoment",true);
}

void H4X::fps() noexcept
{
    QObject *win = m_qmlEngine->rootObjects().value(0);
    win->setProperty("enableFPSCounter",{!(win->property("enableFPSCounter").toBool())});
    Game::gameInstance()->acknowledgeFPSToggle();
}

void H4X::destroyEverything() noexcept
{
    QSettings().setValue("save01",{});
    exit(0);
}

void H4X::freezeGameProgress() noexcept
{
    Game::gameInstance()->m_base->m_freezeGameProgress = 1;
    Game::gameInstance()->saveBase();
    exit(0);
}

void H4X::enableAutoUpdate(bool enable) noexcept
{
    m_autoUpdate = enable;
}
