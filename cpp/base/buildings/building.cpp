#include "building.h"

#include "base/base.h"
#include "clock/gameclock.h"
#include "clock/timer_alarms/buildingupgrade.h"

unsigned Building::currentLevel() const noexcept
{
    return m_base->buildingLevel(m_buildingName);
}

BuildingUpgradeRequirements Building::requirementsForNextLevel() const noexcept
{
    return m_base->buildingRequirements(m_buildingName,currentLevel()+1);
}

unsigned Building::requirementsForNextLevelEnergy() const noexcept
{
    return m_base->buildingRequirements(m_buildingName,currentLevel()+1).requiredEnergy;
}

unsigned Building::requirementsForNextLevelBM() const noexcept
{
    return m_base->buildingRequirements(m_buildingName,currentLevel()+1).requiredBuildingMaterials;
}

unsigned Building::requirementsForNextLevelTime() const noexcept
{
    return m_base->buildingRequirements(m_buildingName,currentLevel()+1).requiredTime;
}

bool Building::tryUpgrading() noexcept
{
    BuildingUpgradeRequirements reqs = requirementsForNextLevel();
    if (reqs.requiredBuildingMaterials > m_base->currentBuildingMaterialsAmount())
        return 0;
    if (reqs.requiredEnergy > m_base->currentEnergyAmount())
        return 0;

    TimerAlarm *alrm=new BuildingUpgradeTimerAlarm(m_base,m_buildingName,currentLevel()+1);
    if (m_base->gameClock()->checkIfAlarmIsSet(alrm))
    {
        delete alrm;
        return 0;
    }

    m_base->setCurrentBuildingMaterialsAmount(m_base->currentBuildingMaterialsAmount() - reqs.requiredBuildingMaterials);
    m_base->setCurrentEnergyAmount(m_base->currentEnergyAmount() - reqs.requiredEnergy);
    m_base->gameClock()->addAlarm(reqs.requiredTime,alrm);

    registerUpgradeStart();
    return 1;
}

QString Building::description() const noexcept
{
    return m_base->buildingDescription(m_buildingName);
}

Building::Building(BuildingEnums::Building buildingName, Base *base, unsigned level) noexcept
    : m_buildingName(buildingName), m_base(base), m_isBeingUpgraded(0)
{
    m_base->setBuildingLevel(m_buildingName,level);
}
