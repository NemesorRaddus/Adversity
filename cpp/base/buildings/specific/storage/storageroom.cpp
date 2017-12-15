#include "storageroom.h"

#include "base/base.h"
#include "clock/gameclock.h"
#include "clock/timer_alarms/buildingupgrade.h"

StorageRoom::StorageRoom(Base *base, unsigned level, const AnyBuildingLevelsInfo *levelsInfo) noexcept
    : Building(BuildingEnums::B_StorageRoom, base, level, levelsInfo) {}

int StorageRoom::buildingMaterialsLimit() const noexcept
{
    return currentLevelInfo()->buildingMaterialsLimit;
}

int StorageRoom::buildingMaterialsLimitAfterUpgrade() const noexcept
{
    return nextLevelInfo()->buildingMaterialsLimit;
}

void StorageRoom::setLevelsInfo(const QVector<StorageRoomLevelInfo *> &info) noexcept
{
    Building::setLevelsInfo(new AnyBuildingLevelsInfo(info));
}

unsigned StorageRoom::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(base(),BuildingEnums::B_StorageRoom,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

StorageRoomLevelInfo *StorageRoom::currentLevelInfo() const noexcept
{
    return Building::currentLevelInfo<StorageRoomLevelInfo>();
}

StorageRoomLevelInfo *StorageRoom::nextLevelInfo() const noexcept
{
    return Building::nextLevelInfo<StorageRoomLevelInfo>();
}
