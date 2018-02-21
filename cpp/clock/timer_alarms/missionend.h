#pragma once

#include <QString>

#include "timeralarm.h"

class Base;
class Mission;
class QDataStream;

class MissionEndTimerAlarm : public TimerAlarm
{
public:
    explicit MissionEndTimerAlarm(Base *base, Mission *mission) noexcept;
    MissionEndTimerAlarm() noexcept//NEVER USE MANUALLY - ONLY FOR QT
        : m_mission(nullptr) {}

    bool operator ==(const MissionEndTimerAlarm &other) const noexcept;
    inline bool operator !=(const MissionEndTimerAlarm &other) const noexcept
    {
        return !(*this == other);
    }

    Mission *mission() noexcept;

    QDataStream &read(QDataStream &stream) noexcept;
    QDataStream &write(QDataStream &stream) const noexcept;

private:
    QString m_missionMercenaryName;
    Mission *m_mission;
};

QDataStream &operator<<(QDataStream &stream, const MissionEndTimerAlarm &alarm) noexcept;
QDataStream &operator>>(QDataStream &stream, MissionEndTimerAlarm &alarm) noexcept;
