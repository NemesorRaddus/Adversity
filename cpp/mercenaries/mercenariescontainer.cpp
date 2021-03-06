#include "mercenariescontainer.h"

#include "mercenary.h"
#include "base/base.h"
#include "base/buildings/specific/destressing/bar.h"
#include "base/buildings/specific/other/dockingstation.h"
#include "base/buildings/specific/training/gym.h"
#include "base/buildings/specific/other/hospital.h"
#include "base/buildings/specific/training/laboratory.h"
#include "base/buildings/specific/destressing/playingfield.h"
#include "base/buildings/specific/destressing/seclusion.h"
#include "base/buildings/specific/destressing/shrine.h"
#include "base/buildings/specific/training/trainingground.h"
#include "base/managers/buildingsmanager.h"
#include "clock/gameclock.h"
#include "general/game.h"
#include "logging/loggersprovider.h"
#include "missions/mission.h"

MercenariesContainer::MercenariesContainer(Base *base) noexcept
    : m_preparedMercenary(nullptr), m_basePtr(base) {}

bool MercenariesContainer::prepareMercenaryAt(unsigned index) noexcept
{
    if (index >= m_mercenaries.size())
        return 0;
    m_preparedMercenary = m_mercenaries[index];
    return 1;
}

void MercenariesContainer::addMercenary(Mercenary *mercenary) noexcept
{
    m_mercenaries+=mercenary;
    connectMercenaryToBanSystem(mercenary->name());

    LoggersProvider::mercenariesLogger()->trace("[{}] Mercenary added: {}",mercenary->base()->gameClock()->currentTime().toQString().toStdString(), mercenary->name().toStdString());
}

void MercenariesContainer::removeMercenary(unsigned index) noexcept
{
    if (index < m_mercenaries.size())
    {
        LoggersProvider::mercenariesLogger()->trace("[{}] Removing mercenary: {}",m_mercenaries[index]->base()->gameClock()->currentTime().toQString().toStdString(), m_mercenaries[index]->name().toStdString());

        if (m_mercenaries[index]->currentActivity() == MercenaryEnums::CA_InHospital)
            m_basePtr->buildings()->hospital()->removeMercenary(m_mercenaries[index]->name());
        else if (m_mercenaries[index]->currentActivity() == MercenaryEnums::CA_OnTrainingGround)
            m_basePtr->buildings()->trainingGround()->removeMercenary(m_mercenaries[index]->name());
        else if (m_mercenaries[index]->currentActivity() == MercenaryEnums::CA_InGym)
            m_basePtr->buildings()->gym()->removeMercenary(m_mercenaries[index]->name());
        else if (m_mercenaries[index]->currentActivity() == MercenaryEnums::CA_InLaboratory)
            m_basePtr->buildings()->laboratory()->removeMercenary(m_mercenaries[index]->name());
        else if (m_mercenaries[index]->currentActivity() == MercenaryEnums::CA_InPlayingField)
            m_basePtr->buildings()->playingField()->removeMercenary(m_mercenaries[index]->name());
        else if (m_mercenaries[index]->currentActivity() == MercenaryEnums::CA_InBar)
            m_basePtr->buildings()->bar()->removeMercenary(m_mercenaries[index]->name());
        else if (m_mercenaries[index]->currentActivity() == MercenaryEnums::CA_InShrine)
            m_basePtr->buildings()->shrine()->removeMercenary(m_mercenaries[index]->name());
        else if (m_mercenaries[index]->currentActivity() == MercenaryEnums::CA_InSeclusion)
            m_basePtr->buildings()->seclusion()->removeMercenary(m_mercenaries[index]->name());
        else if (m_mercenaries[index]->currentActivity() == MercenaryEnums::CA_Arriving)
            m_basePtr->buildings()->dockingStation()->cancelMercenaryArrival(m_mercenaries[index]->name());
        else if (m_mercenaries[index]->currentActivity() == MercenaryEnums::CA_OnMission)
        {
            auto m = m_mercenaries[index]->assignedMission();
            if (m != nullptr)
                m->forceEndBecauseOfDeath();
        }
        Game::gameInstance()->assetsPool().unloadMercenary(m_mercenaries[index]->name());
        m_mercenaries.remove(index);
    }
}

int MercenariesContainer::findMercenary(const QString &name) const noexcept
{
    for (int i=0;i < m_mercenaries.size();++i)
        if (m_mercenaries[i]->name() == name)
            return i;
    return -1;
}

void MercenariesContainer::handleNewDay() noexcept
{
    for (auto e : m_mercenaries)
        e->handleNewDay();

    for (auto e : m_mercenaries)
        if (!e->isCommunicationAvailable())
        {
            if (!e->isDead())
                e->increaseStress(20);
            for (auto f : m_mercenaries)
                if (!f->isDead() && (f->currentActivity() != MercenaryEnums::CA_Arriving && f->currentActivity() != MercenaryEnums::CA_OnMission))
                {
                    if (e->nature() == f->nature())
                        f->increaseStress(20);
                    else
                        f->increaseStress(10);
                }
        }
}

void MercenariesContainer::handleNewWeek() noexcept
{
    for (auto e : m_mercenaries)
        e->handleNewWeek();
}

void MercenariesContainer::addDoStBan(QString name, unsigned daysAmount) noexcept
{
    disconnectMercenaryFromBanSystem(name);
    Game::gameInstance()->addDoStBan(name,daysAmount);
    removeMercenary(findMercenary(name));
}

void MercenariesContainer::addDoStBan(QString name) noexcept
{
    auto natureOfKilledMerc = m_mercenaries[findMercenary(name)]->nature();

    addDoStBan(name,-1/*that's unsigned so yeah...*/);

    for (auto e : m_mercenaries)
        if (!e->isDead() && (e->currentActivity() != MercenaryEnums::CA_Arriving && e->currentActivity() != MercenaryEnums::CA_OnMission))
        {
            if (e->nature() == natureOfKilledMerc)
                e->increaseStress(40);
            else
                e->increaseStress(20);
        }
}

void MercenariesContainer::connectMercenaryToBanSystem(const QString &name) noexcept
{
    connect(m_mercenaries[findMercenary(name)],SIGNAL(died(QString)),this,SLOT(addDoStBan(QString)));
    connect(m_mercenaries[findMercenary(name)],SIGNAL(ranAway(QString,uint)),this,SLOT(addDoStBan(QString,uint)));
}

void MercenariesContainer::disconnectMercenaryFromBanSystem(const QString &name) noexcept
{
    disconnect(m_mercenaries[findMercenary(name)],SIGNAL(died(QString)),this,SLOT(addDoStBan(QString)));
    disconnect(m_mercenaries[findMercenary(name)],SIGNAL(ranAway(QString,uint)),this,SLOT(addDoStBan(QString,uint)));
}
