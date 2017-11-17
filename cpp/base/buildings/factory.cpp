#include "factory.h"

#include "base/base.h"
#include "clock/gameclock.h"
#include "clock/timer_alarms/buildingupgrade.h"
#include "general/game.h"
#include "logging/loggershandler.h"

Factory::Factory(Base *base, unsigned level, const AnyBuildingLevelsInfo *levelsInfo) noexcept
    : Building(BuildingEnums::B_Factory, base, level, levelsInfo), m_currentCycles(0) {}

int Factory::useCostInBuildingMaterials() const noexcept
{
    return -(currentLevelInfo()->buildingMaterialsGiven * m_currentCycles);
}

int Factory::productionInBuildingMaterialsSingle() const noexcept
{
    return -(currentLevelInfo())->buildingMaterialsGiven;
}

int Factory::productionInBuildingMaterialsSingleAfterUpgrade() const noexcept
{
    return -(nextLevelInfo())->buildingMaterialsGiven;
}

int Factory::useCostInAetherite() const noexcept
{
    return currentLevelInfo()->aetheriteOreTaken * m_currentCycles;
}

int Factory::useCostInAetheriteSingle() const noexcept
{
    return currentLevelInfo()->aetheriteOreTaken;
}

int Factory::useCostInAetheriteSingleAfterUpgrade() const noexcept
{
    return currentLevelInfo()->aetheriteOreTaken;
}

void Factory::exchangeResources() noexcept
{
    unsigned cyclesToDo = base()->currentAetheriteAmount() / currentLevelInfo()->aetheriteOreTaken;
    unsigned uselessnessLimit = currentLevelInfo()->buildingMaterialsGiven != 0 ? (((base()->currentBuildingMaterialsLimit() - base()->currentBuildingMaterialsAmount()) / currentLevelInfo()->buildingMaterialsGiven) + ((base()->currentBuildingMaterialsLimit() - base()->currentBuildingMaterialsAmount()) % currentLevelInfo()->buildingMaterialsGiven == 0 ? 0 : 1)) : 0;//that way it doesn't do additional cycles if resource limit is reached earlier

    if (cyclesToDo > uselessnessLimit)
        cyclesToDo = uselessnessLimit;
    if (cyclesToDo > m_currentCycles)
        cyclesToDo = m_currentCycles;

    Game::gameInstance()->loggers()->buildingsLogger()->trace("[{}] Factory: doing {} cycles",base()->gameClock()->currentTime().toQString().toStdString(), cyclesToDo);
    base()->setCurrentAetheriteAmount(base()->currentAetheriteAmount() - (cyclesToDo * currentLevelInfo()->aetheriteOreTaken));
    base()->setCurrentBuildingMaterialsAmount(base()->currentBuildingMaterialsAmount() + (cyclesToDo * currentLevelInfo()->buildingMaterialsGiven));
}

void Factory::setCurrentCycles(unsigned amount) noexcept
{
    if (amount<=maxCycles())
    {
        m_currentCycles=amount;
        Game::gameInstance()->loggers()->buildingsLogger()->trace("[{}] Factory: current cycles amount: {}",base()->gameClock()->currentTime().toQString().toStdString(), m_currentCycles);
    }
}

unsigned Factory::maxCycles() const noexcept
{
    return currentLevelInfo()->maxCycles;
}

unsigned Factory::maxCyclesAfterUpgrade() const noexcept
{
    return nextLevelInfo()->maxCycles;
}

void Factory::setLevelsInfo(const QVector<FactoryLevelInfo *> &info) noexcept
{
    Building::setLevelsInfo(new AnyBuildingLevelsInfo(info));
}

unsigned Factory::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(base(),BuildingEnums::B_Factory,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

FactoryLevelInfo *Factory::currentLevelInfo() const noexcept
{
    return Building::currentLevelInfo<FactoryLevelInfo>();
}

FactoryLevelInfo *Factory::nextLevelInfo() const noexcept
{
    return Building::nextLevelInfo<FactoryLevelInfo>();
}
