#include "powerplant.h"

#include "base/base.h"
#include "base/managers/resourcesmanager.h"
#include "clock/gameclock.h"
#include "clock/timer_alarms/buildingupgrade.h"
#include "general/game.h"
#include "logging/loggersprovider.h"

Powerplant::Powerplant(Base *base, unsigned level, const AnyBuildingLevelsInfo *levelsInfo) noexcept
    : Building(BuildingEnums::B_Powerplant, base, level, levelsInfo), m_currentCycles(0) {}

int Powerplant::useCostInEnergy() const noexcept
{
    return -(currentLevelInfo()->energyGiven * m_currentCycles);
}

int Powerplant::productionInEnergySingle() const noexcept
{
    return -(currentLevelInfo())->energyGiven;
}

int Powerplant::productionInEnergySingleAfterUpgrade() const noexcept
{
    return -(nextLevelInfo())->energyGiven;
}

int Powerplant::useCostInAetherite() const noexcept
{
    return currentLevelInfo()->aetheriteOreTaken * m_currentCycles;
}

int Powerplant::useCostInAetheriteSingle() const noexcept
{
    return currentLevelInfo()->aetheriteOreTaken;
}

int Powerplant::useCostInAetheriteSingleAfterUpgrade() const noexcept
{
    return nextLevelInfo()->aetheriteOreTaken;
}

int Powerplant::energyLimit() const noexcept
{
    return currentLevelInfo()->energyLimit;
}

int Powerplant::energyLimitAfterUpgrade() const noexcept
{
    return nextLevelInfo()->energyLimit;
}

void Powerplant::exchangeResources() noexcept
{
    unsigned cyclesToDo = base()->resources()->currentAetheriteAmount() / currentLevelInfo()->aetheriteOreTaken;
    unsigned uselessnessLimit = currentLevelInfo()->energyGiven != 0 ? (((currentLevelInfo()->energyLimit - base()->resources()->currentEnergyAmount()) / currentLevelInfo()->energyGiven) + ((currentLevelInfo()->energyLimit - base()->resources()->currentEnergyAmount()) % currentLevelInfo()->energyGiven == 0 ? 0 : 1)) : 0;//that way it doesn't do additional cycles if resource limit is reached earlier

    if (cyclesToDo > uselessnessLimit)
        cyclesToDo = uselessnessLimit;
    if (cyclesToDo > m_currentCycles)
        cyclesToDo = m_currentCycles;

    LoggersProvider::buildingsLogger()->trace("[{}] Powerplant: doing {} cycles",base()->gameClock()->currentTime().toQString().toStdString(), cyclesToDo);
    base()->resources()->setCurrentAetheriteAmount(base()->resources()->currentAetheriteAmount() - (cyclesToDo * currentLevelInfo()->aetheriteOreTaken));
    base()->resources()->setCurrentEnergyAmount(base()->resources()->currentEnergyAmount() + (cyclesToDo * currentLevelInfo()->energyGiven));
}

void Powerplant::setCurrentCycles(unsigned amount) noexcept
{
    if (amount <= maxCycles())
    {
        m_currentCycles = amount;
        LoggersProvider::buildingsLogger()->trace("[{}] Powerplant: current cycles amount: {}",base()->gameClock()->currentTime().toQString().toStdString(), m_currentCycles);
    }
}

unsigned Powerplant::maxCycles() const noexcept
{
    return currentLevelInfo()->maxCycles;
}

unsigned Powerplant::maxCyclesAfterUpgrade() const noexcept
{
    return nextLevelInfo()->maxCycles;
}

void Powerplant::setLevelsInfo(const QVector < PowerplantLevelInfo *> &info) noexcept
{
    Building::setLevelsInfo(new AnyBuildingLevelsInfo(info));
}

unsigned Powerplant::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(base(),BuildingEnums::B_Powerplant,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

PowerplantLevelInfo *Powerplant::currentLevelInfo() const noexcept
{
    return Building::currentLevelInfo<PowerplantLevelInfo > ();
}

PowerplantLevelInfo *Powerplant::nextLevelInfo() const noexcept
{
    return Building::nextLevelInfo<PowerplantLevelInfo > ();
}
