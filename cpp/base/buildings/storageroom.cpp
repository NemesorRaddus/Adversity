#include "storageroom.h"

#include "base/base.h"
#include "clock/gameclock.h"
#include "clock/timer_alarms/buildingupgrade.h"

StorageRoom::StorageRoom(Base *base, unsigned level, const QVector<StorageRoomLevelInfo> &levelsInfo) noexcept
    : Building(BuildingEnums::B_StorageRoom, base, level), m_levelsInfo(levelsInfo){}

void StorageRoom::setLevelsInfo(const QVector<StorageRoomLevelInfo> &info) noexcept
{
    m_levelsInfo=info;
}

unsigned StorageRoom::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(base(),BuildingEnums::B_StorageRoom,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}
