#include "powerplant.h"

#include "base/base.h"
#include "clock/gameclock.h"
#include "clock/timer_alarms/buildingupgrade.h"
#include "general/game.h"
#include "logging/loggershandler.h"

Powerplant::Powerplant(Base *base, unsigned level, const QVector<PowerplantLevelInfo> &levelsInfo) noexcept
    : Building(BuildingEnums::B_Powerplant, base, level), m_levelsInfo(levelsInfo), m_currentCycles(0) {}

void Powerplant::exchangeResources() noexcept
{
    unsigned cyclesToDo = base()->currentAetheriteAmount() / m_levelsInfo.value(currentLevel()).aetheriteOreTaken;
    unsigned uselessnessLimit = m_levelsInfo.value(currentLevel()).energyGiven != 0 ? (((m_levelsInfo.value(currentLevel()).energyLimit - base()->currentEnergyAmount()) / m_levelsInfo.value(currentLevel()).energyGiven) + ((m_levelsInfo.value(currentLevel()).energyLimit - base()->currentEnergyAmount()) % m_levelsInfo.value(currentLevel()).energyGiven == 0 ? 0 : 1)) : 0;//that way it doesn't do additional cycles if resource limit is reached earlier

    if (cyclesToDo > uselessnessLimit)
        cyclesToDo = uselessnessLimit;
    if (cyclesToDo > m_currentCycles)
        cyclesToDo = m_currentCycles;

    Game::gameInstance()->loggers()->buildingsLogger()->trace("[{}] Powerplant: doing {} cycles",base()->gameClock()->currentTime().toQString().toStdString(), cyclesToDo);
    base()->setCurrentAetheriteAmount(base()->currentAetheriteAmount() - (cyclesToDo * m_levelsInfo.value(currentLevel()).aetheriteOreTaken));
    base()->setCurrentEnergyAmount(base()->currentEnergyAmount() + (cyclesToDo * m_levelsInfo.value(currentLevel()).energyGiven));
}

void Powerplant::setCurrentCycles(unsigned amount) noexcept
{
    if (amount<=maxCycles())
    {
        m_currentCycles=amount;
        Game::gameInstance()->loggers()->buildingsLogger()->trace("[{}] Powerplant: current cycles amount: {}",base()->gameClock()->currentTime().toQString().toStdString(), m_currentCycles);
    }
}

void Powerplant::setLevelsInfo(const QVector<PowerplantLevelInfo> &info) noexcept
{
    m_levelsInfo=info;
}

unsigned Powerplant::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(base(),BuildingEnums::B_Powerplant,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}
