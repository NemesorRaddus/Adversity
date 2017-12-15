#include "bar.h"

#include "base/base.h"
#include "base/managers/mercenariesmanager.h"
#include "base/managers/resourcesmanager.h"
#include "clock/gameclock.h"
#include "clock/timer_alarms/buildingupgrade.h"
#include "mercenaries/mercenariescontainer.h"

Bar::Bar(Base *base, unsigned level, const AnyBuildingLevelsInfo *levelsInfo) noexcept
    : Building(BuildingEnums::B_Bar, base, level, levelsInfo)
{
    m_mercenariesBeingDestressed.fill(nullptr, currentLevelInfo()->amountOfSlots);
}

int Bar::useCostInEnergy() const noexcept
{
    return currentLevelInfo()->perCapitaCostInEnergy * (m_mercenariesBeingDestressed.size() - m_mercenariesBeingDestressed.count(nullptr));
}

int Bar::useCostInEnergySingle() const noexcept
{
    return currentLevelInfo()->perCapitaCostInEnergy;
}

int Bar::useCostInEnergySingleAfterUpgrade() const noexcept
{
    return nextLevelInfo()->perCapitaCostInEnergy;
}

int Bar::amountOfSlots() const noexcept
{
    return m_mercenariesBeingDestressed.size();
}

int Bar::amountOfSlotsAfterUpgrade() const noexcept
{
    return nextLevelInfo()->amountOfSlots;
}

Mercenary *Bar::slot(int index) noexcept
{
    return m_mercenariesBeingDestressed.value(index,nullptr);
}

QString Bar::mercenaryNameInSlot(unsigned index) const noexcept
{
    if (index < m_mercenariesBeingDestressed.size() && m_mercenariesBeingDestressed[index]!=nullptr)
        return m_mercenariesBeingDestressed[index]->name();
    return "";
}

QString Bar::mercenaryProfessionInSlot(unsigned index) const noexcept
{
    if (index < m_mercenariesBeingDestressed.size() && m_mercenariesBeingDestressed[index]!=nullptr)
        return m_mercenariesBeingDestressed[index]->professionString();
    return "";
}

void Bar::placeMercenaryInSlot(unsigned slotIndex, const QString &mercenaryName) noexcept
{
    if (slotIndex>=m_mercenariesBeingDestressed.size())
        return;

    if (m_mercenariesBeingDestressed[slotIndex]!=nullptr)
        emptySlot(slotIndex);

    int pos = base()->mercenaries()->mercenaries()->findMercenary(mercenaryName);
    if (pos==-1)
        return;

    if (base()->mercenaries()->mercenaries()->getMercenary(pos)->currentActivity() != MercenaryEnums::CA_Idle)
        return;

    m_mercenariesBeingDestressed[slotIndex]=base()->mercenaries()->mercenaries()->getMercenary(pos);
    m_mercenariesBeingDestressed[slotIndex]->setCurrentActivity(MercenaryEnums::CA_InBar);
    setRecoveryValuesForMercenary(slotIndex);
}

void Bar::emptySlot(unsigned slotIndex) noexcept
{
    if (slotIndex>=m_mercenariesBeingDestressed.size())
        return;

    if (m_mercenariesBeingDestressed[slotIndex]==nullptr)
        return;

    m_mercenariesBeingDestressed[slotIndex]->setCurrentActivity(MercenaryEnums::CA_Idle);
    m_mercenariesBeingDestressed[slotIndex]->setDailyStressRecoveryBuildingBonus(0);
    m_mercenariesBeingDestressed[slotIndex]=nullptr;
}

void Bar::removeMercenary(const QString &name) noexcept
{
    for (int i=0;i<m_mercenariesBeingDestressed.size();++i)
        if (m_mercenariesBeingDestressed[i]!=nullptr && m_mercenariesBeingDestressed[i]->name() == name)
        {
            m_mercenariesBeingDestressed[i]->setCurrentActivity(MercenaryEnums::CA_Idle);
            m_mercenariesBeingDestressed[i]=nullptr;
            break;
        }
}

int Bar::activeStressRelief() const noexcept
{
    return currentLevelInfo()->stressReductionForActive;
}

int Bar::activeStressReliefAfterUpgrade() const noexcept
{
    return nextLevelInfo()->stressReductionForActive;
}

int Bar::convivialStressRelief() const noexcept
{
    return currentLevelInfo()->stressReductionForConvivial;
}

int Bar::convivialStressReliefAfterUpgrade() const noexcept
{
    return nextLevelInfo()->stressReductionForConvivial;
}

int Bar::recluseStressRelief() const noexcept
{
    return currentLevelInfo()->stressReductionForRecluse;
}

int Bar::recluseStressReliefAfterUpgrade() const noexcept
{
    return nextLevelInfo()->stressReductionForRecluse;
}

int Bar::religiousStressRelief() const noexcept
{
    return currentLevelInfo()->stressReductionForReligious;
}

int Bar::religiousStressReliefAfterUpgrade() const noexcept
{
    return nextLevelInfo()->stressReductionForReligious;
}

void Bar::destressMercenaries() noexcept
{
    for (int i=0;i<m_mercenariesBeingDestressed.size();++i)
        if (m_mercenariesBeingDestressed[i]!=nullptr && base()->resources()->canDecreaseEnergyAmount(currentLevelInfo()->perCapitaCostInEnergy))
        {
            base()->resources()->decreaseEnergyAmount(currentLevelInfo()->perCapitaCostInEnergy);

            if (m_mercenariesBeingDestressed[i]->nature() == MercenaryEnums::N_Active)
                m_mercenariesBeingDestressed[i]->decreaseStress(currentLevelInfo()->stressReductionForActive);
            else if (m_mercenariesBeingDestressed[i]->nature() == MercenaryEnums::N_Convivial)
                m_mercenariesBeingDestressed[i]->decreaseStress(currentLevelInfo()->stressReductionForConvivial);
            else if (m_mercenariesBeingDestressed[i]->nature() == MercenaryEnums::N_Recluse)
                m_mercenariesBeingDestressed[i]->decreaseStress(currentLevelInfo()->stressReductionForRecluse);
            else if (m_mercenariesBeingDestressed[i]->nature() == MercenaryEnums::N_Religious)
                m_mercenariesBeingDestressed[i]->decreaseStress(currentLevelInfo()->stressReductionForReligious);
        }
}

void Bar::setRecoveryValuesForMercenary(unsigned index) noexcept
{
    switch (m_mercenariesBeingDestressed[index]->nature())
    {
    case MercenaryEnums::N_Active:
        m_mercenariesBeingDestressed[index]->setDailyStressRecoveryBuildingBonus(activeStressRelief());
        break;
    case MercenaryEnums::N_Convivial:
        m_mercenariesBeingDestressed[index]->setDailyStressRecoveryBuildingBonus(convivialStressRelief());
        break;
    case MercenaryEnums::N_Recluse:
        m_mercenariesBeingDestressed[index]->setDailyStressRecoveryBuildingBonus(recluseStressRelief());
        break;
    case MercenaryEnums::N_Religious:
        m_mercenariesBeingDestressed[index]->setDailyStressRecoveryBuildingBonus(religiousStressRelief());
        break;
    }
}

void Bar::setRecoveryValuesForMercenaries() noexcept
{
    for (int i=0;i<m_mercenariesBeingDestressed.size();++i)
        if (m_mercenariesBeingDestressed[i]!=nullptr)
            setRecoveryValuesForMercenary(i);
}

void Bar::setLevelsInfo(const QVector<BarLevelInfo *> &info) noexcept
{
    Building::setLevelsInfo(new AnyBuildingLevelsInfo(info));
}

unsigned Bar::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(base(),BuildingEnums::B_Bar,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

void Bar::registerUpgradeCompletion() noexcept
{
    m_isBeingUpgraded=0;
    resizeSlotsAfterUpgrade();
}

void Bar::resizeSlotsAfterUpgrade() noexcept
{
    while (m_mercenariesBeingDestressed.size() < currentLevelInfo()->amountOfSlots)
        m_mercenariesBeingDestressed.push_back(nullptr);
    m_mercenariesBeingDestressed.resize(currentLevelInfo()->amountOfSlots);//for downgrades
    setRecoveryValuesForMercenaries();
}

BarLevelInfo *Bar::currentLevelInfo() const noexcept
{
    return Building::currentLevelInfo<BarLevelInfo>();
}

BarLevelInfo *Bar::nextLevelInfo() const noexcept
{
    return Building::nextLevelInfo<BarLevelInfo>();
}

void Bar::setSlot(unsigned index, Mercenary *mercenary) noexcept
{
    if (index<m_mercenariesBeingDestressed.size())
        m_mercenariesBeingDestressed[index]=mercenary;
}
