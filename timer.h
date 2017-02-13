#ifndef GAMECLOCK_H
#define GAMECLOCK_H

#include <QMultiMap>
#include <QVector>
#include <QDateTime>

#include "base.h"

struct TimerAlarmEnums
{
    enum AlarmType
    {
        AT_BuildingUpgrade,
        AT_MissionEnd,
        AT_Information,
        AT_END
    };
};

class TimerAlarm
{
public:
    TimerAlarmEnums::AlarmType type() const noexcept;

protected:
    explicit TimerAlarm(TimerAlarmEnums::AlarmType type, bool isAlreadyActive = 0) noexcept;

private:
    TimerAlarmEnums::AlarmType m_type;
    bool m_isAlreadyActive;//if true, decrease daysToTimeout in container at the end of current day
};

class BuildingUpgradeTimerAlarm : public TimerAlarm
{
public:
    explicit BuildingUpgradeTimerAlarm(BaseEnums::Building buildingName, unsigned buildingLevel) noexcept;

    BaseEnums::Building buildingName() const noexcept
    {
        return m_buildingName;
    }
    unsigned buildingLevel() const noexcept
    {
        return m_buildingLevel;
    }

private:
    BaseEnums::Building m_buildingName;
    unsigned m_buildingLevel;
};

class TimerAlarmsContainer : public QObject
{
    Q_OBJECT
public:
    void addAlarm(unsigned daysToTimeout, TimerAlarm *alarm) noexcept;
    void cancelAlarm(const TimerAlarm &alarm) noexcept;

    int checkDaysToTimeoutOfAlarm(const TimerAlarm &alarm) const noexcept;//returns -1 if no such alarm is set

    QVector <TimerAlarm *> moveToNextDayAndGetTimeoutedResults() noexcept;

    QMultiMap <unsigned, TimerAlarm *> getAllAlarms() const noexcept;

private:
    void decreaseDaysToTimeout() noexcept;
    QVector <TimerAlarm *> getTimeoutedAlarms() const noexcept;

    QMultiMap <unsigned, TimerAlarm *> m_alarms;
};

class GameClock : public TimerAlarmsContainer
{
    Q_OBJECT
public:
    GameClock() noexcept;

    Q_INVOKABLE void markCurrentDateAsFirstRegistered() noexcept;

    Q_INVOKABLE void updateClock() noexcept;

private:
    QDateTime m_firstDate;
    unsigned m_currentTimeInGameDay;
    unsigned m_currentTimeInGameHour;
    unsigned m_currentTimeInGameMin;
};

#endif // GAMECLOCK_H
