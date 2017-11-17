#include "laboratory.h"

#include "base/base.h"
#include "clock/gameclock.h"
#include "clock/timer_alarms/buildingupgrade.h"
#include "mercenaries/mercenariescontainer.h"
#include "missions/events/event.h"
#include "reports/basereports.h"
#include "reports/unifiedreport.h"

Laboratory::Laboratory(Base *base, unsigned level, const AnyBuildingLevelsInfo *levelsInfo) noexcept
    : Building(BuildingEnums::B_Laboratory, base, level, levelsInfo)
{
    m_mercenariesBeingTrained.fill({nullptr,0}, currentLevelInfo()->amountOfSlots);
}

int Laboratory::useCostInEnergy() const noexcept
{
    int cnt=0;
    for (int i=0;i<m_mercenariesBeingTrained.size();++i)
        if (m_mercenariesBeingTrained[i].first==nullptr)
            ++cnt;
    return currentLevelInfo()->perCapitaCostInEnergy * (m_mercenariesBeingTrained.size() - cnt);
}

int Laboratory::useCostInEnergySingle() const noexcept
{
    return currentLevelInfo()->perCapitaCostInEnergy;
}

int Laboratory::useCostInEnergySingleAfterUpgrade() const noexcept
{
    return nextLevelInfo()->perCapitaCostInEnergy;
}

int Laboratory::amountOfSlots() const noexcept
{
    return m_mercenariesBeingTrained.size();
}

int Laboratory::amountOfSlotsAfterUpgrade() const noexcept
{
    return nextLevelInfo()->amountOfSlots;
}

QPair<Mercenary *, unsigned> Laboratory::slot(int index) noexcept
{
    return m_mercenariesBeingTrained.value(index,{nullptr,0});
}

QString Laboratory::mercenaryNameInSlot(unsigned index) const noexcept
{
    if (index < m_mercenariesBeingTrained.size() && m_mercenariesBeingTrained[index].first!=nullptr)
        return m_mercenariesBeingTrained[index].first->name();
    return "";
}

QString Laboratory::mercenaryProfessionInSlot(unsigned index) const noexcept
{
    if (index < m_mercenariesBeingTrained.size() && m_mercenariesBeingTrained[index].first!=nullptr)
        return m_mercenariesBeingTrained[index].first->professionString();
    return "";
}

void Laboratory::placeMercenaryInSlot(unsigned slotIndex, const QString &mercenaryName) noexcept
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
    m_mercenariesBeingTrained[slotIndex].first->setCurrentActivity(MercenaryEnums::CA_InLaboratory);
    m_mercenariesBeingTrained[slotIndex].second=duration();
}

void Laboratory::emptySlot(unsigned slotIndex) noexcept
{
    if (slotIndex>=m_mercenariesBeingTrained.size())
        return;

    if (m_mercenariesBeingTrained[slotIndex].first==nullptr)
        return;

    m_mercenariesBeingTrained[slotIndex].first->setCurrentActivity(MercenaryEnums::CA_Idle);
    m_mercenariesBeingTrained[slotIndex].first=nullptr;
    m_mercenariesBeingTrained[slotIndex].second=0;
}

void Laboratory::removeMercenary(const QString &name) noexcept
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

int Laboratory::clevernessBonus() const noexcept
{
    return currentLevelInfo()->clevernessBonus;
}

int Laboratory::clevernessBonusAfterUpgrade() const noexcept
{
    return nextLevelInfo()->clevernessBonus;
}

int Laboratory::duration() const noexcept
{
    return currentLevelInfo()->duration;
}

int Laboratory::durationAfterUpgrade() const noexcept
{
    return nextLevelInfo()->duration;
}

void Laboratory::trainMercenaries() noexcept
{
    for (int i=0;i<m_mercenariesBeingTrained.size();++i)
        if (m_mercenariesBeingTrained[i].first!=nullptr)
        {
            if (m_mercenariesBeingTrained[i].second>0 && base()->canDecreaseEnergyAmount(currentLevelInfo()->perCapitaCostInEnergy))
            {
                base()->decreaseEnergyAmount(currentLevelInfo()->perCapitaCostInEnergy);

                --m_mercenariesBeingTrained[i].second;
            }
            else if (m_mercenariesBeingTrained[i].second==0)
            {
                base()->addReport(new UnifiedReport(new TrainingCompletionReport(m_mercenariesBeingTrained[i].first->pathToArt(), m_mercenariesBeingTrained[i].first->name(), BuildingEnums::B_Laboratory, base()->gameClock()->currentTime())));
                m_mercenariesBeingTrained[i].first->trainCleverness();
                m_mercenariesBeingTrained[i].first->setCurrentActivity(MercenaryEnums::CA_Idle);
                m_mercenariesBeingTrained[i].first=nullptr;
                m_mercenariesBeingTrained[i].second=0;
            }
        }
}

void Laboratory::setLevelsInfo(const QVector<LaboratoryLevelInfo *> &info) noexcept
{
    Building::setLevelsInfo(new AnyBuildingLevelsInfo(info));
}

unsigned Laboratory::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(base(),BuildingEnums::B_Laboratory,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

void Laboratory::registerUpgradeCompletion() noexcept
{
    m_isBeingUpgraded=0;
    resizeSlotsAfterUpgrade();
}

void Laboratory::resizeSlotsAfterUpgrade() noexcept
{
    while (m_mercenariesBeingTrained.size() < currentLevelInfo()->amountOfSlots)
        m_mercenariesBeingTrained+={nullptr,0};
    m_mercenariesBeingTrained.resize(currentLevelInfo()->amountOfSlots);//for downgrades
}

int Laboratory::remainingDaysOfTraining(const QString &mercenaryName) const noexcept
{
    for (int i=0;i<m_mercenariesBeingTrained.size();++i)
        if (m_mercenariesBeingTrained[i].first!=nullptr && m_mercenariesBeingTrained[i].first->name()==mercenaryName)
            return m_mercenariesBeingTrained[i].second;
    return -1;
}

LaboratoryLevelInfo *Laboratory::currentLevelInfo() const noexcept
{
    return Building::currentLevelInfo<LaboratoryLevelInfo>();
}

LaboratoryLevelInfo *Laboratory::nextLevelInfo() const noexcept
{
    return Building::nextLevelInfo<LaboratoryLevelInfo>();
}

void Laboratory::setSlot(unsigned index, Mercenary *mercenary, unsigned duration) noexcept
{
    if (index<m_mercenariesBeingTrained.size())
    {
        m_mercenariesBeingTrained[index].first=mercenary;
        m_mercenariesBeingTrained[index].second=duration;
    }
}
