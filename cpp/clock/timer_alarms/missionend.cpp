#include "missionend.h"

#include <QDataStream>

#include "base/base.h"
#include "mercenaries/mercenary.h"
#include "missions/mission.h"

MissionEndTimerAlarm::MissionEndTimerAlarm(Base *base, Mission *mission) noexcept
    : TimerAlarm(base,TimerAlarmEnums::AT_MissionEnd,1), m_mission(mission) {}

bool MissionEndTimerAlarm::operator ==(const MissionEndTimerAlarm &other) const noexcept
{
    return m_mission==other.m_mission;
}

Mission *MissionEndTimerAlarm::mission() noexcept
{
    if (m_mission!=nullptr)
        return m_mission;
    for (const auto &e : m_base->missions())
        if (m_missionMercenaryName==e->assignedMercenary()->name())
        {
            m_mission=e;
            return e;
        }
    return nullptr;
}

QDataStream &MissionEndTimerAlarm::read(QDataStream &stream) noexcept
{
    stream>>m_missionMercenaryName;

    return stream;
}

QDataStream &MissionEndTimerAlarm::write(QDataStream &stream) const noexcept
{
    stream<<(m_mission!=nullptr ? m_mission->assignedMercenary()->name() : m_missionMercenaryName);

    return stream;
}

QDataStream &operator<<(QDataStream &stream, const MissionEndTimerAlarm &alarm) noexcept
{
    alarm.write(stream);
}

QDataStream &operator>>(QDataStream &stream, MissionEndTimerAlarm &alarm) noexcept
{
    alarm.read(stream);
}
