#include "h4x.h"

#include "game.h"

H4X::H4X(QQmlApplicationEngine *engine)
{
    m_qmlEngine=engine;
    _h4xQmlEngine=engine;
}

H4X::H4X()
{
    m_qmlEngine=_h4xQmlEngine;
}

void H4X::doTimeTravel(int days, int hours, int minutes) noexcept
{
    int mins=(days*24 + hours)*60 + minutes;
    if (mins>0)
        Game::gameInstance()->m_base->m_gameClock->updateClock(mins);
}

void H4X::speedUpTime(float multiplier) noexcept
{
    Game::gameInstance()->m_base->m_gameClock->m_realMinutesToOneGameDayRatio /= multiplier;
    QObject *win=m_qmlEngine->rootObjects().value(0);
    win->setProperty("gameTimerInterval",win->property("gameTimerInterval").toInt() / multiplier);
}

void H4X::slowDownTime(float multiplier) noexcept
{
    Game::gameInstance()->m_base->m_gameClock->m_realMinutesToOneGameDayRatio *= multiplier;
    QObject *win=m_qmlEngine->rootObjects().value(0);
    win->setProperty("gameTimerInterval",win->property("gameTimerInterval").toInt() * multiplier);
}

void H4X::freezeTime() noexcept
{
    QObject *win=m_qmlEngine->rootObjects().value(0);
    win->setProperty("gameTimerRunning",false);
}

void H4X::unfreezeTime() noexcept
{
    QObject *win=m_qmlEngine->rootObjects().value(0);
    win->setProperty("gameTimerRunning",true);
}

void H4X::setAetherite(unsigned amount) noexcept
{
    Game::gameInstance()->m_base->m_aetherite=amount;
}

void H4X::setBuildingMaterials(unsigned amount) noexcept
{
    Game::gameInstance()->m_base->m_buildingMaterials=amount;
}

void H4X::setEnergy(unsigned amount) noexcept
{
    Game::gameInstance()->m_base->m_energy=amount;
}

void H4X::setFoodSupplies(unsigned amount) noexcept
{
    Game::gameInstance()->m_base->m_foodSupplies=amount;
}

void H4X::refill() noexcept
{
    Game::gameInstance()->m_base->m_aetherite = Game::gameInstance()->m_base->currentAetheriteLimit();
    Game::gameInstance()->m_base->m_buildingMaterials = Game::gameInstance()->m_base->currentBuildingMaterialsLimit();
    Game::gameInstance()->m_base->m_energy = Game::gameInstance()->m_base->currentEnergyLimit();
    Game::gameInstance()->m_base->m_foodSupplies = Game::gameInstance()->m_base->currentFoodSuppliesLimit();
}

void H4X::getFreshMeat() noexcept
{
    Game::gameInstance()->m_base->m_dockingStation->prepareRecruits();
}

void H4X::getNewStuff() noexcept
{
    Game::gameInstance()->m_base->m_dockingStation->prepareEquipments();
}

void H4X::upgradeBuilding(const QString &buildingName) noexcept
{
    setBuildingLevel(buildingName,Game::gameInstance()->m_base->buildingLevel(BaseEnums::fromQStringToBuildingEnum(buildingName)) + 1);
}

void H4X::setBuildingLevel(const QString &buildingName, unsigned level) noexcept
{
    if (level > Game::gameInstance()->m_base->getBuilding(BaseEnums::fromQStringToBuildingEnum(buildingName))->maxLevel())
        return;

    Game::gameInstance()->m_base->setBuildingLevel(BaseEnums::fromQStringToBuildingEnum(buildingName),level);

    if (Game::gameInstance()->m_base->getBuilding(BaseEnums::fromQStringToBuildingEnum(buildingName))->isBeingUpgraded())
    {
        auto clock = Game::gameInstance()->m_base->m_gameClock;
        auto als = clock->getAllAlarms();
        for (int i=0;i<als.size();++i)
            if (als[i].second->type() == TimerAlarmEnums::AT_BuildingUpgrade && static_cast<BuildingUpgradeTimerAlarm*>(als[i].second)->buildingName() == BaseEnums::fromQStringToBuildingEnum(buildingName))
            {
                clock->cancelAlarmAtPos(i);
                break;//upgrade status removed
            }
    }
    Game::gameInstance()->m_base->getBuilding(BaseEnums::fromQStringToBuildingEnum(buildingName))->registerUpgradeCompletion();//slots resized

    Game::gameInstance()->m_base->recalculateAmountOfHeroSlots();//barracks slots
}

void H4X::completeUpgrade(const QString &buildingName) noexcept
{
    if (Game::gameInstance()->m_base->getBuilding(BaseEnums::fromQStringToBuildingEnum(buildingName))->isBeingUpgraded())
        upgradeBuilding(buildingName);//+1
}

void H4X::burnItDown() noexcept
{
    auto clock = Game::gameInstance()->m_base->m_gameClock;
    auto als = clock->getAllAlarms();
    for (int i=0;i<als.size();++i)
        if (als[i].second->type() == TimerAlarmEnums::AT_BuildingUpgrade)
            clock->cancelAlarmAtPos(i);//remove all upgrade statuses

    Game::gameInstance()->m_base->m_buildingLevels.insert(BaseEnums::B_CentralUnit, 1);
    Game::gameInstance()->m_base->m_buildingLevels.insert(BaseEnums::B_Hospital, 0);
    Game::gameInstance()->m_base->m_buildingLevels.insert(BaseEnums::B_TrainingGround, 0);
    Game::gameInstance()->m_base->m_buildingLevels.insert(BaseEnums::B_Gym, 0);
    Game::gameInstance()->m_base->m_buildingLevels.insert(BaseEnums::B_Laboratory, 0);
    Game::gameInstance()->m_base->m_buildingLevels.insert(BaseEnums::B_PlayingField, 0);
    Game::gameInstance()->m_base->m_buildingLevels.insert(BaseEnums::B_Bar, 0);
    Game::gameInstance()->m_base->m_buildingLevels.insert(BaseEnums::B_Shrine, 0);
    Game::gameInstance()->m_base->m_buildingLevels.insert(BaseEnums::B_Seclusion, 0);
    Game::gameInstance()->m_base->m_buildingLevels.insert(BaseEnums::B_Powerplant, 1);
    Game::gameInstance()->m_base->m_buildingLevels.insert(BaseEnums::B_Factory, 1);
    Game::gameInstance()->m_base->m_buildingLevels.insert(BaseEnums::B_CoolRoom, 1);
    Game::gameInstance()->m_base->m_buildingLevels.insert(BaseEnums::B_StorageRoom, 1);
    Game::gameInstance()->m_base->m_buildingLevels.insert(BaseEnums::B_AetheriteSilo, 1);
    Game::gameInstance()->m_base->m_buildingLevels.insert(BaseEnums::B_Barracks, 1);
    Game::gameInstance()->m_base->m_buildingLevels.insert(BaseEnums::B_DockingStation, 1);
}

void H4X::setMercenaryAttribute(const QString &mercenaryName, const QString &attribute, float value) noexcept
{
    int pos = Game::gameInstance()->m_base->m_heroes->findHero(mercenaryName);
    if (pos==-1)
        return;

    Game::gameInstance()->m_base->m_heroes->getHero(pos)->setAttributeValue(HeroEnums::fromQStringToAttributeEnum(attribute),value);
}

void H4X::hire(const QString &mercenaryName) noexcept
{
    if (Game::gameInstance()->m_base->m_dockingStation->getRecruitsNames().contains(mercenaryName))
    {
        Game::gameInstance()->m_base->m_dockingStation->hireMercenary(mercenaryName,0);
    }
    else
    {
        if (Game::gameInstance()->m_base->m_heroes->canAddHero())
        {
            if (Game::gameInstance()->assetsPool().allHeroes().contains(mercenaryName))
            {
                Game::gameInstance()->assetsPool().loadHeroNamedFromList(mercenaryName);
                for (int i=0;i<Game::gameInstance()->assetsPool().loadedHeroes().size();++i)
                    if (Game::gameInstance()->assetsPool().loadedHeroes()[i]->name() == mercenaryName)
                    {
                        Game::gameInstance()->m_base->m_heroes->addHero(Game::gameInstance()->assetsPool().loadedHeroes()[i]);
                        break;
                    }
            }
        }
    }
}

void H4X::kill(const QString &mercenaryName) noexcept
{
    for (int i=0;i<Game::gameInstance()->m_base->m_heroes->amountOfHeroes();++i)
        if (Game::gameInstance()->m_base->m_heroes->getHero(i)->name() == mercenaryName && !Game::gameInstance()->m_base->m_heroes->getHero(i)->isDead())
            Game::gameInstance()->m_base->m_heroes->getHero(i)->die();
}

void H4X::dismiss(const QString &mercenaryName, unsigned banTime) noexcept
{
    for (int i=0;i<Game::gameInstance()->m_base->m_heroes->amountOfHeroes();++i)
        if (Game::gameInstance()->m_base->m_heroes->getHero(i)->name() == mercenaryName && !Game::gameInstance()->m_base->m_heroes->getHero(i)->isDead())
            Game::gameInstance()->m_base->m_heroes->getHero(i)->dismiss(banTime);
}

void H4X::killThemAll() noexcept
{
    for (int i=0;i<Game::gameInstance()->m_base->m_heroes->amountOfHeroes();)
    {
        if (!Game::gameInstance()->m_base->m_heroes->getHero(i)->isDead())
            Game::gameInstance()->m_base->m_heroes->getHero(i)->die();
        else
            ++i;
    }
}

void H4X::engulfThemInPain() noexcept
{
    for (int i=0;i<Game::gameInstance()->m_base->m_heroes->amountOfHeroes();++i)
        if (!Game::gameInstance()->m_base->m_heroes->getHero(i)->isDead())
            Game::gameInstance()->m_base->m_heroes->getHero(i)->m_currentAttributesValues.health=1;
}

void H4X::chaosComesForYou() noexcept
{
    for (int i=0;i<Game::gameInstance()->m_base->m_heroes->amountOfHeroes();++i)
        if (!Game::gameInstance()->m_base->m_heroes->getHero(i)->isDead())
        {
            Game::gameInstance()->m_base->m_heroes->getHero(i)->m_currentAttributesValues.stress = Game::gameInstance()->m_base->m_heroes->getHero(i)->m_currentAttributesValues.stressLimit-1;
            if (!Game::gameInstance()->m_base->m_heroes->getHero(i)->isStressBorderEffectActive())
                Game::gameInstance()->m_base->m_heroes->getHero(i)->activateStressBorderEffect();
        }
}

void H4X::forceUIUpdate() noexcept
{
    QObject *win=m_qmlEngine->rootObjects().value(0);
    win->setProperty("updateEverythingInAMoment",true);
}

void H4X::fps() noexcept
{
    QObject *win=m_qmlEngine->rootObjects().value(0);
    win->setProperty("enableFPSCounter",{!(win->property("enableFPSCounter").toBool())});
}

void H4X::destroyEverything() noexcept
{
    QSettings().setValue("save01",{});
    exit(0);
}

void H4X::freezeGameProgress() noexcept
{
    Game::gameInstance()->m_base->m_freezeGameProgress=1;
    Game::gameInstance()->saveBase();
    exit(0);
}
