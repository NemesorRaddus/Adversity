#pragma once

#include <QObject>
#include <QVector>

#include "time.h"
#include "timeralarmscontainer.h"

class TimerAlarm;
class Base;
class Mission;

class GameClock : public TimerAlarmsContainer
{
    Q_OBJECT

    friend class H4X;

public:
    GameClock() noexcept;

    void setBasePtr(Base *base) noexcept;

    Q_INVOKABLE void updateClock(const Time &lastKnownTimeInGame) noexcept;//gets time from save
    Q_INVOKABLE void updateClock(int minutesToAdd) noexcept;//enforces time change
    Q_INVOKABLE void updateClock() noexcept;//changes time smartly
    Q_INVOKABLE bool hasDayChangedLately() const noexcept
    {
        return (static_cast<unsigned>(m_currentTimeInGame.h)==0 && static_cast<unsigned>(m_currentTimeInGame.min) == 0);
    }

    Q_INVOKABLE inline int currentDay() const noexcept
    {
        return m_currentTimeInGame.d;
    }
    Q_INVOKABLE inline int currentHour() const noexcept
    {
        return m_currentTimeInGame.h;
    }
    Q_INVOKABLE inline int currentMin() const noexcept
    {
        return m_currentTimeInGame.min;
    }
    inline Time currentTime() const noexcept
    {
        return m_currentTimeInGame;
    }

    Q_INVOKABLE void skipToNextDay() noexcept;

    void forceAutosave() noexcept;

    Q_INVOKABLE inline int realMinutesToOneGameDayRatio() const noexcept
    {
        return m_realMinutesToOneGameDayRatio;
    }

signals:
    void doAutosave();

private:
    void addMinutesToGameTime(int minutes) noexcept;
    void addHoursToGameTime(int hours) noexcept;
    void addDaysToGameTime(int days) noexcept;

    int realMsToOneGameMin() const noexcept;

    void tryAutosaving() noexcept;
    void autosave() noexcept;

    Time m_currentTimeInGame;

    const unsigned m_autosaveIntervalInMin = 15;//1-59
    unsigned m_latestAutosaveMinTimestamp;

    unsigned m_realMinutesToOneGameDayRatio = 15;
};
