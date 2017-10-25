#include "factory.h"

#include "base/base.h"
#include "clock/gameclock.h"
#include "clock/timer_alarms/buildingupgrade.h"
#include "general/game.h"
#include "logging/loggershandler.h"

Factory::Factory(Base *base, unsigned level, const QVector<FactoryLevelInfo> &levelsInfo) noexcept
    : Building(BuildingEnums::B_Factory, base, level), m_levelsInfo(levelsInfo), m_currentCycles(0) {}

void Factory::exchangeResources() noexcept
{
    unsigned cyclesToDo = base()->currentAetheriteAmount() / m_levelsInfo.value(currentLevel()).aetheriteOreTaken;
    unsigned uselessnessLimit = m_levelsInfo.value(currentLevel()).buildingMaterialsGiven != 0 ? (((base()->currentBuildingMaterialsLimit() - base()->currentBuildingMaterialsAmount()) / m_levelsInfo.value(currentLevel()).buildingMaterialsGiven) + ((base()->currentBuildingMaterialsLimit() - base()->currentBuildingMaterialsAmount()) % m_levelsInfo.value(currentLevel()).buildingMaterialsGiven == 0 ? 0 : 1)) : 0;//that way it doesn't do additional cycles if resource limit is reached earlier

    if (cyclesToDo > uselessnessLimit)
        cyclesToDo = uselessnessLimit;
    if (cyclesToDo > m_currentCycles)
        cyclesToDo = m_currentCycles;

    Game::gameInstance()->loggers()->buildingsLogger()->trace("[{}] Factory: doing {} cycles",base()->gameClock()->currentTime().toQString().toStdString(), cyclesToDo);
    base()->setCurrentAetheriteAmount(base()->currentAetheriteAmount() - (cyclesToDo * m_levelsInfo.value(currentLevel()).aetheriteOreTaken));
    base()->setCurrentBuildingMaterialsAmount(base()->currentBuildingMaterialsAmount() + (cyclesToDo * m_levelsInfo.value(currentLevel()).buildingMaterialsGiven));
}

void Factory::setCurrentCycles(unsigned amount) noexcept
{
    if (amount<=maxCycles())
    {
        m_currentCycles=amount;
        Game::gameInstance()->loggers()->buildingsLogger()->trace("[{}] Factory: current cycles amount: {}",base()->gameClock()->currentTime().toQString().toStdString(), m_currentCycles);
    }
}

void Factory::setLevelsInfo(const QVector<FactoryLevelInfo> &info) noexcept
{
    m_levelsInfo=info;
}

unsigned Factory::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(base(),BuildingEnums::B_Factory,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}
