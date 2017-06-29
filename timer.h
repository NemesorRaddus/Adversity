#ifndef GAMECLOCK_H
#define GAMECLOCK_H

#include <QVector>
#include <QDateTime>

#include "base.h"

#include <QDebug>

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
    TimerAlarmEnums::AlarmType type() const noexcept
    {
        return m_type;
    }
    bool isAlreadyActive() const noexcept
    {
        return m_isAlreadyActive;
    }

    void activate() noexcept;

    bool isTrulyEqualTo(TimerAlarm *alarmsSubclassObject) noexcept;

protected:
    explicit TimerAlarm(TimerAlarmEnums::AlarmType type, bool isAlreadyActive = 0) noexcept;
    TimerAlarm() noexcept{}//NEVER USE MANUALLY - ONLY FOR QT

    TimerAlarmEnums::AlarmType m_type;
    bool m_isAlreadyActive;//if true, decrease daysToTimeout in container at the end of current day
};

class BuildingUpgradeTimerAlarm : public TimerAlarm
{
public:
    explicit BuildingUpgradeTimerAlarm(BaseEnums::Building buildingName, unsigned buildingLevel) noexcept;
    BuildingUpgradeTimerAlarm() noexcept{}//NEVER USE MANUALLY - ONLY FOR QT

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

    QDataStream &read(QDataStream &stream) noexcept;
    QDataStream &write(QDataStream &stream) const noexcept;

private:
    BaseEnums::Building m_buildingName;
    unsigned m_buildingLevel;
};

QDataStream &operator<<(QDataStream &stream, const BuildingUpgradeTimerAlarm &alarm) noexcept;
QDataStream &operator>>(QDataStream &stream, BuildingUpgradeTimerAlarm &alarm) noexcept;


class TimerAlarmsContainer : public QObject
{
    Q_OBJECT
public:
    void addAlarm(unsigned daysToTimeout, TimerAlarm *alarm) noexcept;
    void cancelAlarm(TimerAlarm *alarm) noexcept;
    void cancelAlarmAtPos(unsigned index) noexcept;
    void clearAlarms() noexcept;

    int checkDaysToTimeoutOfAlarm(TimerAlarm *alarm) const noexcept;//returns -1 if no such alarm is set
    bool checkIfAlarmIsSet(TimerAlarm *alarm) const noexcept;

    QVector <TimerAlarm *> moveToNextDayAndGetTimeoutedResults() noexcept;

    QVector <QPair <unsigned, TimerAlarm *> > getAllAlarms() const noexcept;

private:
    void decreaseDaysToTimeout() noexcept;
    QVector <TimerAlarm *> takeTimeoutedAlarms() noexcept;

    QVector <QPair <unsigned, TimerAlarm *> > m_alarms;
};

class GameClock : public TimerAlarmsContainer
{
    Q_OBJECT

    friend class H4X;

public:
    GameClock() noexcept;

    void setBasePtr(Base *base) noexcept;

    Q_INVOKABLE void saveCurrentDate() noexcept;

    Q_INVOKABLE void updateClock(const QDateTime &lastKnownDate, unsigned lastKnownDay, unsigned lastKnownHour, unsigned lastKnownMin) noexcept;//gets time from date time
    Q_INVOKABLE void updateClock(int minutesToAdd) noexcept;//enforces time change
    Q_INVOKABLE void updateClock() noexcept;//changes time smartly
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

    void forceAutosave() noexcept;

    Q_INVOKABLE int realMinutesToOneGameDayRatio() const noexcept
    {
        return m_realMinutesToOneGameDayRatio;
    }

signals:
    void doAutosave();

private:
    void addMinutesToGameTime(int minutes) noexcept;
    void addHoursToGameTime(int hours) noexcept;
    void addDaysToGameTime(int days) noexcept;

    bool isClockHealthy() const noexcept;//for clock freezes
    void updateDateFromPreviousClockUpdate() noexcept;

    int realMsToOneGameMin() const noexcept;

    void tryAutosaving() noexcept;
    void autosave() noexcept;

    QDateTime m_lastKnownDate;
    unsigned m_lastKnownDay;
    unsigned m_lastKnownHour;
    unsigned m_lastKnownMin;

    unsigned m_currentTimeInGameDay;
    unsigned m_currentTimeInGameHour;
    unsigned m_currentTimeInGameMin;

    QDateTime m_dateFromPreviousClockUpdate;//to handle all clock freezes (game freezes on Android, etc.)

    const unsigned m_autosaveIntervalInMin = 15;//1-59
    unsigned m_latestAutosaveMinTimestamp;

    unsigned m_realMinutesToOneGameDayRatio = 30;

    Base *m_base;
};

#endif // GAMECLOCK_H
