#include "trainingground.h"

#include "base/base.h"
#include "clock/gameclock.h"
#include "clock/timer_alarms/buildingupgrade.h"
#include "mercenaries/mercenary.h"
#include "missions/events/event.h"
#include "reports/basereports.h"
#include "reports/unifiedreport.h"

TrainingGround::TrainingGround(Base *base, unsigned level, const QVector<TrainingGroundLevelInfo> &levelsInfo) noexcept
    : Building(BuildingEnums::B_TrainingGround, base, level), m_levelsInfo(levelsInfo)
{
    m_mercenariesBeingTrained.fill({nullptr,0},levelsInfo.value(level).amountOfSlots);
}

QString TrainingGround::mercenaryNameInSlot(unsigned index) const noexcept
{
    if (index < m_mercenariesBeingTrained.size() && m_mercenariesBeingTrained[index].first!=nullptr)
        return m_mercenariesBeingTrained[index].first->name();
    return "";
}

QString TrainingGround::mercenaryProfessionInSlot(unsigned index) const noexcept
{
    if (index < m_mercenariesBeingTrained.size() && m_mercenariesBeingTrained[index].first!=nullptr)
        return m_mercenariesBeingTrained[index].first->professionString();
    return "";
}

void TrainingGround::placeMercenaryInSlot(unsigned slotIndex, const QString &mercenaryName) noexcept
{
    if (slotIndex>=m_mercenariesBeingTrained.size())
        return;

    if (m_mercenariesBeingTrained[slotIndex].first!=nullptr)
        emptySlot(slotIndex);

    int pos = base()->mercenaries()->findMercenary(mercenaryName);
    if (pos==-1)
        return;

    if (base()->mercenaries()->getMercenary(pos)->currentActivity() != MercenaryEnums::CA_Idle)
        return;

    m_mercenariesBeingTrained[slotIndex].first=base()->mercenaries()->getMercenary(pos);
    m_mercenariesBeingTrained[slotIndex].first->setCurrentActivity(MercenaryEnums::CA_OnTrainingGround);
    m_mercenariesBeingTrained[slotIndex].second=duration();
}

void TrainingGround::emptySlot(unsigned slotIndex) noexcept
{
    if (slotIndex>=m_mercenariesBeingTrained.size())
        return;

    if (m_mercenariesBeingTrained[slotIndex].first==nullptr)
        return;

    m_mercenariesBeingTrained[slotIndex].first->setCurrentActivity(MercenaryEnums::CA_Idle);
    m_mercenariesBeingTrained[slotIndex].first=nullptr;
    m_mercenariesBeingTrained[slotIndex].second=0;
}

void TrainingGround::removeMercenary(const QString &name) noexcept
{
    for (int i=0;i<m_mercenariesBeingTrained.size();++i)
        if (m_mercenariesBeingTrained[i].first!=nullptr && m_mercenariesBeingTrained[i].first->name() == name)
        {
            m_mercenariesBeingTrained[i].first->setCurrentActivity(MercenaryEnums::CA_Idle);
            m_mercenariesBeingTrained[i].first=nullptr;
            m_mercenariesBeingTrained[i].second=0;
            break;
        }
}

void TrainingGround::trainMercenaries() noexcept
{
    for (int i=0;i<m_mercenariesBeingTrained.size();++i)
        if (m_mercenariesBeingTrained[i].first!=nullptr)
        {
            if (m_mercenariesBeingTrained[i].second>0 && base()->canDecreaseEnergyAmount(m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy))
            {
                base()->decreaseEnergyAmount(m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy);

                --m_mercenariesBeingTrained[i].second;
            }
            else if (m_mercenariesBeingTrained[i].second==0)
            {
                base()->addReport(new UnifiedReport(new TrainingCompletionReport(m_mercenariesBeingTrained[i].first->pathToArt(), m_mercenariesBeingTrained[i].first->name(), BuildingEnums::B_TrainingGround, base()->gameClock()->currentTime())));
                m_mercenariesBeingTrained[i].first->trainCombatEffectiveness();
                m_mercenariesBeingTrained[i].first->setCurrentActivity(MercenaryEnums::CA_Idle);
                m_mercenariesBeingTrained[i].first=nullptr;
                m_mercenariesBeingTrained[i].second=0;
            }
        }
}

void TrainingGround::setLevelsInfo(const QVector<TrainingGroundLevelInfo> &info) noexcept
{
    m_levelsInfo=info;
}

unsigned TrainingGround::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(base(),BuildingEnums::B_TrainingGround,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

int TrainingGround::remainingDaysOfTraining(const QString &mercenaryName) const noexcept
{
    for (int i=0;i<m_mercenariesBeingTrained.size();++i)
        if (m_mercenariesBeingTrained[i].first!=nullptr && m_mercenariesBeingTrained[i].first->name()==mercenaryName)
            return m_mercenariesBeingTrained[i].second;
    return -1;
}
