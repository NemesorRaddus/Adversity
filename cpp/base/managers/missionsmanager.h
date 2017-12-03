#pragma once

#include <QObject>

#include "base/managers/basemanagerinterface.h"

class Mission;
class MissionInitializer;

class MissionsManager : public QObject, public BaseManagerInterface
{
    Q_OBJECT

    Q_PROPERTY(MissionInitializer* missionInitializer MEMBER m_missionInitializer)

    Q_PROPERTY(Mission* preparedMission MEMBER m_preparedMission)

    friend class H4X;
    friend class Base;

public:
    explicit MissionsManager(Base *base) noexcept;
    ~MissionsManager() noexcept;

    void initializeForNewBase() noexcept final;

    void startMission(Mission *mission) noexcept;
    inline const QVector <Mission *> &missions() const noexcept
    {
        return m_missions;
    }

    void removeMission(Mission *mission) noexcept;

    Q_INVOKABLE inline unsigned amountOfMissions() const noexcept
    {
        return m_missions.size();
    }
    Q_INVOKABLE void prepareMission(unsigned index) noexcept;

    Q_INVOKABLE int remainingMissionDaysForMercenary(const QString &mercenaryName) noexcept;

private:
    MissionInitializer *m_missionInitializer;
    QVector <Mission *> m_missions;
    Mission *m_preparedMission;
};
