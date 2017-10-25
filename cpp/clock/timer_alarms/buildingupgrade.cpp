#include "buildingupgrade.h"

#include <QDataStream>

BuildingUpgradeTimerAlarm::BuildingUpgradeTimerAlarm(Base *base, BuildingEnums::Building buildingName, unsigned buildingLevel) noexcept
    : TimerAlarm(base,TimerAlarmEnums::AT_BuildingUpgrade,1), m_buildingName(buildingName), m_buildingLevel(buildingLevel)
{}

QDataStream &BuildingUpgradeTimerAlarm::read(QDataStream &stream) noexcept
{
    quint8 n;
    stream>>n;
    m_type=static_cast<TimerAlarmEnums::AlarmType>(n);
    stream>>m_isAlreadyActive;


    stream>>n;
    m_buildingName=static_cast<BuildingEnums::Building>(n);
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
