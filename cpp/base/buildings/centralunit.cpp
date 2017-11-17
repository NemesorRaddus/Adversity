#include "centralunit.h"

#include "base/base.h"
#include "clock/gameclock.h"
#include "clock/timer_alarms/buildingupgrade.h"

CentralUnit::CentralUnit(Base *base, unsigned level, const AnyBuildingLevelsInfo *levelsInfo) noexcept
    : Building(BuildingEnums::B_CentralUnit, base, level, levelsInfo) {}

void CentralUnit::setLevelsInfo(const QVector<CentralUnitLevelInfo *> &info) noexcept
{
    Building::setLevelsInfo(new AnyBuildingLevelsInfo(info));
}

unsigned CentralUnit::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(base(),BuildingEnums::B_CentralUnit,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

CentralUnitLevelInfo *CentralUnit::currentLevelInfo() const noexcept
{
    return Building::currentLevelInfo<CentralUnitLevelInfo>();
}

CentralUnitLevelInfo *CentralUnit::nextLevelInfo() const noexcept
{
    return Building::nextLevelInfo<CentralUnitLevelInfo>();
}
