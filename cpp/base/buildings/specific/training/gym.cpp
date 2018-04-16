#include "gym.h"

#include "base/base.h"
#include "base/managers/mercenariesmanager.h"
#include "base/managers/reportsmanager.h"
#include "base/managers/resourcesmanager.h"
#include "clock/gameclock.h"
#include "clock/timer_alarms/buildingupgrade.h"
#include "mercenaries/mercenariescontainer.h"
#include "missions/events/event.h"
#include "reports/basereports.h"
#include "reports/unifiedreport.h"

Gym::Gym(Base *base, unsigned level, const AnyBuildingLevelsInfo *levelsInfo) noexcept
    : Building(BuildingEnums::B_Gym, base, level, levelsInfo)
{
    m_mercenariesBeingTrained.fill({nullptr,0}, currentLevelInfo()->amountOfSlots);
}

int Gym::useCostInEnergy() const noexcept
{
    int cnt = 0;
    for (int i=0;i < m_mercenariesBeingTrained.size();++i)
        if (m_mercenariesBeingTrained[i].first == nullptr)
            ++cnt;
    return currentLevelInfo()->perCapitaCostInEnergy * (m_mercenariesBeingTrained.size() - cnt);
}

int Gym::useCostInEnergySingle() const noexcept
{
    return currentLevelInfo()->perCapitaCostInEnergy;
}

int Gym::useCostInEnergySingleAfterUpgrade() const noexcept
{
    return nextLevelInfo()->perCapitaCostInEnergy;
}

int Gym::amountOfSlots() const noexcept
{
    return m_mercenariesBeingTrained.size();
}

int Gym::amountOfSlotsAfterUpgrade() const noexcept
{
    return nextLevelInfo()->amountOfSlots;
}

QPair < Mercenary *, unsigned> Gym::slot(int index) noexcept
{
    return m_mercenariesBeingTrained.value(index,{nullptr,0});
}

QString Gym::mercenaryNameInSlot(unsigned index) const noexcept
{
    if (index < m_mercenariesBeingTrained.size() && m_mercenariesBeingTrained[index].first != nullptr)
        return m_mercenariesBeingTrained[index].first->name();
    return "";
}

QString Gym::mercenaryProfessionInSlot(unsigned index) const noexcept
{
    if (index < m_mercenariesBeingTrained.size() && m_mercenariesBeingTrained[index].first != nullptr)
        return m_mercenariesBeingTrained[index].first->professionString();
    return "";
}

void Gym::placeMercenaryInSlot(unsigned slotIndex, const QString &mercenaryName) noexcept
{
    if (slotIndex >= m_mercenariesBeingTrained.size())
        return;

    if (m_mercenariesBeingTrained[slotIndex].first != nullptr)
        emptySlot(slotIndex);

    int pos = base()->mercenaries()->mercenaries()->findMercenary(mercenaryName);
    if (pos==-1)
        return;

    if (base()->mercenaries()->mercenaries()->getMercenary(pos)->currentActivity() != MercenaryEnums::CA_Idle)
        return;

    m_mercenariesBeingTrained[slotIndex].first = base()->mercenaries()->mercenaries()->getMercenary(pos);
    m_mercenariesBeingTrained[slotIndex].first->setCurrentActivity(MercenaryEnums::CA_InGym);
    m_mercenariesBeingTrained[slotIndex].second = duration();
}

void Gym::emptySlot(unsigned slotIndex) noexcept
{
    if (slotIndex >= m_mercenariesBeingTrained.size())
        return;

    if (m_mercenariesBeingTrained[slotIndex].first == nullptr)
        return;

    m_mercenariesBeingTrained[slotIndex].first->setCurrentActivity(MercenaryEnums::CA_Idle);
    m_mercenariesBeingTrained[slotIndex].first = nullptr;
    m_mercenariesBeingTrained[slotIndex].second = 0;
}

void Gym::removeMercenary(const QString &name) noexcept
{
    for (int i=0;i < m_mercenariesBeingTrained.size();++i)
        if (m_mercenariesBeingTrained[i].first != nullptr && m_mercenariesBeingTrained[i].first->name() == name)
        {
            m_mercenariesBeingTrained[i].first->setCurrentActivity(MercenaryEnums::CA_Idle);
            m_mercenariesBeingTrained[i].first = nullptr;
            m_mercenariesBeingTrained[i].second = 0;
            break;
        }
}

int Gym::proficiencyBonus() const noexcept
{
    return currentLevelInfo()->proficiencyBonus;
}

int Gym::proficiencyBonusAfterUpgrade() const noexcept
{
    return nextLevelInfo()->proficiencyBonus;
}

int Gym::duration() const noexcept
{
    return currentLevelInfo()->duration;
}

int Gym::durationAfterUpgrade() const noexcept
{
    return nextLevelInfo()->duration;
}

void Gym::trainMercenaries() noexcept
{
    for (int i=0;i < m_mercenariesBeingTrained.size();++i)
        if (m_mercenariesBeingTrained[i].first != nullptr)
        {
            if (m_mercenariesBeingTrained[i].second > 0 && base()->resources()->canDecreaseEnergyAmount(currentLevelInfo()->perCapitaCostInEnergy))
            {
                base()->resources()->decreaseEnergyAmount(currentLevelInfo()->perCapitaCostInEnergy);

                --m_mercenariesBeingTrained[i].second;
            }
            else if (m_mercenariesBeingTrained[i].second == 0)
            {
                base()->reports()->addReport(new UnifiedReport(new TrainingCompletionReport(m_mercenariesBeingTrained[i].first->pathToArt(), m_mercenariesBeingTrained[i].first->name(), BuildingEnums::B_Gym, base()->gameClock()->currentTime())));
                m_mercenariesBeingTrained[i].first->trainProficiency();
                m_mercenariesBeingTrained[i].first->setCurrentActivity(MercenaryEnums::CA_Idle);
                m_mercenariesBeingTrained[i].first = nullptr;
                m_mercenariesBeingTrained[i].second = 0;
            }
        }
}

void Gym::setLevelsInfo(const QVector < GymLevelInfo *> &info) noexcept
{
    Building::setLevelsInfo(new AnyBuildingLevelsInfo(info));
}

unsigned Gym::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(base(),BuildingEnums::B_Gym,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

void Gym::registerUpgradeCompletion() noexcept
{
    m_isBeingUpgraded = 0;
    resizeSlotsAfterUpgrade();
}

void Gym::resizeSlotsAfterUpgrade() noexcept
{
    while (m_mercenariesBeingTrained.size() < currentLevelInfo()->amountOfSlots)
        m_mercenariesBeingTrained+={nullptr,0};
    m_mercenariesBeingTrained.resize(currentLevelInfo()->amountOfSlots);//for downgrades
}

int Gym::remainingDaysOfTraining(const QString &mercenaryName) const noexcept
{
    for (int i=0;i < m_mercenariesBeingTrained.size();++i)
        if (m_mercenariesBeingTrained[i].first!=nullptr && m_mercenariesBeingTrained[i].first->name() == mercenaryName)
            return m_mercenariesBeingTrained[i].second;
    return -1;
}

GymLevelInfo *Gym::currentLevelInfo() const noexcept
{
    return Building::currentLevelInfo<GymLevelInfo > ();
}

GymLevelInfo *Gym::nextLevelInfo() const noexcept
{
    return Building::nextLevelInfo<GymLevelInfo > ();
}

void Gym::setSlot(unsigned index, Mercenary *mercenary, unsigned duration) noexcept
{
    if (index < m_mercenariesBeingTrained.size())
    {
        m_mercenariesBeingTrained[index].first = mercenary;
        m_mercenariesBeingTrained[index].second = duration;
    }
}
