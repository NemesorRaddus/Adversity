#include "coolroom.h"

#include "base/base.h"
#include "clock/gameclock.h"
#include "clock/timer_alarms/buildingupgrade.h"

CoolRoom::CoolRoom(Base *base, unsigned level, const QVector<CoolRoomLevelInfo> &levelsInfo) noexcept
    : Building(BuildingEnums::B_CoolRoom, base, level), m_levelsInfo(levelsInfo){}

void CoolRoom::setLevelsInfo(const QVector<CoolRoomLevelInfo> &info) noexcept
{
    m_levelsInfo=info;
}

unsigned CoolRoom::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(base(),BuildingEnums::B_CoolRoom,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}
