#include "shrine.h"

#include "base/base.h"
#include "clock/gameclock.h"
#include "clock/timer_alarms/buildingupgrade.h"

Shrine::Shrine(Base *base, unsigned level, const QVector<ShrineLevelInfo> &levelsInfo) noexcept
    : Building(BuildingEnums::B_Shrine, base, level), m_levelsInfo(levelsInfo)
{
    m_mercenariesBeingDestressed.fill(nullptr,levelsInfo.value(level).amountOfSlots);
}

QString Shrine::mercenaryNameInSlot(unsigned index) const noexcept
{
    if (index < m_mercenariesBeingDestressed.size() && m_mercenariesBeingDestressed[index]!=nullptr)
        return m_mercenariesBeingDestressed[index]->name();
    return "";
}

QString Shrine::mercenaryProfessionInSlot(unsigned index) const noexcept
{
    if (index < m_mercenariesBeingDestressed.size() && m_mercenariesBeingDestressed[index]!=nullptr)
        return m_mercenariesBeingDestressed[index]->professionString();
    return "";
}

void Shrine::placeMercenaryInSlot(unsigned slotIndex, const QString &mercenaryName) noexcept
{
    if (slotIndex>=m_mercenariesBeingDestressed.size())
        return;

    if (m_mercenariesBeingDestressed[slotIndex]!=nullptr)
        emptySlot(slotIndex);

    int pos = base()->mercenaries()->findMercenary(mercenaryName);
    if (pos==-1)
        return;

    if (base()->mercenaries()->getMercenary(pos)->currentActivity() != MercenaryEnums::CA_Idle)
        return;

    m_mercenariesBeingDestressed[slotIndex]=base()->mercenaries()->getMercenary(pos);
    m_mercenariesBeingDestressed[slotIndex]->setCurrentActivity(MercenaryEnums::CA_InShrine);
    setRecoveryValuesForMercenary(slotIndex);
}

void Shrine::emptySlot(unsigned slotIndex) noexcept
{
    if (slotIndex>=m_mercenariesBeingDestressed.size())
        return;

    if (m_mercenariesBeingDestressed[slotIndex]==nullptr)
        return;

    m_mercenariesBeingDestressed[slotIndex]->setCurrentActivity(MercenaryEnums::CA_Idle);
    m_mercenariesBeingDestressed[slotIndex]->setDailyStressRecoveryBuildingBonus(0);
    m_mercenariesBeingDestressed[slotIndex]=nullptr;
}

void Shrine::removeMercenary(const QString &name) noexcept
{
    for (int i=0;i<m_mercenariesBeingDestressed.size();++i)
        if (m_mercenariesBeingDestressed[i]!=nullptr && m_mercenariesBeingDestressed[i]->name() == name)
        {
            m_mercenariesBeingDestressed[i]->setCurrentActivity(MercenaryEnums::CA_Idle);
            m_mercenariesBeingDestressed[i]=nullptr;
            break;
        }
}

void Shrine::destressMercenaries() noexcept
{
    for (int i=0;i<m_mercenariesBeingDestressed.size();++i)
        if (m_mercenariesBeingDestressed[i]!=nullptr && base()->canDecreaseEnergyAmount(m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy))
        {
            base()->decreaseEnergyAmount(m_levelsInfo.value(currentLevel()).perCapitaCostInEnergy);

            if (m_mercenariesBeingDestressed[i]->nature() == MercenaryEnums::N_Active)
                m_mercenariesBeingDestressed[i]->decreaseStress(m_levelsInfo.value(currentLevel()).stressReductionForActive);
            else if (m_mercenariesBeingDestressed[i]->nature() == MercenaryEnums::N_Convivial)
                m_mercenariesBeingDestressed[i]->decreaseStress(m_levelsInfo.value(currentLevel()).stressReductionForConvivial);
            else if (m_mercenariesBeingDestressed[i]->nature() == MercenaryEnums::N_Recluse)
                m_mercenariesBeingDestressed[i]->decreaseStress(m_levelsInfo.value(currentLevel()).stressReductionForRecluse);
            else if (m_mercenariesBeingDestressed[i]->nature() == MercenaryEnums::N_Religious)
                m_mercenariesBeingDestressed[i]->decreaseStress(m_levelsInfo.value(currentLevel()).stressReductionForReligious);
        }
}

void Shrine::setRecoveryValuesForMercenary(unsigned index) noexcept
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

void Shrine::setRecoveryValuesForMercenaries() noexcept
{
    for (int i=0;i<m_mercenariesBeingDestressed.size();++i)
        if (m_mercenariesBeingDestressed[i]!=nullptr)
            setRecoveryValuesForMercenary(i);
}

void Shrine::setLevelsInfo(const QVector<ShrineLevelInfo> &info) noexcept
{
    m_levelsInfo=info;
}

unsigned Shrine::upgradeTimeRemaining() noexcept
{
    BuildingUpgradeTimerAlarm *buta = new BuildingUpgradeTimerAlarm(base(),BuildingEnums::B_Shrine,currentLevel()+1);
    unsigned r = base()->gameClock()->checkDaysToTimeoutOfAlarm(buta);
    delete buta;
    return r;
}

void Shrine::resizeSlotsAfterUpgrade() noexcept
{
    while (m_mercenariesBeingDestressed.size() < m_levelsInfo.value(currentLevel()).amountOfSlots)
        m_mercenariesBeingDestressed.push_back(nullptr);
    m_mercenariesBeingDestressed.resize(m_levelsInfo.value(currentLevel()).amountOfSlots);//for downgrades
    setRecoveryValuesForMercenaries();
}
