#include "timeralarmscontainer.h"

#include "base/base.h"
#include "base/managers/missionsmanager.h"
#include "clock/timer_alarms/timeralarm.h"
#include "clock/timer_alarms/missionend.h"
#include "general/game.h"
#include "logging/loggershandler.h"
#include "mercenaries/mercenary.h"
#include "missions/mission.h"
#include "reports/missionreports.h"
#include "reports/unifiedreport.h"

void TimerAlarmsContainer::addAlarm(unsigned daysToTimeout, TimerAlarm *alarm) noexcept
{
    int i = 0;
    for (;i < m_alarms.size();++i)
        if (m_alarms[i].first > daysToTimeout)
            break;
    m_alarms.insert(i,{daysToTimeout,alarm});
}

void TimerAlarmsContainer::cancelAlarm(TimerAlarm *alarm) noexcept
{
    for (int i=0; i < m_alarms.size(); ++i)
        if (m_alarms[i].second->isTrulyEqualTo(alarm))
        {
            m_alarms.remove(i);
            break;
        }
}

void TimerAlarmsContainer::cancelAlarmAtPos(unsigned index) noexcept
{
    if (index < m_alarms.size())
        m_alarms.removeAt(index);
}

void TimerAlarmsContainer::clearAlarms() noexcept
{
    m_alarms.clear();
}

int TimerAlarmsContainer::checkDaysToTimeoutOfAlarm(TimerAlarm *alarm) const noexcept
{
    for (int i=0; i < m_alarms.size(); ++i)
        if (m_alarms[i].second->isTrulyEqualTo(alarm))
            return m_alarms[i].first;
    return -1;
}

bool TimerAlarmsContainer::checkIfAlarmIsSet(TimerAlarm *alarm) const noexcept
{
    return checkDaysToTimeoutOfAlarm(alarm)==-1 ? 0 : 1;
}

QVector < TimerAlarm *> TimerAlarmsContainer::moveToNextDayAndGetTimeoutedResults() noexcept
{
    decreaseDaysToTimeout();
    return takeTimeoutedAlarms();
}

QVector<QPair < unsigned, TimerAlarm *> > TimerAlarmsContainer::getAllAlarms() const noexcept
{
    return m_alarms;
}

void TimerAlarmsContainer::addMissionAlarm(const Time &time, Mission *mission) noexcept
{
    m_missionAlarms+={time, mission};

    Game::gameInstance()->loggers()->missionsLogger()->trace("Adding mission alarm (time: {}, mercenary: {})",time.toQString().toStdString(), mission->assignedMercenary()->name().toStdString());
}

void TimerAlarmsContainer::checkMissionAlarms(const Time &now) noexcept
{
    for (int i=0;i < m_missionAlarms.size();++i)
        if (m_missionAlarms[i].first <= now)
        {
            auto temp = m_missionAlarms[i];
            m_missionAlarms.remove(i);
            --i;
            auto er = temp.second->doEncounter(temp.first);
            if (m_base->missions()->missions().contains(temp.second) && !temp.second->assignedMercenary()->isDead())
                temp.second->assignedMercenary()->trySendingReport(new UnifiedReport(er), temp.second);
        }
}

void TimerAlarmsContainer::setMissionAlarms(const QVector<QPair < Time, Mission *> > &alarms) noexcept
{
    m_missionAlarms = alarms;
}

void TimerAlarmsContainer::removeAlarmsConnectedWithMission(const Mission *mission) noexcept
{
    removeMissionAlarms(mission);
    removeMissionEndAlarm(mission);
}

void TimerAlarmsContainer::decreaseDaysToTimeout() noexcept
{
    for (int i=0;i < m_alarms.size();++i)
    {
        if (m_alarms[i].second->isAlreadyActive())
            --m_alarms[i].first;
        else
            m_alarms[i].second->activate();
    }
}

QVector < TimerAlarm *> TimerAlarmsContainer::takeTimeoutedAlarms() noexcept
{
    QVector <TimerAlarm *> r;
    int i = 0;
    for (;i < m_alarms.size() && m_alarms[i].first == 0;++i)
        r.push_back(m_alarms[i].second);
    m_alarms.remove(0,i);
    return r;
}

void TimerAlarmsContainer::removeMissionAlarms(const Mission *mission) noexcept
{
    for (int i=0;i < m_missionAlarms.size();)
    {
        if (m_missionAlarms[i].second == mission)
        {
            Game::gameInstance()->loggers()->missionsLogger()->trace("Removing mission alarm (mercenary: {})", mission->assignedMercenary()->name().toStdString());

            m_missionAlarms.remove(i);
        }
        else
            ++i;
    }
}

void TimerAlarmsContainer::removeMissionEndAlarm(const Mission *mission) noexcept
{
    for (int i=0;i < m_alarms.size();++i)
        if (m_alarms[i].second->type() == TimerAlarmEnums::AT_MissionEnd && static_cast < MissionEndTimerAlarm *>(m_alarms[i].second)->mission() == mission)
        {
            m_alarms.remove(i);
            break;
        }
}
