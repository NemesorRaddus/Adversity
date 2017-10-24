#include "timeralarm.h"

#include "clock/timer_alarms/buildingupgrade.h"
#include "clock/timer_alarms/missionend.h"

void TimerAlarm::activate() noexcept
{
    m_isAlreadyActive=1;
}

bool TimerAlarm::isTrulyEqualTo(TimerAlarm *alarmsSubclassObject) noexcept
{
    if (m_type!=alarmsSubclassObject->m_type)
        return 0;
    if (m_type==TimerAlarmEnums::AT_BuildingUpgrade)
        if (*static_cast<BuildingUpgradeTimerAlarm*>(this)!=*static_cast<BuildingUpgradeTimerAlarm*>(alarmsSubclassObject))
            return 0;
    else if (m_type==TimerAlarmEnums::AT_MissionEnd)
        if (*static_cast<MissionEndTimerAlarm*>(this)!=*static_cast<MissionEndTimerAlarm*>(alarmsSubclassObject))
            return 0;
    return 1;
}

void TimerAlarm::setBasePtr(Base *base) noexcept
{
    m_base=base;
}

TimerAlarm::TimerAlarm(Base *base, TimerAlarmEnums::AlarmType type, bool isAlreadyActive) noexcept
    : m_base(base), m_type(type), m_isAlreadyActive(isAlreadyActive)
{}
