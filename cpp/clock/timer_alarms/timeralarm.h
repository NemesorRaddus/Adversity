#pragma once

#include "enums.h"

class Base;

class TimerAlarm
{
public:
    inline TimerAlarmEnums::AlarmType type() const noexcept
    {
        return m_type;
    }
    inline bool isAlreadyActive() const noexcept
    {
        return m_isAlreadyActive;
    }

    void activate() noexcept;

    bool isTrulyEqualTo(TimerAlarm *alarmsSubclassObject) noexcept;

    void setBasePtr(Base *base) noexcept;

protected:
    explicit TimerAlarm(Base *base, TimerAlarmEnums::AlarmType type, bool isAlreadyActive = 0) noexcept;
    TimerAlarm() noexcept{}//NEVER USE MANUALLY - ONLY FOR QT

    TimerAlarmEnums::AlarmType m_type;
    bool m_isAlreadyActive;//if true, decrease daysToTimeout in container at the end of current day
    Base *m_base;
};
