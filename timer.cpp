#include "timer.h"

TimerAlarmEnums::AlarmType TimerAlarm::type() const noexcept
{
    return m_type;
}

TimerAlarm::TimerAlarm(TimerAlarmEnums::AlarmType type, bool isAlreadyActive) noexcept
    : m_type(type), m_isAlreadyActive(isAlreadyActive)
{

}

BuildingUpgradeTimerAlarm::BuildingUpgradeTimerAlarm(BaseEnums::Building buildingName, unsigned buildingLevel) noexcept
    : TimerAlarm(TimerAlarmEnums::AT_BuildingUpgrade)
{

}

void TimerAlarmsContainer::addAlarm(unsigned daysToTimeout, TimerAlarm *alarm) noexcept
{

}

void TimerAlarmsContainer::cancelAlarm(const TimerAlarm &alarm) noexcept
{

}

int TimerAlarmsContainer::checkDaysToTimeoutOfAlarm(const TimerAlarm &alarm) const noexcept
{

}

QVector<TimerAlarm *> TimerAlarmsContainer::moveToNextDayAndGetTimeoutedResults() noexcept
{

}

QMultiMap<unsigned, TimerAlarm *> TimerAlarmsContainer::getAllAlarms() const noexcept
{

}

void TimerAlarmsContainer::decreaseDaysToTimeout() noexcept
{

}

QVector<TimerAlarm *> TimerAlarmsContainer::getTimeoutedAlarms() const noexcept
{

}

GameClock::GameClock() noexcept
{

}

void GameClock::markCurrentDateAsFirstRegistered() noexcept
{

}

void GameClock::updateClock() noexcept
{

}
