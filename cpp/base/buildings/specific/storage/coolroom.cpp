#include "coolroom.h"

#include "base/base.h"
#include "clock/gameclock.h"
#include "clock/timer_alarms/buildingupgrade.h"

CoolRoom::CoolRoom(Base *base, unsigned level, const AnyBuildingLevelsInfo *levelsInfo) noexcept
    : Building(BuildingEnums::B_CoolRoom, base, level, levelsInfo) {}

int CoolRoom::foodSuppliesLimit() const noexcept
{
    return currentLevelInfo()->foodSuppliesLimit;
}

int CoolRoom::foodSuppliesLimitAfterUpgrade() const noexcept
{
    return nextLevelInfo()->foodSuppliesLimit;
}

void CoolRoom::setLevelsInfo(const QVector < CoolRoomLevelInfo *> &info) noexcept
{
    Building::setLevelsInfo(new AnyBuildingLevelsInfo(info));
}

unsigned CoolRoom::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(base(),BuildingEnums::B_CoolRoom,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

CoolRoomLevelInfo *CoolRoom::currentLevelInfo() const noexcept
{
    return Building::currentLevelInfo<CoolRoomLevelInfo > ();
}

CoolRoomLevelInfo *CoolRoom::nextLevelInfo() const noexcept
{
    return Building::nextLevelInfo<CoolRoomLevelInfo > ();
}
