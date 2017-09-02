#include "timer.h"

#include "event.h"

#include <QDebug>

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
    return 1;
}

TimerAlarm::TimerAlarm(TimerAlarmEnums::AlarmType type, bool isAlreadyActive) noexcept
    : m_type(type), m_isAlreadyActive(isAlreadyActive)
{}

BuildingUpgradeTimerAlarm::BuildingUpgradeTimerAlarm(BaseEnums::Building buildingName, unsigned buildingLevel) noexcept
    : TimerAlarm(TimerAlarmEnums::AT_BuildingUpgrade), m_buildingName(buildingName), m_buildingLevel(buildingLevel)
{}

QDataStream &BuildingUpgradeTimerAlarm::read(QDataStream &stream) noexcept
{
    quint8 n;
    stream>>n;
    m_type=static_cast<TimerAlarmEnums::AlarmType>(n);
    stream>>m_isAlreadyActive;


    stream>>n;
    m_buildingName=static_cast<BaseEnums::Building>(n);
    stream>>n;
    m_buildingLevel=static_cast<unsigned>(n);

    return stream;
}

QDataStream &BuildingUpgradeTimerAlarm::write(QDataStream &stream) const noexcept
{
    stream<<static_cast<quint8>(m_type);
    stream<<m_isAlreadyActive;

    stream<<static_cast<quint8>(m_buildingName);
    stream<<static_cast<quint8>(m_buildingLevel);

    return stream;
}

QDataStream &operator<<(QDataStream &stream, const BuildingUpgradeTimerAlarm &alarm) noexcept
{
    return alarm.write(stream);
}

QDataStream &operator>>(QDataStream &stream, BuildingUpgradeTimerAlarm &alarm) noexcept
{
    return alarm.read(stream);
}

bool BuildingUpgradeTimerAlarm::operator ==(const BuildingUpgradeTimerAlarm &other) const noexcept
{
    if (m_buildingLevel!=other.m_buildingLevel)
        return 0;
    if (m_buildingName!=other.m_buildingName)
        return 0;
    return 1;
}

void TimerAlarmsContainer::addAlarm(unsigned daysToTimeout, TimerAlarm *alarm) noexcept
{
    int i=0;
    for (;i<m_alarms.size();++i)
        if (m_alarms[i].first>daysToTimeout)
            break;
    m_alarms.insert(i,{daysToTimeout,alarm});
}

void TimerAlarmsContainer::cancelAlarm(TimerAlarm *alarm) noexcept
{
    for (int i=0; i<m_alarms.size(); ++i)
        if (m_alarms[i].second->isTrulyEqualTo(alarm))
        {
            m_alarms.remove(i);
            break;
        }
}

void TimerAlarmsContainer::cancelAlarmAtPos(unsigned index) noexcept
{
    if (index<m_alarms.size())
        m_alarms.removeAt(index);
}

void TimerAlarmsContainer::clearAlarms() noexcept
{
    m_alarms.clear();
}

int TimerAlarmsContainer::checkDaysToTimeoutOfAlarm(TimerAlarm *alarm) const noexcept
{
    for (int i=0; i<m_alarms.size(); ++i)
        if (m_alarms[i].second->isTrulyEqualTo(alarm))
            return m_alarms[i].first;
    return -1;
}

bool TimerAlarmsContainer::checkIfAlarmIsSet(TimerAlarm *alarm) const noexcept
{
    return checkDaysToTimeoutOfAlarm(alarm)==-1 ? 0 : 1;
}

QVector<TimerAlarm *> TimerAlarmsContainer::moveToNextDayAndGetTimeoutedResults() noexcept
{
    decreaseDaysToTimeout();
    return takeTimeoutedAlarms();
}

QVector<QPair<unsigned, TimerAlarm *> > TimerAlarmsContainer::getAllAlarms() const noexcept
{
    return m_alarms;
}

void TimerAlarmsContainer::addMissionAlarm(const Time &time, Mission *mission) noexcept
{
    for (auto e : m_missionAlarms)
        if (e.second == mission)
            return;

    m_missionAlarms+={time, mission};
}

void TimerAlarmsContainer::checkMissionAlarms(const Time &now) noexcept
{
    for (int i=0;i<m_missionAlarms.size();++i)
        if (m_missionAlarms[i].first <= now)
        {
            m_base->addEncounterReport(m_missionAlarms[i].second->doEncounter());
            m_missionAlarms.remove(i);
            --i;
        }
}

void TimerAlarmsContainer::decreaseDaysToTimeout() noexcept
{
    for (int i=0;i<m_alarms.size();++i)
    {
        if (m_alarms[i].second->isAlreadyActive())
            --m_alarms[i].first;
        else
            m_alarms[i].second->activate();
    }
}

QVector<TimerAlarm *> TimerAlarmsContainer::takeTimeoutedAlarms() noexcept
{
    QVector <TimerAlarm *> r;
    int i=0;
    for (;i<m_alarms.size() && m_alarms[i].first==0;++i)
        r.push_back(m_alarms[i].second);
    m_alarms.remove(0,i);
    return r;
}

Time::Time() noexcept
    : d(1), h(0), min(0) {}

Time::Time(unsigned day, unsigned hour, unsigned minute) noexcept
    : d(day), h(hour), min(minute) {}

bool Time::operator ==(const Time &other) const noexcept
{
    return d==other.d && h==other.h && min==other.min;
}

bool Time::operator <(const Time &other) const noexcept
{
    if (d<other.d)
        return 1;
    else if (d>other.d)
        return 0;

    if (h<other.h)
        return 1;
    else if (h>other.h)
        return 0;

    if (min<other.min)
        return 1;
    else
        return 0;
}

GameClock::GameClock() noexcept
    : m_currentTimeInGame(1,12,0), m_lastKnownDate(QDateTime::currentDateTime()), m_lastKnownTimeInGame(1,12,0),  m_latestAutosaveMinTimestamp(0), m_dateFromPreviousClockUpdate({QDate(1970,1,1),QTime(0,0)})
{}

void GameClock::setBasePtr(Base *base) noexcept
{
    m_base=base;
}

void GameClock::saveCurrentDate() noexcept
{
    m_lastKnownDate=QDateTime::currentDateTime();
    m_lastKnownTimeInGame=m_currentTimeInGame;

    updateDateFromPreviousClockUpdate();
}

void GameClock::updateClock(const QDateTime &lastKnownDate, const Time &lastKnownTimeInGame) noexcept
{
    m_lastKnownDate=lastKnownDate;
    m_lastKnownTimeInGame=lastKnownTimeInGame;

    m_currentTimeInGame=lastKnownTimeInGame;

    updateDateFromPreviousClockUpdate();

    long long ms = m_lastKnownDate.msecsTo(QDateTime::currentDateTime());

    int daysPassed=(ms*24*60*60*1000/1000/60/realMinutesToOneGameDayRatio() + m_lastKnownTimeInGame.h*60*60*1000 + m_lastKnownTimeInGame.min*60*1000)/1000/60/60/24;
    int minutesToAdd=ms*24*60/1000/60/realMinutesToOneGameDayRatio();// /1000 s /60 min /r dni *24 h *60 min
    for (int i=0;i<daysPassed;++i)
    {
        addMinutesToGameTime(60*24);
        minutesToAdd-=60*24;
        ++m_currentTimeInGame.d;

        m_base->startNewDay();
    }

    addMinutesToGameTime(minutesToAdd);
    tryAutosaving();
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

    updateDateFromPreviousClockUpdate();

    tryAutosaving();
}

void GameClock::updateClock() noexcept
{
    if (isClockHealthy())
        updateClock(1);
    else
        updateClock(m_lastKnownDate,m_lastKnownTimeInGame);
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

bool GameClock::isClockHealthy() const noexcept
{
    return m_dateFromPreviousClockUpdate.msecsTo(QDateTime::currentDateTime())<realMsToOneGameMin()*2;
}

void GameClock::updateDateFromPreviousClockUpdate() noexcept
{
    m_dateFromPreviousClockUpdate=QDateTime::currentDateTime();
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
