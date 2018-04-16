#include "barracks.h"

#include "base/base.h"
#include "clock/gameclock.h"
#include "clock/timer_alarms/buildingupgrade.h"

Barracks::Barracks(Base *base, unsigned level, const AnyBuildingLevelsInfo *levelsInfo) noexcept
    : Building(BuildingEnums::B_Barracks, base, level, levelsInfo) {}

int Barracks::mercenariesLimit() const noexcept
{
    return currentLevelInfo()->mercenariesLimit;
}

int Barracks::mercenariesLimitAfterUpgrade() const noexcept
{
    return nextLevelInfo()->mercenariesLimit;
}

void Barracks::setLevelsInfo(const QVector < BarracksLevelInfo *> &info) noexcept
{
    Building::setLevelsInfo(new AnyBuildingLevelsInfo(info));
}

unsigned Barracks::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(base(),BuildingEnums::B_Barracks,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

BarracksLevelInfo *Barracks::currentLevelInfo() const noexcept
{
    return Building::currentLevelInfo<BarracksLevelInfo > ();
}

BarracksLevelInfo *Barracks::nextLevelInfo() const noexcept
{
    return Building::nextLevelInfo<BarracksLevelInfo > ();
}
