#include "missionsmanager.h"

#include "base/base.h"
#include "base/managers/mercenariesmanager.h"
#include "mercenaries/enums.h"
#include "mercenaries/mercenariescontainer.h"
#include "mercenaries/mercenary.h"
#include "missions/mission.h"

MissionsManager::MissionsManager(Base *base) noexcept
    : BaseManagerInterface(base)
{
    m_missionInitializer = new MissionInitializer(base);
}

MissionsManager::~MissionsManager() noexcept
{
    delete m_missionInitializer;
}

void MissionsManager::initializeForNewBase() noexcept {}

void MissionsManager::startMission(Mission *mission) noexcept
{
    m_missions+=mission;
    mission->start();
}

void MissionsManager::removeMission(Mission *mission) noexcept
{
    for (int i=0;i < m_missions.size();++i)
        if (m_missions[i] == mission)
        {
            delete m_missions[i];
            m_missions.remove(i);
            break;
        }
}

void MissionsManager::prepareMission(unsigned index) noexcept
{
    if (index < m_missions.size())
        m_preparedMission = m_missions[index];
}

int MissionsManager::remainingMissionDaysForMercenary(const QString &mercenaryName) noexcept
{
    for (const auto &e : base()->mercenaries()->mercenaries()->mercenaries())
        if (e->name() == mercenaryName)
        {
            if (e->currentActivity() != MercenaryEnums::CA_OnMission)
                return -2;
            if (e->isCommunicationAvailable())
                return e->assignedMission()->remainingDays();
            else
                return -1;
        }
    return -3;
}
