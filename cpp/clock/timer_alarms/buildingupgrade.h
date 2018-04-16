#pragma once

#include "timeralarm.h"
#include "base/enums.h"
#include "base/buildings/enums.h"

class QDataStream;

class BuildingUpgradeTimerAlarm : public TimerAlarm
{
public:
    explicit BuildingUpgradeTimerAlarm(Base *base, BuildingEnums::Building buildingName, unsigned buildingLevel) noexcept;
    BuildingUpgradeTimerAlarm() noexcept{}//NEVER USE MANUALLY - ONLY FOR QT

    bool operator ==(const BuildingUpgradeTimerAlarm &other) const noexcept;
    inline bool operator !=(const BuildingUpgradeTimerAlarm &other) const noexcept
    {
        return !(*this == other);
    }

    inline BuildingEnums::Building buildingName() const noexcept
    {
        return m_buildingName;
    }
    inline unsigned buildingLevel() const noexcept
    {
        return m_buildingLevel;
    }

    QDataStream &read(QDataStream &stream) noexcept;
    QDataStream &write(QDataStream &stream) const noexcept;

private:
    BuildingEnums::Building m_buildingName;
    unsigned m_buildingLevel;
};

QDataStream &operator<<(QDataStream &stream, const BuildingUpgradeTimerAlarm &alarm) noexcept;
QDataStream &operator>>(QDataStream &stream, BuildingUpgradeTimerAlarm &alarm) noexcept;
