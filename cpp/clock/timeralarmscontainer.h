#pragma once

#include <QObject>
#include <QVector>

#include "time.h"

class TimerAlarm;
class Time;
class Mission;
class Base;

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

    void addMissionAlarm(const Time &time, Mission *mission) noexcept;
    void checkMissionAlarms(const Time &now) noexcept;
    inline QVector <QPair <Time, Mission *> > missionAlarms() const noexcept
    {
        return m_missionAlarms;
    }
    void setMissionAlarms(const QVector <QPair <Time, Mission *> > &alarms) noexcept;
    void removeAlarmsConnectedWithMission(const Mission *mission) noexcept;

protected:
    Base *m_base;

private:
    void decreaseDaysToTimeout() noexcept;
    QVector <TimerAlarm *> takeTimeoutedAlarms() noexcept;
    void removeMissionAlarms(const Mission *mission) noexcept;
    void removeMissionEndAlarm(const Mission *mission) noexcept;

    QVector <QPair <unsigned, TimerAlarm *> > m_alarms;
    QVector <QPair <Time, Mission *> > m_missionAlarms;
};
