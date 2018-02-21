#include "aetheritesilo.h"

#include "base/base.h"
#include "clock/gameclock.h"
#include "clock/timer_alarms/buildingupgrade.h"

AetheriteSilo::AetheriteSilo(Base *base, unsigned level, const AnyBuildingLevelsInfo *levelsInfo) noexcept
    : Building(BuildingEnums::B_AetheriteSilo, base, level, levelsInfo) {}

int AetheriteSilo::aetheriteLimit() const noexcept
{
    return currentLevelInfo()->aetheriteOreLimit;
}

int AetheriteSilo::aetheriteLimitAfterUpgrade() const noexcept
{
    return nextLevelInfo()->aetheriteOreLimit;
}

void AetheriteSilo::setLevelsInfo(const QVector < AetheriteSiloLevelInfo *> &info) noexcept
{
    Building::setLevelsInfo(new AnyBuildingLevelsInfo(info));
}

unsigned AetheriteSilo::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(base(),BuildingEnums::B_AetheriteSilo,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

AetheriteSiloLevelInfo *AetheriteSilo::currentLevelInfo() const noexcept
{
    return Building::currentLevelInfo<AetheriteSiloLevelInfo > ();
}

AetheriteSiloLevelInfo *AetheriteSilo::nextLevelInfo() const noexcept
{
    return Building::nextLevelInfo<AetheriteSiloLevelInfo > ();
}
