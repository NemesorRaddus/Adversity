#include "seclusion.h"

#include "base/base.h"
#include "base/managers/mercenariesmanager.h"
#include "base/managers/resourcesmanager.h"
#include "clock/gameclock.h"
#include "clock/timer_alarms/buildingupgrade.h"
#include "mercenaries/mercenariescontainer.h"

Seclusion::Seclusion(Base *base, unsigned level, const AnyBuildingLevelsInfo *levelsInfo) noexcept
    : Building(BuildingEnums::B_Seclusion, base, level, levelsInfo)
{
    m_mercenariesBeingDestressed.fill(nullptr, currentLevelInfo()->amountOfSlots);
}

int Seclusion::useCostInEnergy() const noexcept
{
    return currentLevelInfo()->perCapitaCostInEnergy * (m_mercenariesBeingDestressed.size() - m_mercenariesBeingDestressed.count(nullptr));
}

int Seclusion::useCostInEnergySingle() const noexcept
{
    return currentLevelInfo()->perCapitaCostInEnergy;
}

int Seclusion::useCostInEnergySingleAfterUpgrade() const noexcept
{
    return nextLevelInfo()->perCapitaCostInEnergy;
}

int Seclusion::amountOfSlots() const noexcept
{
    return m_mercenariesBeingDestressed.size();
}

int Seclusion::amountOfSlotsAfterUpgrade() const noexcept
{
    return nextLevelInfo()->amountOfSlots;
}

Mercenary *Seclusion::slot(int index) noexcept
{
    return m_mercenariesBeingDestressed.value(index,nullptr);
}

QString Seclusion::mercenaryNameInSlot(unsigned index) const noexcept
{
    if (index < m_mercenariesBeingDestressed.size() && m_mercenariesBeingDestressed[index]!=nullptr)
        return m_mercenariesBeingDestressed[index]->name();
    return "";
}

QString Seclusion::mercenaryProfessionInSlot(unsigned index) const noexcept
{
    if (index < m_mercenariesBeingDestressed.size() && m_mercenariesBeingDestressed[index]!=nullptr)
        return m_mercenariesBeingDestressed[index]->professionString();
    return "";
}

void Seclusion::placeMercenaryInSlot(unsigned slotIndex, const QString &mercenaryName) noexcept
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
    m_mercenariesBeingDestressed[slotIndex]->setCurrentActivity(MercenaryEnums::CA_InSeclusion);
    setRecoveryValuesForMercenary(slotIndex);
}

void Seclusion::emptySlot(unsigned slotIndex) noexcept
{
    if (slotIndex>=m_mercenariesBeingDestressed.size())
        return;

    if (m_mercenariesBeingDestressed[slotIndex]==nullptr)
        return;

    m_mercenariesBeingDestressed[slotIndex]->setCurrentActivity(MercenaryEnums::CA_Idle);
    m_mercenariesBeingDestressed[slotIndex]->setDailyStressRecoveryBuildingBonus(0);
    m_mercenariesBeingDestressed[slotIndex]=nullptr;
}

void Seclusion::removeMercenary(const QString &name) noexcept
{
    for (int i=0;i<m_mercenariesBeingDestressed.size();++i)
        if (m_mercenariesBeingDestressed[i]!=nullptr && m_mercenariesBeingDestressed[i]->name() == name)
        {
            m_mercenariesBeingDestressed[i]->setCurrentActivity(MercenaryEnums::CA_Idle);
            m_mercenariesBeingDestressed[i]=nullptr;
            break;
        }
}

int Seclusion::activeStressRelief() const noexcept
{
    return currentLevelInfo()->stressReductionForActive;
}

int Seclusion::activeStressReliefAfterUpgrade() const noexcept
{
    return nextLevelInfo()->stressReductionForActive;
}

int Seclusion::convivialStressRelief() const noexcept
{
    return currentLevelInfo()->stressReductionForConvivial;
}

int Seclusion::convivialStressReliefAfterUpgrade() const noexcept
{
    return nextLevelInfo()->stressReductionForConvivial;
}

int Seclusion::recluseStressRelief() const noexcept
{
    return currentLevelInfo()->stressReductionForRecluse;
}

int Seclusion::recluseStressReliefAfterUpgrade() const noexcept
{
    return nextLevelInfo()->stressReductionForRecluse;
}

int Seclusion::religiousStressRelief() const noexcept
{
    return currentLevelInfo()->stressReductionForReligious;
}

int Seclusion::religiousStressReliefAfterUpgrade() const noexcept
{
    return nextLevelInfo()->stressReductionForReligious;
}

void Seclusion::destressMercenaries() noexcept
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

void Seclusion::setRecoveryValuesForMercenary(unsigned index) noexcept
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

void Seclusion::setRecoveryValuesForMercenaries() noexcept
{
    for (int i=0;i<m_mercenariesBeingDestressed.size();++i)
        if (m_mercenariesBeingDestressed[i]!=nullptr)
            setRecoveryValuesForMercenary(i);
}

void Seclusion::setLevelsInfo(const QVector<SeclusionLevelInfo *> &info) noexcept
{
    Building::setLevelsInfo(new AnyBuildingLevelsInfo(info));
}

unsigned Seclusion::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(base(),BuildingEnums::B_Seclusion,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

void Seclusion::registerUpgradeCompletion() noexcept
{
    m_isBeingUpgraded=0;
    resizeSlotsAfterUpgrade();
}

void Seclusion::resizeSlotsAfterUpgrade() noexcept
{
    while (m_mercenariesBeingDestressed.size() < currentLevelInfo()->amountOfSlots)
        m_mercenariesBeingDestressed.push_back(nullptr);
    m_mercenariesBeingDestressed.resize(currentLevelInfo()->amountOfSlots);//for downgrades
    setRecoveryValuesForMercenaries();
}

SeclusionLevelInfo *Seclusion::currentLevelInfo() const noexcept
{
    return Building::currentLevelInfo<SeclusionLevelInfo>();
}

SeclusionLevelInfo *Seclusion::nextLevelInfo() const noexcept
{
    return Building::nextLevelInfo<SeclusionLevelInfo>();
}

void Seclusion::setSlot(unsigned index, Mercenary *mercenary) noexcept
{
    if (index<m_mercenariesBeingDestressed.size())
        m_mercenariesBeingDestressed[index]=mercenary;
}
