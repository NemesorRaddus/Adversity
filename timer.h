#ifndef GAMECLOCK_H
#define GAMECLOCK_H

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

    bool isTrulyEqualTo(TimerAlarm *alarmsSubclassObject) noexcept;

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

    bool operator ==(const BuildingUpgradeTimerAlarm &other) const noexcept;
    bool operator !=(const BuildingUpgradeTimerAlarm &other) const noexcept
    {
        return !(*this==other);
    }

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
    void cancelAlarm(TimerAlarm *alarm) noexcept;

    int checkDaysToTimeoutOfAlarm(TimerAlarm *alarm) const noexcept;//returns -1 if no such alarm is set

    QVector <TimerAlarm *> moveToNextDayAndGetTimeoutedResults() noexcept;

    QVector <QPair <unsigned, TimerAlarm *> > getAllAlarms() const noexcept;

private:
    void decreaseDaysToTimeout() noexcept;
    QVector <TimerAlarm *> takeTimeoutedAlarms() const noexcept;

    QVector <QPair <unsigned, TimerAlarm *> > m_alarms;
};

class GameClock : public TimerAlarmsContainer
{
    Q_OBJECT
public:
    GameClock() noexcept;

    Q_INVOKABLE void saveCurrentDate() noexcept;

    Q_INVOKABLE void updateClock() noexcept;//gets time from date time
    Q_INVOKABLE void updateClock(int minutesToAdd) noexcept;//enforces time change
    Q_INVOKABLE bool hasDayChangedLately() const noexcept
    {
        return (m_currentTimeInGameHour==0 && m_currentTimeInGameMin==0);
    }

    Q_INVOKABLE int currentDay() const noexcept
    {
        return m_currentTimeInGameDay;
    }
    Q_INVOKABLE int currentHour() const noexcept
    {
        return m_currentTimeInGameHour;
    }
    Q_INVOKABLE int currentMin() const noexcept
    {
        return m_currentTimeInGameMin;
    }

private:
    void determineCurrentGameTime() noexcept;
    void addMinutesToGameTime(int minutes) noexcept;
    void addHoursToGameTime(int hours) noexcept;
    void addDaysToGameTime(int days) noexcept;

    QDateTime m_lastKnownDate;
    unsigned m_lastKnownDay;
    unsigned m_lastKnownHour;
    unsigned m_lastKnownMin;

    unsigned m_currentTimeInGameDay;
    unsigned m_currentTimeInGameHour;
    unsigned m_currentTimeInGameMin;
};

#endif // GAMECLOCK_H
