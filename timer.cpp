#include "timer.h"

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
            return 0;//TODO make implementations of other subclasses of TimerAlarm
//    else if (m_type==TimerAlarmEnums::AT_MissionEnd)
//            if (*static_cast<MissionEndTimerAlarm*>(this)!=*static_cast<MissionEndTimerAlarm*>(alarmsSubclassObject))
//                return 0;
//    else if (m_type==TimerAlarmEnums::AT_Information)
//        if (*static_cast<InformationTimerAlarm*>(this)!=*static_cast<InformationTimerAlarm*>(alarmsSubclassObject))
//            return 0;
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

GameClock::GameClock() noexcept
    : m_currentTimeInGameDay(1), m_currentTimeInGameHour(12), m_currentTimeInGameMin(0), m_latestAutosaveMinTimestamp(0)
{}

void GameClock::setBasePtr(Base *base) noexcept
{
    m_base=base;
}

void GameClock::saveCurrentDate() noexcept
{
    m_lastKnownDate=QDateTime::currentDateTime();
    m_lastKnownDay=m_currentTimeInGameDay;
    m_lastKnownHour=m_currentTimeInGameHour;
    m_lastKnownMin=m_currentTimeInGameMin;
}

void GameClock::updateClock(const QDateTime &lastKnownDate, unsigned lastKnownDay, unsigned lastKnownHour, unsigned lastKnownMin) noexcept
{
    m_lastKnownDate=lastKnownDate;
    m_lastKnownDay=lastKnownDay;
    m_lastKnownHour=lastKnownHour;
    m_lastKnownMin=lastKnownMin;

    m_currentTimeInGameDay=lastKnownDay;
    m_currentTimeInGameHour=lastKnownHour;
    m_currentTimeInGameMin=lastKnownMin;

    long long ms = m_lastKnownDate.msecsTo(QDateTime::currentDateTime());

    int daysPassed=(ms*24*60*60*1000/1000/60/realMinutesToOneGameDayRatio() + m_lastKnownHour*60*60*1000 + m_lastKnownMin*60*1000)/1000/60/60/24;
    for (int i=0;i<daysPassed;++i)
        m_base->startNewDay();

    addMinutesToGameTime(ms*24*60/1000/60/realMinutesToOneGameDayRatio());// /1000 s /60 min /r dni *24 h *60 min
    tryAutosaving();
}

void GameClock::updateClock(int minutesToAdd) noexcept
{
    int daysPassed=(minutesToAdd + m_currentTimeInGameHour*60 + m_currentTimeInGameMin)/(60*24);
    for (int i=0;i<daysPassed;++i)
        m_base->startNewDay();
    addMinutesToGameTime(minutesToAdd);
    tryAutosaving();
}

void GameClock::forceAutosave() noexcept
{
    autosave();
}

void GameClock::addMinutesToGameTime(int minutes) noexcept
{
    addHoursToGameTime(minutes/60);
    minutes%=60;
    if (minutes+m_currentTimeInGameMin>59)
    {
        addHoursToGameTime(1);
        minutes-=(60-m_currentTimeInGameMin-1);
    }
    m_currentTimeInGameMin+=minutes;
    m_currentTimeInGameMin%=60;
}

void GameClock::addHoursToGameTime(int hours) noexcept
{
    addDaysToGameTime(hours/24);
    hours%=24;
    if (hours+m_currentTimeInGameHour>23)
    {
        addDaysToGameTime(1);
        hours-=(24-m_currentTimeInGameHour-1);
    }
    m_currentTimeInGameHour+=hours;
    m_currentTimeInGameHour%=24;
}

void GameClock::addDaysToGameTime(int days) noexcept
{
    m_currentTimeInGameDay+=days;
}

void GameClock::tryAutosaving() noexcept
{
    if ((m_latestAutosaveMinTimestamp+m_autosaveIntervalInMin)%60 <= m_currentTimeInGameMin)
        autosave();
}

void GameClock::autosave() noexcept
{
    m_latestAutosaveMinTimestamp=m_currentTimeInGameMin;
    emit doAutosave();
}
