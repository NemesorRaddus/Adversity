#include "gameclock.h"

#include "base/base.h"
#include "h4x/h4x.h"

GameClock::GameClock() noexcept
    : m_currentTimeInGame(1,0,0), m_latestAutosaveMinTimestamp(0) {}

void GameClock::setBasePtr(Base *base) noexcept
{
    m_base=base;
}

void GameClock::updateClock(const Time &lastKnownTimeInGame) noexcept
{
    m_currentTimeInGame=lastKnownTimeInGame;
}

void GameClock::updateClock(int minutesToAdd) noexcept
{
    int daysPassed=(minutesToAdd + m_currentTimeInGame.h*60 + m_currentTimeInGame.min)/(60*24);
    for (int i=0;i<daysPassed;++i)
    {
        addMinutesToGameTime(60*24);
        minutesToAdd-=60*24;

        checkMissionAlarms(m_currentTimeInGame);
        m_base->startNewDay();
    }

    addMinutesToGameTime(minutesToAdd);
    checkMissionAlarms(m_currentTimeInGame);

    tryAutosaving();
}

void GameClock::updateClock() noexcept
{
    updateClock(1);
}

void GameClock::skipToNextDay() noexcept
{
    updateClock((24-m_currentTimeInGame.h-1)*60 + (60-m_currentTimeInGame.min));
    H4X hax;
    hax.forceUIUpdate();
}

void GameClock::forceAutosave() noexcept
{
    autosave();
}

void GameClock::addMinutesToGameTime(int minutes) noexcept
{
    addHoursToGameTime(minutes/60);
    minutes%=60;
    if (minutes+m_currentTimeInGame.min>59)
    {
        addHoursToGameTime(1);
        minutes-=(60-m_currentTimeInGame.min-1);
    }
    m_currentTimeInGame.min+=minutes;
    m_currentTimeInGame.min%=60;
}

void GameClock::addHoursToGameTime(int hours) noexcept
{
    addDaysToGameTime(hours/24);
    hours%=24;
    if (hours+m_currentTimeInGame.h>23)
    {
        addDaysToGameTime(1);
        hours-=(24-m_currentTimeInGame.h-1);
    }
    m_currentTimeInGame.h+=hours;
    m_currentTimeInGame.h%=24;
}

void GameClock::addDaysToGameTime(int days) noexcept
{
    m_currentTimeInGame.d+=days;
}

int GameClock::realMsToOneGameMin() const noexcept
{
    return static_cast<float>(m_realMinutesToOneGameDayRatio)/0.024;
}

void GameClock::tryAutosaving() noexcept
{
    if (m_currentTimeInGame.min>m_latestAutosaveMinTimestamp)
    {
        if (m_currentTimeInGame.min>=m_latestAutosaveMinTimestamp+m_autosaveIntervalInMin)
            autosave();
    }
    else
    {
        if (m_currentTimeInGame.min+60-m_latestAutosaveMinTimestamp>=m_autosaveIntervalInMin)
            autosave();
    }
}

void GameClock::autosave() noexcept
{
    m_latestAutosaveMinTimestamp=m_currentTimeInGame.min;
    emit doAutosave();
}
